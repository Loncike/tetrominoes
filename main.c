#include "raylib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "scenes/gameScene.h"
#include "scenes/gameOverScene.h"
#include "scenes/mainMenuScene.h"

#define SCENESYSTEM_IMPLEMENTATION
#include "scene.h"
#include "game.h"


#define ArraySize(xs) (sizeof(xs)/sizeof(xs[0]))

int main(){
  srand(time(NULL));

  GlobalState globalState = {0};

  GameScene gameS = {(Scene){gameSceneInit, gameSceneUpdate, GameSceneDraw}, &globalState};
  MainMenuScene mainMenuS = {(Scene){mainMenuSceneInit, mainMenuSceneUpdate, mainMenuSceneDraw}, &globalState};
  GameOverScene gameOverS = {(Scene){gameOverSceneInit, gameOverSceneUpdate, gameOverSceneDraw}, &globalState};

  Scene *scenes[10];
  scenes[SCENE_MAINMENUSCENE] = &mainMenuS.base;
  scenes[SCENE_GAMESCENE] = &gameS.base;
  scenes[SCENE_GAMEOVERSCENE] = &gameOverS.base;

  SceneManager *sm = InitSceneManager(scenes, ArraySize(scenes));
  
  sceneManagerPushScene(sm, sm->scenes[SCENE_MAINMENUSCENE]);

  InitWindow(Width, Height, "Tetris");
  SetTargetFPS(60);

  while (!WindowShouldClose()){
    sceneManagerCurrent(sm)->update(sm);
    BeginDrawing();
      sceneManagerCurrent(sm)->draw(sm);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
