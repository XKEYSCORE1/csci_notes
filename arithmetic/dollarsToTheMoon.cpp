#include <iostream>
#include <string>
using namespace std; 

string insertCommas(long long int value){
	string s = to_string(value);
	int n = s.length() - 3;
	int end = (value >= 0) ? 0 : 1; // support for negative numbers
	while (n > ) {
		s.insert(n, ","); // insert the comma into the string at position n
		n -= 3; //go to the left 3 places
	}
	return s;
}

int main() {
	float dollarThickness = 0.10922;
	int kmToMoon = 384400; //roughly
	int mmToKm = 1000000;  // 1000^2
	float dollarsInMm = 1/dollarThickness;
	float dollarsToKm = dollarsInMm * mmToKm; 
	long long int x = dollarsToKm * kmToMoon;
	cout << "Unformatted result: " << x << endl;
	cout << insertCommas(x) << " Dollars piled to the moon!\n";
	return 0;
}
