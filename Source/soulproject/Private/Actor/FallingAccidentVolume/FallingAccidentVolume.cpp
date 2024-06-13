#include "Actor/FallingAccidentVolume/FallingAccidentVolume.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Components/BoxComponent.h"

// Sets default values
AFallingAccidentVolume::AFallingAccidentVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	FallAccidentArea = CreateDefaultSubobject<UBoxComponent>(TEXT("FALLING_AREA"));
	FallAccidentArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AFallingAccidentVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallingAccidentVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFallingAccidentVolume::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)

{
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(OtherActor);
	if (!IsValid(gameCharacter)) return;

	AGamePlayerController* playerController =
		Cast<AGamePlayerController>(gameCharacter->GetController());

	if (!IsValid(playerController)) return;


	// ³«»ç Ã³¸®
	playerController->SetCurrentHp(0.0f);



}


