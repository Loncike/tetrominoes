#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "../scene.h"
#include "../game.h"

typedef struct{
  Scene base;

   GlobalState *globalState;
}MainMenuScene;

SCENESYSTEM_DECLARFUNCS(mainMenuScene)

#endif
