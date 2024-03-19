#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <string>
#include <iterator> 
#include <map> 
#include <utility> 
using namespace std;

struct Multipass{
  string name; // e.g., "Leeloo Dallas"
  string id;  // e.g., "12345"
};

bool nameIsSorted(Multipass testArray[], int size){
	bool sorted = true;
	for(int i=0; i<size; i++){
		// if the next item exists
		if(i+1 < size){
			if(testArray[i].name > testArray[i+1].name){
				return false;
			}
		}
	}
	return sorted;
}

bool idIsSorted(Multipass testArray[], int size){
	bool sorted = true;
	for(int i=0; i<size; i++){
		// if the next item exists
		if(i+1 < size){
			if(testArray[i].id > testArray[i+1].id){
				return false;
			}
		}
	}
	return sorted;
}


int main() {
  int a = 3;
  int b = 4;
  int temp;

  // this is how you swap simple values:
  cout << "\nExample 1 (simple int):\n";
  temp = a;
  a = b;
  b = temp;
  cout << "a: " << a << endl;
  cout << "b: " << b << endl;

  // a little harder, with an array:
  cout << "\nExample 2 (int Array):\n";
  int myList[] = {3,4};
  temp = myList[0];
  myList[0] = myList[1];
  myList[1] = temp;

  for(int i=0; i<2; i++){
    cout << myList[i] << endl;
  }

  // hard example using structs
  Multipass x,y; // create 2 multipasses
  x.name = "Leeloo Dallas";
  x.id = "12345";
  y.name = "Corben Dallas";
  y.id = "67890";

  // exchange struct objects
  cout << "\nExample 3 (struct):\n";
  Multipass tempPass;
  tempPass = x;
  x = y;
  y = tempPass;
  cout << "x: " + x.name + "," + x.id << endl;
  cout << "y: " << y.name << "," << y.id << endl;

  // a struct in an Array:
  cout << "\nExample 4 (in Array):\n";
  Multipass passes[3];
  passes[0] = x; // Corben
  passes[1] = y; // Leeloo

  tempPass = passes[0];
  passes[0] = passes[1];
  passes[1] = tempPass;

  // should've changed places:
  for(int i=0; i<2; i++){
    cout << passes[i].name + ", " + passes[i].id << endl;
  }

  // swap the name strings but not the ids:
  cout << "\nExample 5 (swap just names):\n";
  tempPass.name = passes[0].name;
  passes[0].name = passes[1].name;
  passes[1].name = tempPass.name;
  for(int i=0; i<2; i++){
    cout << passes[i].name + ", " + passes[i].id << endl;
  }

  cout << "\nExample 6 (sorting):\n";
  // Multipass z;
  // z.name = "Jean-Baptiste Emanuel Zorg";
  // z.id = "54321";
  // passes[2] = z;
  passes[2].name = "Jean-Baptiste Emanuel Zorg";
  passes[2].id = "09876";
  for(int i=0; i<3; i++){
    cout << passes[i].name + ", " + passes[i].id << endl;
  }

  cout << "Sort by name string:\n";
  int size = 3;
  while(!nameIsSorted(passes, size)){
    cout << "Starting from the beginning.\n";
		for(int i=0; i<size; i++){
			// if the next item exists
			if((i >= 0) && (i+1 < size)){
				// compare the current element to the next
				if(passes[i].name > passes[i+1].name){
					cout << "Swapping: " << passes[i].name << " for " << passes[i+1].name << endl;
					tempPass = passes[i];
					passes[i] = passes[i+1];
					passes[i+1] = tempPass;
				}
			}
		}
  }

  cout << "\n*** Sorted by name: ***\n";
  for(int i=0; i<3; i++){
    cout << passes[i].name + ", " + passes[i].id << endl;
  }

  cout << "\nSort by ID string:\n";
  while(!idIsSorted(passes, size)){
    cout << "Starting from the beginning.\n";
		for(int i=0; i<size; i++){
			// if the next item exists
			if((i >= 0) && (i+1 < size)){
				// compare the current element to the next
				if(passes[i].id > passes[i+1].id){
					cout << "Swapping: " << passes[i].id << " for " << passes[i+1].id << endl;
					tempPass = passes[i];
					passes[i] = passes[i+1];
					passes[i+1] = tempPass;
				}
			}
		}
  }

  cout << "\n*** Sorted by ID number: ***\n";
  for(int i=0; i<3; i++){
    cout << passes[i].name + ", " + passes[i].id << endl;
  }

  return 0;
}