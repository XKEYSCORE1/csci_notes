#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator> 
#include <map>
#include <utility>
using namespace std;

struct student{
  string name; // e.g., "Harry Potter"
  string house;  // e.g., "Griffindor"
};

bool nameIsSorted(student hogwarts[], int size){ // returns true if the names are sorted in alphabetical order
bool sorted = true; 
for(int i=0; i<size; i++){ // loop through the array
  // if the next item exists
  if(i+1 < size){
    if(hogwarts[i].name > hogwarts[i+1].name){ // if the next item is smaller than the current item
      return false;
    }
  }
}
 return sorted;  // if the loop finishes, the array is sorted
};


bool houseIsSorted(student hogwarts[], int size){ // returns true if the houses are sorted in alphabetical order
  bool sorted = true; 
  for(int i=0; i<size; i++){ // loop through the array
    // if the next item exists
    if(i+1 < size){
      if(hogwarts[i].house > hogwarts[i+1].house){ // if the next item is smaller than the current item
        return false;
      }
    }
  }
  return sorted; // i the loop finishes, the array is sorted
};

// main function
int main() { 
  student a,b,c,d; // create 4 students and assign names and houses 
  a.name = "Harry Potter";
  a.house = "Griffindor";
  b.name = "Cho Chang";
  b.house = "Ravenclaw";
  c.name = "Draco Malfoy";
  c.house = "Slytherin";
  d.name = "Cedric Diggory";
  d.house = "Hufflepuff";
  
  student hogwarts[] = {a,b,c,d}; // create an array of students
 

  student tempStudent; // create a temporary student


  int size = 4; // set the size of the array
  
  while(!nameIsSorted(hogwarts, size)){ // while the array is not sorted (parameters are the array and the size))

    for(int i=0; i<size; i++){ // loop through the array

      if((i >= 0) && (i+1 < size)){ // if the counter i is greater than or equal to 0 and the next item is less than the size of the array

        if(hogwarts[i].name > hogwarts[i+1].name){ // if the next item is smaller than the current item

          tempStudent = hogwarts[i]; // set the temporary student to the current item
          hogwarts[i] = hogwarts[i+1]; // set the current item to the next item
          hogwarts[i+1] = tempStudent; // set the next item to the temporary student
        }
      }
    }
  }
  cout << "\n*** Sorted by name: ***\n";
  
  for(int i=0; i<size; i++){ // loop through the array
    cout << hogwarts[i].name + ", " + hogwarts[i].house << endl; // print the name and house of the student
  }



  while(!houseIsSorted(hogwarts, size)){ // while the array is not sorted (parameters are the array and the size))
  
    for(int i=0; i<size; i++){ // loop through the array
    
      if((i >= 0) && (i+1 < size)){ // if the counter i is greater than or equal to 0 and the next item is less than the size of the array
       
        if(hogwarts[i].house > hogwarts[i+1].house){ // if the next item is smaller than the current item
         
          tempStudent = hogwarts[i]; // set the temporary student to the current item
          hogwarts[i] = hogwarts[i+1]; // set the current item to the next item
          hogwarts[i+1] = tempStudent; // set the next item to the temporary student
        }
      }
    }
  }

  cout << "\n*** Sorted by house: ***\n";
  
  for(int i=0; i<size; i++){ // loop through the array
    cout << hogwarts[i].name + ", " + hogwarts[i].house << endl; // primt the name and house of the student
  }



  return 0; // exit the main function
}