#include <iostream>
#include <iomanip>
#include <string>
#define MAX_INDEX 11

using namespace std;

int main(){

	string simple2dArray[MAX_INDEX-1][MAX_INDEX-1];

	// create an empty grid
	// for(int row=1; row < MAX_INDEX; row++){
	//   for(int col=1; col < MAX_INDEX; col++){
	//     simple2dArray[row-1][col-1] = "0";
	//   }
	//   cout << endl;
	// }

	// print the grid
	// for(int row=1; row < MAX_INDEX; row++){
	//   for(int col=1; col < MAX_INDEX; col++){
	//     cout << simple2dArray[row-1][col-1] << '\t';
	//   }
	//   cout << endl;
	// }

	// set the values
	for(int row=1; row < MAX_INDEX; row++){
		for(int col=1; col < MAX_INDEX; col++){
			simple2dArray[row-1][col-1] = to_string(row * col);
			cout << setw(3) << right << simple2dArray[row-1][col-1] << '\t';
		}
		cout << endl;
	}
	
	return 0;
}