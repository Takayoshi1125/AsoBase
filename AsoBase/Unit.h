#pragma once
#include"Vector2.h"
#include"GameoverScene.h"

#define NUM_ANIM_X 3
#define NUM_ANIM_Y 4
#define IMG_SIZE 32

class SceneManager;
class GameScene;

class Unit
{
public:

	//1マス当たりの時間
	static constexpr float TIME_MOVE = 0.4f;

	static constexpr int CNT_ANIM = 4;

	static constexpr int SPEED_SLOW_ANIM = 8;


	//状態
	enum class STATE
	{
		NONE,
		IDLE,
		MOVE,
		BACK_MOVE
	};


	//コンストラクタ
	Unit(GameScene* scene);

	//マップ座標
	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void Release(void);

	//巻き戻し指示
	void BackMove(GameScene::History his);

	//
	bool IsEnableBack(void);

private:
	SceneManager* mSceneManager;
	GameScene* mGameScene;

	//通常画像
	int mUnitimg[NUM_ANIM_Y][NUM_ANIM_X];

	//押し出し画像
	int mImagesPush[NUM_ANIM_Y][NUM_ANIM_X];

	int mAniCnt;	//授業はmCntAnim

	//状態
	STATE mState;

	//現在のスクリーン座標
	Vector2 mPos;

	//移動元座標
	Vector2 mMvSPos;

	//移動先座標
	Vector2 mMvEPos;

	//移動開始からの経過時間
	float mStepMove;

	//移動方向
	DIR mDir;

	//押し出し中
	bool mIsPushing;

	//操作を戻す
	GameScene::History mHistory;

	//状態遷移
	void ChangeState(STATE state);

};

