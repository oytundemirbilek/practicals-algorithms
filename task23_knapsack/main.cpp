// Oytun Demirbilek
// 150150032

#include <iostream>
#include <vector>
#include <string>
#include "testSuite.h"

using namespace std;
int main() {
    testSuite tests;
    // Running Times are Weights
    vector<string> testnames = tests.get_testnames();
    vector<int> weightarray = tests.get_runningtimes();
    vector<int> valuearray = tests.get_bugs();

    // Maximum Running Time
    int weightscap = tests.get_cap();
    int value_len = testnames.size();
    pair<vector<int>, vector<int> > solution = tests.knapsack(value_len, weightscap, weightarray, valuearray);
    vector<string> selected = tests.get_selectedtests();
    for (int i = 0; i < selected.size(); i++)
        cout << "TEST: " << selected[i] << " BUGS: " << solution.first[i] << " TIME: " << solution.second[i] << endl;
    tests.order_testcases();
    tests.find_distances();

	return 0;
}