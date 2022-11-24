// Oytun Demirbilek
// 150150032
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

struct heapnode {
	heapnode* left = NULL;
	heapnode* right = NULL;
	int data;
	string eventname;
};
void swap(int* firstdata, int *seconddata, string *firstevent, string *secondevent)
{
	int temp = *firstdata;
	*firstdata = *seconddata;
	*seconddata = temp;

	string tempstring = *firstevent;
	*firstevent = *secondevent;
	*secondevent = tempstring;
}
heapnode* add_event(heapnode* tree, int time, string name) {
	if (tree == NULL) {
		tree = new heapnode;
		tree->data = time;
		tree->eventname = name;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}

	if (tree->left != NULL && tree->right == NULL) {
		tree->right = add_event(tree->right, time, name);
		return tree;
	}
	tree->left = add_event(tree->left, time, name);
	return tree;


}
void traverse(heapnode * iter) {
	if (iter != NULL) {
		cout << iter->data << ", " << iter->eventname << endl;
		traverse(iter->left);
		traverse(iter->right);
	}
}
heapnode* minheapify(heapnode* iter) {
	if (iter != NULL) {
		if (iter->left != NULL && iter->data > iter->left->data) {
			if (iter->right != NULL && iter->left->data > iter->right->data) {
				//swap current node with right child
				swap(&iter->data, &iter->right->data, &iter->eventname, &iter->right->eventname);
			}
			else {
				//swap current node with left child
				swap(&iter->data, &iter->left->data, &iter->eventname, &iter->left->eventname);
			}
		}

		//cout << iter->data << ", " << iter->eventname << endl;
		iter->left = minheapify(iter->left);
		iter->right = minheapify(iter->right);
	}
	return iter;
	//return minheap;
}

int main() {
	heapnode* tree = NULL;
	//READ EVENT FILE
	string eventname;
	int starttime;
	int endtime;
	char readcurrent = '0';
	FILE* fp = fopen("events.txt", "r");//OPEN FILE

	while(!feof(fp)){
		while (readcurrent != '\t' && !feof(fp)) {
			fscanf(fp, "%c", &readcurrent);
			if (readcurrent == '\t'){
				eventname += '\0';
				fgetc(fp);
			}
			else if(readcurrent != '\n') eventname += readcurrent;
		}
		if(!feof(fp)){
			cout << eventname + "end"<< endl;
			fscanf(fp, "%d", &starttime);
			fscanf(fp, "%d", &endtime);
		
			tree = add_event(tree, starttime, eventname);
			tree = add_event(tree, endtime, eventname);
			readcurrent = '0';
			eventname = "";
		}

	}


	traverse(tree);
	//INITIALIZE
	//heapnode* tree = NULL;
	//tree = add_event(tree, 8, "event-A-start");
	//tree = add_event(tree, 4, "event-C-start");
	//tree = add_event(tree, 6, "event-B-start");
	//tree = add_event(tree, 10, "event-A-end");
	//tree = add_event(tree, 16, "event-B-end");

	//traverse(tree);
	cout << endl;

	heapnode*  minheap = minheapify(tree);
	traverse(minheap);
	cout << endl;

	minheap = minheapify(minheap);
	traverse(minheap);

	//ADD ALL EVENTS


	return 0;
}

//BUILD_MAX_HEAP(A)
//heap_size[A] ← length[A]
//for i ← floor(length[A] / 2) downto 1
//do MAX_HEAPIFY(A, i)

//MAX_HEAPIFY(A, i)
//l ← LEFT(i)
//r ← RIGHT(i); largest ← i
//if l ≤ heap_size[A] and A[l] > A[i]
//then largest ← l
//else largest ← i
//if r ≤ heap_size[A] and A[r] > A[largest]
//then largest ← r
//if largest ≠ i
//then exchange A[i] ↔ A[largest]
//MAX_HEAPIFY(A, largest)
