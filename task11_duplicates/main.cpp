// Oytun Demirbilek
// 150150032

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
int * create_array(int x) {
	int *farr;
	// get enough memory space
	farr = (int *)malloc(x * sizeof(int));
	// fill the array with random integers
	for (int i = 0; i < x; i++) farr[i] = (rand() % x) + 1;
	return farr;
}
void print_array(int * farr, int size) {
	cout << "ARRAY:\n";
	// print an array in specified form
	for (int i = 0; i < size; i++) {
		if ((i + 1) % 10 == 0)cout << farr[i] << "\n";
		else if (i == size - 1)cout << farr[i] << "\n";
		else cout << farr[i] << " ";
		
	}
}
int find_duplications(int * farr, int size) {
	int count = 0;
	// traverse the array to detect duplications and print them
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			if (farr[i] == farr[j]) {
				cout << "(" << j + 1 << ", " << i + 1 << ") ";
				count++;
				break;
			}
		}
	}
	return count;
}
float expect(int n) {
	float guess = (float(n) - 1) / 2;
	return guess;
}
int main()
{
	int number = 0;
	cout << "Enter Array Size: " << endl;
	cin >> number;
	auto start = high_resolution_clock::now(); // get current time
	(srand(time(NULL))); // srand function to get a random seed for each run
	int * arr1 = create_array(number);
	print_array(arr1, number);
	float exp = expect(number);
	cout << "EXPECTED NUMBER OF DUPLICATIONS: " << exp << endl;
	int count = find_duplications(arr1, number);
	cout << "\nDUPLICATION COUNT: " << count << endl;
	free(arr1);// release the used memory by the array
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);// get the time algorithm spent in microseconds

	cout << "EXECUTION TIME: "<< duration.count() << " microseconds" << endl;
	return 0;
}


