#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollisionController.generated.h"

UINTERFACE(MinimalAPI)
class UCollisionController : public UInterface
{
	GENERATED_BODY()
};

class UNRANKHUNTER_API ICollisionController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionController")
	void OnCollisionStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionController")
	void OnCollisionEnd();
};
