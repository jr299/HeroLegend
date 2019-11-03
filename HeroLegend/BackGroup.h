#pragma once
#ifndef _BACKGROUP_H_
#define _BACKGROUP_H_
#include <GameEngine.h>
#include <string>
#include "Define.h"

using namespace std;
class BackGroup
{
public:
	BackGroup();
	void Init(string fileName, string AIPutId, string playerPutID, Vector2* pos);
	void Render();
	Image* GetAIPutImage();
	Image* GetPlayerPutImage();
	void SetPosition(Vector2* pos);
	Vector2* GetPosition();
	void  Update(float deltaTime);
	float GetAIPutValue();
	float GetPlayerPutValue();
private:
	Image* m_backGroup;
	Image* m_playerPut;
	Image* m_AIPut;
	Vector2* m_position;
	float m_AIPutValue;
	float m_playerPutValue;
};

#endif // !