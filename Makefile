SCENESPATH = scenes/
SCENES = $(SCENESPATH)gameScene.c $(SCENESPATH)gameOverScene.c

run: build
	./bin/main

build:
	mkdir -p bin
	gcc -o ./bin/main main.c $(SCENES) -L./raylib/lib -I./raylib/include -l:libraylib.a  -lGL -lm -lpthread -ldl -lrt -lX11 -lm -ggdb
	
