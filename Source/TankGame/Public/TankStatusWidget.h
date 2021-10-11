#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TankStatusWidget.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankStatusWidget : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OrientToCamera();
};
