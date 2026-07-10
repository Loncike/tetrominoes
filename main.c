#include "raylib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Width 800
#define Height 800

#define GameFieldGridsWidth 10
#define GameFieldGridsHeight 20
// + 2 maybe
#define GridSize ((int)((Width/20)*.8))

#define GameFieldColsOffset ((Width/2)-(GameFieldGridsWidth*GridSize/2))
#define GameFieldRowsOffset ((Height/2)-(GameFieldGridsHeight*GridSize/2))


typedef struct{
  int x, y;
}Vector2Int;

#define TetrominoMatrixSize 4
#define TetrominoRotationSize 4

static const int TetrominoI[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
  },
  {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
  },
};


static const int TetrominoO[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 0, 1, 1},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 1},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 1},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 1},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
};

static const int TetrominoT[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 0, 1, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
};

static const int TetrominoL[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 0, 0, 1},
    {0, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
};

static const int TetrominoJ[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 1, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
  },
};

static const int TetrominoS[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
};

static const int TetrominoZ[TetrominoRotationSize][TetrominoMatrixSize][TetrominoMatrixSize] = {
  {
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
  },
};

typedef enum{
  TI,
  TO,
  TT,
  TS,
  TZ,
  TJ,
  TL,
}TetrominoType;

typedef struct{
  TetrominoType type;
  int x,y; 
  int rotation;
}Tetromino;

int Gameover = 0;

static const int (*Tetrominoes[])[4][4] = {TetrominoI, TetrominoO, TetrominoT, TetrominoS, TetrominoZ, TetrominoJ, TetrominoL};
static const Color TetrominoColors[7] = {SKYBLUE, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE};

int GameField[GameFieldGridsHeight][GameFieldGridsWidth] = {0};

void placeShape(Tetromino t){
  if (t.y < 2){
    Gameover = 1;
  }

  for (int y = 0; y < 4; ++y){
    for (int x = 0; x < 4; ++x){
      if (!Tetrominoes[t.type][t.rotation][y][x]) continue;
      GameField[y+t.y][x+t.x] = Tetrominoes[t.type][t.rotation][y][x];
    }
  }
}

int checkCollision(Tetromino t, int newX, int newY, int newRot){
 for (int x = 0; x < 4; ++x){
    for (int y = 0; y < 4; ++y){
      if (!Tetrominoes[t.type][newRot][y][x]) continue;

      int dx = newX + x;
      int dy = newY + y;
      if (dx < 0 || dx >= GameFieldGridsWidth || dy >= GameFieldGridsHeight) return 1;
      if (GameField[dy][dx] != 0) return 1;
    }
  }
  return 0;
}

//should introduce game/scene state struct
void GamePlayScene(Tetromino *curTetromino, float *fallTimer, float fallInterval, float *moveTimer, float moveInterval, int *score){

  float dt = GetFrameTime();
  *fallTimer += dt;
  *moveTimer += dt;

  if (*fallTimer >= fallInterval) {
    *fallTimer -= fallInterval;
    if (!checkCollision(*curTetromino, curTetromino->x, curTetromino->y + 1, curTetromino->rotation)) {
      curTetromino->y += 1;
    } else {
      placeShape(*curTetromino);
      *curTetromino = (Tetromino){0};
      curTetromino->type = rand() % 7;
      assert(curTetromino->type < 7 && "Tetromino type out of range");
    }
  }
  if (IsKeyPressed(KEY_S)) {
    while (!checkCollision(*curTetromino, curTetromino->x, curTetromino->y + 1, curTetromino->rotation)) {
      curTetromino->y += 1;
    }
    placeShape(*curTetromino);
    *curTetromino = (Tetromino){0};
    curTetromino->type = rand() % 7;
    assert(curTetromino->type < 7 && "Tetromino type out of range");
  }

  if (IsKeyDown(KEY_A) && *moveTimer >= moveInterval && !checkCollision(*curTetromino, curTetromino->x - 1, curTetromino->y, curTetromino->rotation)) {
    curTetromino->x -= 1;
    *moveTimer = 0;
  } else if (IsKeyDown(KEY_D) && *moveTimer >= moveInterval && !checkCollision(*curTetromino, curTetromino->x + 1, curTetromino->y, curTetromino->rotation)) {
    curTetromino->x += 1;
    *moveTimer = 0;
  }

  else if (IsKeyPressed(KEY_Q)) {
    int newRot = (curTetromino->rotation + 3) % 4;
    if (!checkCollision(*curTetromino, curTetromino->x, curTetromino->y, newRot)) {
      curTetromino->rotation = newRot;
    }
  } else if (IsKeyPressed(KEY_E)) {
    int newRot = (curTetromino->rotation + 5) % 4;
    if (!checkCollision(*curTetromino, curTetromino->x, curTetromino->y, newRot)) {
      curTetromino->rotation = newRot;
    }
  }

  int linesCleared = 0;
  int linesOffset = 0;
  int tmpY = 0;
  for (int y = 0; y < GameFieldGridsHeight; ++y) {
    int full = 1;
    for (int x = 0; x < GameFieldGridsWidth; ++x) {
      if (GameField[y][x] == 0) {
        full = 0;
        break;
      }
    }
    if (full) {
      //for moving it down
      for (int row = y; row > 0; --row) {
        for (int x = GameFieldGridsWidth - 1; x > 0; --x) {
          GameField[row][x] = GameField[row - 1][x];
        }
      }
      linesCleared++;
    }
  }

  //TODO do level based scoring
  switch(linesCleared){
    case 0:
      // so we dont log it as too much
      break;
    case 1:
      *score +=  40;
      break;
    case 2:
      *score += 100;
      break;
    case 3:
      *score += 300;
      break;
    case 4:
      *score += 1200;
      break;
    default:
      TraceLog(LOG_WARNING, "Too much lines cleard %d", linesCleared);
  }
  

  BeginDrawing();
  ClearBackground((Color){18, 18, 18, 255});
  DrawText(TextFormat("Score: %d", *score), 0, 0, 32, WHITE);

  for (int y = 0; y < GameFieldGridsHeight; ++y) {
    for (int x = 0; x < GameFieldGridsWidth; ++x) {
      if (GameField[y][x] == 0) {
        DrawRectangle(x * GridSize + GameFieldColsOffset, y * GridSize + GameFieldRowsOffset, GridSize - 2, GridSize - 2, (Color){ 28, 28, 30, 255 });
      } else {
        DrawRectangle(x * GridSize + GameFieldColsOffset, y * GridSize + GameFieldRowsOffset, GridSize - 2, GridSize - 2, RED);
      }
    }
  }

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (Tetrominoes[curTetromino->type][curTetromino->rotation][y][x]) {
        DrawRectangle((x + curTetromino->x) * GridSize + GameFieldColsOffset, (y + curTetromino->y) * GridSize + GameFieldRowsOffset, GridSize - 2, GridSize - 2, TetrominoColors[curTetromino->type]);
      }
    }
  }

  EndDrawing();
}

void GameOverScene(int *score, int *highscore, int *newHighScore){

  if (IsKeyPressed(KEY_R)){
    for (int y = 0; y < GameFieldGridsHeight; ++y){
      for (int x = 0; x < GameFieldGridsWidth; ++x){
         GameField[y][x] = 0;
      }
    }
    Gameover = 0;
    *score = 0;
  }

  if (*highscore < *score){
    *highscore = *score;
  }

  BeginDrawing();
    ClearBackground((Color){18, 18, 18, 255});
    DrawText(TextFormat("Game over"), (Width/2)-(MeasureText(TextFormat("Game over"), 48)/2), Height/2, 48, RED);
    DrawText(TextFormat("Press R to (R)estart"), (Width/2)-(MeasureText(TextFormat("Press R to (R)estart"), 48)/2), Height/2+2*48, 48, RED);
    DrawText(TextFormat("Score: %d", *score), (Width/2)-(MeasureText(TextFormat("Score: %d", *score), 48)/2), Height/2+3*48, 48, RED);
    DrawText(TextFormat("High score: %d", *highscore), (Width/2)-(MeasureText(TextFormat("High score: %d", *highscore), 48)/2), Height/2+4*48, 48, RED);
   EndDrawing();
}

int main(){
  srand(time(NULL));

  float fallTimer = .0f;
  float fallInterval = .5f;

  // Think abt different solution
  float moveTimer = .0f;
  float moveInterval = .1f;

  Tetromino curTetromino = {0};
  curTetromino.type = TT;

  int score = 0;
  int highScore = 0;
  int newHighScore = 0;

  InitWindow(Width, Height, "Tetris");
  SetTargetFPS(60);

  while (!WindowShouldClose()){
    if (!Gameover){
      GamePlayScene(&curTetromino, &fallTimer, fallInterval, &moveTimer, moveInterval, &score);    
    }else{
      GameOverScene(&score, &highScore, &newHighScore);
    }
  }

  CloseWindow();
  return 0;
}
