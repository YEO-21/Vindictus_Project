#include "Object/CameraShake/AttackCameraShake.h"

UAttackCameraShake::UAttackCameraShake()
{
	bSingleInstance = true;
	OscillationDuration = 0.5f;

	// ���� ����
	RotOscillation.Pitch.Amplitude = 0.5f;

	// ���� �ӵ�
	RotOscillation.Pitch.Frequency= 10.0f;

	RotOscillation.Yaw.Amplitude = 0.5f;
	RotOscillation.Yaw.Frequency = 10.0f;



}
