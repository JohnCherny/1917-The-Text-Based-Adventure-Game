all:
	g++ -std=c++17 Main.cpp Game.cpp Player.cpp Room.cpp -o adventure

clean:
	rm -f adventure