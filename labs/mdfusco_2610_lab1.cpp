/*
CSIS 2610 - Lab 1
10 points
Due: 2/04/2024 5:10pm 
please name this sourcecode file like "jdittrich_2610_lab1.cpp" - 
using your banner name (that comes before @student.ysu.edu in email)
email to: james.dittrich+YSU@gmail.com as a single .cpp attachment.
replace this comment with author: (your name)
*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main(){

	cout << "\n====Q1: greeting====\n";

	/*
	Q1: greeting (4 points)
	=== pseudocode ===
	prompt user for their (first) name
	print "Hello, <name>"
	prompt user for their birth year
	do some arithmetic
	print "<name> will be <integer> years old in 2023"
	*/

//  *********************************************************
    string name; // declare a string variable to store the user's name

    cout << "Please enter your first name: "; // prompt the user for their name
    cin >> name; // store the user's input in the variable name

    cout << "Hello, " << name << endl; // print a greeting to the user


    int birthYear; // declare an integer variable to store the user's birth year

    cout << "Enter your birth year: "; // prompt the user for their birth year
    cin >> birthYear; // store the user's input in the variable birthYear

    int age = 2023 - birthYear; // calculate the user's age in 2023
    cout << name << " will be " << age << " years old in 2023" << endl; // print the user's age in 2023
// ---------------------------------------------------------

	cout << "\n====Q2: sequence of 8 digits/alternating zeroes and ones ====\n";

	/*
	Q2: print a sequence of alternating zeroes and ones
	print exactly eight numbers, starting with zero e.g.:
	0,1,0,1,0,1,0,1
	print exactly one term per line.
	*/

// *********************************************************
	int i = 0; // declare a counter variable

	while( i < 4 ){ // loop until the counter variable is greater than 4 (4 loops * 2 numbers per loop = 8 numbers)
        cout << "0\n1\n"; // print a 0 and a 1
        i++; // increment the counter variable "i"
	}
// ---------------------------------------------------------

	cout << "\n====Q3: first n integers ^ n ====\n";

	/*
	Q3: print the first 20 integers to the nth power, where n is the current integer
	[1,4,27,...,104857600000000000000000000]
	print exactly 20 numbers, one per line.
	declare variables - you will need a counter!
	use do-while for looping.
	*/

//  *********************************************************    
    int n = 1; // declare a counter variable

	do{
        cout << pow(n, n) << endl; // print the current integer to the nth power
        n++; // increment the counter variable "n"

	}while( n <= 20 ); // loop until the counter variable is greater than 20
// ---------------------------------------------------------

	return 0;

} // end main