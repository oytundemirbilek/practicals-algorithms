// Oytun Demirbilek
// 150150032
#include "graph.h"
#include <iostream>
#include <vector>
using namespace std;
#define INFINITE 99999

graph::graph()
{
    this->totalnodes = 0;
    this->jh = 0;
    this->jd = 0;
    this->lh = 0;
    this->ld = 0;
}

graph::graph(int totalnodes, int jh, int jd, int lh, int ld)
{
    this->totalnodes = totalnodes;
    this->jh = jh;
    this->jd = jd;
    this->lh = lh;
    this->ld = ld;
    this->adj.resize(totalnodes);
    for (int i = 0; i < totalnodes; i++)
        this->adj[i].resize(totalnodes);
}
void graph::add_edge(int source, int dest, int weight) {
    this->adj[source][dest] = weight;
}
void graph::remove_connection(int start_node, int end_node){
    
    //cout << "Weight: "<<this->adj[start_node][end_node] <<endl;
    this->adj[start_node][end_node] = 0;

    
}
void graph::print_graph()
{
    cout << "JOSEPH --> HOTEL: " << jh << " DESTINATION: " << jd << endl;
    cout << "LUCY --> HOTEL: " << lh << " DESTINATION: " << ld << endl;
    for (int i = 0; i < this->totalnodes; i++) {
        for (int j = 0; j < this->totalnodes; j++)cout << adj[i][j] << " ";
        cout << endl;
    }
}

vector<pair<int, int> > graph::set_path(vector<int> parents, int dest) {
    vector<pair<int, int> > path;
    int j = dest;
    int distance = 0;
    while(parents[j] != -1) {
        distance = this->adj[parents[j]][j];
        path.insert(path.begin(), make_pair(j,distance));
        j = parents[j];
    }
    path.insert(path.begin(), make_pair(j, 0));
    int total = 0;
    for (unsigned int i = 0; i < path.size(); i++) {
        path[i].second = path[i].second + total;
        total = path[i].second;
    }
    return path;
}
vector<pair<int, int> > graph::find_shortest(int source, int dest)
{
    // Vector of distances
    vector<int> distances(this->totalnodes, INFINITE);
    vector<bool> shortest_path(this->totalnodes, false);
    vector<int> parents(this->totalnodes, -1);
    // Distance of source to itself is 0
    distances[source] = 0;

    // Find shortest path from source for all vertices
    for (int count = 0; count < this->totalnodes - 1; count++) {

        int min = INFINITE, min_index;

        // Find Minimum Distance
        for (int v = 0; v < this->totalnodes; v++)
            if (shortest_path[v] == false && distances[v] <= min)
                min = distances[v], min_index = v;

        // Mark minimum index as True
        shortest_path[min_index] = true;

        // Update distance values of the adjacent vertices of the picked vertex.
        for (int v = 0; v < this->totalnodes; v++) {
            if (!shortest_path[v] && this->adj[min_index][v] && distances[min_index] != INFINITE && distances[min_index] + this->adj[min_index][v] < distances[v]) {
                distances[v] = distances[min_index] + this->adj[min_index][v];
                parents[v] = min_index;
            }
        }
    }
    vector<pair<int, int> > path = this->set_path(parents, dest);
    return path;
}

pair<int,int> graph::check_paths(vector<pair<int, int> > firstpath, vector<pair<int, int> > secondpath)
{
    int prev_node = -1, prev_time = -1;
    for (unsigned int i = 0; i < firstpath.size(); i++)
        for (unsigned int j = 0; j < secondpath.size(); j++) {
            //cout << firstpath[i].first <<" "<< secondpath[j].first <<" "<< firstpath[i].second <<" "<< secondpath[j].second <<" "<< endl;
            if (firstpath[i].first == secondpath[j].first && firstpath[i].second == secondpath[j].second)return make_pair(prev_node, secondpath[j].first);
            if (prev_node == secondpath[j].first && secondpath[j].first == firstpath[i].first && firstpath[i].second >= prev_time && firstpath[i].second <= secondpath[j].second) 
                return make_pair(secondpath[j-2].first,prev_node);
            //if (firstpath[i].first==this->jd && secondpath[j].first==this->jd && secondpath[j].second > firstpath[i].second)
                //return make_pair(prev_node, secondpath[j].first);
            //if (firstpath[i].first == this->ld && secondpath[j].first == this->ld && secondpath[j].second > firstpath[i].second)
                //return make_pair(prev_node, secondpath[j].first);
            prev_node = secondpath[j].first;
            prev_time = secondpath[j].second;
        }
        
    return make_pair(-1,-1);
}

int graph::get_hotel(string name) {
    if (name == "joseph" || name == "Joseph" || name == "JOSEPH")return this->jh;
    else if (name == "lucy" || name == "Lucy" || name == "LUCY")return this->lh;
    else return 0;
}
int graph::get_dest(string name) {
    if (name == "joseph" || name == "Joseph" || name == "JOSEPH")return this->jd;
    else if (name == "lucy" || name == "Lucy" || name == "LUCY")return this->ld;
    else return 0;
}
int graph::get_totalnodes() {
    return this->totalnodes;
}
graph::~graph()
{
    //delete[] adjacencymatrix;
}