#pragma once
#include "Scene.h"

enum SceneIndex{
	S_Title,
	S_Opening,
	S_Stage1,
	S_HowToPlay,
	S_Store,
	S_Stage2,
	S_Ending,
	S_Rank,
	S_Make,
};

class CSceneManager
{
public:
	CSceneManager(void);
	~CSceneManager(void);
	
	void init();
	void update();

	bool m_isNextScene;
	SceneIndex m_eNextScene;

	CScene * p_Scene;

	CScene *  GetScene(){return p_Scene;};
	void setScene(CScene * scene){p_Scene = scene;}
	
	void SceneChange(SceneIndex index);
	void NowSceneChange(SceneIndex index);
};

