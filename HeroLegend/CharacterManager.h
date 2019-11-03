#pragma once
#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_
#include "Define.h"
#include <GameEngine.h>
#include <string>
#include <mutex>
using namespace std;

class CharacterManager
{
public:
	CharacterManager();
	CharacterManager(string fileName, Vector2 *pos, int trackNumber, float mass);
	~ CharacterManager();
	Image* GetCharacterImage();
	void CreateAnimation(list<Image*> list);
	void SetCharacterImage(string fileName);
	void SetPosition(Vector2 *characterPosition);
	Vector2* GetPosition();
	void Render();
	void RenderAnimation(gamerize::Animation* anim, int loop);
	void Move(Vector2* m_characte, float posY);
	float GetPosYCharacter();
	float GetPosXCharacter();
	float GetBottomCharacter();
	void SetName(string name);
	string GetName();
	void SetCharacterMass(float mass);
	float GetCharacterMass();
	void SetAnimation(gamerize::Animation* m_anim);
	gamerize::Animation* GetAnimation();
	void EnableRunForCharacter(bool canRun);
	bool DoCharacterRun();
	void SetTrackNumber(int trackNumber);
	int GetTrackNumber();
private:
	Vector2 *m_positionCharacter;
	Image* m_characterImage;
	string m_name;
	float m_mass;
	float m_velocity;
	int m_point;
	gamerize::Animation *m_animation;
	bool m_playerCanCreate;
	bool m_canRun;
	mutex m_door;
	Graphics* m_graphics;
	int m_trackNumber;
};
#endif
