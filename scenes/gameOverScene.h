#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "../scene.h"
#include "../game.h"

typedef struct{
  Scene base;
  GlobalState *globalState;
}GameOverScene;

void gameOverSceneInit(SceneManager *sm);
void gameOverSceneUpdate(SceneManager *sm);
void gameOverSceneDraw(SceneManager *sm);

#endif
