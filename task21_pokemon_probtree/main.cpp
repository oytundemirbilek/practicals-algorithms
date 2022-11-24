// Oytun Demirbilek
// 150150032

#include "pokemon.h"
#include "skill.h"

#include <iostream>
#include <queue>
#include <cstring>
#include <time.h>

using namespace std;

char* string_to_charptr(string str) {
	int n = str.length();
	char* charptr = new char[n+1];
	strcpy(charptr, str.c_str());
	return charptr;
}
int find_skillcount(char* pokemon_name) {
	char* filename = strcat(pokemon_name, ".txt");
	char headers[100];
	int skillcount = 0;
	FILE* fp = fopen(filename, "r");
	while (!feof(fp)) {
		fgets(headers, 100, fp);
		skillcount++;
	}
	fclose(fp);
	return skillcount - 1;
}
pokemon pokemon_from_file(pokemon pokemonobj, int skillcount)
{
	char* pokemon_name = string_to_charptr(pokemonobj.get_name());
	char* filename = strcat(pokemon_name, ".txt");
	FILE* fp = fopen(filename, "r");
	char headers[100];
	fgets(headers, 100, fp);
	char c;
	string attackname;

	int pp = 0, accuracy = 0, damage = 0, firstuse = 0, skillcounter=0;

	while (!feof(fp)) {
		c = fgetc(fp);
		if (c == ',') {
			//attackname += '\0';
			if (fscanf(fp, "%d,%d,%d,%d", &pp, &accuracy, &damage, &firstuse)) {
				skill skillobj(pp, accuracy, damage, firstuse, attackname);
				pokemonobj.add_skill(skillobj, skillcounter);
				//cout << pokemonobj.get_skill(skillcounter).get_name() << "\t";
				skillcounter++;
				attackname = "";
				fgetc(fp);
			}
			else break;
		}
		else attackname += c;
	}
	return pokemonobj;
}

struct node {
	queue <node*> nextdata;
	pokemon attacker;
	pokemon defender;
	string turn = attacker.get_name();
	double probability;
	int level;
	bool isleaf;
	string message;
	void printnode() {
		cout << attacker.get_name() + "_PP: " <<  attacker.get_power() << " " + attacker.get_name() << "_HP: " << attacker.get_health() << " ";
		cout << defender.get_name() + "_PP: " <<  defender.get_power() << " " + defender.get_name() << "_HP: " << defender.get_health() << " ";
		cout << "PROB: " << probability << endl;
	}
};

struct probability_tree {
	node* root;
	pokemon p1, p2;
	int maxlevel, nodecount = 0;
	void find_next_data(node* current, bool print) {
		int total_skills = 0;
		// COUNT AVAILABLE SKILLS
		for (int i = 0; i < current->attacker.get_skillcount(); i++) {
			if(current->attacker.get_skill(i).get_firstusage() <= (current->level / 2) + 1)
				total_skills++;
		}
		node* tempnode;
		pokemon temppokemon = current->attacker;
		for (int i = 0; i < current->attacker.get_skillcount(); i++) {
			// ATTACK ONLY IF THE SKILL CAN BE USED
			if (current->attacker.get_skill(i).get_firstusage() <= (current->level / 2) + 1) {
				// CASE OF SUCCESSFUL ATTACK:
				tempnode = new node;
				tempnode->message = current->attacker.get_name() + " used " + current->attacker.get_skill(i).get_name() + ". It's Effective.\n";
				tempnode->level = current->level + 1;
				tempnode->isleaf = true;
				tempnode->probability = current->probability * (1.0 / (double)total_skills) * (double)current->attacker.get_skill(i).get_acc() / (double)100;

				tempnode->attacker = current->defender;
				tempnode->defender = temppokemon;
				tempnode->attacker.set_health(current->defender.get_health() - current->attacker.get_skill(i).get_damage());
				tempnode->defender.set_power(current->attacker.get_power() + current->attacker.get_skill(i).get_pp());

				if(print)tempnode->printnode();
				current->nextdata.push(tempnode);
				// CASE OF UNSUCCESSFUL ATTACK:
				if (current->attacker.get_skill(i).get_acc() != 100) {
					tempnode = new node;
					tempnode->message = current->attacker.get_name() + " used " + current->attacker.get_skill(i).get_name() + ". It's NOT Effective.\n";
					tempnode->level = current->level + 1;
					tempnode->isleaf = true;

					tempnode->probability = current->probability * (1.0 / (double)total_skills) * (1.0 - ((double)current->attacker.get_skill(i).get_acc() / (double)100));

					tempnode->attacker = current->defender;
					tempnode->defender = temppokemon;
					tempnode->defender.set_power(current->attacker.get_power() + current->attacker.get_skill(i).get_pp());

					if (print)tempnode->printnode();
					current->nextdata.push(tempnode);
				}
			}
			current->isleaf = false;
		}
			
	}
	node* add_level(node* current, bool print_on) {
		if (current == NULL) {
			// CREATE ROOT NODE
			current = new node;
			current->attacker = p1;
			current->defender = p2;
			current->turn = current->attacker.get_name();
			current->probability = 1.0;
			current->level = 0;
			current->isleaf = true;
			current->message = "Battle Started!\n";
			root = current;
			//current->printnode();
			return current;
		}
		else if (current->nextdata.empty()) {
			// CREATE NEXT NODE QUEUE
			find_next_data(current, print_on);
			return current;
		}
		else {
			// TRAVERSE TO LEAVES
			queue <node*> tempdata = current->nextdata;
			while (!tempdata.empty()) {
				current = tempdata.front();
				tempdata.pop();
				current = add_level(current, print_on);
			}
			return current;
		}
	}
	
	//DFS Preorder
	void preorder_dfs(node* current) {
		if (current == NULL)return;
		//cout << "NODE: " << current->probability << " NO: " << ++nodecount << endl;
		nodecount++;
		queue <node*> tempdata = current->nextdata;
		while (!tempdata.empty()) {
			preorder_dfs(tempdata.front());
			tempdata.pop();
		}
	}
	
	//BFS traverse and utilization function
	void printLevel(node* current, int level)
	{
		if (current == NULL)
			return;
		if (level == 1)
			//cout << "NODE: " << current->probability << " NO: " << ++nodecount << endl;
			nodecount++;
		else if (level > 1){
			queue <node*> tempdata = current->nextdata;
			while (!tempdata.empty()) {
				printLevel(tempdata.front(), level - 1);
				tempdata.pop();
			}
		}
	}
	void bfs(node* current) {
		for (int i = 0; i <= maxlevel; i++)printLevel(root, i + 1);
	}
};

int main(int argv, char** argc)
{
	
	/*******************************************************************************/
	// CREATE POKEMONS
	string pokname = "pikachu";
	char* pokname2 = string_to_charptr(pokname);
	int skillcount = find_skillcount(pokname2);
	pokemon pikachu(273, 100, pokname, skillcount);
	pikachu = pokemon_from_file(pikachu, skillcount);
	//cout << endl;

	pokname = "blastoise";
	pokname2 = string_to_charptr(pokname);
	skillcount = find_skillcount(pokname2);
	pokemon blastoise(361, 100, pokname, skillcount);
	blastoise = pokemon_from_file(blastoise, skillcount);
	//cout << endl;
	/*******************************************************************************/
	// PART 1

	// INITIALIZE
	probability_tree* tree = new probability_tree;
	tree->p1 = pikachu;
	tree->p2 = blastoise;
	tree->maxlevel = atoi(argc[2]);
	node* root = NULL;
	node* leaf = NULL;
	// FIRST NODE
	root = tree->add_level(root, false);
	//cout << endl;

	// CREATE GRAPH LEVEL BY LEVEL
	for (int i = 0; i < tree->maxlevel - 1; i++) {
		leaf = tree->add_level(tree->root, false);
		if (tree->p1.get_health() < 0 || tree->p2.get_health() < 0)break;
		//cout << endl;
	}
	// IMPORTANT NOTE: POKEMONS NAME WILL APPEAR ON LEFT IF IT IS ITS TURN
	// EXAMPLE: pikachu_PP: x pikachu_HP: y blastoise_PP: z blastoise_HP: c --> means it is pikachu's turn
	if (tree->p1.get_health() > 0 && tree->p2.get_health() > 0){
		if(!strcmp(argc[1], "part1"))leaf = tree->add_level(tree->root, true);
		else leaf = tree->add_level(tree->root, false);
		//cout << endl;
	}
	/*******************************************************************************/
	// PART 2
	clock_t start, end;
	double extime;
	if(!strcmp(argc[1], "part2")){
		//BFS TRAVERSE
		if(!strcmp(argc[3], "bfs")){
			cout << "BFS: ";
		
			start = clock();
			tree->bfs(tree->root);
			end = clock();
		
			extime = double(end - start) / double(CLOCKS_PER_SEC);
			cout << "Node Count: " << tree->nodecount << " Execution Time of BFS: " << extime << " sec." << endl;
		}
		if(!strcmp(argc[3], "dfs")){
			//DFS TRAVERSE
			tree->nodecount = 0;
			cout << "DFS: ";
		
			start = clock();
			tree->preorder_dfs(tree->root);
			end = clock();
		
			extime = double(end - start) / double(CLOCKS_PER_SEC);
			cout << "Node Count: " << tree->nodecount << " Execution Time of DFS: " << extime << " sec." << endl;
		}
		cout << endl;
	}
	/*******************************************************************************/

	return 0;
}
