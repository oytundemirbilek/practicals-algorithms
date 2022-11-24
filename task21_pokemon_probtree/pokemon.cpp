// Oytun Demirbilek
// 150150032
#include "pokemon.h"
#include <iostream>
using namespace std;

pokemon::pokemon()
{
	this->pp = 0;
	this->hp = 0;
	this->name = "";
	this->skills = NULL;
	this->skillcount = 0;
}

pokemon::pokemon(int hp, int pp, string name, int skillcount)
{
	this->pp = pp;
	this->hp = hp;
	this->name = name;
	this->skillcount = skillcount;
	this->skills = new skill[this->skillcount];
}
void pokemon::set_health(int amount)
{
	this->hp = amount;
}
void pokemon::set_power(int amount)
{
	this->pp = amount;
}
skill pokemon::get_skill(int index)
{
	return this->skills[index];
}
void pokemon::add_skill(skill skillobj, int skillindex)
{
	if (skillindex > this->skillcount - 1)cout << "Too many skills";
	else if(skillindex >= 0)this->skills[skillindex] = skillobj;
}

string pokemon::get_name()
{
	return this->name;
}
int pokemon::get_health()
{
	return this->hp;
}
int pokemon::get_power()
{
	return this->pp;
}

int pokemon::get_skillcount()
{
	return this->skillcount;
}

pokemon::~pokemon()
{
	//delete[] skills;
}
