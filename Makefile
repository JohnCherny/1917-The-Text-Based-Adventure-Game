
all: linux windows

linux:
	g++ -std=c++17 Main.cpp Game.cpp Player.cpp Room.cpp -o adventure

windows:
	x86_64-w64-mingw32-g++ -std=c++17 Main.cpp Game.cpp Player.cpp Room.cpp -o adventure.exe

clean:
	rm -f adventure adventure.exe
