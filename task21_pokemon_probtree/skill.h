// Oytun Demirbilek
// 150150032

#ifndef SKILL_H
#define SKILL_H
#include <iostream>
using namespace std;
class skill
{
private:
	int pp;
	int accuracy;
	int damage;
	int firstusage;
	string skillname;

public:
	skill();
	skill(int pp, int accuracy, int damage, int firstusage, string skillname);
	int get_damage();
	int get_acc();
	int get_pp();
	int get_firstusage();
	string get_name();
	~skill();
};

#endif