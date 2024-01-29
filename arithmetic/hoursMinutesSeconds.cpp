#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
	//seconds to hours,minutes, & seconds
	bool invalid = true;
	int totalSeconds, hours, secLeft, minutes;

	do{
		cout << "Enter the number of seconds (1-86400): ";
		cin >> totalSeconds;
		if(0 <= totalSeconds and totalSeconds <= 86400){
			invalid = false;
		}else{
			cout << "Please enter a valid value!\n";
		}
	}while(invalid);

	// first take the quotient
	hours = floor(totalSeconds / 3600);
	// the remainder is what's left.
	secLeft = totalSeconds % 3600;

	// now the same for minutes.
	minutes = floor(secLeft / 60);
	secLeft = secLeft % 60;

	cout << hours << "h " << minutes << "m " << secLeft << "s" << endl;
	cout << "Formatted as time:\n";
	cout << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << secLeft << endl;
	return 0;
}
