#include "Game.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Game::Game() : player(3) {
    createWorld();
}

void Game::run() {
    std::cout << "========================================\n";
    std::cout << "     1917: THE TEXT-BASED ADVENTURE\n";
    std::cout << "========================================\n\n";

    std::cout << "Artillery explodes all around you.\n";
    std::cout << "You dive into an enemy bunker just as\n";
    std::cout << "the tunnel collapses behind you.\n\n";
    std::cout << "Find explosives and escape the bunker!\n";
    std::cout << "Type 'help' for available commands.\n";

    // Show the starting location once
    showLocation();

    while (player.isAlive() && !winConditionMet && playing) {
        std::cout << "\n> ";

        std::string command;

        if (!std::getline(std::cin, command)) {
            playing = false;
            break;
        }

        processCommand(command);
    }

    if (winConditionMet) {
        std::cout << "\n========================================\n";
        std::cout << "              VICTORY!\n";
        std::cout << "========================================\n";
        std::cout << "You blow open an escape route!\n";
        std::cout << "You return safely to friendly lines.\n";
    }
    else if (!player.isAlive()) {
        std::cout << "\nGAME OVER: You were shot dead.\n";
    }
    else {
        std::cout << "\nYou abandoned your mission.\n";
    }
}

//Creates the game world with rooms and items
//room.emplace("Room Name", "Room Description");
//room.at("Room Name").addExit("direction", "Destination Room Name", isLocked true or false);
//room.at("Room Name").addItem("Item Name", quantity);
//room.at("Room Name").addEnemy("Enemy Name");
void Game::createWorld(){
    winConditionMet = false;
    playing = true;

    //Room 1
    rooms.emplace("Collapsed Entrance", Room("Collapsed Entrance","Where you entered. It's collapsed now. \nPerhaps you could find some EXPLOSIVES and clear the way. South is the only direction you can go."));
    rooms.at("Collapsed Entrance").addExit("south", "Trench Junction 1", false);
    //Room 2
    rooms.emplace("Trench Junction 1", Room("Trench Junction 1","From here you can see 3 hallways. The collapsed trench you entered from to the North. \nA wooden hallway that has a sign that reads 'Komandant' to the East. \nA concrete hallway that has a sign that reads 'Arsenal' to the South."));
    rooms.at("Trench Junction 1").addExit("north", "Collapsed Entrance", false);
    rooms.at("Trench Junction 1").addExit("east", "Wooden Hallway 1", false);
    rooms.at("Trench Junction 1").addExit("south", "Concrete Hallway 1", false);
    //Room 3
    rooms.emplace("Wooden Hallway 1", Room("Wooden Hallway 1","From here you can see the hallway continues East or West. There are 2 rooms you can see. Both have a sign, 'Latrines' to the North, and 'Kaserne' to the South."));
    rooms.at("Wooden Hallway 1").addExit("north", "Latrines", false);
    rooms.at("Wooden Hallway 1").addExit("south", "Barracks 1", false);
    rooms.at("Wooden Hallway 1").addExit("west", "Trench Junction 1", false);
    rooms.at("Wooden Hallway 1").addExit("east", "Wooden Hallway 2", false);
    rooms.at("Wooden Hallway 1").addEnemy("German Soldier");
    //Room 4
    rooms.emplace("Latrines", Room("Latrines","A foul smelling room. Here's where the enemy made little Kaisers. South is your only exit."));
    rooms.at("Latrines").addExit("south", "Wooden Hallway 1", false);
    rooms.at("Latrines").addItem("Soiled Pants", 1);
    //Room 5
    rooms.emplace("Barracks 1", Room("Barracks 1","A room filled with hammocks and trunks. Here's where the enemy sleeps. The hallway is to the North and the barracks continues East."));
    rooms.at("Barracks 1").addExit("north", "Wooden Hallway 1", false);
    rooms.at("Barracks 1").addExit("east", "Barracks 2", false);
    rooms.at("Barracks 1").addItem("Ammo", 1);
    //Room 6
    rooms.emplace("Barracks 2", Room("Barracks 2","More beds. A toolkit is scattered across the ground. West is your only exit."));
    rooms.at("Barracks 2").addExit("west", "Barracks 1", false);
    rooms.at("Barracks 2").addItem("Wrench", 1);
    rooms.at("Barracks 2").addEnemy("German Soldier");
    //Room 7
    rooms.emplace("Wooden Hallway 2", Room("Wooden Hallway 2","The Officer's Quarters are here to the North. The door is locked and there's a note on the door. \n \n'Wenn du mich brauchst, hol dir meinen Ersatzschlüssel aus der entfernten Kaserne' \n \nYou wish you could read German. \nThe hallway ends here. You must go West."));
    rooms.at("Wooden Hallway 2").addExit("west", "Wooden Hallway 1", false);
    rooms.at("Wooden Hallway 2").addExit("north", "Officer's Quarters", true);
    //Room 8
    rooms.emplace("Officer's Quarters", Room("Officer's Quarters","The Officer's quarters. Surely something useful is in here. South is your only exit."));
    rooms.at("Officer's Quarters").addExit("south", "Wooden Hallway 2", false);
    rooms.at("Officer's Quarters").addItem("Armory Key", 1);
    rooms.at("Officer's Quarters").addItem("Ammo", 1);
    rooms.at("Officer's Quarters").addItem("Medkit", 1);
    rooms.at("Officer's Quarters").addEnemy("German Officer");
    //Room 9
    rooms.emplace("Concrete Hallway 1", Room("Concrete Hallway 1","The concrete hall continues North and South. It's surprising they had time to build this."));
    rooms.at("Concrete Hallway 1").addExit("north", "Trench Junction 1", false);
    rooms.at("Concrete Hallway 1").addExit("south", "Concrete Junction", false);
    //Room 10
    rooms.emplace("Concrete Junction", Room("Concrete Junction","A large metal gate blocks the path East. A sign reads \n \nAuf Befehl des Kommandanten ist niemandem der Zutritt gestattet.' \nThe hall continues North and South"));
    rooms.at("Concrete Junction").addExit("north", "Concrete Hallway 1", false);
    rooms.at("Concrete Junction").addExit("south", "Concrete Hallway 2", false);
    rooms.at("Concrete Junction").addExit("east", "Armory Hallway", true);
    //Room 11
    rooms.emplace("Concrete Hallway 2", Room("Concrete Hallway 2","Natural light shines in from one room to the West. A barracks is also visible South. The hallway only goes North from here."));
    rooms.at("Concrete Hallway 2").addExit("north", "Concrete Junction", false);
    rooms.at("Concrete Hallway 2").addExit("west", "Machine Gun Port", false);
    rooms.at("Concrete Hallway 2").addExit("south", "Concrete Barracks", false);
    rooms.at("Concrete Hallway 2").addEnemy("German Soldier");
    //Room 12
    rooms.emplace("Machine Gun Port", Room("Machine Gun Port","A Machine gun is fixed into position looking out a small port. It's too small to crawl through. \nYou could carry the machine gun if you had someway to unmount it. East is the only exit."));
    rooms.at("Machine Gun Port").addExit("east", "Concrete Hallway 2", false);
    rooms.at("Machine Gun Port").addItem("Ammo", 1);
    //Room 13
    rooms.emplace("Concrete Barracks", Room("Concrete Barracks","A room with cots and actual beds. Officers must sleep here. Going North will take you to the hallway."))   ;
    rooms.at("Concrete Barracks").addExit("north", "Concrete Hallway 2", false);
    rooms.at("Concrete Barracks").addItem("Ammo", 2);
    rooms.at("Concrete Barracks").addItem("Office Key", 1);
    rooms.at("Concrete Barracks").addEnemy("German Soldier");
    //room 14
    rooms.emplace("Armory Hallway", Room("Armory Hallway","The lights go out at the end of this hall to the East. I'll need something to light my path."));
    rooms.at("Armory Hallway").addExit("west", "Concrete Junction", false);
    rooms.at("Armory Hallway").addExit("east", "Armory Guard Post", true);
    //room 15
    rooms.emplace("Armory Guard Post", Room("Armory Guard Post","Extra supplies are stored here. Better make sure you're geared up before going East, to the Storeroom."))  ;
    rooms.at("Armory Guard Post").addExit("west", "Armory Hallway", false);
    rooms.at("Armory Guard Post").addExit("east", "Armory Storeroom", false);
    rooms.at("Armory Guard Post").addItem("Ammo", 1);
    rooms.at("Armory Guard Post").addItem("Medkit", 1);
    rooms.at("Armory Guard Post").addEnemy("German Soldier");
    rooms.at("Armory Guard Post").addEnemy("German Soldier");
    //room 16
    rooms.emplace("Armory Storeroom", Room("Armory Storeroom","The room has a lot of explosives stored here. I could use them to escape. I just need to go back West and North to the exit."));
    rooms.at("Armory Storeroom").addExit("west", "Armory Guard Post", false);
    rooms.at("Armory Storeroom").addItem("Explosives", 1);
    rooms.at("Armory Storeroom").addEnemy("German Stormtrooper");
}

//Displays the player's current location and room description
void Game::showLocation() const {
    const Room& currentRoom = rooms.at(player.location());

    std::cout << "\n----------------------------------------\n";
    std::cout << "LOCATION: " << currentRoom.getName() << "\n";
    std::cout << "----------------------------------------\n";

    std::cout << currentRoom.getDescription() << "\n";

    std::cout << "\nExits: ";

    bool first = true;

    for (const auto& exit : currentRoom.getExits()) {
        if (!first) {
            std::cout << ", ";
        }

        std::cout << exit.first;

        if (currentRoom.isExitLocked(exit.first)) {
            std::cout << " (locked)";
        }

        first = false;
    }

    std::cout << "\nHealth: " << player.getHealth() << "/3\n";
}

//Processes the player's input command
void Game::processCommand(const std::string& command) {
    // Convert the command to lowercase
    std::string lowerCommand = command;

    std::transform(lowerCommand.begin(), lowerCommand.end(), lowerCommand.begin(), [](unsigned char c) { return std::tolower(c); });

    if (lowerCommand == "quit") {
        std::cout << "Are you sure you want to quit? (yes/no)" << std::endl;
        std::string confirm;
        std::getline(std::cin, confirm);

        std::transform(confirm.begin(), confirm.end(), confirm.begin(), [](unsigned char c) { return std::tolower(c); });

        if (confirm == "yes") {
            playing = false;
        }
    }
    else if (lowerCommand == "inventory") {
        player.showInventory();
    }
    else if (lowerCommand == "search") {
        searchRoom();
    }
    else if (lowerCommand == "health") {
        std::cout << "Health: " << player.getHealth() << "/3" << std::endl;
    }
    else if (lowerCommand == "help") {
        showHelp();
    }
    else if (lowerCommand.rfind("move ", 0) == 0) {
        movePlayer(lowerCommand.substr(5));
    }
    else if (lowerCommand.rfind("use ", 0) == 0) {
        useItem(lowerCommand.substr(4));
    }
    else if (lowerCommand == "look") {
        showLocation();
    }
    else {
        std::cout << "Unknown command." << std::endl;
    }
}

//Moves the player to a new room based on the specified direction
void Game::movePlayer(const std::string& direction) {
    Room& currentRoom = rooms.at(player.location());

    auto exit = currentRoom.getExits().find(direction);

    if (exit == currentRoom.getExits().end()) {
        std::cout << "You can't go that way.\n";
        return;
    }

    if (currentRoom.isExitLocked(direction)) {
        std::cout << "That way is locked. You need a way to open it.\n";
        return;
    }

    std::string originalLocation = player.location();
    std::string newLocation = exit->second;

    player.moveto(newLocation);

    std::cout << "\nYou move " << direction << ".\n";

    if (rooms.at(newLocation).hasEnemy()) {
        handleCombat();

        if (player.isAlive() && rooms.at(newLocation).hasEnemy()) {
            player.moveto(originalLocation);
            std::cout << "You retreat to " << originalLocation << ".\n";
        }
    }

    // Display location after movement or retreat
    if (player.isAlive()) {
        showLocation();
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
            std::cout << "- " << item.first;
            if (item.second > 1) {
            std::cout << " x" << item.second;
            }
            std::cout << std::endl;
            player.addItem(item.first, item.second);
            currentRoom.removeItem(item.first, item.second);
        }
    }
}

//Allows the player to use an item from their inventory
void Game::useItem(const std::string& itemName){
    std::string item = itemName;

    std::transform(item.begin(), item.end(), item.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    if (!player.hasItem(itemName)) {
        std::cout << "You don't have " << itemName << "." << std::endl;
        return;
    }

    if (!player.hasItem(itemName)) {
    std::cout << "You don't have " << itemName << "." << std::endl;
    return;
    }
    Room& currentRoom = rooms.at(player.location());

    if (itemName == "revolver"){
        std::cout << "My weapon. As long as I have 'Ammo', I'll be okay." << std::endl;
    }
    else if (itemName == "ammo"){
        std::cout << "I'll need at least 1 ammo to deal any enemies I come across." << std::endl;
    }
    else if (itemName == "medkit"){
        if (player.getHealth() < 3){
            player.heal();
            player.removeItem(itemName, 1);
            std::cout << "You use the medkit and feel much better." << std::endl;
        } else {
            std::cout << "There's no need to use the medkit. Yet." << std::endl;
        }
    }
    else if (itemName == "office key"){
        if (player.location() == "Wooden Hallway 2"){
            currentRoom.unlockExit("north");
            player.removeItem(itemName, 1);
            std::cout << "You unlock the Office Door. You leave the key in the lock." << std::endl;
        } else {
            std::cout << "You can't use the Office Key here." << std::endl;
        }
    }
    else if (itemName == "armory key"){
        if (player.location() == "Concrete Junction"){
            currentRoom.unlockExit("east");
            player.removeItem(itemName, 1);
            std::cout << "You unlock the Armory Door. You should be able to find explosives in here." << std::endl;
        } else {
            std::cout << "You can't use the Armory Key here." << std::endl;
        }
    }
    else if (itemName == "soiled pants"){
        std::cout << "You search the soiled pants and find an Electric Torch. You discard the smell garment." << std::endl;
        player.addItem("Electric Torch", 1);
        player.removeItem(itemName, 1);
    }
    else if (itemName == "electric torch"){
        std::cout << "You turn on the Electric Torch. You can now see in dimly lit areas." << std::endl;
        rooms.at("Armory Hallway").unlockExit("east");
    }
    else if (itemName == "wrench"){
        if (player.location() == "Machine Gun Port"){
            std::cout << "You use the wrench to remove the Machine Gun and discard the wrench. This is some serious firepower. Better save it for when you need it." << std::endl;
            player.addItem("Machine Gun", 1);
            player.removeItem(itemName, 1);
        } else {
            std::cout << "You can't use the Wrench here." << std::endl;
        }
    }
    else if (itemName == "machine gun"){
        std::cout << "This is some serious firepower. Better save it for when you need it." << std::endl;
    }
    else if (itemName == "explosives"){
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
void Game::handleCombat() {
    Room& currentRoom = rooms.at(player.location());

    // Continue fighting while enemies remain and the player is alive
    while (currentRoom.hasEnemy() && player.isAlive()) {
        std::string enemy = currentRoom.getNextEnemy();

        std::cout << "You encounter a " << enemy << "!" << std::endl;

        // German Stormtrooper requires the Machine Gun
        if (enemy == "German Stormtrooper") {
            if (player.hasItem("Machine Gun")) {
                std::cout << "You use your Machine Gun to defeat the " << enemy << "." << std::endl;

                currentRoom.defeatEnemy();
            } else {
                std::cout << "Your revolver cannot penetrate his armor!" << std::endl;
                std::cout << "You take 1 damage." << std::endl;

                player.takeDamage(1);
                break;
            }
        }

        // German Soldier and German Officer use ammunition
        else {
            int ammoRequired = 0;

            if (enemy == "German Soldier") {
                ammoRequired = 1;
            }
            else if (enemy == "German Officer") {
                ammoRequired = 2;
            }
            else {
                std::cout << "Unknown enemy type." << std::endl;
                break;
            }

            // Check that the player has a revolver and enough ammo
            if (player.hasItem("Revolver") && player.getItemCount("Ammo") >= ammoRequired) {

                player.removeItem("Ammo", ammoRequired);
                currentRoom.defeatEnemy();

                std::cout << "You use " << ammoRequired << " ammo to defeat the " << enemy << "." << std::endl;
            }
            else {
                std::cout << "You don't have enough ammunition!" << std::endl;
                std::cout << "The " << enemy << " shoots you. You take 1 damage." << std::endl;
                player.takeDamage(1);
                break;
            }
        }
    }

    // Check if the player died during combat
    if (!player.isAlive()) {
        std::cout << "You have been defeated." << std::endl;
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
    std::cout << "- look: Examine your current location.\n";
}