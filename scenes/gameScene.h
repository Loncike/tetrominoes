#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "../scene.h"
#include "../game.h"

typedef struct{
  Scene base;

  GlobalState *globalState;

  float fallTimer;
  float fallInterval;
  float moveTimer;
  float moveInterval;

  int GameField[GameFieldGridsHeight][GameFieldGridsWidth];
  Tetromino currentTetromino;

}GameScene;

void gameSceneInit(SceneManager *sm);
void gameSceneUpdate(SceneManager *sm);
void GameSceneDraw(SceneManager *sm);

#endif
