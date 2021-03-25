#pragma once
#include "Object.h"
#include <iostream>
#include <time.h>
#include <iterator>
#include <algorithm>
#include <Windows.h>
using namespace std;

// Combat function. Torn straight from project 2, it was in fact designed with this in mind
bool combat(PlayerState& player, Entity& enemy) {
	const char* name = enemy.getName();
	cout << "As you journey across the lands of Celestia, " << enemy.getName() << " approaches you, " << player.name.c_str() << "! They're looking for a fight!\n";
	// BEGIN FIGHT

	char action[255];
	char att[255] = { "attack" };
	char fir[255] = { "fireball" };
	char ice[255] = { "ice" };
	char heal[255] = { "heal" };
	char run[255] = { "run" };
	int tempNum = 0;
	int dergAtt;
	int nikoAtt;
	while (true) {
		fill_n(action, 255, NULL); // Shouldn't cause infinite loop problem anymore when the array was too long
		cout << "\nYour HP is " << player.hero.getHP() << " and your mana is " << player.hero.manaRemaining() << ". Your enemy, " << enemy.getName() << " has " << enemy.getHP() << " HP and " << enemy.manaRemaining() << " mana available.\n"
			// BEGIN PLAYER TURN
			<< "What will you do, attack, fireball, ice, or heal?\n> ";
		cin.getline(action, 255); // Upon review of this for addition into the text adventure, I realized I'm not entirely sure what I was doing. 
		if (equal(begin(action), end(action), begin(att))) {
			if (player.hasESword) {
				tempNum = ESword::getInstance().getDamage();
				cout << "You swing the Emerald Sword, dealing " << tempNum << " damage!\n\n";
			}
			else if (player.hasCSword) {
				tempNum = CSword::getInstance().getDamage();
				cout << "You swing your crystal sword, dealing " << tempNum << " damage!\n\n";
			}
			else {
				tempNum = Longsword::getInstance().getDamage();
				cout << "You swing your longsword, dealing " << tempNum << " damage!\n\n";
			}
			enemy.damage(tempNum);
		}
		else if (equal(begin(action), end(action), begin(ice))) {
			if (player.hero.manaRemaining() >= 1) {
				tempNum = Ice::getInstance().getDamage();
				if (enemy.getType() == 3) tempNum *= 2;
				enemy.damage(tempNum);
				cout << "You attack with a blast of ice, dealing " << tempNum << " damage!\n\n";
				if (enemy.getType() != 5) {
					enemy.updateFrozenFlag(true);
					cout << "You have frozen your enemy!\n\n";
				}
				player.hero.updateMana(-1 * Ice::getInstance().getCost());
			}
			else {
				cout << "Insufficient mana\n\n";
			}
		}
		else if (equal(begin(action), end(action), begin(fir))) {
			if (player.hero.manaRemaining() >= 2) {
				tempNum = Fireball::getInstance().getDamage();
				if (enemy.getType() == 5) tempNum *= 2;
				enemy.damage(tempNum);
				cout << "You attack with a fireball, dealing " << tempNum << " damage!\n\n";
				player.hero.updateMana(-1 * Fireball::getInstance().getCost());
			}
			else {
				cout << "Insufficient mana\n\n";
			}
		}
		else if (equal(begin(action), end(action), begin(heal))) { // I should fix the infinite health bug...
			if (player.hero.manaRemaining() >= 1) {
				tempNum = rand() % 10 + 11;
				cout << "You heal yourself for " << tempNum << " HP and feel much better.\n\n";
				player.hero.damage(-1 * tempNum);
				player.hero.updateMana(-1);
			}
			else {
				cout << "Insufficient mana\n\n";
			}
		}
		else if (equal(begin(action), end(action), begin(run))) { // Go watch Monty Python and the Holy Grail if you don't get it
			cout << "\nBrave Sir Robin ran away.\n"
				<< "Bravely ran away away.\n"
				<< "When danger reared it's ugly head,\n"
				<< "He bravely turned his tail and fled.\n"
				<< "Yes, brave Sir Robin turned about\n"
				<< "And gallantly he chickened out.\n"
				<< "Swiftly taking to his feet,\n"
				<< "He beat a very brave retreat.\n"
				<< "Bravest of the brave, Sir Robin!\n\n";
			player.hero.damage(1000000);
			break;
		}
		else {
			cout << "Unknown command, not that the " << enemy.getName() << " cares. They press on!\n\n";
		}
		cout << "\n";
		if (player.hero.getHP() == 0) break; // Don't like the lack of brackets? Sue me.
		if (enemy.getHP() == 0) break;
		Sleep(1000);
		// BEGIN ENEMY TURN
		cout << "Your HP is " << player.hero.getHP() << " and your mana is " << player.hero.manaRemaining() << ". The " << enemy.getName() << " has " << enemy.getHP() << " HP and " << enemy.manaRemaining() << " mana available.\n";
		if (enemy.getFrozen()) {
			enemy.updateFrozenFlag(false);
			cout << "Your enemy is frozen, but is breaking free!\n\n";
		}
		else if (enemy.getType() == 1) { // Removed poison effect due to bug where you can end up healing the goblin by getting hit too much
			tempNum = Dagger::getInstance().getDamage();
			cout << "The goblin stabs you with a dagger, dealing " << tempNum << " damage!\n\n";
			player.hero.damage(tempNum);
		}
		else if (enemy.getType() == 2) {
			tempNum = Longsword::getInstance().getDamage();
			cout << "The bandit swings its longsword at you, dealing " << tempNum << " damage!\n\n";
			player.hero.damage(tempNum + enemy.getStrMod());
		}
		else if (enemy.getType() == 4) {
			tempNum = Longsword::getInstance().getDamage();
			cout << "The skeleton swings its longsword at you, dealing " << tempNum << " damage!\n\n";
			player.hero.damage(tempNum);
		}
		else if (enemy.getType() == 3) {
			dergAtt = rand() % 2;
			if (dergAtt == 0 && enemy.manaRemaining() >= 2) {
				tempNum = Fireball::getInstance().getDamage();
				enemy.updateMana(-1 * Fireball::getInstance().getCost());
				cout << "The dragon attacks with a fireball, dealing " << tempNum << " damage!\n\n";
			}
			else {
				tempNum = Claw::getInstance().getDamage();
				cout << "The dragon attacks with its claws, dealing " << tempNum << " damage!\n\n";
			}
			player.hero.damage(tempNum);
		}
		else if (enemy.getType() == 5) {
			dergAtt = rand() % 2;
			if (dergAtt == 0 && enemy.manaRemaining() >= 2) {
				tempNum = Ice::getInstance().getDamage();
				enemy.updateMana(-1 * Ice::getInstance().getCost());
				cout << "The dragon attacks with a blast of ice, dealing " << tempNum << " damage!\n\n";
			}
			else {
				tempNum = Claw::getInstance().getDamage();
				cout << "The dragon attacks with its claws, dealing " << tempNum << " damage!\n\n";
			}
			player.hero.damage(tempNum);
		}
		else if (enemy.getType() == 6) {
			nikoAtt = rand() % 3; // Ah yes, highly intelligent enemy attack logic
			if (nikoAtt == 0 && enemy.manaRemaining() >= 2) {
				tempNum = Fireball::getInstance().getDamage();
				enemy.updateMana(-1 * Fireball::getInstance().getCost());
				cout << "Nikolai attacks with a blast of ice, dealing " << tempNum << " damage!\n\n";
			}
			else if (nikoAtt == 1 && enemy.manaRemaining() >= 2) {
				tempNum = Ice::getInstance().getDamage();
				enemy.updateMana(-1 * Ice::getInstance().getCost());
				cout << "Nikolai attacks with a blast of ice, dealing " << tempNum << " damage!\n\n";
			}
			else {
				tempNum = Longsword::getInstance().getDamage();
				cout << "Nikolai attacks with a longsword, dealing " << tempNum << " damage!\n\n";
			}
			player.hero.damage(tempNum);
		}
		if (player.hero.getHP() == 0) break;
		if (enemy.getHP() == 0) break;
		Sleep(1000);
	}
	if (player.hero.getHP() > 0) {
		cout << "You have won the day, " << player.name.c_str() << "! Your quest continues...\n\n";
		return false;
	}
	else {
		cout << "You have been slain by " << enemy.getName() << ". " << player.name.c_str() << "'s journey ends tragically...\n\n";
		return true;
	}
}