#include "Actor/MyLevelStreamingActor/MyLevelStreamingActor.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyLevelStreamingActor::AMyLevelStreamingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Bounds = CreateDefaultSubobject<USphereComponent>(TEXT("BOUNDS"));
	SetRootComponent(Bounds);
	Bounds->OnComponentBeginOverlap.AddDynamic(this, &AMyLevelStreamingActor::OnBeginOverlap);
	Bounds->OnComponentEndOverlap.AddDynamic(this, &AMyLevelStreamingActor::OnEndOverlap);
}

// Called when the game starts or when spawned
void AMyLevelStreamingActor::BeginPlay()
{
	Super::BeginPlay();


	
}

void AMyLevelStreamingActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 겹친 액터가 GameCharacter 형식이라면
	
	if (OtherActor->IsA<AGameCharacter>())
	{
		FLatentActionInfo info;
		UGameplayStatics::LoadStreamLevel(this, LoadLevelName, true, true, info);
	}
}

void AMyLevelStreamingActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AGameCharacter>())
	{
		FLatentActionInfo info;
		UGameplayStatics::UnloadStreamLevel(this, LoadLevelName, info, true);
	}
}



