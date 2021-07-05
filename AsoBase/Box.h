#pragma once
#include"Vector2.h"
#include"GameoverScene.h"
class GameScene;
class SceneManager;


class Box
{
public:
	//1�}�X������̎���
	static constexpr float TIME_MOVE = 0.4f;


	//���
	enum class STATE
	{
		NONE,
		IDLE,
		MOVE,
		BACK_MOVE
	};

	Box(GameScene* scene);

	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void DrawTest(void);
	void Release(void);

	//���W�̎擾
	Vector2 GetPos(void);

	//�����o������
	void Push(DIR dir);

	//�ו��̈ړ���̏Փ˔���
	bool IsPossiblePush(DIR dir);

	bool IsStayStorage(void);

	//�����߂��w��
	void BackMove(GameScene::History his);

private:
	SceneManager* mSceneManager;
	GameScene* mGameScene;

	STATE mState;

	int mImage;

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

	//�ו��u����̏�ɐݒu����Ă��邩
	bool mIsStayStorage;

	//�����߂�
	GameScene::History mHistory;

	//��ԑJ��
	void ChangeState(STATE state);

};

