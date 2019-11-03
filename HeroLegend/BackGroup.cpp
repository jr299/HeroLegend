#include "BackGroup.h"
#include "SceneManager.h"
BackGroup::BackGroup()
	:m_backGroup(NULL),
	m_AIPut(NULL),
	m_playerPut(NULL),
	m_position((0, 0)),
	m_AIPutValue(0.1),
	m_playerPutValue(0)
{

}

void BackGroup::Init(string fileName, string AIPutId, string playerPutID, Vector2* pos)
{
	m_position = pos;
	m_backGroup = new Image(fileName.c_str());
	m_AIPut = new Image(AIPutId.c_str());
	m_playerPut = new Image(playerPutID.c_str());
	SceneManager *m_scene = SceneManager::GetInstance();
}

Image* BackGroup::GetAIPutImage()
{
	return m_AIPut;
}

Image* BackGroup::GetPlayerPutImage()
{
	return m_playerPut;
}

void BackGroup::SetPosition(Vector2* pos)
{
	m_position = pos;
}

Vector2* BackGroup::GetPosition()
{
	return m_position;
}

float BackGroup::GetAIPutValue()
{
	return m_AIPutValue;
}

float BackGroup::GetPlayerPutValue()
{
	return m_playerPutValue;
}

void BackGroup::Update(float deltaTime)
{
	Device::GetInstance()->GetGraphics()->FillRect((m_backGroup->GetWidth() - CHARACTER_PUT_WIDTH) / 2,
		AI_PUT_POSY, m_AIPutValue, CHARACTER_PUT_HEIGHT);
	if (m_AIPutValue <= CHARACTER_PUT_WIDTH )
	{
		m_AIPutValue += deltaTime * 10;
	}
	else
	{
		m_AIPutValue = 0;
	}
	
	Device::GetInstance()->GetGraphics()->FillRect((m_backGroup->GetWidth() - CHARACTER_PUT_WIDTH) / 2,
		PLAYER_PUT_POS_Y, m_playerPutValue, CHARACTER_PUT_HEIGHT);
	if (SceneManager::GetInstance()->CanCreatePlayerAnim())
	{
		if (m_playerPutValue <= CHARACTER_PUT_WIDTH)
		{
			m_playerPutValue += deltaTime * 100;
		}
		else
		{
			m_playerPutValue = 0;
		}
	}
}

void BackGroup::Render()
{
	Device::GetInstance()->GetGraphics()->DrawImage(m_backGroup, m_position->x, m_position->y, 0);
	Device::GetInstance()->GetGraphics()->DrawImage(m_AIPut, m_position->x, m_position->y, 0);
	Device::GetInstance()->GetGraphics()->DrawImage(m_playerPut, m_position->x, 700, 0);
	Device::GetInstance()->GetGraphics()->DrawRect((m_backGroup->GetWidth() - CHARACTER_PUT_WIDTH) / 2, AI_PUT_POSY, CHARACTER_PUT_WIDTH, CHARACTER_PUT_HEIGHT);
	Device::GetInstance()->GetGraphics()->DrawRect((m_backGroup->GetWidth() - CHARACTER_PUT_WIDTH) / 2, PLAYER_PUT_POS_Y, CHARACTER_PUT_WIDTH, CHARACTER_PUT_HEIGHT);
	
}

