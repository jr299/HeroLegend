#include "CharacterManager.h"
CharacterManager::CharacterManager()
	:m_positionCharacter((0, 0)),
	m_characterImage(NULL),
	m_animation(NULL),
	m_playerCanCreate(true)
{

}

CharacterManager::CharacterManager(string fileName, Vector2 *pos, float mass = 2)
	:m_positionCharacter(pos),
	m_mass(mass),
	m_point(0),
	m_playerCanCreate(true),
	m_canRun(false)
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
	delete m_characterImage;
	m_characterImage = new Image(fileName.c_str());
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
	m_characte->y += posY;
}

void CharacterManager::Render(Graphics *graphics)
{
	graphics->DrawImage(m_characterImage, m_positionCharacter->x, m_positionCharacter->y, 0);
}

void CharacterManager::RenderAnimation(Graphics* graphics, gamerize::Animation* anim, int loop)
{
	anim->SetLoop(loop);
	anim->SetEnableAnimation(true);
	graphics->DrawAnimation(anim, m_positionCharacter->x, m_positionCharacter->y, 0);
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

bool CharacterManager::IsCharacterCanRun()
{
	return m_canRun;
}

CharacterManager::~CharacterManager()
{
	m_animation = NULL;
	m_positionCharacter = NULL;
	m_characterImage = NULL;
}