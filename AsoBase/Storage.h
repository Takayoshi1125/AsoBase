#pragma once
#include"Vector2.h"
class GameScene;
class SceneManager;
class Storage
{
public:
	Storage(GameScene* scene);

	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void Release(void);

	//���W�̎擾
	Vector2 GetPos(void);

private:
	SceneManager* mSceneManager;
	GameScene* mGameScene;

	//���݂̃X�N���[�����W
	Vector2 mPos;

	int mImage;
};

