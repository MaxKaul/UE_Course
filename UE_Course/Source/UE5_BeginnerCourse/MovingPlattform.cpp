// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlattform.h"

#include "SplineClass.h"
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


}

void AMovingPlattform::OnPlayerInteraction_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
	Super::OnPlayerInteraction_OnOverlapEnd(_overlapComp, _otherActor, _otherComp, _otherBodyIdx);


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
}

void AMovingPlattform::OnPlayerInteract()
{
	Super::OnPlayerInteract();

	if(!curveTimeline.IsPlaying())
		BeginTimeline();
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
