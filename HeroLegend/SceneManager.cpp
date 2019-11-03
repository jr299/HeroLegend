#include "SceneManager.h"
#include "Define.h"
#define AI_PATH "AI"
#include <time.h>
#include <chrono>

using namespace std;

SceneManager* SceneManager::m_instance = NULL;
SceneManager* SceneManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SceneManager();
	}
	return m_instance;
}

SceneManager::SceneManager()
	:m_AIId(""),
	m_PlayerId(""),
	m_backGroup(NULL),
	m_postison((0, 0)),
	m_AIRunPosXFollowAISizeInEachTrack(0),
	m_playerRunPosXFollowAISizeInEachTrack(0),
	m_AIRandom(0),
	m_AIRandomPosX(0),
	m_playerRandom(0),
	m_AITitlePosX(0),
	m_AITitlePosY(0),
	m_playerTitlePosX(0),
	m_playerTitlePosY(0),
	m_AITitle(NULL),
	m_playerTitle(NULL),
	m_characterMass(1),
	m_AINumberToFinish(0),
	m_PlayerNumberToFinish(0),
	m_listSmallAIImage(NULL),
	m_listMediumAIImage(NULL),
	m_listBigAIImage(NULL),
	m_listBigPlayerImage(NULL),
	m_listSmallPlayerImage(NULL),
	m_listMediumPlayerImage(NULL),
	m_canCreatePlayerAnim(true),
	m_AIOnTrack(0),
	m_PlyerOnTrack(0),
	m_listAIOnTrack1(NULL),
	m_listAIOnTrack2(NULL),
	m_listAIOnTrack3(NULL),
	m_listPlayerOnTrack1(NULL),
	m_listPlayerOnTrack2(NULL),
	m_listPlayerOnTrack3(NULL),
	m_listAIMassTrack1(0),
	m_listAIMassTrack2(0),
	m_listAIMassTrack3(0),
	m_listPlayerMassTrack1(0),
	m_listPlayerMassTrack2(0),
	m_listPlayerMassTrack3(0)
{

}

void SceneManager::Init()
{
	CreateListCharacterImage();
	_sleep(5000);
	srand((unsigned int)time(0));

	RandomAIValue();
	RandomPlayerValue();

	m_backGroup = new BackGroup();
	m_backGroup->Init(MAP_NAME, AI_PUT_NAME, PLAYER_PUT_NAME, new Vector2(0, 0));

	CreateAITitle();
	CreatePlayerTitle();
	m_instance = this;
}

void SceneManager::Update(float deltaTime)
{
	m_backGroup->Update(deltaTime);
	/*thread AIThread(&SceneManager::BeginAIThreadAI, this);
	thread playerThread(&SceneManager::BeginPlayerThread, this);
	CreateAITitle();
	AIThread.join();	
	playerThread.join();*/
	if (m_backGroup->GetAIPutValue() >= 60)
	{
		if (m_AITitle != nullptr)
		{
			AICharacter* AIRun = new AICharacter(m_AIId + to_string(AI_FIRST_NUMBER),
				new Vector2(m_AIRunPosXFollowAISizeInEachTrack - int(m_AITitle->GetCharacterImage()->GetWidth() / 2), AI_POS_Y), m_AIOnTrack, m_characterMass);
			CreateAIAnimation(AIRun);
			m_listAI.push_back(AIRun);
			switch (m_AIOnTrack)
			{
			case 1:
				m_listAIOnTrack1.push_back(AIRun);
				break;
			case 2:
				m_listAIOnTrack2.push_back(AIRun);
				break;
			case 3:
				m_listAIOnTrack3.push_back(AIRun);
				break;
			default:
				break;
			}

			RandomAIValue();
			CreateAITitle();
		}
	}

	if (m_backGroup->GetPlayerPutValue() >= 60)
	{
		if (m_playerTitle != nullptr && m_canCreatePlayerAnim)
		{
			Player* playerRun = new Player(m_PlayerId + to_string(PLAYER_FIRST_NUMBER),
				new Vector2(m_playerRunPosXFollowAISizeInEachTrack, PLAYER_POS_Y), m_PlyerOnTrack, m_characterMass);
			CreatePlayerAnimation(playerRun);
			m_listPlayer.push_back(playerRun);
			switch (m_PlyerOnTrack)
			{
			case 1:
				m_listPlayerOnTrack1.push_back(playerRun);
				break;
			case 2:
				m_listPlayerOnTrack2.push_back(playerRun);
				break;
			case 3:
				m_listPlayerOnTrack3.push_back(playerRun);
				break;
			default:
				break;
			}

			RandomPlayerValue();
			m_canCreatePlayerAnim = false;
		}
	}

}

void SceneManager::OnEvent(TouchData* touchData)
{
	float touchPosX = touchData->position.x;
	if (CanRun(&(touchData->position)) && m_listPlayer.size() > 0)
	{
		if (!m_canCreatePlayerAnim)
		{
			if (touchPosX <= 180)
			{
				m_playerRunPosXFollowAISizeInEachTrack = TRACK_1_POS_X;
				m_PlyerOnTrack = 1;
			}
			else if (touchPosX <= 310)
			{
				m_playerRunPosXFollowAISizeInEachTrack = TRACK_2_POS_X;
				m_PlyerOnTrack = 2;
			}
			else
			{
				m_playerRunPosXFollowAISizeInEachTrack = TRACK_3_POS_X;
				m_PlyerOnTrack = 3;
			}
			m_listPlayer[m_listPlayer.size() - 1]->SetPosition(new Vector2(m_playerRunPosXFollowAISizeInEachTrack - int(m_playerTitle->GetCharacterImage()->GetWidth() / 2), m_listPlayer[m_listPlayer.size() - 1]->GetPosYCharacter()));
			m_listPlayer[m_listPlayer.size() - 1]->EnableRunForCharacter(true);
			CreatePlayerTitle();
		}
		m_canCreatePlayerAnim = true;
	}

}

void SceneManager::Render()
{

	if (m_backGroup != nullptr)
	{
		m_backGroup->Render();
	}

	if (m_AITitle != nullptr)
	{
		m_AITitle->Render();
	}

	if (m_playerTitle != nullptr)
	{
		m_playerTitle->Render();
	}

	//thread AITitleThread(&SceneManager::RenderAITitleThread, this);
	
	//thread playerTitleThread(&SceneManager::RenderPlayerTitleThread, this);
	
	//thread AIAnimThread(&SceneManager::RenderAIAnimThread, this);
	
	//thread playerAnimThread(&SceneManager::RenderPlayerAnimThread, this);
	
	//AITitleThread.join();
	//playerTitleThread.join();
	//AIAnimThread.join();
	//playerAnimThread.join();

	CheckCollisionAI(m_listAIOnTrack1);
	CheckCollisionAI(m_listAIOnTrack2);
	CheckCollisionAI(m_listAIOnTrack3);
	CheckCollisionPlayer(m_listPlayerOnTrack1);
	CheckCollisionPlayer(m_listPlayerOnTrack2);
	CheckCollisionPlayer(m_listPlayerOnTrack3);

	for (size_t i = 1; i < 3; i++)
	{
		RenderCharacterOnEachTrack(i);
	}

	/*for (size_t i = 0; i < m_listAI.size(); i++)
	{
		m_listAI[i]->Move(m_listAI[i]->GetPosition(), 0.3f);
		m_listAI[i]->RenderAnimation(m_listAI[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
		if (m_listAI[i]->GetPosYCharacter() > PLAYER_POS_Y + 50)
		{
			printf("m_listAI size before erase : %d \n", m_listAI.size());
			m_listAI.erase(m_listAI.begin() + i);
			printf("m_listAI Size after erase: %d \n", m_listAI.size());
			m_AINumberToFinish++;
		}
	}

	for (size_t i = 0; i < m_listPlayer.size(); i++)
	{
		if (m_listPlayer[i]->DoCharacterRun())
		{
			m_listPlayer[i]->Move(m_listPlayer[i]->GetPosition(), -0.3f);
			m_listPlayer[i]->RenderAnimation(m_listPlayer[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
			if (m_listPlayer[i]->GetPosYCharacter() < AI_POS_Y)
			{
				printf("m_listPlayer size before erase : %d \n", m_listPlayer.size());
				m_listPlayer.erase(m_listPlayer.begin() + i);
				printf("m_listPlayer Size after erase: %d \n", m_listPlayer.size());
				m_PlayerNumberToFinish++;
			}
		}
	}*/
}

void SceneManager::RenderCharacterOnEachTrack(int trackNumber)
{
	switch (trackNumber)
	{
	case 1:
		RenderTrack(m_listAIOnTrack1, m_listPlayerOnTrack1, m_listAIMassTrack1, m_listPlayerMassTrack1);
		break;
	case 2:
		RenderTrack(m_listAIOnTrack2, m_listPlayerOnTrack2, m_listAIMassTrack2, m_listPlayerMassTrack2);
		break;
	case 3:
		RenderTrack(m_listAIOnTrack3, m_listPlayerOnTrack3, m_listAIMassTrack3, m_listPlayerMassTrack3);
		break;
	default:
		break;
	}
}

void SceneManager::RenderTrack(vector<AICharacter*> m_listAI, vector<Player*> m_listPlayer, int m_listAIMass, int m_listPlayerMass)
{
	int mass = 0;
	mass = m_listAIMassTrack1 - m_listPlayerMassTrack1;
	for (int i = 0; i < m_listAI.size(); i++)
	{

		m_listAI[i]->Move(m_listAI[i]->GetPosition(), mass * CHARACTER_VELOCITY);
		m_listAI[i]->RenderAnimation(m_listAI[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
		if (m_listAI[i]->GetPosYCharacter() > PLAYER_POS_Y + 50)
		{
			printf("m_listAI size before erase : %d \n", m_listAI.size());
			m_listAI.erase(m_listAI.begin() + i);
			printf("m_listAI Size after erase: %d \n", m_listAI.size());
			m_AINumberToFinish++;
		}
	}

	for (size_t i = 0; i < m_listPlayer.size(); i++)
	{
		if (m_listPlayer[i]->DoCharacterRun())
		{
			m_listPlayer[i]->Move(m_listPlayer[i]->GetPosition(), mass * CHARACTER_VELOCITY);
			m_listPlayer[i]->RenderAnimation(m_listPlayer[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
			if (m_listPlayer[i]->GetPosYCharacter() < AI_POS_Y)
			{
				printf("m_listPlayer size before erase : %d \n", m_listPlayer.size());
				m_listPlayer.erase(m_listPlayer.begin() + i);
				printf("m_listPlayer Size after erase: %d \n", m_listPlayer.size());
				m_PlayerNumberToFinish++;
			}
		}
	}
}

bool SceneManager::CheckCollisionAI(vector<AICharacter*> list)
{
	bool isCollisionAI = false;
	int mass = 0;
	bool isCollisionWithRival = false;
	if (list.size() > 0)
	{
		if (list[0]->GetTrackNumber() == 1)
		{
			isCollisionWithRival = CheckCollisionOnTrack1();
		}
		else if (list[0]->GetTrackNumber() == 2)
		{
			isCollisionWithRival = CheckCollisionOnTrack2();
		}
		else
		{
			isCollisionWithRival = CheckCollisionOnTrack3();
		}

		if (m_listAIMassTrack3)
		{
			for (int i = 0; i < list.size(); i++)
			{
				float AI1Top = list[i]->GetPosYCharacter();
				float AI2Bottom = list[i + 1]->GetPosYCharacter() + list[i + 1]->GetCharacterImage()->GetHeight();
				if (AI1Top <= AI2Bottom)
				{
					mass = list[i]->GetCharacterMass() + list[i + 1]->GetCharacterMass();
					isCollisionAI = true;
				}
			}
			if (list[0]->GetTrackNumber() == 1)
			{
				m_listAIMassTrack1 = mass;
			}
			else if (list[0]->GetTrackNumber() == 2)
			{
				m_listAIMassTrack2 = mass;
			}
			else
			{
				m_listAIMassTrack3 = mass;
			}
		}
	}
	return isCollisionAI;
}

bool SceneManager::CheckCollisionPlayer(vector<Player*> list)
{
	bool isCollisionPlayer = false;
	int mass = 0;
	bool isCollisionWithRival = false;
	if (list.size())
	{
		if (list[0]->GetTrackNumber() == 1)
		{
			isCollisionWithRival = CheckCollisionOnTrack1();
		}
		else if (list[0]->GetTrackNumber() == 2)
		{
			isCollisionWithRival = CheckCollisionOnTrack2();
		}
		else
		{
			isCollisionWithRival = CheckCollisionOnTrack3();
		}
		if (isCollisionWithRival)
		{
			for (int i = 0; i < list.size(); i++)
			{
				float player1Bottom = list[i]->GetPosYCharacter() + list[i]->GetCharacterImage()->GetHeight();
				float player2Top = list[i + 1]->GetPosYCharacter();
				if (player1Bottom >= player2Top)
				{
					mass = list[i]->GetCharacterMass() + list[i + 1]->GetCharacterMass();
					isCollisionPlayer = true;
				}
			}
			if (list[0]->GetTrackNumber() == 1)
			{
				m_listPlayerMassTrack1 = mass;
			}
			else if (list[0]->GetTrackNumber() == 2)
			{
				m_listPlayerMassTrack2 = mass;
			}
			else
			{
				m_listPlayerMassTrack3 = mass;
			}
		}
	}
	
	return isCollisionPlayer;
}

bool SceneManager::IsCollison(AICharacter* AI, Player* player)
{
	float AIBottom = AI->GetBottomCharacter();
	float playerTop = player->GetPosYCharacter();
	if (AIBottom >= playerTop)
	{
		return true;
	}
	return false;
}

bool SceneManager::CheckCollisionOnTrack1()
{
	if (m_listAIOnTrack1.size() > 0 && m_listPlayerOnTrack1.size() > 0)
	{
		return m_listAIOnTrack1[0]->GetPosYCharacter() + m_listAIOnTrack1[0]->GetCharacterImage()->GetHeight()
			>= m_listPlayerOnTrack1[0]->GetPosYCharacter();
	}
	return false;
}

bool SceneManager::CheckCollisionOnTrack2()
{
	if (m_listAIOnTrack2.size() > 0 && m_listPlayerOnTrack2.size() > 0)
	{
		return m_listAIOnTrack2[0]->GetPosYCharacter() + m_listAIOnTrack2[0]->GetCharacterImage()->GetHeight()
			>= m_listPlayerOnTrack2[0]->GetPosYCharacter();
	}
	return false;
}
bool SceneManager::CheckCollisionOnTrack3()
{
	if (m_listAIOnTrack3.size() > 0 && m_listPlayerOnTrack3.size() > 0)
	{
		return m_listAIOnTrack3[0]->GetPosYCharacter() + m_listAIOnTrack3[0]->GetCharacterImage()->GetHeight()
			>= m_listPlayerOnTrack3[0]->GetPosYCharacter();
	}
	return false;
}

void SceneManager::RenderAITitleThread()
{
	if (m_AITitle != NULL)
	{
		m_AITitle->Render();
	}
}

void SceneManager::RenderPlayerTitleThread()
{
	if (m_playerTitle != NULL)
	{
		m_playerTitle->Render();
	}
}

void SceneManager::RenderAIAnimThread()
{
	for (size_t i = 0; i < m_listAI.size(); i++)
	{
		m_listAI[i]->Move(m_listAI[i]->GetPosition(), 0.3f);
		m_listAI[i]->RenderAnimation(m_listAI[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
		if (m_listAI[i]->GetPosYCharacter() > PLAYER_POS_Y + 50)
		{
			printf("m_listAI size before erase : %d \n", m_listAI.size());
			m_listAI.erase(m_listAI.begin() + i);
			printf("m_listAI Size after erase: %d \n", m_listAI.size());
			m_AINumberToFinish++;
		}
	}
}

void SceneManager::RenderPlayerAnimThread()
{
	for (size_t i = 0; i < m_listPlayer.size(); i++)
	{
		if (m_listPlayer[i]->DoCharacterRun())
		{
			m_listPlayer[i]->Move(m_listPlayer[i]->GetPosition(), -0.3f);
			m_listPlayer[i]->RenderAnimation(m_listPlayer[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
			if (m_listPlayer[i]->GetPosYCharacter() < AI_POS_Y)
			{
				printf("m_listPlayer size before erase : %d \n", m_listPlayer.size());
				m_listPlayer.erase(m_listPlayer.begin() + i);
				printf("m_listPlayer Size after erase: %d \n", m_listPlayer.size());
				m_PlayerNumberToFinish++;
			}
		}
	}
}

void SceneManager::CreateAIAnimation(AICharacter* AI)
{
	switch (m_AIRandom)
	{
	case 1:
		AI->CreateAnimation(m_listSmallAIImage);
		break;
	case 2:
		AI->CreateAnimation(m_listMediumAIImage);
		break;
	case 3:
		AI->CreateAnimation(m_listBigAIImage);
		break;
	default:
		break;
	}
}

void SceneManager::CreatePlayerAnimation(Player* player)
{
	switch (m_playerRandom)
	{
	case 1:
		player->CreateAnimation(m_listSmallPlayerImage);
		break;
	case 2:
		player->CreateAnimation(m_listMediumPlayerImage);
		break;
	case 3:
		player->CreateAnimation(m_listBigPlayerImage);
		break;
	default:
		break;
	}
}

void SceneManager::CreateAITitle()
{
	if (m_AITitle == NULL)
	{
		m_AITitle = new AICharacter(m_AIId + to_string(AI_FIRST_NUMBER), new Vector2(-100, -100), 0, m_characterMass);
	}
	else
	{
		m_AITitle->SetCharacterImage(m_AIId + to_string(AI_FIRST_NUMBER));
	}
	m_AITitlePosX = m_backGroup->GetAIPutImage()->GetWidth() / 2 - int(m_AITitle->GetCharacterImage()->GetWidth()) / 2;
	m_AITitle->SetPosition(new Vector2(m_AITitlePosX, CHARACTER_TITLE_POS_Y));
}

void SceneManager::CreatePlayerTitle()
{
	if (m_playerTitle == NULL)
	{
		m_playerTitle = new Player(m_PlayerId + to_string(PLAYER_FIRST_NUMBER), new Vector2(-100, 100), 0, m_characterMass);
	}
	else
	{
		m_playerTitle->SetCharacterImage(m_PlayerId + to_string(PLAYER_FIRST_NUMBER));
	}

	m_playerTitlePosX = (m_backGroup->GetPlayerPutImage()->GetWidth() - int(m_playerTitle->GetCharacterImage()->GetWidth())) / 2;
	m_playerTitle->SetPosition(new Vector2(m_playerTitlePosX, PLAYER_TITLE_POS_Y));
}

void SceneManager::RandomAIValue()
{
	m_AIRandom = 1 + rand() % 3;
	switch (m_AIRandom)
	{
	case 1:
		m_AIId = SMALL_AI_PATH;
		m_characterMass = SMALL_CHARACTER_MASS;
		break;
	case 2:
		m_AIId = MEDIUM_AI_PATH;
		m_characterMass = MEDIUM_CHARACTER_MASS;
		break;
	case 3:
		m_AIId = BIG_AI_PATH;
		m_characterMass = BIG_CHARACTER_MASS;
		break;
	default:
		break;
	}
	int AItrackBlock = BlockAITrack();
	switch (AItrackBlock)
	{
	case 1:
		m_AIRandomPosX = 2 + rand() % 2;
		break;
	case 2:
		m_AIRandomPosX = 1;
		break;
	case 3:
		m_AIRandomPosX = 1 + rand() % 2;
		break;
	default:
		m_AIRandomPosX = 1 + rand() % 3;
		break;
	}
	switch (m_AIRandomPosX)
	{
	case 1:
		m_AIRunPosXFollowAISizeInEachTrack = TRACK_1_POS_X;
		m_AIOnTrack = 1;
		break;
	case 2:
		m_AIRunPosXFollowAISizeInEachTrack = TRACK_2_POS_X;
		m_AIOnTrack = 2;
		break;
	case 3:
		m_AIRunPosXFollowAISizeInEachTrack = TRACK_3_POS_X;
		m_AIOnTrack = 3;
		break;
	default:
		break;
	}
}

void SceneManager::RandomPlayerValue()
{
	m_playerRandom = 1 + rand() % 3;
	switch (m_playerRandom)
	{
	case 1:
		m_PlayerId = SMALL_PLAYER_PATH;
		m_characterMass = SMALL_CHARACTER_MASS;
		break;
	case 2:
		m_PlayerId = MEDIUM_PLAYER_PATH;
		m_characterMass = MEDIUM_CHARACTER_MASS;
		break;
	case 3:
		m_PlayerId = BIG_PLAYER_PATH;
		m_characterMass = BIG_CHARACTER_MASS;
		break;
	default:
		break;
	}
}

void SceneManager::CreateListCharacterImage()
{
	for (size_t i = AI_FIRST_NUMBER; i < AI_FIRST_NUMBER + CHARACTER_NUMBER; i++)
	{
		m_listSmallAIImage.push_back(new Image((SMALL_AI_PATH + to_string(i) + IMAGE_TYPE).c_str()));
		m_listMediumAIImage.push_back(new Image((MEDIUM_AI_PATH + to_string(i) + IMAGE_TYPE).c_str()));
		m_listBigAIImage.push_back(new Image((BIG_AI_PATH + to_string(i) + IMAGE_TYPE).c_str()));
	}

	for (size_t i = PLAYER_FIRST_NUMBER; i <= PLAYER_FIRST_NUMBER + CHARACTER_NUMBER; i++)
	{
		m_listSmallPlayerImage.push_back(new Image((SMALL_PLAYER_PATH + to_string(i) + IMAGE_TYPE).c_str()));
		m_listMediumPlayerImage.push_back(new Image((MEDIUM_PLAYER_PATH + to_string(i) + IMAGE_TYPE).c_str()));
		m_listBigPlayerImage.push_back(new Image((BIG_PLAYER_PATH + to_string(i) + IMAGE_TYPE).c_str()));
	}

	/*thread j1(&SceneManager::CreateAIListImage, this, true);
	thread j2(&SceneManager::CreateAIListImage, this, false);
	j1.join();
	j2.join();*/
}

void SceneManager::CreateAIListImage(bool ad)
{
	printf("******************* Thread %d \n", this_thread::get_id());
	m_door.lock();
	printf("******************* Thread %d *** 2 \n", this_thread::get_id());
	if (ad)
	{
		for (size_t i = AI_FIRST_NUMBER; i < AI_FIRST_NUMBER + CHARACTER_NUMBER; i++)
		{
			printf("******************* Thread %d ***** %d \n", this_thread::get_id(), i);
			m_listSmallAIImage.push_back(new Image((SMALL_AI_PATH + to_string(i) + IMAGE_TYPE).c_str()));
			m_listMediumAIImage.push_back(new Image((MEDIUM_AI_PATH + to_string(i) + IMAGE_TYPE).c_str()));
			m_listBigAIImage.push_back(new Image((BIG_AI_PATH + to_string(i) + IMAGE_TYPE).c_str()));
		}
	}
	else
	{
		printf("******************* Thread %d \n", this_thread::get_id());
		for (size_t i = PLAYER_FIRST_NUMBER; i <= PLAYER_FIRST_NUMBER + CHARACTER_NUMBER; i++)
		{
			printf("******************* Thread %d ***** %d \n", this_thread::get_id(), i);
			m_listSmallPlayerImage.push_back(new Image((SMALL_PLAYER_PATH + to_string(i) + IMAGE_TYPE).c_str()));
			m_listMediumPlayerImage.push_back(new Image((MEDIUM_PLAYER_PATH + to_string(i) + IMAGE_TYPE).c_str()));
			m_listBigPlayerImage.push_back(new Image((BIG_PLAYER_PATH + to_string(i) + IMAGE_TYPE).c_str()));
		}
	}
	m_door.unlock();
}

void SceneManager::CreatePlayerListImage()
{
	
}

bool SceneManager::CanCreatePlayerAnim()
{
	return m_canCreatePlayerAnim;
}

bool SceneManager::CanRun(Vector2* pos)
{
	bool canRun = true;
	if (!(pos->x >= 0 && pos->x <= SCREEN_WIDTH && pos->y >= 0 && pos->y <= SCREEN_HEIGHT))
	{
		canRun = false;
	}
	return canRun;
}

int SceneManager::BlockAITrack()
{
	if (m_listPlayer.size() > 0)
	{
		if (m_listPlayer[0]->GetPosYCharacter() - 20 <= AI_POS_Y)
		{
			int a = (int)(m_listPlayer[0]->GetCharacterImage()->GetWidth() / 2);
			int b = m_listPlayer[0]->GetPosXCharacter();
			int playerPosX = b + a;
			switch (playerPosX)
			{
			case TRACK_1_POS_X:
				return 1;
			case TRACK_2_POS_X:
				return 2;
			case TRACK_3_POS_X:
				return 3;
			default:
				break;
			}
		}
	}
	return 0;
}

int SceneManager::BlockPlayerTrack()
{
	if (m_listAI.size() > 0)
	{
		if (m_listAI[0]->GetPosYCharacter() >= PLAYER_POS_Y)
		{
			int AIPosX = m_listAI[0]->GetPosXCharacter() + (int)(m_listAI[0]->GetCharacterImage()->GetWidth() / 2);
			switch (AIPosX)
			{
			case TRACK_1_POS_X:
				return 1;
			case TRACK_2_POS_X:
				return 2;
			case TRACK_3_POS_X:
				return 3;
			default:
				break;
			}
		}
	}
	return 0;
}

