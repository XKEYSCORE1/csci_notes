#include <iostream>
using namespace std;

long int myPow(int x, int y) {
	long int result = 1;
	while (y > 0) {
		result = result * x;
		y--;
	}
	return result;
}

int main() {
	cout << "UNLIMITED POWER!\n";
	cout << myPow(2, 3) << endl; // prints '8'
	cout << myPow(3, 1) << endl; // prints '3'
	cout << myPow(2, 0) << endl; // prints '1'
}
