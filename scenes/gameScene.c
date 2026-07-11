#include "raylib.h"
#include "../game.h"
#include "gameScene.h"


// introduce some global game state etc etc
// gameFieald should be a part of game scene
void placeShape(SceneManager *sm){
  GameScene *s = (GameScene *)sceneManagerCurrent(sm);

  if (s->currentTetromino.y < 2){
    sceneManagerReplaceScene(sm, sm->scenes[SCENE_GAMEOVERSCENE]);
  }

  
  for (int y = 0; y < 4; ++y){
    for (int x = 0; x < 4; ++x){
      if (!Tetrominoes[s->currentTetromino.type][s->currentTetromino.rotation][y][x]) continue;
      s->GameField[y+s->currentTetromino.y][x+s->currentTetromino.x] = Tetrominoes[s->currentTetromino.type][s->currentTetromino.rotation][y][x];
    }
  }
}

int checkCollision(SceneManager *sm, int newX, int newY, int newRot){
  GameScene *s = (GameScene *)sceneManagerCurrent(sm);

 for (int x = 0; x < 4; ++x){
    for (int y = 0; y < 4; ++y){
      if (!Tetrominoes[s->currentTetromino.type][newRot][y][x]) continue;

      int dx = newX + x;
      int dy = newY + y;
      if (dx < 0 || dx >= GameFieldGridsWidth || dy >= GameFieldGridsHeight) return 1;
      if (s->GameField[dy][dx] != 0) return 1;
    }
  }
  return 0;
}

void gameSceneInit(SceneManager *sm){
  GameScene *s = (GameScene *)sceneManagerCurrent(sm);

  s->fallTimer = .0f;
  s->fallInterval = .5f;

  s->moveTimer = .0f;
  s->moveInterval = .1f;

  s->currentTetromino = (Tetromino){0};
  s->currentTetromino.type = rand() % 7;
  assert(s->currentTetromino.type < 7 && "Tetromino type out of range");

  s->linesClearedCounter = 0;

  s->globalState->score = 0;

  for (int y = 0; y < GameFieldGridsHeight; ++y) {
    for (int x = 0; x < GameFieldGridsWidth; ++x) {
      s->GameField[y][x] = 0;
    }
  }
}

void gameSceneUpdate(SceneManager *sm){
  GameScene *s = (GameScene *)sceneManagerCurrent(sm);
 
  float dt = GetFrameTime();
  s->fallTimer += dt;
  s->moveTimer += dt;

  if (s->fallTimer >= s->fallInterval) {
    s->fallTimer -= s->fallInterval;
    if (!checkCollision(sm, s->currentTetromino.x, s->currentTetromino.y + 1, s->currentTetromino.rotation)) {
      s->currentTetromino.y += 1;
    } else {
      placeShape(sm);
      s->currentTetromino = (Tetromino){0};
      s->currentTetromino.type = rand() % 7;
      assert(s->currentTetromino.type < 7 && "Tetromino type out of range");
    }
  }
  if (IsKeyPressed(KEY_S)) {
    while (!checkCollision(sm, s->currentTetromino.x, s->currentTetromino.y + 1, s->currentTetromino.rotation)) {
      s->currentTetromino.y += 1;
    }
    placeShape(sm);
    s->currentTetromino = (Tetromino){0};
    s->currentTetromino.type = rand() % 7;
    assert(s->currentTetromino.type < 7 && "Tetromino type out of range");
  }

  if (IsKeyDown(KEY_A) && s->moveTimer >= s->moveInterval && !checkCollision(sm, s->currentTetromino.x - 1, s->currentTetromino.y, s->currentTetromino.rotation)) {
    s->currentTetromino.x -= 1;
    s->moveTimer = 0;
  } else if (IsKeyDown(KEY_D) && s->moveTimer >= s->moveInterval && !checkCollision(sm, s->currentTetromino.x + 1, s->currentTetromino.y, s->currentTetromino.rotation)) {
    s->currentTetromino.x += 1;
    s->moveTimer = 0;
  }

  else if (IsKeyPressed(KEY_Q)) {
    int newRot = (s->currentTetromino.rotation + 3) % 4;
    if (!checkCollision(sm, s->currentTetromino.x, s->currentTetromino.y, newRot)) {
      s->currentTetromino.rotation = newRot;
    }
  } else if (IsKeyPressed(KEY_E)) {
    int newRot = (s->currentTetromino.rotation + 5) % 4;
    if (!checkCollision(sm, s->currentTetromino.x, s->currentTetromino.y, newRot)) {
      s->currentTetromino.rotation = newRot;
    }
  }

  int linesCleared = 0;
  for (int y = 0; y < GameFieldGridsHeight; ++y) {
    int full = 1;
    for (int x = 0; x < GameFieldGridsWidth; ++x) {
      if (s->GameField[y][x] == 0) {
        full = 0;
        break;
      }
    }
    if (full) {
      //for moving it down
      for (int row = y; row > 0; --row) {
        for (int x = GameFieldGridsWidth - 1; x > 0; --x) {
          s->GameField[row][x] = s->GameField[row - 1][x];
        }
      }
      linesCleared++;
    }
  }

  s->linesClearedCounter += linesCleared;
  if (s->linesClearedCounter >= 10){
    s->linesClearedCounter = 0;
    s->globalState->level++;
  }

  //TODO maybe no need for switch, and can be solved by math only
  switch(linesCleared){
    case 0:
      // so we dont log it as too much
      break;
    case 1:
      s->globalState->score +=    40 * (s->globalState->level + 1);
      break;
    case 2:
      s->globalState->score +=   100 * (s->globalState->level + 1);
      break;
    case 3:
      s->globalState->score +=   300 * (s->globalState->level + 1);
      break;
    case 4:
      s->globalState->score +=  1200 * (s->globalState->level + 1);
      break;
    default:
      TraceLog(LOG_WARNING, "Too much lines cleard %d", linesCleared);
  } 
}

void GameSceneDraw(SceneManager *sm){
  GameScene *s = (GameScene *)sceneManagerCurrent(sm);
  
ClearBackground((Color){18, 18, 18, 255});
  DrawText(TextFormat("Score: %d", s->globalState->score), 0, 0, 32, WHITE);

  for (int y = 0; y < GameFieldGridsHeight; ++y) {
    for (int x = 0; x < GameFieldGridsWidth; ++x) {
      if (s->GameField[y][x] == 0) {
        DrawRectangle(x * GridSize + GameFieldColsOffset, y * GridSize + GameFieldRowsOffset, GridSize - 2, GridSize - 2, (Color){ 28, 28, 30, 255 });
      } else {
        DrawRectangle(x * GridSize + GameFieldColsOffset, y * GridSize + GameFieldRowsOffset, GridSize - 2, GridSize - 2, RED);
      }
    }
  }

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (Tetrominoes[s->currentTetromino.type][s->currentTetromino.rotation][y][x]) {
        DrawRectangle((x + s->currentTetromino.x) * GridSize + GameFieldColsOffset, (y + s->currentTetromino.y) * GridSize + GameFieldRowsOffset, GridSize - 2, GridSize - 2, TetrominoColors[s->currentTetromino.type]);
      }
    }
  }
}
