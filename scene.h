/*  scene.h - v0.1 - Public domain scene system for raylib

    For a demo, see: https://github.com/loncike/scene.h

    To use this library, do this in *one* C file:
    #define SCENESYSTEM_IMPLEMENTATION
    #include "scene.h"

    LICENSE
      See end of file for license information 

    DOCUMENTATION
      TODO

    TODOS
      TODO: Add deinit funciton to scene so user can freed allocated memory and have more controll 
      TODO: Add non crashing error handling instead of assert
*/


#ifndef SCENESYSTEM_H_
#define SCENESYSTEM_H_

#include <stdlib.h>

#ifndef MAXSTACKSCENES
 #define MAXSTACKSCENES 10
#endif

#ifndef MAXSCENES
  #define MAXSCENES 10
#endif

#ifndef SCENESYSTEM_ASSERT
  #include <assert.h>
  #define SCENESYSTEM_ASSERT(x) assert(x)
#endif
 
typedef struct Scene Scene;
typedef struct SceneManager SceneManager;

struct Scene{
  void (*init)(SceneManager *sm);
  void (*update)(SceneManager *sm);
  void (*draw)(SceneManager *sm);
};

struct SceneManager{
  Scene *scenesStack[MAXSCENES];
  int top;

  Scene *scenes[MAXSCENES];
};

SceneManager *InitSceneManager(Scene **scenes, size_t scenesLen);
void sceneManagerPushScene(SceneManager *sm, Scene *newScene);
void sceneManagerPopScene(SceneManager *sm);
Scene *sceneManagerCurrent(SceneManager *sm);
void sceneManagerReplaceScene(SceneManager *sm, Scene *newScene);

#endif // SCENESYSTEM_H_

#ifdef SCENESYSTEM_IMPLEMENTATION

void sceneManagerInit(SceneManager *sm);

SceneManager *InitSceneManager(Scene **scenes, size_t scenesLen){
  SCENESYSTEM_ASSERT(scenesLen <= MAXSCENES && "too many scenes provided: increase MAXSCENES or reduce scene count");
  SceneManager *sm = malloc(sizeof(SceneManager));
  for (int i = 0; i < scenesLen; ++i){
    sm->scenes[i] = scenes[i];
  }
  sm->top = 0;
  return sm;
}

void sceneManagerPushScene(SceneManager *sm, Scene *newScene){
  SCENESYSTEM_ASSERT(sm->top < MAXSTACKSCENES && "Scene stack overflow");
  sm->scenesStack[sm->top++] = newScene;
  sceneManagerInit(sm);
}

void sceneManagerPopScene(SceneManager *sm){
  SCENESYSTEM_ASSERT(sm->top > 0 && "scene stack underflow");
  sm->top--;
  //TODO: call deinit
}

Scene *sceneManagerCurrent(SceneManager *sm){
  SCENESYSTEM_ASSERT(sm->top > 0 && "no current scene, stack is empty");
  return sm->scenesStack[sm->top-1];
}

void sceneManagerReplaceScene(SceneManager *sm, Scene *newScene){
  SCENESYSTEM_ASSERT(sm->top > 0 && "scene stack underflow");
  sm->scenesStack[sm->top-1] = newScene;
  sceneManagerCurrent(sm)->init(sm);
}

void sceneManagerInit(SceneManager *sm){
  sceneManagerCurrent(sm)->init(sm);
}

void sceneManagerUpdate(SceneManager *sm){
  sceneManagerCurrent(sm)->update(sm);
}

void sceneManagerDraw(SceneManager *sm){
  sceneManagerCurrent(sm)->draw(sm);
}

#endif

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org/>
*/
