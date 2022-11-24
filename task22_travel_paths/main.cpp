// Oytun Demirbilek
// 150150032

#include <iostream>
#include "graph.h"
#include <vector>
#include <cstdio>
using namespace std;

graph graph_from_file(char* filename)
{
	FILE* fp = fopen(filename, "r");

	int totalnodes, jh, jd, lh, ld, source, dest, weight;
	fscanf(fp, "%d", &totalnodes);
	fscanf(fp, "%d %d %d %d", &jh, &jd, &lh, &ld);
	graph gr1(totalnodes, jh, jd, lh, ld);

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &source, &dest, &weight);
		gr1.add_edge(source, dest, weight);
	}
	return gr1;
}
void print_paths(pair<vector<pair<int, int> >, vector<pair<int, int> > > solution) {
	vector < pair<int, int> > josephs_path = solution.first, lucys_path = solution.second;
	cout << "Joseph's Path, " << "duration: " << josephs_path.back().second << endl;
	for (unsigned int i = 0; i < josephs_path.size();i++) {
		
		cout << "Node: " << josephs_path[i].first << " Time: " << josephs_path[i].second << endl;
		if (i != josephs_path.size() - 1 && josephs_path[i].first == josephs_path[i + 1].first)cout << "--return--" << endl;
	}
	cout << "Lucy's Path, " << "duration: " << lucys_path.back().second << endl;
	for (unsigned int i = 0; i < lucys_path.size(); i++) {
		cout << "Node: " << lucys_path[i].first << " Time: " << lucys_path[i].second << endl;
		if (i != lucys_path.size() - 1 && lucys_path[i].first == lucys_path[i + 1].first)cout << "--return--" << endl;
	}
}
pair<vector<pair<int, int> >, vector<pair<int, int> > > backward_traverse(graph joseph_return_graph, graph lucy_return_graph, vector<pair<int, int> > josephs_path, vector<pair<int, int> > lucys_path) {
	vector<pair<int, int> > josephs_return_path, lucys_return_path, error_vector(1, make_pair(-1, -1));
	int joseph_arrival = josephs_path.back().second, lucy_arrival = lucys_path.back().second;
	pair<vector<pair<int, int> >, vector<pair<int, int> > > return_error = make_pair(error_vector, error_vector);

	/**************************************************           RETURN JOSEPH!             ************************************************/

	//cout << "--return joseph--" << endl;
	josephs_return_path = joseph_return_graph.find_shortest(joseph_return_graph.get_dest("joseph"), joseph_return_graph.get_hotel("joseph"));
	int bound = josephs_return_path.size();
	if (josephs_return_path.front().first != joseph_return_graph.get_dest("joseph") || josephs_return_path.back().first != joseph_return_graph.get_hotel("joseph"))
		return return_error;
	for (int i = 0; i < bound; i++) {
		//cout << "Node: " << josephs_return_path[i].first << " ";
		//cout << "Time: " << josephs_return_path[i].second + 30 + joseph_arrival << endl;
		josephs_path.push_back(make_pair(josephs_return_path[i].first, josephs_return_path[i].second + 30 + joseph_arrival));
	}

	/**************************************************           RETURN LUCY!             ************************************************/

	//cout << "--return lucy--" << endl;
	lucys_return_path = lucy_return_graph.find_shortest(lucy_return_graph.get_dest("lucy"), lucy_return_graph.get_hotel("lucy"));
	bound = lucys_return_path.size();
	if (lucys_return_path.front().first != lucy_return_graph.get_dest("lucy") || lucys_return_path.back().first != lucy_return_graph.get_hotel("lucy"))
		return return_error;
	for (int i = 0; i < bound; i++) {
		//cout << "Node: " << lucys_return_path[i].first << " ";
		//cout << "Time: " << lucys_return_path[i].second + 30 + lucy_arrival << endl;
		lucys_path.push_back(make_pair(lucys_return_path[i].first, lucys_return_path[i].second + 30 + lucy_arrival));
	}
	//cout << endl;
	return make_pair(josephs_path, lucys_path);
}
pair<vector<pair<int, int> >, vector<pair<int, int> > > forward_traverse(graph joseph_travel_graph, graph lucy_travel_graph) {
	vector<pair<int, int> > josephs_path, lucys_path, josephs_return_path, lucys_return_path, error_vector(1, make_pair(-1,-1));
	int joseph_arrival = 0, lucy_arrival = 0;
	pair<vector<pair<int, int> >, vector<pair<int, int> > > return_error = make_pair(error_vector, error_vector);

	/**************************************************           GO JOSEPH!             ***********************************************/

	//cout << "Joseph's Path:" << endl;
	josephs_path = joseph_travel_graph.find_shortest(joseph_travel_graph.get_hotel("joseph"), joseph_travel_graph.get_dest("joseph"));
	if (josephs_path.back().first != joseph_travel_graph.get_dest("joseph") || josephs_path.front().first != joseph_travel_graph.get_hotel("joseph"))
		return return_error;
	for (unsigned int i = 0; i < josephs_path.size(); i++) {
		//cout << "Node: " << josephs_path[i].first << " ";
		//cout << "Time: " << josephs_path[i].second << endl;
	}

	/**************************************************           GO LUCY!             ************************************************/

	//cout << "Lucy's Path:" << endl;
	lucys_path = lucy_travel_graph.find_shortest(lucy_travel_graph.get_hotel("lucy"), lucy_travel_graph.get_dest("lucy"));
	if (lucys_path.back().first != lucy_travel_graph.get_dest("lucy") || lucys_path.front().first != lucy_travel_graph.get_hotel("lucy"))
		return return_error;
	for (unsigned int i = 0; i < lucys_path.size(); i++) {
		//cout << "Node: " << lucys_path[i].first << " ";
		//cout << "Time: " << lucys_path[i].second << endl;
	}

	return make_pair(josephs_path, lucys_path);
}
int main(int argc, char**argv) {
	graph travel_graph;
	graph alternative_graph;
	travel_graph = graph_from_file(argv[1]);
	pair<int, int> intersect;
	bool forw_intersect=false, back_intersect=false, solution_found=true;
	pair<vector<pair<int, int> >, vector<pair<int, int> > > paths, alternatives1, alternatives2, solution;

	// Execute and check intersections in forward pass
	paths = forward_traverse(travel_graph, travel_graph);
	intersect = travel_graph.check_paths(paths.first, paths.second);
	//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
	if (intersect.first == -1)forw_intersect = false;
	else forw_intersect = true;
	// Execute and check intersections in backward pass
	paths = backward_traverse(travel_graph, travel_graph, paths.first, paths.second);
	intersect = travel_graph.check_paths(paths.first, paths.second);
	//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
	//intersect = travel_graph.check_paths(paths.second, paths.first);
	//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
	if (intersect.first == -1) back_intersect = false;
	else back_intersect = true;

	if (forw_intersect) {
		// Intersection while forward pass
		alternative_graph = travel_graph;
		//cout << "Connection removed: " << intersect.first << intersect.second << endl;
		alternative_graph.remove_connection(intersect.first, intersect.second);
		// Change Lucy's Path
		alternatives1 = forward_traverse(travel_graph, alternative_graph);
		
		if (alternatives1.first[0].first != -1) {
			// If the alternative is valid
			intersect = travel_graph.check_paths(alternatives1.first, alternatives1.second);
			//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
			alternatives1 = backward_traverse(travel_graph, travel_graph, alternatives1.first, alternatives1.second);
			// If there is an intersection found, mark the alternative as invalid.
			if (intersect.first != -1) {
				vector < pair<int, int> > error_vector(1, make_pair(-1, -1));
				alternatives1 = make_pair(error_vector, error_vector);
			}
		}
		//else cout << "NO WAY for Lucy's Go" << endl;

		// Get Joseph's node-to-node connection causing intersection
		intersect = travel_graph.check_paths(paths.second, paths.first);
		alternative_graph = travel_graph;
		//cout << "Connection removed: " << intersect.first << intersect.second << endl;
		alternative_graph.remove_connection(intersect.first, intersect.second);
		// Change Joseph's Path
		alternatives2 = forward_traverse(alternative_graph, travel_graph);

		if (alternatives2.first[0].first != -1) {
			// If the alternative is valid
			intersect = travel_graph.check_paths(alternatives2.first, alternatives2.second);
			//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
			alternatives2 = backward_traverse(travel_graph, travel_graph, alternatives2.first, alternatives2.second);
			// If there is an intersection found, mark the alternative as invalid.
			if (intersect.first != -1) {
				vector < pair<int, int> > error_vector(1, make_pair(-1, -1));
				alternatives2 = make_pair(error_vector, error_vector);
			}
		}
		//else cout << "NO WAY for Joseph's Go" << endl;

		// There are no valid alternatives
		if (alternatives1.first.back().first == -1 && alternatives2.first.back().first == -1) {
			cout << "No Solution!" << endl;
			solution_found = false;
		}
		// There is only one valid alternative
		else if (alternatives1.first.back().first != -1 && alternatives2.first.back().first == -1)solution = alternatives1;
		else if (alternatives2.first.back().first != -1 && alternatives1.first.back().first == -1)solution = alternatives2;
		// Both alternatives are valid
		else if (alternatives1.first.back().second + alternatives1.second.back().second >
			alternatives2.first.back().second + alternatives2.second.back().second)
			solution = alternatives2;
		else solution = alternatives1;
	}
	else if(back_intersect){
		// Intersection while backward pass
		alternative_graph = travel_graph;
		//cout << "Connection removed: " << intersect.first << intersect.second << endl;
		alternative_graph.remove_connection(intersect.first, intersect.second);
		// Change Lucy's Path
		alternatives1 = forward_traverse(travel_graph, travel_graph);
		alternatives1 = backward_traverse(travel_graph, alternative_graph, alternatives1.first, alternatives1.second);
		if (alternatives1.first[0].first != -1) {
			// If the alternative is valid
			intersect = travel_graph.check_paths(alternatives1.first, alternatives1.second);
			//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
			// If there is an intersection found, mark the alternative as invalid.
			if (intersect.first != -1) {
				vector < pair<int, int> > error_vector(1, make_pair(-1, -1));
				alternatives1 = make_pair(error_vector, error_vector);
			}
		}
		//else cout << "NO WAY for Lucy's Return" << endl;

		// Get Joseph's node-to-node connection causing intersection
		intersect = travel_graph.check_paths(paths.second, paths.first);
		alternative_graph = travel_graph;
		//cout << "Connection removed: " << intersect.first << intersect.second << endl;
		alternative_graph.remove_connection(intersect.first, intersect.second);
		// Change Joseph's Path
		alternatives2 = forward_traverse(travel_graph, travel_graph);
		alternatives2 = backward_traverse(alternative_graph, travel_graph, alternatives2.first, alternatives2.second);
		if (alternatives2.first[0].first != -1) {
			// If the alternative is valid
			intersect = travel_graph.check_paths(alternatives2.first, alternatives2.second);
			//cout << "INTERSECTION: " << intersect.first << " " << intersect.second << endl;
			// If there is an intersection found, mark the alternative as invalid.
			if (intersect.first != -1) {
				vector < pair<int, int> > error_vector(1, make_pair(-1, -1));
				alternatives2 = make_pair(error_vector, error_vector);
			}
		}
		//else cout << "NO WAY for Joseph's Return" << endl;

		// There are no valid alternatives
		if (alternatives1.first.back().first == -1 && alternatives2.first.back().first == -1) {
			cout << "No Solution!" << endl;
			solution_found = false;
		}
		// There is only one valid alternative
		else if (alternatives1.first.back().first != -1 && alternatives2.first.back().first == -1)solution = alternatives1;
		else if (alternatives2.first.back().first != -1 && alternatives1.first.back().first == -1)solution = alternatives2;
		// Both alternatives are valid
		else if (alternatives1.first.back().second + alternatives1.second.back().second >
			alternatives2.first.back().second + alternatives2.second.back().second)
			solution = alternatives2;
		else solution = alternatives1;

	}

	
	else solution = paths;
	if(solution_found)print_paths(solution);
	return 0;
}