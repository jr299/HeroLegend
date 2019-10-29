#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "CharacterManager.h"
class Player : public CharacterManager
{
public:
	Player();
	Player(string fileName, Vector2 *pos, float mass);
	void Walking();
};

#endif