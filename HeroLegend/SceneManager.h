#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
#include "AICharacter.h"
#include "Player.h"
#include "BackGroup.h"
#include <vector>

class SceneManager
{
private:
	SceneManager();
	static SceneManager* m_instance;

public:
	
	void Init(Graphics *graphics);
	void Render();
	void CreateAIAnimation(AICharacter* AI);
	void CreatePlayerAnimation(Player* AI);
	void CreateListCharacterImage();
	void Update(float deltaTime);
	bool CharacterCollison(AICharacter *AI, Player *player);
	BackGroup* m_backGroup;
	void RandomAIValue();
	void RandomPlayerValue();
	void CreateAITitle();
	void CreatePlayerTitle();
	void OnEvent(TouchData *touchData);
	static SceneManager* GetInstance();
	bool CanCreatePlayerAnim();
	bool CanRun(Vector2 *pos);
	int BlockAITrack();
	int BlockPlayerTrack();
private:
	
	Graphics* m_graphics;
	string m_AIId;
	string m_PlayerId;
	Vector2* m_postison;
	vector<AICharacter*> m_listAI;
	vector<Player*> m_listPlayer;
	float m_AIRunPosXFollowAISizeInEachTrack;
	float m_playerRunPosXFollowAISizeInEachTrack;
	int m_AIRandom;
	int m_AIRandomPosX;
	int m_playerRandom;
	int m_AITitlePosX;
	int m_AITitlePosY;
	int m_playerTitlePosX;
	int m_playerTitlePosY;
	AICharacter* m_AITitle;
	Player* m_playerTitle;
	float m_characterMass;
	int m_AINumberToFinish;
	int m_PlayerNumberToFinish;
	list<Image*> m_listSmallAIImage;
	list<Image*> m_listMediumAIImage;
	list<Image*> m_listBigAIImage;
	list<Image*> m_listSmallPlayerImage;
	list<Image*> m_listMediumPlayerImage;
	list<Image*> m_listBigPlayerImage;
	bool m_canCreatePlayerAnim;
	int m_playerIndex;
	vector<int*> m_listTouch;
};

#endif