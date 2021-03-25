#pragma once
#include <vector>
#include "Entity.h"
#include <string>
using namespace std;

struct Position {
	int x;
	int y;
	bool operator==(const Position& other) {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Position& other) {
		return !(*this == other);
	}
};

struct PlayerState {
	bool WantsToExit;
	bool WantsToLook;
	bool WantsInventoryListed;
	int currentRoomIndex;
	Position currentPos = { 6, 6 }; // Totally random so the player doesn't start in a wall
	Position desiredPos;
	string desiredExit;
	string desiredPickup;
	bool hasSilverKey;
	bool hasObsidianKey;
	bool hasMap;
	bool hasESword;
	bool hasCSword;
	Player hero;
	string name;
	bool moved;
};

struct RoomExit {
	string Name;
	int targetRoomIndex;
	bool lockedS;
	bool lockedO;
	bool lockedM;
};

struct RoomData {
	string roomName;
	string roomDesc;
	string roomMap;
	vector<RoomExit> Exits;
	Position roomPosition;
	bool hasSilverKey;
	bool hasObsidianKey;
	bool hasMap;
	bool hasESword;
	bool hasCSword;
};

struct WorldState {
	vector<RoomData> Rooms;
	bool nikolaiAlive = true;
	bool iceDragonAlive = true;
	bool combatFlag = false;
};

void InitializeGame(PlayerState& playerState, WorldState& worldState);
void GetInput(PlayerState& playerState, const WorldState& worldState);
void RenderGame(const PlayerState& playerState, const WorldState& worldState);
void UpdateGame(PlayerState& playerState, WorldState& worldState);
void CleanupGame(PlayerState& playerState, WorldState& worldState);
int PosToIndex(const Position pos);
bool validSpace(const Position& pos, const RoomData& currentRoom, const PlayerState& playerState);
bool spaceOOB(const Position& pos); // Only reason this gets away with not checking the room map is the fact all the rooms are hardcoded to be the same size