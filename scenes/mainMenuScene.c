#include "gameScene.h"
#include "raylib.h"
#include "mainMenuScene.h"
#include "../game.h"

void mainMenuSceneInit(SceneManager *sm){
  MainMenuScene *s = (MainMenuScene *)sceneManagerCurrent(sm);

  s->globalState->level = 0;
}

void mainMenuSceneUpdate(SceneManager *sm){
  MainMenuScene *s = (MainMenuScene *)sceneManagerCurrent(sm);
  
  if (IsKeyPressed(KEY_D)){
    if (s->globalState->level < 9) s->globalState->level++;
    
  }else if (IsKeyPressed(KEY_A)){
    if (s->globalState->level > 0) s->globalState->level--;
    
  }else if (IsKeyPressed(KEY_SPACE)){
    sceneManagerReplaceScene(sm, sm->scenes[SCENE_GAMESCENE]);
  }
}

//TODO: Add a leaderboard etc...
void mainMenuSceneDraw(SceneManager *sm){
  MainMenuScene *s = (MainMenuScene *)sceneManagerCurrent(sm);

  ClearBackground((Color){18, 18, 18, 255});


  DrawText(TextFormat("Tetrominoes"), (Width/2)-(MeasureText(TextFormat("Tetrominoes"), 48)/2), 0, 48, RAYWHITE);
  for (int i = 0; i <= 9; ++i){

    //TODO: Use better colors, and better positioning
    if (i == s->globalState->level){
      DrawRectangle(i*64+Width/10, Width/2, 60, 60, RED);
    }else{
      DrawRectangle(i*64+Width/10, Width/2, 60, 60, GRAY);
    }
    DrawText(TextFormat("%d", i),i*64+Width/10 + (60-MeasureText(TextFormat("%d", i), 24)) / 2 , Width/2 + (60 - 24) / 2, 24, WHITE);
  }
}
