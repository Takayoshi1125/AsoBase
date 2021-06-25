#pragma once
#include"Vector2.h"

#define NUM_ANIM_X 3
#define NUM_ANIM_Y 4
#define IMG_SIZE 32

class SceneManager;
class GameScene;

class Unit
{
public:

	//1�}�X������̎���
	static constexpr float TIME_MOVE = 0.4f;

	static constexpr int CNT_ANIM = 4;

	static constexpr int SPEED_SLOW_ANIM = 8;


	//���
	enum class STATE
	{
		NONE,
		IDLE,
		MOVE
	};


	//�R���X�g���N�^
	Unit(GameScene* scene);

	//�}�b�v���W
	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void Release(void);


private:
	SceneManager* mSceneManager;
	GameScene* mGameScene;

	//�ʏ�摜
	int mUnitimg[NUM_ANIM_Y][NUM_ANIM_X];

	//�����o���摜
	int mImagesPush[NUM_ANIM_Y][NUM_ANIM_X];

	int mAniCnt;	//���Ƃ�mCntAnim

	//���
	STATE mState;

	//���݂̃X�N���[�����W
	Vector2 mPos;

	//�ړ������W
	Vector2 mMvSPos;

	//�ړ�����W
	Vector2 mMvEPos;

	//�ړ��J�n����̌o�ߎ���
	float mStepMove;

	//�ړ�����
	DIR mDir;

	//�����o����
	bool mIsPushing;

	//��ԑJ��
	void ChangeState(STATE state);

};

