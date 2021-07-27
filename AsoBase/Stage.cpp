#include<DxLib.h>
#include<vector>
#include<string>
#include<fstream>
#include"SceneManager.h"
#include"GameoverScene.h"
#include"Utility.h"
#include "Stage.h"

Stage::Stage(GameScene* scene)
{
	mGameScene = scene;
	//mSceneManager = scene->GetSceneManager();
}

void Stage::Init(int stageNo)
{
	LoadDivGraph("Image/StageChip.png", 4, 2, 2, 32, 32, mImage, true);


	//SetStage(stageNo);
	
	//外部データでステージ設定
	LoadDate(stageNo);

}

void Stage::UpDate(void)
{
}

void Stage::Draw(void)
{
	for (int y = 0; y < SCREEN_SIZE_Y / BLOCK_SIZE; y++)
	{
		for (int x = 0; x < SCREEN_SIZE_X / BLOCK_SIZE; x++)
		{
			DrawGraph(x * BLOCK_SIZE, y * BLOCK_SIZE, mImage[3], true);
		}
	}

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x< MAP_SIZE_X; x++)
		{
			if (mMap[y][x] == -1)
			{
				DrawGraph(x * BLOCK_SIZE + GAME_AREA_X,
					y * BLOCK_SIZE + GAME_AREA_Y,
					mImage[0], true);
			}
			else if (mMap[y][x] == 1)
			{
				DrawGraph(x * BLOCK_SIZE + GAME_AREA_X,
					y * BLOCK_SIZE + GAME_AREA_Y,
					mImage[1], true);
			}
			else if (mMap[y][x] == 2)
			{
				DrawGraph(x * BLOCK_SIZE + GAME_AREA_X,
					y * BLOCK_SIZE + GAME_AREA_Y,
					mImage[2], true);
			}
		}
	}
}

void Stage::Release(void)
{
	DeleteGraph(mImage[0]);
	DeleteGraph(mImage[1]);
	DeleteGraph(mImage[2]);
	DeleteGraph(mImage[3]);
}

bool Stage::IsCollision(Vector2 mapPos)
{
	if (mapPos.y < 0)
	{
		return true;
	}
	if (mapPos.y >= (MAP_SIZE_Y - 1))
	{
		return true;
	}


	return mMap[mapPos.y][mapPos.x]>1;
}

void Stage::SetStage(int stageNo)
{
	switch (stageNo)
	{
	case 2:
	{
		int tmpMap[MAP_SIZE_Y][MAP_SIZE_X] = {
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9,9, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,9,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,9,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,9,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,9,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9,9, 9,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0},
		};

		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			for (int x = 0; x < MAP_SIZE_X; x++)
			{
				mMap[y][x] = tmpMap[y][x];
			}
		}
	}
	}

	

}

void Stage::LoadDate(int stageNo)
{
	//ファイルパス取得
	std::string filePath = mGameScene->GetCsvPathGround(stageNo);

	//ファイルを読み込む
	std::ifstream ifs(filePath);

	//1行ずつ読み込む
	int y = 0;
	std::string line;
	while (getline(ifs, line))
	{
		//Yで分割されたline
		

		std::vector<std::string>strvec =
			Utility::Split(line, ',');


		//Xで分割されたstrvec
		int size = strvec.size();
		for (int x = 0; x < size; x++)
		{
			mMap[y][x] = stoi(strvec[x]);
		}

		int i = stoi(strvec[0]);

		y++;

	}

	if(true){}

}
