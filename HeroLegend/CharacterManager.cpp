#include "CharacterManager.h"
CharacterManager::CharacterManager()
{

}

CharacterManager::CharacterManager(string fileName, Vector2 *pos, int trackNumber, float mass = 2)
	:m_positionCharacter(pos),
	m_mass(mass),
	m_point(0),
	m_playerCanCreate(true),
	m_canRun(false),
	m_trackNumber(trackNumber),
	m_animation(NULL)
{
	m_characterImage = new Image((fileName + IMAGE_TYPE).c_str());
}

void CharacterManager::CreateAnimation(list<Image*> list)
{
	this->m_animation = new gamerize::Animation(list, FRAME_SPEED);
}

float CharacterManager::GetPosXCharacter()
{
	return m_positionCharacter->x;
}

float CharacterManager::GetPosYCharacter()
{
	return m_positionCharacter->y + CHARACTER_PADDING;
}

float CharacterManager::GetBottomCharacter()
{
	return m_positionCharacter->y + m_characterImage->GetHeight() - CHARACTER_PADDING;
}

Image* CharacterManager::GetCharacterImage()
{
	return m_characterImage;
}

void CharacterManager::SetCharacterImage(string fileName)
{
	m_characterImage->Load((fileName + IMAGE_TYPE).c_str());
}

void CharacterManager::SetPosition(Vector2 *characterPosition)
{
	m_positionCharacter = characterPosition;
}

Vector2* CharacterManager::GetPosition()
{
	return m_positionCharacter;
}

void CharacterManager::Move(Vector2 *m_characte, float posY)
{
	//m_door.lock();
	m_characte->y += posY;
	//m_door.unlock();
}

void CharacterManager::Render()
{
	Device::GetInstance()->GetGraphics()->DrawImage(m_characterImage, m_positionCharacter->x, m_positionCharacter->y, 0);
}

void CharacterManager::RenderAnimation(gamerize::Animation* anim, int loop)
{
	//m_door.lock();
	anim->SetLoop(loop);
	anim->SetEnableAnimation(true);
	Device::GetInstance()->GetGraphics()->DrawAnimation(anim, m_positionCharacter->x, m_positionCharacter->y, 0);
	//m_door.unlock();
}

void CharacterManager::SetName(string name)
{
	m_name = name;
}

string CharacterManager::GetName()
{
	return m_name;
}

void CharacterManager::SetCharacterMass(float mass)
{
	m_mass = mass;
}

void CharacterManager::SetAnimation(gamerize::Animation* anim)
{
	m_animation = anim;
}

gamerize::Animation* CharacterManager::GetAnimation()
{
	return m_animation;
}

float CharacterManager::GetCharacterMass()
{
	return m_mass;
}

void CharacterManager::EnableRunForCharacter(bool canRun)
{
	m_canRun = canRun;
}

bool CharacterManager::DoCharacterRun()
{
	return m_canRun;
}

int CharacterManager::GetTrackNumber()
{
	return m_trackNumber;
}

CharacterManager::~CharacterManager()
{
	m_animation = NULL;
	m_positionCharacter = NULL;
	m_characterImage = NULL;
}