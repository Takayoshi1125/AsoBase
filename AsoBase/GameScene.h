#pragma once
#include<vector>
#include<string>
#include<stack>
#include<map>
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
class PopupUIBase;

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

	//巻き戻し用構造体
	struct History
	{
		DIR dir;
		Vector2 unitPos;
		Box* box;
		Vector2 boxPos;
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

	void DrawScore(void);

	void Release(void) override;

	Stage* GetStage(void);

	//荷物との衝突判定
	Box* GetCollisionBox(Vector2 pos);

	//荷物置き場との衝突判定
	Storage* GetCollisionStorage(Vector2 pos);

	Fader* mFader;

	//ステージ構成パスを取得
	std::string GetCsvPathGround(int stageNo);

	//ギミック構成パスを取得
	std::string GetCsvPathGimmick(int stageNo);

	std::string GetCsvPathScore(void);

	//操作履歴に登録
	void RegistHistory(DIR dir, Vector2 pos, Box* box);

	void PlusCntMove(void);

	void MinusCntMove(void);

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

	//巻き戻し
	std::stack<History> mHistoryBack;

	float mStepClear;

	//移動歩数
	int mCntMove;

	//現在のステージのBestスコア
	int mBestScore;

	//ステージごとのBestScore
	std::map<int, int>mBestScores;


	void ChangeState(STATE state);

	//メニューUI
	PopupUIBase* mPopupUIBase;


	void ChangeStage(void);

	void SetStage(void);

	void LoadGimicData(void);

	void LoadScore(void);


	void SaveScore(void);
	//現在のステージのBestScoreを取得
	int GetBestScore(void);

};
