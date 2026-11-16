#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Player.h"

#include <string>
#include <map>

class Game {
    private:
        Player player; //The player object
        std::map<std::string, Room> rooms; //A map to store the rooms in the game world
        bool playerAlive; //Flag to track if the player is alive
        bool winConditionMet; //Flag to track if the win condition has been met
        bool playing; //Flag to track if the game is still being played

        void createWorld(); //Creates the game world with rooms and items
        void showLocation() const; //Displays the player's current location and room description
        void processCommand(const std::string& command); //Processes the player's input command

        void movePlayer(const std::string& direction); //Moves the player to a new room based on the specified direction
        void searchRoom(); //Allows the player to search the current room for items
        void useItem(const std::string& itemName); //Allows the player to use an item from their inventory
        void handleCombat(); //Handles combat with enemies in the current room
        void showHelp() const; //Displays a list of available commands and their descriptions
        
    public:
        Game();
        void run(); //Starts the game loop
};

#endif