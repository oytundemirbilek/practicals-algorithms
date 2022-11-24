// Oytun Demirbilek
// 150150032
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

//data type to handle multiple returns
struct output{
	string eventname;
	int eventtime;
};
//swaps 2 nodes in a tree
void swap(int* firsttime, int *secondtime, string *firstevent, string *secondevent){
	int temp = *firsttime;
	*firsttime = *secondtime;
	*secondtime = temp;

	string tempstring = *firstevent;
	*firstevent = *secondevent;
	*secondevent = tempstring;
}
class minheap{
	int* timearray;
	string* eventarray;
	int capacity;
	int size;
public:
	minheap(int maxsize);
	void minheapify(int i);
	output* remove_event();
	void add_event(int eventtime, string eventname);
	int getmin(){ return timearray[0]; } 
	int getsize(){return size;}
};
//constructor of the minheap object
minheap::minheap(int maxsize){
	size = 0;
	capacity = maxsize;
	timearray = new int[maxsize];
	eventarray = new string[maxsize];
}
//adds a node contains of eventname start or eventname end with its time
void minheap::add_event(int eventtime, string eventname){
	size++;
	int i = size - 1;
	timearray[i] = eventtime;
	eventarray[i] = eventname;

	//to maintain the minheap property, the new node needs to find its right place
	while (i != 0 && timearray[(i - 1) / 2] > timearray[i])
	{
		swap(&timearray[i], &timearray[(i - 1) / 2], &eventarray[i], &eventarray[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
//extracts the node on top of the tree which has the minimum time value
output* minheap::remove_event(){
	//handles underflow
	if (size <= 0)return NULL;
	//returns the minimum value and removes it from tree
	output* result = new output;
	result->eventtime = timearray[0];
	result->eventname = eventarray[0];
	timearray[0] = timearray[size - 1];
	eventarray[0] = eventarray[size - 1];
	size--;
	//to keep the tree minheap
	minheapify(0);

	return result;
}
void minheap::minheapify(int i){
	//find left node and right node
	int left = (2 * i + 1);
	int right = (2 * i + 2);
	int smallest = i;
	//check left and right to find which is smallest
	if (left < size && timearray[left] < timearray[i])
		smallest = left;
	if (right < size && timearray[right] < timearray[smallest])
		smallest = right;
	//if right or left is found as the smallest, swap places and minheapify
	if (smallest != i)
	{
		swap(&timearray[i], &timearray[smallest], &eventarray[i], &eventarray[smallest]);
		minheapify(smallest);
	}
}

minheap buildfromfile(char*filename){
	FILE* fp = fopen(filename, "r");
	char buffer[50];
	int counter = 0;
	string eventname;
	int starttime;
	int endtime;
	char readcurrent = '0';
	//Find capacity of the heap needed
	while (!feof(fp)) {
		fgets(buffer, 50,fp);
		//check if the line is empty or not(handles last line in file)
		if(buffer != NULL)counter++;

	}
	//heap capacity equals to 2 x number of non-empty lines in file
	int heapcap = counter * 2;
	rewind(fp);
	//define minheap
	minheap tree(heapcap);
	//read file until the end
	while (!feof(fp)) {
		//read all caharacters until tab seperation
		while (readcurrent != '\t' && !feof(fp)) {
			fscanf(fp, "%c", &readcurrent);
			//end of searching event name
			if (readcurrent == '\t') {
				eventname += '\0';
				//skip next whitespace char
				fgetc(fp);
			}
			//append new found char of eventname
			else if (readcurrent != '\n') eventname += readcurrent;
		}
		//read integers in the following characters in current line
		if (!feof(fp)) {
			fscanf(fp, "%d", &starttime);
			fscanf(fp, "%d", &endtime);
			//create nodes with information found
			tree.add_event(starttime, eventname + " START");
			tree.add_event(endtime, eventname + " END");
			//empty iterator variables for the next iteration
			readcurrent = '0';
			eventname = "";
		}

	}
	fclose(fp);
	return tree;
}

int main(int argc, char ** argv)
{

	minheap tree = buildfromfile(argv[1]);

	output* show;

	for(int i = 0;;i++){
		//loop break if the tree is empty
		if(tree.getsize() != 0)
			//print current event if the time matches
			if(i == tree.getmin()){
				show = tree.remove_event();
				cout << "TIME " << i << ": " << show->eventname << "ED" << endl;
				//handles next event if it happens in the same time
				if(tree.getmin() == i && tree.getsize() != 0)i--;
			}
			else{
				cout << "TIME " << i << ": NO EVENT" << endl;
			}
		else {
			cout << "TIME " << i - 1 << ": NO MORE EVENTS, SCHEDULER EXITS" << endl;
			break;
		}
	}
	
	return 0;
}
