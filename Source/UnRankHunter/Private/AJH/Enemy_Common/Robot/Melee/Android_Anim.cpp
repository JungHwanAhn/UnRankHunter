#include "Android_Anim.h"
#include "Android.h"
#include "KismetAnimationLibrary.h"

UAndroid_Anim::UAndroid_Anim()
{
	
}

void UAndroid_Anim::Attack(FString pattern)
{

}

void UAndroid_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	Android = Cast<AAndroid>(Owner);
}

void UAndroid_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Android) {
		velocity = Android->GetVelocity();
		speed = velocity.Size2D();

		androidRotation = Android->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, androidRotation);
	}
}
