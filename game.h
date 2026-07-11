#ifndef GAME_H_
#define GAME_H_
#define Width 800
#define Height 800

#define GameFieldGridsWidth 10
#define GameFieldGridsHeight 20
// + 2 maybe
#define GridSize ((int)((Width/20)*.8))

#define GameFieldColsOffset ((Width/2)-(GameFieldGridsWidth*GridSize/2))
#define GameFieldRowsOffset ((Height/2)-(GameFieldGridsHeight*GridSize/2))

#include "raylib.h"

typedef struct{
  int x, y;
}Vector2Int;

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

static const int (*Tetrominoes[])[4][4] = {TetrominoI, TetrominoO, TetrominoT, TetrominoS, TetrominoZ, TetrominoJ, TetrominoL};
static const Color TetrominoColors[7] = {SKYBLUE, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE};

typedef struct{
   int score;
   int highScore;

   int level;
}GlobalState;

typedef enum{
  SCENE_MAINMENUSCENE,
  SCENE_GAMESCENE,
  SCENE_GAMEOVERSCENE,
}Scenes;

#endif
