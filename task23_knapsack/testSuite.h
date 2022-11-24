// Oytun Demirbilek
// 150150032

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef TESTSUITE_H
#define TESTSUITE_H

using namespace std;
class testSuite
{
private:
	int capacity;
	int level;
	vector<string> headers;
	vector<string> testnames;
	vector<int> runningtimes;
	vector<int> bugs;
	vector<pair<string, vector<int> > > freq_profiles;
	vector<pair<string, vector<int> > > orderedtestcases;
	vector<string> selectedtests;


public:
	testSuite();
	FILE* read_headers(FILE* fp);
	FILE* read_line(FILE* fp);
	int get_cap();
	vector<string> get_headers();
	vector<string> get_testnames();
	vector<int> get_runningtimes();
	vector<int> get_bugs();
	vector<pair<string, vector<int> > > get_testfrequencies();
	vector<string> get_selectedtests();
	void order_testcases();
	pair<vector<int>, vector<int> > knapsack(int length, int capacity, vector<int> weights, vector<int> values);
	void find_distances();
	~testSuite();
};

#endif