// Oytun Demirbilek
// 150150032

#ifndef POKEMON_H
#define POKEMON_H
#include "skill.h"
#include <iostream>
using namespace std;
class pokemon
{
private:
	int hp;
	int pp;
	string name;
	skill* skills;
	int skillcount;

public:
	pokemon();
	pokemon(int hp, int pp, string name, int skillcount);
	void set_health(int amount);
	void set_power(int amount);
	skill get_skill(int index);
	void add_skill(skill skillobj, int skillindex);
	string get_name();
	int get_health();
	int get_power();
	int get_skillcount();
	~pokemon();
};

#endif