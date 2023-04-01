all:
	g++ -I src/headers -I src/include -L src/lib -o bin/main src/compile/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	.\bin\main.exe

debugvscode:
	make clean
	g++ -I src/headers -I src/include -L src/lib -o bin/main src/compile/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
build:
	g++ -I src/headers -I src/include -L src/lib -o bin/main src/compile/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows
clean:
	del ".\bin\main.exe"
	