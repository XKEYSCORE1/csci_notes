// Array example
#include <iostream>
#include <iomanip>
#include <string>
#define MAX_ARRAY 10
using namespace std;

int main(){

	int x = 0;
	float y = 0.0;
	char blank = ' ';
	string empty_str = "";

	int numbers[MAX_ARRAY];
	float decimals[MAX_ARRAY];
	char letters[25];
	string names[MAX_ARRAY];
	string fnames[MAX_ARRAY] = {
		"Harrison",
		"Sean",
		"Rutger",
		"Edward James",
		"M. Emmet",
		"Daryl",
		"William",
		"Brion",
		"Joe",
		"Joanna"
	};
	string lnames[MAX_ARRAY] = {
		"Ford",
		"Young",
		"Hauer",
		"Olmos",
		"Walsh",
		"Hannah",
		"Sanderson",
		"James",
		"Turkel",
		"Cassidy"
	};

	// arrays don't start out with any values.
	// you have to initialize them.
	cout << "Initializing arrays:\n";
	for(int i = 0; i < MAX_ARRAY; i++){
		numbers[i] = x;
		decimals[i] = y;
		letters[i] = blank;
		names[i] = empty_str;
	}

	cout << "Numbers:\n";
	for(int j = 0; j < MAX_ARRAY; j++){
		cout << "[" << j << "]: " << numbers[j] << endl;
	}

	cout << "\nDecimals:\n";
	for(int k = 0; k < MAX_ARRAY; k++){
		cout << "[" << k << "]: " << decimals[k] << endl;
	}

	cout << "\nLetters:\n";
	for(int l = 0; l < MAX_ARRAY; l++){
		cout << "[" << l << "]: " << "'" << letters[l] << "'" << endl;
	}

	cout << "\nNames:\n";
	for(int m = 0; m < MAX_ARRAY; m++){
		cout << "[" << m << "]: " << "\"" << names[m] << "\"" << endl;
	}

	cout << "\nSetting values.\n";
	x = 0;
	while(x < MAX_ARRAY){
		numbers[x] = x+1;
		decimals[x] = (x+1) * 1.1;
		names[x] = "string  ";
		names[x][7] = static_cast<char>(x+65);
		letters[x] = static_cast<char>(x+97);
		x++;
	}

	cout << "Numbers:\n";
	for(int a = 0; a < MAX_ARRAY; a++){
		cout << "[" << a << "]: " << numbers[a] << endl;
	}

	cout << "\nDecimals:\n";
	for(int b = 0; b < MAX_ARRAY; b++){
		cout << "[" << b << "]: " << setw(4) << setprecision(4) << showpoint << right << decimals[b] << endl;
	}

	cout << "\nNames:\n";
	for(int c = 0; c < MAX_ARRAY; c++){
		cout << "[" << c << "]: " << "\"" << names[c] << "\"" << endl;
	}

	cout << "\nLetters: " << letters << endl;

	cout << "\nParallel arrays (fname & lname):\n";
	for(int d = 0; d < MAX_ARRAY; d++){
		cout << "[" << d << "]: " << fnames[d] << " " << lnames[d] << endl;
	}

	return 0;
}