#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <map>
#include <vector>

class Room {
    private:
        std::string roomName;
        std::string roomDescription;
        std::map<std::string, int> items;
        std::map<std::string, std::string> exits;
        std::map<std::string, bool> lockedExits;
        std::vector<std::string> enemies;
    public:
        Room(const std::string& roomName, const std::string& roomDescription);
        const std::string& getName() const;
        const std::string& getDescription() const;
        void describe() const;

        const std::map<std::string, int>& getItems() const;
        void addItem(const std::string& itemName, int quantity);
        void removeItem(const std::string& itemName, int quantity);

        const std::map<std::string, std::string>& getExits() const;
        void addExit(const std::string& direction, const std::string& roomName, bool isLocked) ;
        bool isExitLocked(const std::string& direction) const;
        void unlockExit(const std::string& direction);

        bool hasEnemy() const;
        void addEnemy(const std::string& enemyName);
        std::string getNextEnemy() const;
        void defeatEnemy();

};

#endif