#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
#include "AICharacter.h"
#include "Player.h"
#include "BackGroup.h"
#include <vector>
#include<thread>

class SceneManager
{
private:
	SceneManager();
	static SceneManager* m_instance;

public:
	
	void Init();
	void Render();
	void CreateAIAnimation(AICharacter* AI);
	void CreatePlayerAnimation(Player* AI);
	void CreateListCharacterImage();
	void Update(float deltaTime);
	bool IsCollison(AICharacter *AI, Player *player);
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
	void RenderAITitleThread();
	void RenderPlayerTitleThread();
	void RenderAIAnimThread();
	void RenderPlayerAnimThread();
	void CreateAIListImage(bool ad);
	void CreatePlayerListImage();
	bool CheckCollisionAI(vector<AICharacter*> list);
	bool CheckCollisionPlayer(vector<Player*> list);
	bool CheckCollisionOnTrack1();
	bool CheckCollisionOnTrack2();
	bool CheckCollisionOnTrack3();
	void RenderCharacterOnEachTrack(int trackNumber);
	void RenderTrack(vector<AICharacter*> m_listAI, vector<Player*> m_listPlayer, int m_listAIMass, int m_listPlayerMass);

public:
	vector<AICharacter*> m_listAI;
	vector<AICharacter*> m_listAIOnTrack1;
	vector<AICharacter*> m_listAIOnTrack2;
	vector<AICharacter*> m_listAIOnTrack3;
	int m_listAIMassTrack1;
	int m_listAIMassTrack2;
	int m_listAIMassTrack3;
	int m_listPlayerMassTrack1;
	int m_listPlayerMassTrack2;
	int m_listPlayerMassTrack3;
private:
	
	Graphics* m_graphics;
	string m_AIId;
	string m_PlayerId;
	Vector2* m_postison;
	
	vector<Player*> m_listPlayer;
	vector<Player*> m_listPlayerOnTrack1;
	vector<Player*> m_listPlayerOnTrack3;
	vector<Player*> m_listPlayerOnTrack2;
	float m_AIRunPosXFollowAISizeInEachTrack;
	float m_playerRunPosXFollowAISizeInEachTrack;
	int m_AIOnTrack;
	int m_PlyerOnTrack;
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
	mutex m_door;
};

#endif