#include "gameOverScene.h"
#include "raylib.h"
#include "../game.h"

void gameOverSceneInit(SceneManager *sm){
  GameOverScene *s = (GameOverScene *)sceneManagerCurrent(sm);
 
  if (s->globalState->highScore < s->globalState->score) {
    s->globalState->highScore = s->globalState->score;
  } 
}

void gameOverSceneUpdate(SceneManager *sm){
  GameOverScene *s = (GameOverScene *)sceneManagerCurrent(sm);
  if (IsKeyPressed(KEY_SPACE)) {
    sceneManagerReplaceScene(sm, sm->scenes[SCENE_MAINMENUSCENE]);
    s->globalState->score = 0;
  }

}

void gameOverSceneDraw(SceneManager *sm){
  GameOverScene *s = (GameOverScene *)sceneManagerCurrent(sm);

  ClearBackground((Color){18, 18, 18, 255});
  DrawText(TextFormat("Game over"), (Width/2)-(MeasureText(TextFormat("Game over"), 48)/2), Height/2, 48, RED);
  DrawText(TextFormat("Press Space to go back to the Main menu"), (Width/2)-(MeasureText(TextFormat("Press Space to go back to the Main menu"), 48)/2), Height/2+2*48, 48, RED);
  DrawText(TextFormat("Score: %d", s->globalState->score), (Width/2)-(MeasureText(TextFormat("Score: %d", s->globalState->score), 48)/2), Height/2+3*48, 48, RED);
  DrawText(TextFormat("High score: %d", s->globalState->highScore), (Width/2)-(MeasureText(TextFormat("High score: %d", s->globalState->highScore), 48)/2), Height/2+4*48, 48, RED);
}
