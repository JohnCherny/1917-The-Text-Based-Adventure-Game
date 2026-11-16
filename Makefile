
all: linux windows

linux:
	g++ -std=c++17 Main.cpp Game.cpp Player.cpp Room.cpp -o 1917Linux

windows:
	x86_64-w64-mingw32-g++ -std=c++17 -static Main.cpp Game.cpp Player.cpp Room.cpp -o 1917Win.exe

clean:
	rm -f 1917Linux 1917Win.exe

.PHONY: all linux windows clean
