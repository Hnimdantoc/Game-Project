all:
	windres src/resources/resources.rc -O coff -o src/resources/resources.res
	g++ -I src/headers -I src/include -L src/lib -o bin/main src/compile/*.cpp src/resources/resources.res -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
debugvscode:
	make clean
	g++ -I src/headers -I src/include -L src/lib -o bin/main src/compile/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
build:
	g++ -I src/headers -I src/include -L src/lib -o bin/main src/compile/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows
clean:
	del ".\bin\main.exe"
	