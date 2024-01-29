#include <iostream>
#include <iomanip>
using namespace std;

int main(){

	// float n = 65.0;
	// int m = 90;
	// cout << "trying float: ";
	// cout << static_cast<char>(n) << endl;
	// cout << "trying int: ";
	// cout << static_cast<char>(m) << endl;
	// n = m;
	// cout << "changed value: ";
	// cout << static_cast<char>(n) << endl;

	for(int x = 0; x <= 255; x++){
		cout << setw(3) << setfill('0') << right << x << ": " << static_cast<char>(x) << endl;
	}

	return 0;
}