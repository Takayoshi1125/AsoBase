#include<DxLib.h>
#include"Vector2.h"
#include"GameCommon.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"Stage.h"
#include "Storage.h"

Storage::Storage(GameScene* scene)
{
	mGameScene = scene;
	mSceneManager = scene->GetSceneManager();
}

void Storage::Init(Vector2 mapPos)
{
	mImage = LoadGraph("Image/Storage.png", true);

	mPos.x = mapPos.x * BLOCK_SIZE;
	mPos.y = mapPos.y * BLOCK_SIZE;
}

void Storage::Update(void)
{
}

void Storage::Draw(void)
{
	DrawGraph(mPos.x + GAME_AREA_X, mPos.y + GAME_AREA_Y, mImage, true);
}

void Storage::Release(void)
{
	DeleteGraph(mImage);
}

Vector2 Storage::GetPos(void)
{
	return mPos;
}
