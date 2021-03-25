#pragma once
#include <stdlib.h>

// Generic attack class. Contains basic information about an attack
class Attack {
protected:
	int damage;			// Max damage per die
	int damageDie;		// Damage dice
	int manaCost;		// Mana cost
	const char* name;	// The name of the attack
	int damageOut;		// Damage output for return statement for some reason needs to be here
	int index;			// Used for a BS solution to item picking up since I'm way too tired to do this intelligently right now

public:
	// Returns damage
	int getDamage() {
		damageOut = 0;
		for (int i = 0; i < damageDie; i++) {
			damageOut += rand() % damage + 1;
		}
		if (damageOut < 0) return 0;
		return damageOut;
	}

	// Returns mana cost
	int getCost() {
		return manaCost;
	}
};

// Not gonna lie, I borrowed the design for the attacks from Stack Overflow at the recommendation of a dev friend. Not entirely sure how it works.

// Fireball
class Fireball : public Attack {
public:
	static Fireball& getInstance() {
		static Fireball instance;
		return instance;
	}
private:
	Fireball() {
		damage = 5;
		damageDie = 3;
		manaCost = 2;
		name = "fireball";
	}
public:
	Fireball(Fireball const&) = delete;
	void operator=(Fireball const&) = delete;
};

// Longsword
class Longsword : public Attack {
public:
	static Longsword& getInstance() {
		static Longsword instance;
		return instance;
	}
private:
	Longsword() {
		damage = 8;
		damageDie = 1;
		manaCost = 0;
		name = "longsword";
	}
public:
	Longsword(Longsword const&) = delete;
	void operator=(Longsword const&) = delete;
};

// Poison dagger
class Dagger : public Attack {
public:
	static Dagger& getInstance() {
		static Dagger instance;
		return instance;
	}
private:
	Dagger() {
		damage = 5;
		damageDie = 1;
		manaCost = 0;
		name = "dagger";
	}
public:
	Dagger(Dagger const&) = delete;
	void operator=(Dagger const&) = delete;
};

// Dragon claw
class Claw : public Attack {
public:
	static Claw& getInstance() {
		static Claw instance;
		return instance;
	}
private:
	Claw() {
		damage = 5;
		damageDie = 2;
		manaCost = 0;
		name = "claw swipe";
	}
public:
	Claw(Claw const&) = delete;
	void operator=(Claw const&) = delete;
};

// Ice blast
class Ice : public Attack {
public:
	static Ice& getInstance() {
		static Ice instance;
		return instance;
	}
private:
	Ice() {
		damage = 4;
		damageDie = 3;
		manaCost = 2;
		name = "blast of ice";
	}
public:
	Ice(Ice const&) = delete;
	void operator=(Ice const&) = delete;
};

// Emerald Sword
class ESword : public Attack {
public:
	static ESword& getInstance() {
		static ESword instance;
		return instance;
	}
private:
	ESword() {
		damage = 10;
		damageDie = 3;
		manaCost = 0;
		name = "legendary sword";
		index = 49;
	}
};

// Crystal Sword
class CSword : public Attack {
public:
	static CSword& getInstance() {
		static CSword instance;
		return instance;
	}
private:
	CSword() {
		damage = 6;
		damageDie = 3;
		manaCost = 0;
		name = "legendary sword";
		index = 49;
	}
};