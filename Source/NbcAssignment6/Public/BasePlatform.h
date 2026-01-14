#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.generated.h"

class UShuttleMoveComponent;
class URotateComponent;

UCLASS()
class NBCASSIGNMENT6_API ABasePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePlatform();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UShuttleMoveComponent* ShuttleMoveComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URotateComponent* RotateComponent;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
};
