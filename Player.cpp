#include "Player.h"
#include <iostream>

//Initializes a new player with default values
Player::Player(){
    currentLocation = "Test Room";
    health = 3;
}

//Initializes a new player with specified name and health at start of level 1
Player::Player(const int playerHealth){
    currentLocation = "Collapsed Entrance";
    health = playerHealth;
    inventory["Revolver"] = 1;
    inventory["Ammo"] = 4;
}

//Returns the player's current health
int Player::getHealth() const {
    return health;
}

//Reduces the player's health by the specified damage amount
void Player::takeDamage(int damage) {
    health -= damage;
}


//Restores the player's health to full (3) if not already at full health
void Player::heal() {
    if (health != 3) {
        health = 3;
    } else {
        std::cout << "You are already at full health!" << std::endl;
    }
}

// reutrns the player's current location
const std::string& Player::location() const{
    return currentLocation;
}

//Moves the player to a new location
void Player::moveto(const std::string& newLocation){
    currentLocation = newLocation;
}

//Adds an item to the player's inventory with the specified quantity
void Player::addItem(const std::string& itemName, int quantity) {
    inventory[itemName] += quantity;
}

//Checks if the player has a specific item in their inventory and displays the quantity
bool Player::hasItem(const std::string& itemName, int quantity) const {
    auto it = inventory.find(itemName);

    if (it != inventory.end()) {
        return it->second >= quantity;
    }

    return false;
} 

//Removes a specified quantity of an item from the player's inventory
void Player::removeItem(const std::string& itemName, int quantity) {
    if (inventory.find(itemName) != inventory.end()) {
        inventory[itemName] -= quantity;
        if (inventory[itemName] <= 0) {
            inventory.erase(itemName);
        }
    }
}

//Displays the player's current inventory
void Player::showInventory() const {
    std::cout << "Inventory:" << std::endl;
    for (const auto& pair : inventory) {
        std::cout << "- " << pair.second << " " << pair.first << std::endl;
    }
}

//Checks if the player is alive
bool Player::isAlive() const {
    return health > 0;
}