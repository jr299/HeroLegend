#include "SceneManager.h"
#include "Define.h"
#define AI_PATH "AI"
#include <time.h>
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
	:m_graphics(NULL),
	m_AIId(""),
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
	m_canCreatePlayerAnim(true)
{

}

void SceneManager::Init(Graphics* graphics)
{
	m_graphics = graphics;
	CreateListCharacterImage();

	srand((unsigned int)time(0));

	RandomAIValue();
	RandomPlayerValue();

	m_backGroup = new BackGroup();
	m_backGroup->Init(MAP_NAME, AI_PUT_NAME, PLAYER_PUT_NAME, new Vector2(0, 0), graphics);

	CreateAITitle();
	CreatePlayerTitle();
	m_instance = this;
}

void SceneManager::Update(float deltaTime)
{
	m_backGroup->Update(deltaTime);
	if (m_backGroup->GetAIPutValue() >= 60)
	{
		if (m_AITitle != nullptr)
		{
			AICharacter* AIRun = new AICharacter(m_AIId + to_string(AI_FIRST_NUMBER), new Vector2(m_AIRunPosXFollowAISizeInEachTrack - m_AITitle->GetCharacterImage()->GetWidth() / 2, AI_POS_Y), m_characterMass);
			CreateAIAnimation(AIRun);
			m_listAI.push_back(AIRun);

			RandomAIValue();
			delete m_AITitle;
			CreateAITitle();
		}
	}

	if (m_backGroup->GetPlayerPutValue() >= 60)
	{
		if (m_playerTitle != nullptr && m_canCreatePlayerAnim)
		{
			Player* playerRun = new Player(m_PlayerId + to_string(PLAYER_FIRST_NUMBER), new Vector2(m_playerRunPosXFollowAISizeInEachTrack, PLAYER_POS_Y), m_characterMass);
			CreatePlayerAnimation(playerRun);
			m_listPlayer.push_back(playerRun);

			RandomPlayerValue();
			m_canCreatePlayerAnim = false;
		}
	}


}

void SceneManager::OnEvent(TouchData *touchData)
{
	float touchPosX = touchData->position.x;
	if (CanRun(&(touchData->position)) && m_listPlayer.size() > 0)
	{
		if (!m_canCreatePlayerAnim)
		{
			if (touchPosX <= 180)
			{
				m_playerRunPosXFollowAISizeInEachTrack = TRACK_1_POS_X;
			}
			else if (touchPosX <= 310)
			{
				m_playerRunPosXFollowAISizeInEachTrack = TRACK_2_POS_X;
			}
			else
			{
				m_playerRunPosXFollowAISizeInEachTrack = TRACK_3_POS_X;
			}
			m_listPlayer[m_listPlayer.size() - 1]->SetPosition(new Vector2(m_playerRunPosXFollowAISizeInEachTrack - m_playerTitle->GetCharacterImage()->GetWidth() / 2, m_listPlayer[m_listPlayer.size() - 1]->GetPosYCharacter()));
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
		m_backGroup->Render(m_graphics);
	}

	if (m_AITitle != nullptr)
	{
		m_AITitle->Render(m_graphics);
	}

	if (m_playerTitle != nullptr)
	{
		m_playerTitle->Render(m_graphics);
	}

	for (size_t i = 0; i < m_listAI.size(); i++)
	{
		m_listAI[i]->Move(m_listAI[i]->GetPosition(), 0.3f);
		m_listAI[i]->RenderAnimation(m_graphics, m_listAI[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
		if (m_listAI[i]->GetPosYCharacter() > PLAYER_POS_Y)
		{
			printf("m_listAI size before erase : %d \n", m_listAI.size());
			m_listAI.erase(m_listAI.begin() + i);
			printf("m_listAI Size after erase: %d \n", m_listAI.size());
			m_AINumberToFinish++;
		}
	}

	for (size_t i = 0; i < m_listPlayer.size(); i++)
	{
		if (m_listPlayer[i]->IsCharacterCanRun())
		{
			m_listPlayer[i]->Move(m_listPlayer[i]->GetPosition(), -0.3f);
			m_listPlayer[i]->RenderAnimation(m_graphics, m_listPlayer[i]->GetAnimation(), (int)SCREEN_HEIGHT / 7);
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
	m_AITitle = new AICharacter(m_AIId + to_string(AI_FIRST_NUMBER), new Vector2(-100, -100), m_characterMass);
	m_AITitlePosX = (m_backGroup->GetAIPutImage()->GetWidth() - m_AITitle->GetCharacterImage()->GetWidth()) / 2;
	m_AITitle->SetPosition(new Vector2(m_AITitlePosX, CHARACTER_TITLE_POS_Y));
}

void SceneManager::CreatePlayerTitle()
{
	delete m_playerTitle;
	m_playerTitle = new Player(m_PlayerId + to_string(PLAYER_FIRST_NUMBER), new Vector2(-100, 100), m_characterMass);
	m_playerTitlePosX = (m_backGroup->GetPlayerPutImage()->GetWidth() - m_playerTitle->GetCharacterImage()->GetWidth()) / 2;
	m_playerTitle->SetPosition(new Vector2(m_playerTitlePosX, PLAYER_TITLE_POS_Y));
}

bool SceneManager::CharacterCollison(AICharacter* AI, Player* player)
{
	float AIBottom = AI->GetBottomCharacter();
	float playerTop = player->GetPosYCharacter();
	if (AIBottom >= playerTop)
	{
		return true;
	}
	return false;
}

void SceneManager::RandomAIValue()
{
	m_AIRandom = 1 + rand() % 3;
	m_AIRandomPosX = 1 + rand() % 3;
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

	switch (m_AIRandomPosX)
	{
	case 1:
		m_AIRunPosXFollowAISizeInEachTrack = TRACK_1_POS_X;
		break;
	case 2:
		m_AIRunPosXFollowAISizeInEachTrack = TRACK_2_POS_X;
		break;
	case 3:
		m_AIRunPosXFollowAISizeInEachTrack = TRACK_3_POS_X;
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
}

bool SceneManager::CanCreatePlayerAnim()
{
	return m_canCreatePlayerAnim;
}

bool SceneManager::CanRun(Vector2 *pos)
{
	bool canRun = true;
	if (!(pos->x >= 0 && pos->x <= SCREEN_WIDTH && pos->y >= 0 && pos->y <= SCREEN_HEIGHT))
	{
		canRun = false;
	}
	return canRun;
}

