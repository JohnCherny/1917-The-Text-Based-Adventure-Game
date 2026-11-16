#include "Game.h"
#include "Player.h"
#include "Room.h"
#include <iostream>

Game::Game() : player(3) {
    createWorld();
}

void Game::run() {
    std::cout << "1917: The Text-Base Adventure Game" << std::endl;
    std::cout << "The screeching sound of artillery is exloding all around you." << std::endl;
    std::cout << "You're force to dive into an enemy bunker and not a moment too soon." << std::endl;
    std::cout << "The Tunnel collapses behind you as you stand and shake the dust from your coat." << std::endl;
    std::cout << "Type 'help' for a list of commands." << std::endl;

    while (player.isAlive() && !winConditionMet && playing) {
        showLocation();
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        processCommand(command);
    }

    if (winConditionMet) {
    std::cout << "You blow open an escape route! You leave the bunker and return to friendly lines." << std::endl;
    }
    else if (!player.isAlive()) {
    std::cout << "You were shot dead. Game over." << std::endl;
    }
    else {
    std::cout << "You abandoned your mission." << std::endl;
    }
}

//Creates the game world with rooms and items
void Game::createWorld(){
    winConditionMet = false;
    playerAlive = true;
    playing = true;
}

//Displays the player's current location and room description
void Game::showLocation() const{
    std::cout << "You are in " << player.location() << std::endl;
    std::cout << rooms.at(player.location()).getDescription() << std::endl;
}

//Processes the player's input command
void Game::processCommand(const std::string& command) {
    if (command == "quit") {
        std::cout << "Are you sure you want to quit? (yes/no)" << std::endl;
        std::string confirm;
        std::getline(std::cin, confirm);
        if (confirm == "yes") {
            playing = false;
        }
    }
    else if (command == "inventory") {
        player.showInventory();
    }
    else if (command == "search") {
        searchRoom();
    }
    else if (command == "health") {
    std::cout << "Health: " << player.getHealth() << "/3" << std::endl;
}
    else if (command == "help") {
        showHelp();
    }
    else if (command.rfind("move ", 0) == 0) {
        movePlayer(command.substr(5));
    }
    else if (command.rfind("use ", 0) == 0) {
        useItem(command.substr(4));
    }
    else {
        std::cout << "Unknown command.\n";
    }
}

//Moves the player to a new room based on the specified direction
void Game::movePlayer(const std::string& direction) {
    Room& currentRoom = rooms.at(player.location());

    auto exit = currentRoom.getExits().find(direction);

    if (exit == currentRoom.getExits().end() || exit->second == "") {
        std::cout << "You can't go that way." << std::endl;
        return;
    }

    if (currentRoom.isExitLocked(direction)) {
        std::cout << "That way is locked. You need to use something to pass." << std::endl;
        return;
    }

    std::string originalLocation = player.location();
    std::string newLocation = exit->second;

    player.moveto(newLocation);
    std::cout << "You move " << direction << " to " << newLocation << "." << std::endl;

    if (rooms[newLocation].hasEnemy()) {
        handleCombat();

        if (rooms[newLocation].hasEnemy()) {
            player.moveto(originalLocation);
            std::cout << "You retreat to " << originalLocation << "." << std::endl;
        }
    }
}

//Allows the player to search the current room for items
void Game::searchRoom(){
    Room& currentRoom = rooms.at(player.location());
    const std::map<std::string, int> items = currentRoom.getItems();
    if (items.empty()){
        std::cout << "You don't see anything of interest." << std::endl;
    } else {
        std::cout << "You see the following items and place them in your inventory:" << std::endl;
        for (const auto& item : items){
            std::cout << "- " << item.first << std::endl;
            player.addItem(item.first, item.second);
            currentRoom.removeItem(item.first, item.second);
        }
    }
}

//Allows the player to use an item from their inventory
void Game::useItem(const std::string& itemName){
    if (!player.hasItem(itemName)) {
    std::cout << "You don't have " << itemName << "." << std::endl;
    return;
    }
    Room& currentRoom = rooms.at(player.location());

    if (itemName == "Revolver"){
        std::cout << "My weapon. As long as I have 'Ammo', I'll be okay." << std::endl;
    }
    else if (itemName == "Ammo"){
        std::cout << "I'll need at least 1 ammo to deal any enemies I come across." << std::endl;
    }
    else if (itemName == "Medkit"){
        if (player.getHealth() < 3){
            player.heal();
            player.removeItem(itemName, 1);
            std::cout << "You use the medkit and feel much better." << std::endl;
        } else {
            std::cout << "There's no need to use the medkit. Yet." << std::endl;
        }
    }
    else if (itemName == "Office Key"){
        if (player.location() == "Wooden Hallway 2"){
            currentRoom.unlockExit("north");
            player.removeItem(itemName, 1);
            std::cout << "You unlock the Office Door. You leave the key in the lock." << std::endl;
        } else {
            std::cout << "You can't use the Office Key here." << std::endl;
        }
    }
    else if (itemName == "Armory Key"){
        if (player.location() == "Concrete Junction"){
            currentRoom.unlockExit("east");
            player.removeItem(itemName, 1);
            std::cout << "You unlock the Armory Door. You should be able to find explosives in here." << std::endl;
        } else {
            std::cout << "You can't use the Armory Key here." << std::endl;
        }
    }
    else if (itemName == "Soiled Pants"){
        std::cout << "You search the soiled pants and find an Electric Torch. You discard the smell garment." << std::endl;
        player.addItem("Electric Torch", 1);
        player.removeItem(itemName, 1);
    }
    else if (itemName == "Electric Torch"){
        std::cout << "You turn on the Electric Torch. You can now see in dimly lit areas." << std::endl;
    }
    else if (itemName == "Wrench"){
        if (player.location() == "Machine Gun Port"){
            std::cout << "You use the Wrench to remove the debris blocking the exit. You can now leave the building." << std::endl;
            currentRoom.unlockExit("north");
            player.removeItem(itemName, 1);
        } else {
            std::cout << "You can't use the Wrench here." << std::endl;
        }
    }
    else if (itemName == "Machine Gun"){
        std::cout << "This is some serious firepower. Better save it for when you need it." << std::endl;
    }
    else if (itemName == "Explosives"){
        if (player.location() == "Collapsed Entrance"){
            std::cout << "You place the explosives at the collapsed entrance." << std::endl;
            player.removeItem(itemName, 1);
            winConditionMet = true;
        }
        else {
            std::cout << "Go back to the collapsed entrance to use these." << std::endl;
        }
    }
    else {
        std::cout << "You don't know how to use that item." << std::endl;
    }
}

//Handles combat with enemies in the destination room
void Game::handleCombat(){
    if (rooms.at(player.location()).hasEnemy()){
        std::string enemy = rooms.at(player.location()).getNextEnemy();
        std::cout << "You encounter a " << enemy << "!" << std::endl;
        if (player.hasItem("Revolver") && player.hasItem("Ammo")){
            std::cout << "You use your revolver to defeat the " << enemy << "." << std::endl;
            player.removeItem("Ammo", 1);
            rooms.at(player.location()).defeatEnemy();
        } else {
            std::cout << "You don't have a weapon or ammo to fight the " << enemy << ". You take damage." << std::endl;
            player.takeDamage(1);
            if (!player.isAlive()){
                playerAlive = false;
                std::cout << "You have been defeated by the " << enemy << "." << std::endl;
            }
        }
    }
}

//Displays a list of available commands and their descriptions
void Game::showHelp() const{
    std::cout << "Available commands:" << std::endl;
    std::cout << "- move <direction>: Move to a new room in the specified direction (north, south, east, west)." << std::endl;
    std::cout << "- search: Search the current room for items." << std::endl;
    std::cout << "- use <item>: Use an item from your inventory." << std::endl;
    std::cout << "- inventory: Show your current inventory." << std::endl;
    std::cout << "- health: Show your current health." << std::endl;
    std::cout << "- help: Show this list of available commands." << std::endl;
}