#include "Framework.h"
#include "Audio.h"

Audio::Audio(Context * context)
	: ISubsystem(context)
	, system(nullptr)
	, distanceFactor(1.0f)
	, maxChannel(32)
	, result(FMOD_OK)
	, bInitialized(false)
{
	EventSystem::Get()->Subscribe(EventType::Update, EVENT_HANDLER(Update));
}

Audio::~Audio()
{
	if (!bInitialized)
		return;

	result = system->close();
	assert(result == FMOD_OK);

	result = system->release();
	assert(result == FMOD_OK);
}

const bool Audio::Initialize()
{
	if (bInitialized)
		return false;

	//FMOD System ����
	result = System_Create(&system);
	assert(result == FMOD_OK);

	//FMOD Version Check
	uint version = 0;
	result = system->getVersion(&version);
	assert(result == FMOD_OK);
	assert(version == FMOD_VERSION);

	//�ý��ۿ� ���� ī�� ��ġ�� �ִ��� Ȯ��
	int driverCount = 0;
	result = system->getNumDrivers(&driverCount);
	assert(result == FMOD_OK);
	assert(driverCount > 0);

	//FMOD System �ʱ�ȭ
	result = system->init(maxChannel, FMOD_INIT_NORMAL, nullptr);
	assert(result == FMOD_OK);

	//FMOD 3D Settings
	result = system->set3DSettings
	(
		1.0f,
		distanceFactor,
		0.0f
	);
	assert(result == FMOD_OK);

	bInitialized = true;

	return true;
}

void Audio::Update()
{
	if (!bInitialized)
		return;

	result = system->update();
	assert(result == FMOD_OK);
}