#include "Room.h"
#include <iostream>

//Initializes a new room with the specified name and description
Room::Room(const std::string& roomName, const std::string& roomDescription){
    this->roomName = roomName;
    this->roomDescription = roomDescription;
}

//Returns the name of the room
const std::string& Room::getName() const {
    return roomName;
}

//Returns the description of the room
const std::string& Room::getDescription() const {
    return roomDescription;
}

//Prints the room's name and description to the console
void Room::describe() const {
    std::cout << "You are in the " << roomName << "." << std::endl;
    std::cout << roomDescription << std::endl;
}   

//Returns a constant reference to the map of items in the room
const std::map<std::string, int>& Room::getItems() const {
    return items;
}

//Adds an item to the room's item map with the specified quantity
void Room::addItem(const std::string& itemName, int quantity) {
    items[itemName] += quantity;
}
//Removes a specified quantity of an item from the room's item map
void Room::removeItem(const std::string& itemName, int quantity){
    if (items.find(itemName) != items.end()) {
        items[itemName] -= quantity;
        if (items[itemName] <= 0) {
            items.erase(itemName);
        }
    }
}

//Returns a constant reference to the map of exits in the room
const std::map<std::string, std::string>& Room::getExits() const {
    return exits;
}

//Adds an exit to the room's exit map with the specified direction and room name, and optionally locks the exit
void Room::addExit(const std::string& direction, const std::string& roomName, bool isLocked) {
    exits[direction] = roomName;
    lockedExits[direction] = isLocked;
}

//Checks if the exit in the specified direction is locked
bool Room::isExitLocked(const std::string& direction) const {
    auto it = lockedExits.find(direction);

    if (it != lockedExits.end()) {
        return it->second;
    }

    return false;
}

//Unlocks the exit in the specified direction
void Room::unlockExit(const std::string& direction) {
    auto it = lockedExits.find(direction);

    if (it != lockedExits.end()) {
        it->second = false;
    }
}

//Checks if there are any enemies in the room
bool Room::hasEnemy() const{
    return !enemies.empty();
}

//Returns the name of the next enemy in the room, or an empty string if there are no enemies
std::string Room::getNextEnemy() const{
    if (!enemies.empty()) {
        return enemies.back();
    }
    return "";
}

//Removes the next enemy from the room's enemy vector
void Room::defeatEnemy(){
    if (!enemies.empty()) {
        enemies.pop_back();
    }
}
