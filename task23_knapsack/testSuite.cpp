// Oytun Demirbilek
// 150150032

#include "testSuite.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;
int find_max(vector<int> v) {
    int max_elem = 0;
    int index = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > max_elem) {
            max_elem = v[i];
            index = i;
        }
    }
    return index;
}
int find_min(vector<int> v) {
    int min_elem = 99999;
    int index = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < min_elem) {
            min_elem = v[i];
            index = i;
        }
    }
    return index;
}
int min(int a, int b) {
    return (a < b) ? a : b;
}
int max(int a, int b) {
    int max_val = (a > b) ? a : b;
    return max_val;
}

vector<int> convert(vector<int> testcase) {
    vector<int> ordered_seq;
    int min_index = 0;
    for (int i = 0; i < testcase.size(); i++) {
        min_index = find_min(testcase);
        testcase[min_index] = 999999;
        ordered_seq.push_back(min_index + 1);
    }
    return ordered_seq;
}
void reorder(vector<int> distances) {
    // Insertion Sort
    int next;
    vector<int> ordereddist;
    next = find_min(distances);
    distances[next] = 0;
    ordereddist.push_back(next + 1);
    for (int i = 0; i < distances.size()-1; i++) {
        next = find_max(distances);
        distances[next] = -1;
        ordereddist.push_back(next + 1);

    }

    for (int i = 0; i < ordereddist.size(); i++)
        cout << ordereddist[i] << " ";
    cout << endl;
}
vector<int> most_significant(vector< vector<int> > testcases) {
    vector<int> basecase;
    int max_nonzero = 0;
    int count_nonzero = 0;
    int index = 0;
    for (int j = 0; j < testcases.size(); j++) {
        // One Test Case
        for (int k = 0; k < testcases[j].size(); k++) {
            if (testcases[j][k] != 0)count_nonzero++;
        }
        if (count_nonzero > max_nonzero) {
            basecase = testcases[j];
            index = j;
            max_nonzero = count_nonzero;
        }
        count_nonzero = 0;
    }
    //cout << "MOST SIGNIFICANT: " << index + 1 << endl;
    return basecase;
}
int levenshtein(vector<int> first_seq, vector<int> second_seq) {

    vector<int> v(first_seq.size() + 1, 0);
    vector <vector<int> > memoize;
    memoize.push_back(v);
    memoize.push_back(v);

    // Starting with 0, 1, 2, 3... N for first sequence
    for (int i = 0; i <= first_seq.size(); i++) memoize[0][i] = i;

    // Iterate second sequence
    for (int i = 1; i <= second_seq.size(); i++) {
        // Compare with first sequence
        for (int j = 0; j <= first_seq.size(); j++) {
            // if first sequence is empty
            if (j == 0) memoize[i % 2][j] = i;
            
            // if both numbers are same
            else if (first_seq[j - 1] == second_seq[i - 1]) memoize[i % 2][j] = memoize[(i - 1) % 2][j - 1];
            
            // if numbers are not same, choose the optimum solution between insert, remove, replace
            else memoize[i % 2][j] = 1 + min(memoize[(i - 1) % 2][j], min(memoize[i % 2][j - 1],memoize[(i - 1) % 2][j - 1]));
            
        }
    }
    return memoize[second_seq.size() % 2][first_seq.size()];
}


testSuite::testSuite()
{
    char* buffer = new char;
    char c;
    FILE* fp = fopen("data.txt", "r");
    int num_lines = 0;
    while (!feof(fp)) {
        c=fgetc(fp);
        if (c == '\n')num_lines++;
    }
    //cout << num_lines << endl;
    rewind(fp);

    c = fgetc(fp);
    while(c!=':')c = fgetc(fp);
    fscanf(fp, " %d", &this->capacity);
    fp = this->read_headers(fp);
    
    for (int i = 0; i < num_lines - 3;i++)fp = this->read_line(fp);

    fclose(fp);
}
FILE* testSuite::read_headers(FILE* fp) {
    char c = fgetc(fp);
    c = fgetc(fp);
    string name = "";
    int num;
    c = fgetc(fp);
    while (c != '\n') {
        if (c == ' ') {
            this->headers.push_back(name);
            name = "";
        }
        else name = name + c;
        c = fgetc(fp);
    }
    this->headers.push_back(name);
    return fp;
}
FILE* testSuite::read_line(FILE* fp) {
    
    string name = "";
    char c = fgetc(fp);
    while (c != ' ') {
        name = name + c;
        c = fgetc(fp);
    }
    this->testnames.push_back(name);
    //cout << name << endl;

    int num;
    fscanf(fp, "%d", &num);
    this->bugs.push_back(num);
    fscanf(fp, "%d", &num);
    this->runningtimes.push_back(num);

    vector <int> freq;
    while (c != '\n' && c != '\t') {
        fscanf(fp, "%d", &num);
        freq.push_back(num);
        c = fgetc(fp);
        if (c == ' ' || c == '\t' || c == '\n') {
            //for (int i = 0; i < freq.size(); i++)cout << freq[i];
            //cout << endl;
            this->freq_profiles.push_back(make_pair(name, freq));
            freq.clear();
        }
        
    }
    return fp;
}


void testSuite::find_distances() {
    int dist = 0;
    int basecase_index;
    vector<int>basecase;
    vector<vector<int> > testcases;
    vector <int> distances;
    for (int i = 0; i < this->selectedtests.size(); i++) {
        for (int j = 0; j < this->freq_profiles.size(); j++) {
            if (this->freq_profiles[j].first == this->selectedtests[i])
                testcases.push_back(this->freq_profiles[j].second);
        }
        
        basecase = most_significant(testcases);
        basecase = convert(basecase);
        
        for (int j = 0; j < this->orderedtestcases.size(); j++) {
            if (this->orderedtestcases[j].first == this->selectedtests[i]) {
                dist = levenshtein(basecase, this->orderedtestcases[j].second);
                distances.push_back(dist);
            }
                
        }
        cout << "Order of Test Cases in Test Suite " << selectedtests[i] << ":" << endl;
        reorder(distances);


        basecase.clear();
        testcases.clear();
        distances.clear();
    }
}
void testSuite::order_testcases() {
    for (int i = 0; i < this->freq_profiles.size(); i++) {
        this->orderedtestcases.push_back(make_pair(this->freq_profiles[i].first, convert(this->freq_profiles[i].second)));
    }
}


pair<vector<int>, vector<int> > testSuite::knapsack(int length, int capacity, vector<int> weights, vector<int> values) {
    int n, w;
    vector<vector<int> > KnapsackMatrix(length + 1);
    vector<int> included_weights;
    vector<int> included_values;
    for (int i = 0; i < length + 1; i++) KnapsackMatrix[i].resize(capacity + 1);

    // Bottom Up Approach to Build Table
    for (n = 0; n <= length; n++) {
        for (w = 0; w <= capacity; w++) {

            if (n == 0 || w == 0) KnapsackMatrix[n][w] = 0;

            else if (weights[n - 1] <= w)
                KnapsackMatrix[n][w] = max(values[n - 1] + KnapsackMatrix[n - 1][w - weights[n - 1]], KnapsackMatrix[n - 1][w]);

            else KnapsackMatrix[n][w] = KnapsackMatrix[n - 1][w];
        }
    }

    // Optimal Solution
    int res = KnapsackMatrix[length][capacity];
    //cout << res << endl;
    
    w = capacity;
    for (n = length; n > 0 && res > 0; n--) {
        if (res != KnapsackMatrix[n - 1][w]) {

            // This Test is included.
            // cout << weights[i - 1] << " ";
            this->selectedtests.push_back(this->testnames[n - 1]);
            included_weights.push_back(weights[n - 1]);
            included_values.push_back(values[n - 1]);
            
            res = res - values[n - 1];
            w = w - weights[n - 1];
        }
    }
    //cout << endl;
    return make_pair(included_values, included_weights);
}

int testSuite::get_cap()
{
    return this->capacity;
}
vector<string> testSuite::get_headers()
{
    return this->headers;
}
vector<string> testSuite::get_testnames()
{
    return this->testnames;
}
vector<int> testSuite::get_runningtimes()
{
    return this->runningtimes;
}
vector<int> testSuite::get_bugs()
{
    return this->bugs;
}
vector<pair<string, vector<int> > > testSuite::get_testfrequencies()
{
    return this->freq_profiles;
}
vector<string> testSuite::get_selectedtests()
{
    return this->selectedtests;
}


testSuite::~testSuite()
{

}