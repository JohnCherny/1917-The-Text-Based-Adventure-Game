#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>

class Player {
    private:
        std::string currentLocation;
        int health;
        std::map<std::string, int> inventory; //Inventory uses a map to store item names and their quantities
    public:
        Player();
        Player(const int playerHealth);
        int getHealth() const;
        void takeDamage(int damage);
        void heal();

        const std::string& location() const;
        void moveto(const std::string& newLocation);

        void addItem(const std::string& itemName, int quantity);
        bool hasItem(const std::string& itemName) const;
        int getItemCount(const std::string& itemName) const;
        void removeItem(const std::string& itemName, int quantity);
        void showInventory() const;
        bool isAlive() const;
};
#endif