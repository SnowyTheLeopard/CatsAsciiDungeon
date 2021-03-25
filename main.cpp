#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include "Object.h"
#include "GameCore.h"
#include "Combat.h"
using namespace std;

/*
Yeah, I just upgraded my text adventure. Built to be reusable though.
This entire project hurt given all the ASCII dungeon upgrades were
done on no sleep for two days. Hey, it works though.

To my dev friends reading this: The entire solution is a complete mess.
It's a strange mix of previous projects, professor provided code, code from the
provided tutorials, and some new garbage I tossed it. Expect to cringe.

Coffee cup counter: VI
*/

//Enemy spawner for general encounters
Entity spawnEnemy(int rnd) {
	// Weight table. THEY MUST REMAIN IN DESCENDING ORDER
	int weights[4] = {
		50, // Goblin
		30, // Bandit
		15, // Skeleton
		5	// Dragon
	};
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += weights[i];
	}
	if (rnd < sum - weights[0]) {
		Goblin enemy;
		return enemy;
	}
	else if (rnd < sum - weights[1]) {
		Bandit enemy;
		return enemy;
	}
	else if (rnd < sum - weights[2]) {
		Skeleton enemy;
		return enemy;
	}
	else {
		Dragon enemy;
		return enemy;
	}
}

int main() // Much of this is borrowed from starter files
{
	PlayerState playerState = {};
	WorldState worldState = {};
	InitializeGame(playerState, worldState);
	
	while (!playerState.WantsToExit)
	{
		RenderGame(playerState, worldState); // The following "line" is probably the worst random encounter generator, but I'm too tired to add another param to the rooms and edit them all
		if ((rand() % 50 == 0) && !worldState.combatFlag && (playerState.currentRoomIndex != 0) && (playerState.currentRoomIndex != 1)
			&& (playerState.currentRoomIndex != 4) && (playerState.currentRoomIndex != 5) && (playerState.currentRoomIndex != 9)
			&& (playerState.currentRoomIndex != 10) && (playerState.currentRoomIndex != 11) && (playerState.currentRoomIndex != 16)
			&& (playerState.currentRoomIndex != 20) && (playerState.currentRoomIndex != 21) && (playerState.currentRoomIndex != 22)
			&& (playerState.currentRoomIndex != 23) && (playerState.currentRoomIndex != 24) && (playerState.currentRoomIndex != 25)
			&& (playerState.currentRoomIndex != 26) && (playerState.currentRoomIndex != 27)) { // Certified trash method
			int rnd = rand() % 100 + 1;
			Entity enemy = spawnEnemy(rnd);
			combat(playerState, enemy);
			worldState.combatFlag = true;
			GetInput(playerState, worldState);
		}
		else if (worldState.iceDragonAlive && playerState.currentRoomIndex == 23) {
			Entity enemy = IDragon();
			worldState.iceDragonAlive = combat(playerState, enemy);
			GetInput(playerState, worldState);
		}
		else if (worldState.nikolaiAlive && playerState.currentRoomIndex == 27) {
			Entity enemy = Nikolai();
			worldState.nikolaiAlive = combat(playerState, enemy);
			GetInput(playerState, worldState);
		}
		else {
			GetInput(playerState, worldState);
		}
		UpdateGame(playerState, worldState);
	}

	CleanupGame(playerState, worldState);

	system("pause");

	return 0;
}