#include "Object/CameraShake/AttackCameraShake.h"

UAttackCameraShake::UAttackCameraShake()
{
	bSingleInstance = true;
	OscillationDuration = 0.5f;

	// ¶³¸² °­µµ
	RotOscillation.Pitch.Amplitude = 0.5f;

	// ¶³¸² ¼Óµµ
	RotOscillation.Pitch.Frequency= 10.0f;

	RotOscillation.Yaw.Amplitude = 0.5f;
	RotOscillation.Yaw.Frequency = 10.0f;



}
