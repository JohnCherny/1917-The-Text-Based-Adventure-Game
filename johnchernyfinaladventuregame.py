def render_introduction():
    '''
    Create the message to be displayed at the start of your game.

    Returns:
        str: The introductory text of your game to be displayed.
    '''
    text = " 1917: The Text-Base Adventure Game \n By: John Cherny \n \n The screeching sound of artillery is exloding all around you. \n You're force to dive into an enemy bunker and not a moment too soon. \n The Tunnel collapses behind you as you stand and shake the dust from your coat.\n \n \nType 'help' for a list of commands.\n"
    return text

def create_world():
    '''
    Creates a new version of the world in its initial state.

    Returns:
        World: The initial state of the world
    '''
    world_dict1 = {
        "map" : create_map(),
        "player" : create_player(),
        "status" : "playing"
        }
    return world_dict1

def create_map():
    """creates a dictionary of locations. Includes name, description, items, and enemies"""
    map_dictionary = {
        "Collapsed Entrance" : {
            'neighbors' : {'south' : 'Trench Junction',},
            'locked path' : {},
            'about' : "Where you entered. It's collapsed now. \nPerhaps you could find some EXPLOSIVES and clear the way. South is the only direction you can go.",
            'items' : [],
            'enemy' : [],
            },
        'Trench Junction' : {
            'neighbors' : {'north' : 'Collapsed Entrance', 'east' : 'Wooden Hallway 1', 'south' : 'Concrete Hall 1'},
            'about' : "From here you can see 3 hallways. The collapsed trench you entered from to the North. \n A wooden hallway that has a sign that reads 'Komandant' to the East. \n A concrete hallway that has a sign that reads 'Arsenal' to the South.",
            'locked path' : {},
            'items' : [],
            'enemy' : [],
            },
        'Wooden Hallway 1' : {
            'neighbors': {'west' : 'Trench Junction','north' : 'Latrines', 'south' : 'Wooden Barracks 1', 'east' : 'Wooden Hallway 2'},
            'about' : "From here you can see the hallway continues East or West. There are 2 rooms you can see. Both have a sign, 'Latrines' to the North, and 'Kaserne' to the South.",
            'locked path' : {},
            'items' : [],
            'enemy' : ['Soldier'],
            },
        'Latrines' : {
            'neighbors': {'south' : 'Wooden Hallway 1'},
            'about' : "A foul smelling room. Here's where the enemy made little Kaisers. South is your only exit.",
            'locked path' : {},
            'items' : {"Soiled Pants" : 1},
            'enemy' : [],
            },
        'Wooden Barracks 1' : {
            'neighbors': { 'north' : 'Wooden Hallway 1', 'east' : 'Wooden Barracks 2'},
            'about' : "A room filled with hammocks and trunks. Here's where the enemy sleeps. The hallway is to the North and the barracks continues East.",
            'locked path' : {},
            'items' : {'Ammo' : 1},
            'enemy' : [],
            },
        'Wooden Barracks 2' : {
            'neighbors': {'west' : 'Wooden Barracks 1'},
            'about' : "More beds. A toolkit is scattered across the ground. West is your only exit.",
            'locked path' : {},
            'items' : {'Wrench' : 1},
            'enemy' : ['Soldier'],
            },
        'Wooden Hallway 2' : {
            'neighbors': {'west' :'Wooden Hallway 1', 'north' : "Officer's Room"},
            'locked path' : { 'north' : True},
            'about' : "The Officer's Quarters are here to the North. The door is locked and there's a note on the door. \n \n 'Wenn du mich brauchst, hol dir meinen Ersatzschlüssel aus der entfernten Kaserne' \n \n You wish you could read German. \nThe hallway ends here. You must go West.",
            'items' : [],
            'enemy' : [],
            },
        "Officer's Room" : {
            'neighbors': {'south' : 'Wooden Hallway 2'},
            'about' : "The Officer's quarters. Surely something useful is in here. South is your only exit.",
            'locked path' : {},
            'items' : {'Armory Key' : 1, 'Ammo' : 2, 'Medkit' : 1},
            'enemy' : ['Officer'],
            },
        'Concrete Hall 1' : {
            'neighbors': {'north' : 'Trench Junction', 'south' : 'Concrete Hall Junction'},
            'about' : "The concrete hall continues North and South. It's surprising they had time to build this.",
            'locked path' : {},
            'items' : [],
            'enemy' : [],
            },
        'Concrete Hall Junction' : {
            'neighbors': {'north' : 'Concrete Hall 1', 'east' : 'Armory Hallway', 'south' : 'Concrete Hall 2'},
            'about' : "A large metal gate blocks the path East. A sign reads \n \n Auf Befehl des Kommandanten ist niemandem der Zutritt gestattet.' \nThe hall continues North and South",
            'locked path' : { 'east' : True},
            'items' : [],
            'enemy' : [],
            },
        'Armory Hallway' : {
            'neighbors': {'west' : 'Concrete Hall Junction', 'east' : 'Armory Guard Post'},
            'locked path' : { 'east' : True},
            'about' : "The lights go out at the end of this hall to the East. I'll need something to light my path.",
            'items' : [],
            'enemy' : [],
            },
        'Armory Guard Post' : {
            'neighbors': {'west' : 'Armory Hallway', 'east' :'Storeroom'},
            'about' : "Extra supplies are stored here. Better make sure you're geared up before going East, to the Storeroom.",
            'locked path' : {},
            'items' : {'Ammo' : 2, 'Medkit' : 1},
            'enemy' : ['Soldier', 'Soldier'],
            },
        'Storeroom' : {
            'neighbors': {'west' : 'Armory Guard Post'},
            'about' : "The room has a lot of explosives stored here. I could use them to escape. I just need to go back West and North to the exit.",
            'locked path' : {},
            'items' : {'Explosives' : 1},
            'enemy' : ['Stormtrooper'],
            },
        'Concrete Hall 2' : {
            'neighbors': {'north' : 'Concrete Hall Junction', 'west' : 'Machine Gun Position', 'south' : 'Concrete Barracks'},
            'about' : "Natural light shines in from one room to the West. A barracks is also visible South. The hallway only goes North from here.",
            'locked path' : {},
            'items' : [],
            'enemy' : ['Soldier'],
            },
        'Machine Gun Position' : {
            'neighbors': {'east' : 'Concrete Hall 2'},
            'about' : "A Machine gun is fixed into position looking out a small port. It's too small to crawl through. \n You could carry the machine gun if you had someway to unmount it. East is the only exit.",
            'locked path' : {},
            'items' : {'Ammo' : 1}, #machine gun is here, need to use wrench here to gain machine gun
            'enemy' : [],
            },
        'Concrete Barracks' : {
            'neighbors': {'north' : 'Concrete Hall 2'},
            'about' : "A room with cots and actual beds. Officers must sleep here. Going North will take you to the hallway.",
            'locked path' : {},
            'items' : {'Ammo' : 2, "Office Key" : 1},
            'enemy' : ['Soldier'],
            },
        }
    return map_dictionary 

def create_player():
    """creates player dictionary . include inventory, current location, and health"""
    player_dictionary = {
        'location' : 'Collapsed Entrance',
        'inventory' : {'Revolver' : 1, 'Ammo': 4}, # ,'medkit' : 1, 'Wrench' : 1, 'Explosives': 1, 'Armory Key' : 1, "Office Key" : 1, 'Electric Torch' : 1},
        'health' : 3,
        }
    return player_dictionary 

def render_location(world):
    """access player's location from dictionary then looks up that location in world dicotnary"""
    health_check(world,world['player']['health'])
    location = world['player']['location']
    here = world['map'][location]
    about = here['about']
    health = health_check(world,world['player']['health'])
    ammo_count = world['player']['inventory']['Ammo']
    
    text = "You are in " + location + "\n" + about + "\n"
    
    #checks for enemy, if enemy but no ammo take 1 damage, if ammo and enemy, enemy is killed and removed
    if here['enemy']:
        for enemy in here['enemy']:
            if enemy == 'Soldier':
                if ammo_count > 0:
                    world['player']['inventory']['Ammo'] -= 1
                    text = text + f'\n\nYou stumble upon a {enemy} and shoot him.'
                    here["enemy"].remove("Soldier")
                    return text
                else:
                    text = text + f'\n\nYou stumble upon a {enemy} and he shoots you.\nYou took 1 damage. Better search for some Ammo.'
                    world['player']['health'] -= 1
                    return text
                    health_check(world,world['player']['health'])
            if enemy == 'Officer':
                if ammo_count > 1:
                    world['player']['inventory']['Ammo'] -= 2
                    text = text + f'\n\nYou stumble upon a {enemy} and shoot him.'
                    here["enemy"].remove("Officer")
                    return text
                else:
                    text = text + f"\n\nYou stumble upon a {enemy} and he shoots you.\nYou took 1 damage. \nYou're forced to retreat. Better search for more Ammo.\n--------------------------------"
                    world['player']['location'] = 'Wooden Hallway 2'
                    world['player']['health'] -= 1
                    print(text)
                    health_check(world,world['player']['health'])
                    return render_location(world)
            if enemy == 'Stormtrooper':
                if 'Machine Gun' in world['player']['inventory']:
                    if world['player']['inventory']['Machine Gun'] == 1:
                        text = text + f"\n\nThere is a {enemy} with metal armor and a big gun.\n\nYou level your machine gun right at the {enemy}'s chest.\nYou pull the trigger and hail of bullets rips right through his armor."
                        here["enemy"].remove("Stormtrooper")
                        return text
                else:
                    text = text + f"\n\n.There is a {enemy} with metal armor and a big gun. You shoot your revolver at him but your bullets plink of his armor harmlessly. He shoots a brust of bullets at you and you're forced to retreat. You took 1 damage.\n--------------------------------"
                    world['player']['location'] = 'Armory Guard Post'
                    world['player']['health'] -= 1
                    print(text)
                    health_check(world,world['player']['health'])
                    return render_location(world)
    else:
        text = text + health
        return text
    
def health_check(world, health):
    """Takes in the player's health number and returns a diegetic statement describing their state to the player. If health = 0, game over."""
    if health == 2:
        return "You are slightly injured"
    elif health == 1:
        return "You are very injured. One more wrong move could mean your death."
    elif health == 3:
        return "You're as healthy as you can be."
    else:
        world['status'] = 'lost'
        return "You are dead."

def render(world):
    '''
    Consumes a world and produces a string that will describe the current state
    of the world. Does not print.

    Args:
        world (World): The current world to describe.

    Returns:
        str: A textual description of the world.
    '''
    text = render_location(world)
    return text
    

def get_options(world):
    '''
    Consumes a world and produces a list of strings representing the options
    that are available to be chosen given this state.

    Args:
        world (World): The current world to get options for.

    Returns:
        list[str]: The list of commands that the user can choose from.
    '''
    commands = ['quit', 'move south','move north', 'move east', 'move west', 'search', 'inventory', 'use', 'help',]
    return commands

def update(world, command):
    '''
    Consumes a world and a command and updates the world according to the
    command, also producing a message about the update that occurred. This
    function should modify the world given, not produce a new one.

    Args:
        world (World): The current world to modify.

    Returns:
        str: A message describing the change that occurred in the world.
    '''
    command = command.strip().lower()
    if command == 'quit':
        world['status'] = 'quit'
        return "You quit the game."
    elif command.startswith('move'):
        return move(world,command)
    elif command == "inventory":
        return inventory(world, command)
    elif command == "search":
        return search(world, command)
    elif command == "help":
        return help(world, command)
    elif command.startswith("use"):
        #print(command)
        return use(world, command)
    return "Unknown command: " + command

def move(world, command):
    """When given a 'move' command: This function checks current player's location. Sees if movement is valid, Then returns the movement and updates location of player."""
    command = command.lower()
    direction = command[len('move'):].strip()
    current_location = world['player']['location']
    valid_moves = world['map'][current_location]['neighbors']
    lockedpath = world['map'][current_location]['locked path']
    
    if direction in lockedpath and lockedpath[direction]:
        return "That way is locked. You need to use something to pass."
    
    if direction in valid_moves:
        world['player']['location'] = valid_moves[direction]
        return "You move " + direction + " to " + valid_moves[direction]
    else:
        return "You can't go that way."

def inventory(world, command):
    """Used for displaying the inventory."""
    inventory = world['player']['inventory']
    text = ["You are carrying:"]
    if inventory:
        for item, amount in inventory.items():
            if amount > 1 or amount == 0 :
                text.append(f" {item} (x{amount})")
            else:
                text.append(f" {item}")
    return "\n".join(text)

def search(world, command):
    """Used to search a room for items then adds those items to the player's inventory. Deletes the items from the room."""
    location = world['player']['location']
    room = world['map'][location]
    items = room['items']
    if items:
        for item in items:
            if item in world['player']['inventory']:
                world['player']['inventory'][item] += 1
            else:
                world['player']['inventory'][item] = 1
        room['items'] = []
        return "You found and took: " + ",".join(items)
    else:
        return "You search but found nothing."

def use(world, command):
    """Used for the player wanting to use an item in the room they're standing in.
    Checks if item is medkit and then uses the medkit.checks the room if it's a key item.
    """
    item_input = command[len("use"):].strip().lower()
    inventory = world['player']['inventory']
    location = world['player']['location']
    inv_item = None
    #debug commands
    #print("Player inventory:", inventory)
    #print("Trying to use:", item_input)
    #ignore case to match command item to inventory item
    for i in inventory:
        if i.lower() == item_input:
            inv_item = i
            break
    #itterates through all item options and returns text, uses the item, or checks location then uses item
    if inv_item:
        #print(inv_item)
        # userevolver
        if inv_item.lower() == "revolver":
            return "My weapon. As long as I have 'Ammo', I'll be okay."
        #use ammo
        elif inv_item.lower() == "ammo":
            return "I'll need at least 1 ammo to kill any enemies I come across."
        #use medkit and heal
        elif inv_item.lower() == "medkit":
            health = world['player']['health']
            if health != 3:
                world['player']['health'] = 3
                inventory['medkit'] -= 1
                if inventory['medkit'] == 0:
                    del inventory['medkit']
                return "You use the medkit and feel much better."
            else:
                return "There's no need to use the medkit. Yet."
        #use wrench and gain machine gun item in mg-port
        elif inv_item.lower() == "wrench":
            if location == 'Machine Gun Position':
                inventory['Machine Gun'] = 1
                del inventory['Wrench']
                return "You use the wrench to remove the Machine Gun and discard the wrench. This is some serious firepower. Better save it for when you need it."
            #use pants to gain torch
        elif inv_item.lower() == "soiled pants":
            inventory['Electric Torch'] = 1
            del inventory['Soiled Pants']
            return "You found an Electric Torch in the pants. You discard the smelly garment."
        #use torch to turn it on
        elif inv_item.lower() == "electric torch":
            world['map']['Armory Hallway']['locked path']['east'] = False
            return "You turn on the Electric Torch"
            #use office key to unlock officer's room
        elif inv_item.lower() == "office key":
            if location == 'Wooden Hallway 2':
                world['map']['Wooden Hallway 2']['locked path']['north'] = False
                del inventory['Office Key']
                return "You unlock the Office Door. You leave the key in the lock."
            else:
                return "You can't unlock the door from here."
            #use armory key to unlock armory in concrete junction
        elif inv_item.lower() == "armory key":
            if location == 'Concrete Hall Junction':
                world['map']['Concrete Hall Junction']['locked path']['east'] = False
                del inventory['Armory Key']
                return "You unlock the Armory Gate. You should be able to find explosives in here."
            else:
                return "You can't unlock the door from here."
            #use explosives to win the game at collapsed entrance
        elif inv_item.lower() == "explosives":
            #print(location)
            if location == 'Collapsed Entrance':
                world['status'] = 'won'
                return "You place the explosives at the collapsed entrance."
            else:
                return "Go back to the start and use these to escape."
            #machine gun item
        elif inv_item.lower() == "machine gun":
            return "You'll know when to use this."
                
        else:
            return f"You try to use the {inv_item}, but nothing happens."
    else:
        return "You don't have that item."

def help(world, command):
    """Used to print out vaild commands. Assist the player with information of the current goal."""
    print("You can:")
    options = ['quit', 'help', 'move "direction"', 'search', 'use "item name"', 'inventory']
    option = 0
    for i in options:
        print("- " + options[option])
        option = option + 1
    pass


def render_ending(world):
    '''
    Create the message to be displayed at the end of your game.

    Args:
        world (World): The final world state to use in describing the ending.

    Returns:
        str: The ending text of your game to be displayed.
    '''
    if world['status'] == 'won':
        return "You blow open an escape route! You leave the bunker and return to friendly lines."
    elif world['status'] == 'lost':
        return "You were shot dead. Game over."
    elif world['status'] == 'quit':
        return "You quit."

def choose(options):
    '''
    Consumes a list of commands, prints them for the user, takes in user input
    for the command that the user wants (prompting repeatedly until a valid
    command is chosen), and then returns the command that was chosen.

    Note:
        Use your answer to Programming Problem #42.3

    Args:
        options (list[str]): The potential commands to select from.

    Returns:
        str: The command that was selected by the user.
    '''
    option = 0
    userinput = ""
    inputs = options
    #print("You can:")
    #for i in options:
        #print("- " + options[option])
        #option = option + 1
    print("------------------------------")
    userinput = input("What will you do? \n")
    userinput = userinput.lower()
    print("------------------------------")
    return userinput

############# Main Function ##############
# Do not modify anything below this line #
##########################################
def main():
    '''
    Run your game using the Text Adventure console engine.
    Consumes and produces nothing, but prints and indirectly takes user input.
    '''
    print(render_introduction())
    world = create_world()
    while world['status'] == 'playing':
        print(render(world))
        options = get_options(world)
        command = choose(options)
        print(update(world, command))
    print(render_ending(world))

if __name__ == '__main__':
    main()
