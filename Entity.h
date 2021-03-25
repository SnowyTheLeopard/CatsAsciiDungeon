#pragma once
#include <stdlib.h>

// ENTITIES

// Generic entity class, parent to all other entities
class Entity {
protected:
	int hp;							// Health points
	int strMod;						// Strength modifier
	int weaponSkill;				// The bonus for attack hit chance  NOT UTILIZED YET
	int armor = 10;					// The ability of an entity to block an attack  NOT UTILIZED YET
	int mana;						// The amount of mana available for magic
	int type;						// 0: player, 1: goblin, 2: bandit, 3: dragon, 4: skeleton    For a quick and dirty ID solution to avoid passing strings
	bool isWeak;					// Flag for the weakened condition
	bool isStrong;					// Flag for the strengthened condition
	bool isFrozen;					// Flag for the frozen condition
	const char* name = "entity";	// Name of the enemy type

public:
	// Returns HP
	int getHP() {
		return hp;
	}

	// Changes HP by specified amount
	void damage(int damage) {
		hp -= damage;
		if (hp < 0) hp = 0;
	}

	// Returns weapon skill
	int getWS() {
		return weaponSkill;
	}

	// Returns armor
	int getArmor() {
		return armor;
	}

	// Returns strength mod
	int getStrMod() {
		return strMod;
	}

	// Updates strength mod
	void updateStrMod(int a) {
		strMod = a;
	}

	// Returns mana
	int manaRemaining() {
		return mana;
	}

	// Updates available mana
	void updateMana(int a) {
		mana += a;
	}

	// Sets mana
	void setMana(int a) {
		mana = a;
	}

	// Returns the entity type
	int getType() {
		return type;
	}

	// Returns if the creature is frozen
	bool getFrozen() {
		return isFrozen;
	}

	// Updates frozen flag
	void updateFrozenFlag(bool a) {
		isFrozen = a;
	}

	// Returns if the creature is weakened
	bool getWeak() {
		return isWeak;
	}

	// Updates weakness flag
	void updateWeakFlag(bool a) {
		isWeak = a;
	}

	// Returns if the creature is strong
	bool getStrong() {
		return isStrong;
	}

	// Updates strength flag
	void updateStrFlag(bool a) {
		isStrong = a;
	}

	// Returns the name of an entity
	const char* getName() {
		return name;
	}
};

// Player class, reserved for the player
class Player : public Entity {
public:
	Player() {
		hp = 25;
		armor = 15;
		mana = 10;
		weaponSkill = 5;
	}
};

// Goblin class
class Goblin : public Entity {
public:
	Goblin() {
		hp = rand() % 5 + 4;
		weaponSkill = rand() % 3 + 2;
		armor = 13;
		type = 1;
		name = "a goblin";
	}
};

// Bandit class
class Bandit : public Entity {
public:
	Bandit() {
		hp = rand() % 7 + 12;
		weaponSkill = 2;
		strMod = 0;
		type = 2;
		name = "a bandit";
	}
};

// Skeleton class
class Skeleton : public Entity {
public:
	Skeleton() {
		hp = 15;
		weaponSkill = 5;
		armor = 15;
		type = 4;
		name = "a skeleton";
	}
};

// Dragon class
class Dragon : public Entity {
public:
	Dragon() {
		hp = 50;
		weaponSkill = 7;
		armor = 18;
		type = 3;
		name = "a fire dragon";
		mana = 8;
	}
};

// Ice dragon
class IDragon : public Entity {
public:
	IDragon() {
		hp = 50;
		type = 5;
		name = "the ice dragon";
		mana = 8;
	}
};

// Nikolai
class Nikolai : public Entity {
public:
	Nikolai() {
		hp = 75;
		type = 6;
		name = "the Evil Sorcerer Nikolai";
		mana = 12;
	}
};
