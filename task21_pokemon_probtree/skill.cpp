// Oytun Demirbilek
// 150150032
#include "skill.h"
#include <iostream>

using namespace std;
skill::skill()
{
	this->pp = 0;
	this->accuracy = 0;
	this->damage = 0;
	this->firstusage = 0;
	this->skillname = "";
}
skill::skill(int pp, int accuracy, int damage, int firstusage, string skillname)
{
	this->pp = pp;
	this->accuracy = accuracy;
	this->damage = damage;
	this->firstusage = firstusage;
	this->skillname = skillname;
}
int skill::get_damage()
{
	return this->damage;
}
int skill::get_acc()
{
	return this->accuracy;
}
int skill::get_pp()
{
	return this->pp;
}
int skill::get_firstusage()
{
	return this->firstusage;
}
string skill::get_name()
{
	return this->skillname;
}

skill::~skill()
{

}
