#pragma once
#ifndef _AI_CHARACTER_H_
#define _AI_CHARACTER_H_
#include "CharacterManager.h"
class AICharacter : public CharacterManager
{
public:
	AICharacter();
	AICharacter(string fileName, Vector2 *pos, float mass);
	void Walking();
};
#endif

