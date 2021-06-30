#pragma once
#include<vector>
#include<string>
#include"GameCommon.h"
#include"Vector2.h"
#include"SceneBase.h"
class SceneManager;
class TimeLimit;
class Fader;
class Stage;
class Unit;
class Box;
class Storage;

class GameScene : public SceneBase
{

public:

	static constexpr int MAX_STAGE_NO = 5;

	static constexpr float TIME_CLEAR_MSG = 3.0f;

	//状態
	enum class STATE
	{
		GAME,
		CLEAR,
		CHANGE_STAGE
	};

	GameScene(SceneManager* manager);
	void Init(void) override;

	void Update(void) override;
	void UpdateGame(void);
	void UpdateClear(void);
	void UpdateChangeStage(void);

	void Draw(void) override;
	void DrawGame(void);
	void DrawClear(void);
	void DrawChangeStage(void);

	void Release(void) override;

	Stage* GetStage(void);

	//荷物との衝突判定
	Box* GetCollisionBox(Vector2 pos);

	//荷物置き場との衝突判定
	Storage* GetCollisionStorage(Vector2 pos);

	Fader* mFader;

	//ステージ構成パスを取得
	std::string GetCsvPathGround(int stageNo);

	std::string GetCsvPathGimmick(int stageNo);


private:
	Stage* mStage;
	Unit* mUnit;
	
	TimeLimit* mTimelimit;

	//クリア画像
	int mImageC;

	//デルタタイム
	float mTickCount;
	float mDeltTime;

	bool mIsFading;

	//動的配列
	std::vector<Box*>mBoxes;

	std::vector<Storage*>mStorages;

	int mStageNo;

	//状態管理
	STATE mState;

	float mStepClear;

	void ChangeState(STATE state);

	void ChangeStage(void);

	void SetStage(void);

	void LoadGimicData(void);

};
