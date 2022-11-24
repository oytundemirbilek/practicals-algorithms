

#include <cstdio>
#include "board.h"
#include "agent.h"
#include <vector>
#include <chrono> 

using namespace std;
using namespace std::chrono; 

int main(int argc, char **argv){
    auto start = high_resolution_clock::now(); 
    agent gamer(argv[1]);
    int result = gamer.minimax(0,true,15,-999999,999999);
    if (result == 1)
        printf("RESULT: %d\n",1);
    else if (result == -1)
        printf("RESULT: %d\n",2);
    else 
        printf("RESULT: %d (DRAW)\n",0);
    // Get ending timepoint 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Time Elapsed: " << duration.count() * 0.000001 << " seconds" << endl; 
    cout << "Maximizer Nodes: " << gamer.get_node_counts().first << " Minimizer Nodes: " << gamer.get_node_counts().second << endl;
    return 0; 
}