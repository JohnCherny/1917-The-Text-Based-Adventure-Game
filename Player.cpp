#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cctype>

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
bool Player::hasItem(const std::string& itemName) const {
    std::string searchName = itemName;

    std::transform(searchName.begin(), searchName.end(), searchName.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    for (const auto& item : inventory) {
        std::string inventoryName = item.first;

        std::transform(inventoryName.begin(), inventoryName.end(), inventoryName.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            });

        if (inventoryName == searchName) {
            return true;
        }
    }

    return false;
}

//returns the quantity of a specific item in the player's inventory
int Player::getItemCount(const std::string& itemName) const {
    std::string searchName = itemName;

    std::transform(searchName.begin(), searchName.end(), searchName.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    for (const auto& item : inventory) {
        std::string inventoryName = item.first;

        std::transform(inventoryName.begin(), inventoryName.end(), inventoryName.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            });

        if (inventoryName == searchName) {
            return item.second;
        }
    }

    return 0;
}


//Removes a specified quantity of an item from the player's inventory
// Removes a specified quantity of an item from the player's inventory
void Player::removeItem(const std::string& itemName, int quantity) {
    std::string searchName = itemName;

    std::transform(searchName.begin(), searchName.end(), searchName.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        std::string inventoryName = it->first;

        std::transform(inventoryName.begin(), inventoryName.end(), inventoryName.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            });

        if (inventoryName == searchName) {
            it->second -= quantity;

            if (it->second <= 0) {
                inventory.erase(it);
            }

            return;
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