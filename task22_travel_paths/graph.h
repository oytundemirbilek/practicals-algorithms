// Oytun Demirbilek
// 150150032

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
using namespace std;
class graph
{
private:
	int totalnodes;
	int jh, jd, lh, ld;
	vector<vector<int> > adj;

public:
	graph();
	graph(int totalnodes, int jh, int jd, int lh, int ld);
	void add_edge(int source, int dest, int weight);
	void remove_connection(int start_node, int end_node);
	void print_graph();
	vector<pair<int, int> > find_shortest(int source, int dest);
	vector<pair<int, int> > set_path(vector<int> parents, int dest);
	pair<int, int> check_paths(vector<pair<int, int> > firstpath, vector<pair<int, int> > secondpath);
	int get_hotel(string name);
	int get_dest(string name);

	int get_totalnodes();

	~graph();
};

#endif