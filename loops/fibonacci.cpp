#include <iostream>
using namespace std;

int main(){
	int prev = 0;
	int curr = 1;
	int next = 0;
	// print the first number
	// don't print the zero
	cout << prev;
	// don't go past 1000
	while(curr <= 1000){
		// the next value is the sum of the previous two
		next = prev + curr;
		// make prev be current
		prev = curr;
		// make current be next
		curr = next;
		// print the old current value
		cout << ", " << prev;
	}
	cout << endl;
	return 0;
}
