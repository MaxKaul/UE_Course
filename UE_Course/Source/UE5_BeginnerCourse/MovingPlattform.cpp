// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlattform.h"

#include "SplineClass.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "MyButton.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMovingPlattform::AMovingPlattform()
{

}

void AMovingPlattform::OnPlayerInteraction_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
                                                          UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult)
{
	Super::OnPlayerInteraction_OnOverlapBegin(_overlapComp, _otherActor, _otherComp, _otherBodyIdx, _bFromSweep,
		_sweepResult);

	if (AUE5_BeginnerCourseCharacter* otherplayer = Cast<AUE5_BeginnerCourseCharacter>(_otherActor))
	{
		if (!_otherComp->ComponentHasTag("PlayerInteractor") && GetConditionsMet())
			OnPlayerInteract();
	}
}

void AMovingPlattform::OnPlayerInteraction_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
	Super::OnPlayerInteraction_OnOverlapEnd(_overlapComp, _otherActor, _otherComp, _otherBodyIdx);

		//if (AUE5_BeginnerCourseCharacter* otherplayer = Cast<AUE5_BeginnerCourseCharacter>(_otherActor))
		//{
		//if (!_otherComp->ComponentHasTag("PlayerInteractor"))
		//	OnPlayerInteract();
		//}
}

void AMovingPlattform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (curveTimeline.IsPlaying())
		curveTimeline.TickTimeline(DeltaSeconds);
}

void AMovingPlattform::BeginPlay()
{
	Super::BeginPlay();

	InitConditions();
}

void AMovingPlattform::OnPlayerInteract()
{
	Super::OnPlayerInteract();

	if(!curveTimeline.IsPlaying())
		BeginTimeline();
}

void AMovingPlattform::InitConditions()
{
	FConditionTableBase* currrow = new FConditionTableBase;

	for(TTuple<FName, unsigned char*> row : combiDataTable->GetRowMap())
	{
		if (reinterpret_cast<FConditionTableBase*>(row.Value)->rowContent == rowContentID)
			currrow = reinterpret_cast<FConditionTableBase*>(row.Value);
	}

	for(TTuple<int, FConditionRowBase> rowcontentmap : currrow->conditionMap)
	{
		if (rowcontentmap.Key == mapContentID)
		{
			activationCondition = rowcontentmap.Value;
			break;
		}
	}

	for (size_t i = 0; i < conditionButtons.Num(); i++)
	{
		conditionButtons[i]->SetButtonOwner(this, i);
	}
}

void AMovingPlattform::ResetConditions()
{
	for (AMyButton* button : conditionButtons)
	{
		button->SetButtonInactive();
	}

	activationCombination_Fill.Empty();
}

void AMovingPlattform::ConditionCallback(bool _status, int _objectID)
{
	if(_status)
	{
		if (!activationCombination_Fill.Contains(_objectID))
			activationCombination_Fill.Add(_objectID);
	}
	else if(!_status)
	{
		if(activationCombination_Fill.Contains(_objectID))
		{
			activationCombination_Fill.Remove(_objectID);
			bConditionMet = false;
		}
	}

	if (activationCombination_Fill.Num() == activationCondition.conditionCombination.Num())
	{
		bool bisvalid = true;

		for (size_t i = 0; i < activationCombination_Fill.Num(); i++)
		{
			if (activationCombination_Fill[i] != activationCondition.conditionCombination[i])
			{
				bisvalid = false;
				break;
			}
		}

		if (!bisvalid)
			ResetConditions();

		bConditionMet = bisvalid;
	}
	else if (activationCombination_Fill.Num() > activationCondition.conditionCombination.Num())
		ResetConditions();
	else if(activationCombination_Fill.Num() > conditionButtons.Num())
		ResetConditions();
}

bool AMovingPlattform::GetConditionsMet()
{
	bool status = false;

	int valids = 0;

	for(AMyButton* button : conditionButtons)
	{
		if (button->WasInteracted())
			valids++;
	}

	if (valids >= conditionButtons.Num())
		status = true;

	return status;
}

void AMovingPlattform::BeginTimeline()
{
	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline"));

	curveTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	curveTimeline.SetPlayRate(1.f / completionTime);
	curveTimeline.SetLooping(false);

	curveTimeline.AddInterpFloat(curveFloat, timelineprogress);

	if(FMath::IsNearlyEqual(lerpDistance, splineClassRef->GetSplineComponent()->GetSplineLength()))
		bHasReachedEnd = true;
	else if (FMath::IsNearlyEqual(lerpDistance, 0))
		bHasReachedEnd = false;

	curveTimeline.PlayFromStart();
}

void AMovingPlattform::TickTimeline(float _alpha)
{
	if(!bHasReachedEnd)
	{
		lerpDistance = UKismetMathLibrary::Lerp(0, splineClassRef->GetSplineComponent()->GetSplineLength(), _alpha);
		SetActorLocation(splineClassRef->GetSplineComponent()->GetLocationAtDistanceAlongSpline(lerpDistance, ESplineCoordinateSpace::World));
	}
	else if(bHasReachedEnd)
	{
		lerpDistance = UKismetMathLibrary::Lerp(splineClassRef->GetSplineComponent()->GetSplineLength(), 0, _alpha);
		SetActorLocation(splineClassRef->GetSplineComponent()->GetLocationAtDistanceAlongSpline(lerpDistance, ESplineCoordinateSpace::World));
	}
}
