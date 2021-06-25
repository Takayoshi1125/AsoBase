#pragma once
#include"GameCommon.h"
#include"Vector2.h"

class GameScene;

class Stage
{
public:
	Stage(GameScene* scene);

	void Init(int stageNo);
	void UpDate(void);
	void Render(void);
	void Release(void);

	//衝突判定
	bool IsCollision(Vector2 mapPos);

private:

	GameScene* mGameScene;

	int mImage[4];

	int mImageInFloor;
	int mImageOutFloor;



	int mMap[MAP_SIZE_Y][MAP_SIZE_X] = {
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9,9, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9,9, 9,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0},
	};

	//これはプログラムコードでステージ設定
	void SetStage(int stageNo);

	//外部ファイルを使用してステージ設定
	void LoadDate(int stageNo);

};

