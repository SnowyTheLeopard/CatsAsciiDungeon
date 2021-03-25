#include "GameCore.h"
#include "CommandParser.h"
#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

RoomData createRoom(bool hasSKey, bool hasOKey, bool hasMap, bool hasCSword, bool hasESword, const string& inName, const string& inDesc) {
	RoomData room = {};
	room.hasSilverKey = hasSKey;
	room.hasObsidianKey = hasOKey;
	room.hasMap = hasMap;
	room.hasCSword = hasCSword;
	room.hasESword = hasESword;
	room.roomName = inName;
	room.roomDesc = inDesc;
	return room;
}

void addExit(RoomData& roomToEdit, const string& exitName, int targetRoomIndex, bool isLockedS, bool isLockedO, bool isLockedM) {
	RoomExit exit = {};
	exit.Name = exitName;
	exit.targetRoomIndex = targetRoomIndex;
	exit.lockedS = isLockedS;
	exit.lockedO = isLockedO;
	exit.lockedM = isLockedM;
	roomToEdit.Exits.push_back(exit);
}

void InitializeGame(PlayerState& playerState, WorldState& worldState)
{
	worldState.nikolaiAlive = true;
	worldState.iceDragonAlive = true;
	srand(time(NULL));
	playerState.currentRoomIndex = 0;
	playerState.WantsToLook = true;
	char heroName[255]; // Yes I know there isn't validation. You can totally name your character ff2052
	cout << "Be warned, input is case sensitive.\nWhat is thy name, hero?\n> ";
	cin.getline(heroName, 255);
	playerState.name = heroName;
	printf("Adventure ommand List: look, quit, go [<exit name>], get [key, map, sword], sleep\nCombat command list: attack, ice, fireball, heal\n");
	cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
	// Welcome to hell. This took ages to type out.
	// room 0
	RoomData LunaHouse = createRoom(0, 0, 0, 1, 0, "Luna's House", "You find yourself in a warm house. There is a door going outside and a door to the basement. Luna is sitting in a chair reading a book.\nLuna: \"Normally, I'd deal with an evil sorcerer myself, but I know you wanted a quest. Find and defeat Nikolai.\"");
	addExit(LunaHouse, "basement", 1, false, false, 0);
	addExit(LunaHouse, "outside", 2, false, false, 0);
	LunaHouse.roomPosition = {0, 0};
	LunaHouse.roomMap =
		"####.#######"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"########.###";
	worldState.Rooms.push_back(LunaHouse);
	// room 1
	RoomData LunaBasement = createRoom(1, 0, 0, 0, 0, "Luna's Basement", "You find yourself in a cold basement. There is a door going back up to the rest of the house.");
	addExit(LunaBasement, "upstairs", 0, false, false, 0);
	LunaBasement.roomPosition = { 0, -1 };
	LunaBasement.roomMap =
		"########.###"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(LunaBasement);
	// room 2
	RoomData MysticValley = createRoom(0, 0, 0, 0, 0, "Mystic Valley", "You find yourself in a beautiful valley. There is a house here and a path going off towards the Orange Plains.");
	addExit(MysticValley, "inside", 0, false, false, 0);
	addExit(MysticValley, "plains", 3, false, false, 0);
	MysticValley.roomPosition = { 0, 1 };
	MysticValley.roomMap =
		"########.###"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"####.#######";
	worldState.Rooms.push_back(MysticValley);
	// room 3
	RoomData Cross1 = createRoom(0, 0, 0, 0, 0, "Mystic Valley Crossroads", "You find yourself at a crossroads in the Mystic Valley. There is a path going into the Mystic Valley, a path headed into the town of Elgard, and a path towards the Orange Plains.");
	addExit(Cross1, "valley", 2, false, false, 0);
	addExit(Cross1, "elgard", 4, 0, 0, 0);
	addExit(Cross1, "plains", 6, 0, 0, 0);
	Cross1.roomPosition = { 0, 2 };
	Cross1.roomMap =
		"######.#####"
		"#..........#"
		"#..........#"
		"...........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"########.###";
	worldState.Rooms.push_back(Cross1);
	// room 4
	RoomData Elgard = createRoom(0, 0, 0, 0, 0, "Elgard Square", "You are in the main square of the town of Elgard. There is a library, a number of houses and other buildings, and the path to the crossroads");
	addExit(Elgard, "library", 5, 0, 0, 0);
	addExit(Elgard, "crossroads", 3, 0, 0, 0);
	Elgard.roomPosition = { -1, 2 };
	Elgard.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"#..........."
		"#..........#"
		"...........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(Elgard);
	// room 5
	RoomData ELibrary = createRoom(0, 0, 0, 0, 0, "Elgard Library", "You are in the Elgard library. After some reading, you determine you should go north through the Orange Plains towards Blackwater Fen to reach the town of Derleth, where you may find more information on how to defeat Nikolai. You also determine there may be a helpful artifact somewhere on Geshtop Plateau, but can't find any record of a path up the Ice Barrier.");
	addExit(ELibrary, "outside", 4, 0, 0, 0);
	ELibrary.roomPosition = { -2, 2 };
	ELibrary.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........."
		"#..........#"
		"############";
	worldState.Rooms.push_back(ELibrary);
	// room 6
	RoomData Cross2 = createRoom(0, 0, 0, 0, 0, "Orange Plains Crossroads", "You find yourself at a crossroads at the south end of the Orange Plains. There is a path going into the Enchanted Forest, a path going further into the plains, a path going into the Mystic Valley, and a path going into Savoy Scrub.");
	addExit(Cross2, "valley", 3, 0, 0, 0);
	addExit(Cross2, "forest", 12, 0, 0, 0);
	addExit(Cross2, "scrub", 17, 0, 0, 0);
	addExit(Cross2, "plains", 7, 0, 0, 0);
	Cross2.roomPosition = { 0, 3 };
	Cross2.roomMap =
		"#####.######"
		"#..........#"
		"#..........#"
		"#..........."
		"#..........#"
		"...........#"
		"#..........#"
		"######.#####";
	worldState.Rooms.push_back(Cross2);
	// room 7
	RoomData Plains = createRoom(0, 0, 0, 0, 0, "Orange Plains", "You find yourself in the Orange plains. There doesn't seem to be much here except the path towards the swamp in the north and the forest to the south.");
	addExit(Plains, "swamp", 8, 0, 0, 0);
	addExit(Plains, "forest", 6, 0, 0, 0);
	Plains.roomPosition = { 0, 4 };
	Plains.roomMap =
		"##########.#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#####.######";
	worldState.Rooms.push_back(Plains);
	// room 8
	RoomData Blackwater = createRoom(0, 0, 0, 0, 0, "Blackwater Fen", "You find yourself in Blackwater Fen, near a lake. There is a path going south into the Orange Plains and a path going into Derleth.");
	addExit(Blackwater, "plains", 7, 0, 0, 0);
	addExit(Blackwater, "derleth", 9, 0, 0, 0);
	Blackwater.roomPosition = { 0, 5 };
	Blackwater.roomMap =
		"############"
		"#..........#"
		"...........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"##########.#";
	worldState.Rooms.push_back(Blackwater);
	// room 9
	RoomData Derleth = createRoom(0, 0, 0, 0, 0, "Derleth square", "You find youself in the main square of Derleth. There is a library, a port with a boat going to the Enchanted Forest (should you take it it will return to Derleth once you get there), some other buildings, and a path out into Blackwater Fen.");
	addExit(Derleth, "swamp", 8, 0, 0, 0);
	addExit(Derleth, "library", 10, 0, 0, 0);
	addExit(Derleth, "port", 12, 0, 0, 0);
	Derleth.roomPosition = { -1, 5 };
	Derleth.roomMap =
		"##.#########"
		"#..........#"
		"#..........."
		"#..........#"
		"#..........#"
		"...........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(Derleth);
	// room 10
	RoomData DLibrary = createRoom(0, 0, 0, 0, 0, "Derleth Library", "You find yourself in a grand library. After some reading, you determine the seer of the Sandy Wastes may be able to help with the Ice Barrier problem, and that Nikolai has taken up residence in the Dark Dungeons in the Goric Mountains west of the Pine Barons beyond the Enchanted Forest. There is also a door with a silver lock here, plus the door going outside.");
	addExit(DLibrary, "vault", 11, 1, 0, 0);
	addExit(DLibrary, "outside", 9, 0, 0, 0);
	DLibrary.roomPosition = { -1, 6 };
	DLibrary.roomMap =
		"######H#####"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"##.#########";
	worldState.Rooms.push_back(DLibrary);
	// room 11
	RoomData Vault = createRoom(0, 0, 1, 0, 0, "Derleth Library Vault", "You are now in a vault containing a number of artifacts and information on the dark places of the world.");
	addExit(Vault, "upstairs", 10, 0, 0, 0);
	Vault.roomPosition = { -1, 7 };
	Vault.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"######.#####";
	worldState.Rooms.push_back(Vault);
	// room 12
	RoomData EnchantedForestDocks = createRoom(0, 0, 0, 0, 0, "Enchanted Forest", "You are in a stunningly beautiful and majestic forest. There are some docks here along the river Uul, as well as a path heading towards the Orange Plains, and a bridge across the Uul deeper into the forest.");
	addExit(EnchantedForestDocks, "plains", 6, 0, 0, 0);
	addExit(EnchantedForestDocks, "forest", 13, 0, 0, 0);
	EnchantedForestDocks.roomPosition = { -1, 3 };
	EnchantedForestDocks.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"............"
		"#..........#"
		"############";
	worldState.Rooms.push_back(EnchantedForestDocks);
	// room 13
	RoomData EnchantedForest = createRoom(0, 0, 0, 0, 0, "Enchanted Forest", "You are deep within the Enchanted Forest. There is a path heading into the Pine Barons and a path heading towards the river Uul.");
	addExit(EnchantedForest, "uul", 12, 0, 0, 0);
	addExit(EnchantedForest, "pines", 14, 0, 0, 0);
	EnchantedForest.roomPosition = { -2, 3 };
	EnchantedForest.roomMap =
		"############"
		"#..........#"
		"...........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........."
		"############";
	worldState.Rooms.push_back(EnchantedForest);
	// room 14
	RoomData PineBarons = createRoom(0, 0, 0, 0, 0, "Pine Barons", "You are in a wonderful pine forest. The Goric mountains loom next to you along one end of the path, while the other way leads into the Enchanted Forest.");
	addExit(PineBarons, "mountains", 15, 0, 0, 0);
	addExit(PineBarons, "forest", 13, 0, 0, 0);
	PineBarons.roomPosition = { -3, 3 };
	PineBarons.roomMap =
		"############"
		"#..........#"
		"#..........."
		"#..........#"
		"...........#"
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(PineBarons);
	// room 15 (Writing these is starting to get old)
	RoomData GoricMountains = createRoom(0, 0, 0, 0, 0, "Goric Mountains", "You are high in the mountains. You can see across all the land from here. There is a path going down into the pine barons, and a maze of pathways through the mountains.");
	addExit(GoricMountains, "pines", 14, 0, 0, 0);
	addExit(GoricMountains, "onward", 16, 0, 0, 1);
	GoricMountains.roomPosition = { -4, 3 };
	GoricMountains.roomMap =
		"############"
		"...........#"
		"#..........#"
		"#..........#"
		"#..........."
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(GoricMountains);
	// room 16
	RoomData TheLedge = createRoom(0, 0, 0, 0, 0, "The Ledge", "You find yourself on a high ledge with only a path down and an obsidian door. You sense you are nearing the end of your quest.");
	addExit(TheLedge, "down", 15, 0, 0, 1);
	addExit(TheLedge, "door", 26, 0, 1, 0);
	TheLedge.roomPosition = { -5, 3 };
	TheLedge.roomMap =
		"######H#####"
		"#...#......."
		"#...########"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(TheLedge);
	// room 17
	RoomData SavoyScrub = createRoom(0, 0, 0, 0, 0, "Savoy Scrub", "You find yourself in a grassland scattered with shrubs. There is a path heading south into the Sandy Wastes, as well as another trail heading towards the Ice Barrier.");
	addExit(SavoyScrub, "plains", 6, 0, 0, 0);
	addExit(SavoyScrub, "barrier", 18, 0, 0, 0);
	addExit(SavoyScrub, "wastes", 19, 0, 0, 0);
	SavoyScrub.roomPosition = { 1, 3 };
	SavoyScrub.roomMap =
		"############"
		"#..........#"
		"#..........."
		"...........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"########.###";
	worldState.Rooms.push_back(SavoyScrub);
	// room 18
	RoomData IceBarrier = createRoom(0, 0, 0, 0, 0, "Ice Barrier", "Looming before you is a massive wall of ice, the land atop known as Geshtop Plateau. There is a slide of ice coming down from the top, though you definitely wouldn't be able to get up it. The only way to go from here is into the scrub.");
	addExit(IceBarrier, "scrub", 17, 0, 0, 0);
	IceBarrier.roomPosition = { 2, 3 };
	IceBarrier.roomMap =
		"############"
		"#..........#"
		"...........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(IceBarrier);
	// room 19
	RoomData SandyWastes = createRoom(0, 0, 0, 0, 0, "Sandy Wastes", "You are in a hot and empty desert, alone except for the cacti and a hut in the distance. There is a path that leads there, as well as back to the scrub.");
	addExit(SandyWastes, "hut", 20, 0, 0, 0);
	addExit(SandyWastes, "scrub", 17, 0, 0, 0);
	SandyWastes.roomPosition = { 1, 2 };
	SandyWastes.roomMap =
		"########.###"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"##.#########";
	worldState.Rooms.push_back(SandyWastes);
	// room 20
	RoomData SeersHut = createRoom(0, 1, 0, 0, 0, "Seer's Hut", "You are in a cool hut where an elderly man seems to have been waiting for you.\nSeer: \"I've been waiting for you. You will need the obsidian key to open the dungeon in which Nikolai resides. I would also suggest you seek out the Emerald Sword on Geshtop. I have opened a portal there, but it is a one way passage. You will need to find your own way down.\"");
	addExit(SeersHut, "outside", 19, 0, 0, 0);
	addExit(SeersHut, "portal", 21, 0, 0, 0);
	SeersHut.roomPosition = { 1, 1 };
	SeersHut.roomMap =
		"##.#########"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........."
		"#..........#"
		"############";
	worldState.Rooms.push_back(SeersHut);
	// room 21
	RoomData GeshtopLanding = createRoom(0, 0, 0, 0, 0, "Edge of Geshtop", "You find youself on top of the Ice Barrier and on the plateau. There are no visible paths anymore, but you can make your way up the Green Glacier or head towards the Azur Peaks.");
	addExit(GeshtopLanding, "glacier", 22, 0, 0, 0);
	addExit(GeshtopLanding, "peaks", 25, 0, 0, 0);
	GeshtopLanding.roomPosition = { 2, 1 };
	GeshtopLanding.roomMap =
		"#######.####"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........."
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(GeshtopLanding);
	// room 22
	RoomData GreenGlacier = createRoom(0, 0, 0, 0, 0, "Green Glacier", "You are on the base of a massive glacier. It seems safe enough to climb, as something big has wandered all over the glacier, leaving footprints.");
	addExit(GreenGlacier, "down", 21, 0, 0, 0);
	addExit(GreenGlacier, "up", 23, 0, 0, 0);
	GreenGlacier.roomPosition = { 3, 1 };
	GreenGlacier.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"#..........."
		"...........#"
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(GreenGlacier);
	// room 23
	RoomData GlacierTop = createRoom(0, 0, 0, 0, 0, "Green Glacier Peak", "You have reached the peak of the glacier. There is a cave in the ice beyond the glacier");
	addExit(GlacierTop, "down", 22, 0, 0, 0);
	addExit(GlacierTop, "cave", 24, 0, 0, 0);
	GlacierTop.roomPosition = { 4, 1 };
	GlacierTop.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"...........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#########.##";
	worldState.Rooms.push_back(GlacierTop);
	// room 24
	RoomData IceCave = createRoom(0, 0, 0, 0, 1, "Ice Cave", "You find yourself in an ice cave. There are some bones lying around, and a skeleton frozen in the ice.");
	addExit(IceCave, "glacier", 23, 0, 0, 0);
	IceCave.roomPosition = { 4, 0 };
	IceCave.roomMap =
		"#########.##"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"############";
	worldState.Rooms.push_back(IceCave);
	// room 25 (Why did I do this to myself)
	RoomData AzurPeaks = createRoom(0, 0, 0, 0, 0, "Azur Peaks", "You find yourself amongst incredible ice spires the size of mountains. You can head over to where the portal dropped you, or take this convenient slide down the Ice Barrier.");
	addExit(AzurPeaks, "landing", 21, 0, 0, 0);
	addExit(AzurPeaks, "slide", 18, 0, 0, 0);
	AzurPeaks.roomPosition = { 2, 2 };
	AzurPeaks.roomMap =
		"####.#######"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#######.####";
	worldState.Rooms.push_back(AzurPeaks);
	// room 26
	RoomData Atrium = createRoom(0, 0, 0, 0, 0, "Dark Atrium", "You find yourself in a dark atrium. There is a skeleton that was cut in half on the left wall, apparently the last one to attempt to fight Nikolai. There is a door going deeper into the dungeon and a door going outside.");
	addExit(Atrium, "outside", 16, 0, 0, 0);
	addExit(Atrium, "onward", 27, 0, 0, 0);
	Atrium.roomPosition = { -5, 4 };
	Atrium.roomMap =
		"######.#####"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"######.#####";
	worldState.Rooms.push_back(Atrium);
	// room 27
	RoomData AltarRoom = createRoom(0, 0, 0, 0, 0, "Altar Room", "You are now in the room of the Black Altar, hopefully the last bastion of evil energy in the magical lands of Celestia.");
	addExit(AltarRoom, "atrium", 26, 0, 0, 0);
	AltarRoom.roomPosition = { -5, 5 };
	AltarRoom.roomMap =
		"############"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"#..........#"
		"######.#####";
	worldState.Rooms.push_back(AltarRoom);
}

void GetInput(PlayerState& playerState, const WorldState& worldState)
{
	playerState.WantsToLook = false;
	playerState.WantsInventoryListed = false;
	playerState.desiredPos = playerState.currentPos;
	playerState.desiredExit = "";
	playerState.desiredPickup = "";
	printf("What do you do?\n");
	printf("> ");
	TextAdventureCommand command = {};
	command.Verb = "";
	while (command.Verb == "") {
		char key = _getch();
		if (key == 'C' || key == 'c') command.Verb = "commandMode";
		else if (key == 'W' || key == 'w') {
			playerState.desiredPos.y = playerState.currentPos.y - 1;
			command.Verb = "w";
		}
		else if (key == 'S' || key == 's') {
			playerState.desiredPos.y = playerState.currentPos.y + 1;
			command.Verb = "s";
		}
		else if (key == 'A' || key == 'a') {
			playerState.desiredPos.x = playerState.currentPos.x - 1;
			command.Verb = "a";
		}
		else if (key == 'D' || key == 'd') {
			playerState.desiredPos.x = playerState.currentPos.x + 1;
			command.Verb = "d";
		}
	}
	if (command.Verb == "commandMode") {
		cout << "COMMAND MODE: ";
		command.Verb = ""; // Relic from trying to fix the old move system while working on the new one. The updated command parser didn't like the old go command. Reverted to the original.
		command = ParseAdventureCommand();
		if (command.Verb == "quit")
		{
			playerState.WantsToExit = true;
		}
		else if (command.Verb == "help")
		{
			printf("Command List: look, quit, inventory, get, go, help, sleep\nCombat commands: attack, ice, fireball, heal\n");
			printf("Key:\n");
			printf("  @ - Player\n");
			printf("  A - Altar\n");
			printf("  i - Item\n");
			printf("  . - Floor\n");
			printf("  # - Wall\n");
			printf("  H - Door (Locked)\n");
			cout << "To pass through a locked door, use the go command with the correct key in your inventory.";
		}
		else if (command.Verb == "look") {
			playerState.WantsToLook = true;
		}
		else if (command.Verb == "go") {
			playerState.desiredExit = command.Parameter;
		}
		else if (command.Verb == "get") {
			playerState.desiredPickup = command.Parameter;
		}
		else if (command.Verb == "sleep") {
			playerState.hero.setMana(10);
			cout << "Mana restored\n";
		}
		else if (command.Verb == "inventory") {
			playerState.WantsInventoryListed = true;
		}
		else if (command.Verb == "w" || command.Verb == "s" || command.Verb == "a" || command.Verb == "d") {
			playerState.moved = true;
		}
		else
		{
			printf("I don't understand\n");
		}
	}
	printf("\n");
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
}

void RenderGame(const PlayerState& playerState, const WorldState& worldState) // Much of the room rendering is cheesey hardcoding, but I've been awake for two days straight to turn this in on time
{
	if (playerState.WantsToLook) {
		RoomData currentRoom = worldState.Rooms[playerState.currentRoomIndex];
		cout << "Location: " << currentRoom.roomName.c_str() << "\n\n"
			<< currentRoom.roomDesc.c_str() << "\n\n"
			<< "Exits:\n";
		if (currentRoom.hasMap) cout << "There is a map in this room.\n";
		if (currentRoom.hasObsidianKey) cout << "There is an obsidian key in this room.\n";
		if (currentRoom.hasSilverKey) cout << "There is a silver key in this room.\n";
		if (currentRoom.hasCSword) cout << "There is a crystal sword in this room.\n";
		if (currentRoom.hasESword) cout << "The Emerald Sword is in this room.\n";
		cout << "\n";
		for (int i = 0; i < currentRoom.Exits.size(); i++) {
			cout << currentRoom.Exits[i].Name.c_str() << "\n";
		}
		cout << "\n";
		string renderedMapStr = ""; // I really don't like using a string over a 2D array, but I was too exhausted to do my own logic, so followed the tutorial
		unsigned int currentSpace = 0;
		while (currentSpace < currentRoom.roomMap.size()) {
			char charToDisplay = currentRoom.roomMap[currentSpace];
			if (PosToIndex(playerState.currentPos) == currentSpace) {
				charToDisplay = '@';
			}
			else if (currentSpace == 49 && (currentRoom.hasCSword || currentRoom.hasESword)) {
				charToDisplay = 'i';
			}
			else if (currentSpace == 27 && currentRoom.hasMap) {
				charToDisplay = 'i';
			}
			else if (currentSpace == 42 && (currentRoom.hasSilverKey || currentRoom.hasObsidianKey)) {
				charToDisplay = 'i';
			}
			renderedMapStr += charToDisplay;
			if (currentSpace % 12 == 11) {
				renderedMapStr += '\n';
			}
			currentSpace++;
		}
		cout << renderedMapStr.c_str();
	}
	else if (playerState.WantsInventoryListed)
	{
		printf("================================================\n");
		printf("INVENTORY:\n");
		if (playerState.hasMap) cout << "Map\n";
		if (playerState.hasSilverKey) cout << "Silver key\n";
		if (playerState.hasObsidianKey) cout << "Obsidian key\n";
		if (playerState.hasCSword) cout << "Crystal sword\n";
		if (playerState.hasESword) cout << "Emerald sword\n";
		if (!(playerState.hasMap || playerState.hasObsidianKey || playerState.hasSilverKey || playerState.hasCSword || playerState.hasESword)) cout << "Empty\n";
		cout << "\n";
		printf("\n"); // One professor likes C, one likes C++, and part of this block is borrowed from the tutorials and free files. I use C++
	}

}

void UpdateGame(PlayerState& playerState, WorldState& worldState)
{
	RoomData& currentRoom = worldState.Rooms[playerState.currentRoomIndex];
	if (playerState.hero.getHP() == 0) playerState.WantsToExit = true;
	if (playerState.desiredExit != "") { // Yes, old movement still works too
		bool foundExit = false;
		for (int i = 0; i < currentRoom.Exits.size(); i++) {
			if (playerState.desiredExit == currentRoom.Exits[i].Name) {
				foundExit = true;
				if (!currentRoom.Exits[i].lockedS && !currentRoom.Exits[i].lockedO && !currentRoom.Exits[i].lockedM) {
					playerState.currentRoomIndex = currentRoom.Exits[i].targetRoomIndex;
					playerState.WantsToLook = true;
					worldState.combatFlag = false;
				}
				else if (playerState.hasSilverKey && currentRoom.Exits[i].lockedS) {
					playerState.currentRoomIndex = currentRoom.Exits[i].targetRoomIndex;
					playerState.WantsToLook = true;
					worldState.combatFlag = false;
				}
				else if (playerState.hasObsidianKey && currentRoom.Exits[i].lockedO) {
					playerState.currentRoomIndex = currentRoom.Exits[i].targetRoomIndex;
					playerState.WantsToLook = true;
					worldState.combatFlag = false;
				}
				else if (playerState.hasMap && currentRoom.Exits[i].lockedM) {
					playerState.currentRoomIndex = currentRoom.Exits[i].targetRoomIndex;
					playerState.WantsToLook = true;
					worldState.combatFlag = false;
				}
				else if (!playerState.hasMap && currentRoom.Exits[i].lockedM) {
					if ((rand() % 10) == 0) {
						playerState.currentRoomIndex = currentRoom.Exits[i].targetRoomIndex;
						playerState.WantsToLook = true;
						worldState.combatFlag = false;
					}
					else {
						cout << "You get lost, but manage to find your way back to where you started.\n";
					}
				}
				else {
					cout << "The door is locked.\n";
				}
			}
		}
		if (!foundExit) {
			cout << "Couldn't find desired exit.\n";
		}
	}
	if (playerState.desiredPickup != "") { // All of these are hardcoded garbage because I'm way too exhauseted to properly implement these
		bool foundItem = false;
		if (playerState.desiredPickup == "key") {
			if (currentRoom.hasSilverKey && (PosToIndex(playerState.currentPos) == 42)) {
				cout << "You have acquired a silver key.\n";
				playerState.hasSilverKey = true;
				currentRoom.hasSilverKey = false;
				foundItem = true;
			}
			else if (currentRoom.hasObsidianKey && (PosToIndex(playerState.currentPos) == 42)) {
				cout << "You have acquired an obsidian key.\n";
				playerState.hasObsidianKey = true;
				currentRoom.hasObsidianKey = false;
				foundItem = true;
			}
			else {
				cout << "Could not find a key\n";
				foundItem = true;
			}
		}
		else if (playerState.desiredPickup == "map" && (PosToIndex(playerState.currentPos) == 27)) {
			if (currentRoom.hasMap) {
				cout << "You have acquired a map of a labyrinth.\n";
				playerState.hasMap = true;
				currentRoom.hasMap = false;
				foundItem = true;
			}
			else {
				cout << "Could not find a map\n";
				foundItem = true;
			}
		}
		else if (playerState.desiredPickup == "sword") {
			if (currentRoom.hasESword && (PosToIndex(playerState.currentPos) == 49)) {
				cout << "You have acquired the Emerald Sword.\n";
				playerState.hasESword = true;
				currentRoom.hasESword = false;
				foundItem = true;
			}
			else if (currentRoom.hasCSword && (PosToIndex(playerState.currentPos) == 49)) {
				cout << "You have acquired the Crystal Sword.\n";
				playerState.hasCSword = true;
				currentRoom.hasCSword = false;
				foundItem = true;
			}
			else {
				cout << "Could not find a weapon\n";
				foundItem = true;
			}
		}
		else if (!foundItem) {
			cout << "Unknown item\n";
		}
	}
	else if (playerState.moved) {
		worldState.combatFlag = false;
	}
	else if (spaceOOB(playerState.desiredPos)) { // Room switch mess
		Position desiredRoomPos = currentRoom.roomPosition;
		int playerPosType = 0;
		if (playerState.desiredPos.x < 0) {
			desiredRoomPos.x--;
			playerPosType = 1;
		}
		else if (playerState.desiredPos.x > 11) {
			desiredRoomPos.x++;
			playerPosType = 2;
		}
		else if (playerState.desiredPos.y < 0) {
			desiredRoomPos.y++;
			playerPosType = 3;
		}
		else if (playerState.desiredPos.y > 7){
			desiredRoomPos.y--;
			playerPosType = 4;
		}
		else {
			cout << "ERROR: How did you get here?"; // If you get here, something went terribly wrong
		}
		bool foundNewRoom = false;
		for (int i = 0; i < worldState.Rooms.size(); i++) {
			if (worldState.Rooms[i].roomPosition == desiredRoomPos) {
				playerState.currentRoomIndex = i;
				playerState.WantsToLook = true;
				switch (playerPosType) {
				case 1:
					playerState.currentPos.x = 11;
					break;
				case 2:
					playerState.currentPos.x = 0;
					break;
				case 3:
					playerState.currentPos.y = 7;
					break;
				case 4:
					playerState.currentPos.y = 0;
					break;
				default:
					cout << "Use \'go port\' to use the port.";
				}
				foundNewRoom = true;
			}
		}
	} // Check for valid space and bocks illegal movement. Does not prevent spawning in walls.
	else if (playerState.currentPos != playerState.desiredPos) {
		if (validSpace(playerState.desiredPos, currentRoom, playerState)) {
			playerState.currentPos = playerState.desiredPos;
			playerState.WantsToLook = true;
		}
		else {
			cout << "You cannot go here.";
		}
	}
	if (!worldState.nikolaiAlive) { // end condition
		cout << "After a long and hard quest you have defeated the evil sorcerer Nikolai. Your quest was not in vain, and Luna will be proud of your accomplishments. But this is only the beginning of your journey...\n\n"
			<< "Thanks for playing!";
		playerState.WantsToExit = true;
	}
}

void CleanupGame(PlayerState& playerState, WorldState& worldState)
{
	printf("Quitting...\n\n");
}

int PosToIndex(const Position pos) {
	return pos.y * 12 + pos.x;
}

bool validSpace(const Position& pos, const RoomData& currentRoom, const PlayerState& playerState) { // Yeah yeah harrdcoded cheese, I have two hours until class so cut me some slack
	return (currentRoom.roomMap[PosToIndex(pos)] == '.' ||
		(currentRoom.roomMap[PosToIndex(pos)] == 'H' && ((playerState.hasSilverKey && playerState.currentRoomIndex == 10) || (playerState.hasObsidianKey && playerState.currentRoomIndex == 16))));
}

bool spaceOOB(const Position& pos) {
	return pos.x < 0 || pos.x > 11 || pos.y < 0 || pos.y > 7;
}