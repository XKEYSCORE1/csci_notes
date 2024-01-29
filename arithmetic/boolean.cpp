#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main(){
	int x,y,z;
	x = 3;
	cout << "x: " << x << endl;

	// evaluating expressions
	y = 2 * pow(x,2) + 3*x + 1;
	cout << "2 * pow(x,2) + 3*x + 1: " << y << endl;

	// modulus (remainder)
	cout << "10 % 3: ";
	z = 10 % 3;
	cout << z << endl;

	cout << "11 % 3: ";
	z = 11 % 3;
	cout << z<< endl;

	cout << "12 % 3: ";
	z = 12 % 3;
	cout << z << endl;

	// implicitly converting without concatenation
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;

	//boolean comparisons
	bool a,b,c;
	b = (x == 3);
	cout << b << endl;

	b = (x != 4);
	cout << b << endl;

	b = (x != 3);
	cout << b << endl;

	cout << "true == 1: " << (true == 1) << endl;

	cout << "true == 0: " << (true == 0) << endl;

	a = true;
	cout << "a: " << a << endl;

	b = false;
	cout << "b: " << b << endl;

	cout << "a == b: " << (a==b) << endl;

	c = not a;
	cout << "!a: " << c << endl;

	c = not b;
	cout << "!b: " << c << endl;
	
	c = (a and not b);
	cout << "a and !b: " << c << endl;
	
	c = (a and not b);
	cout << "a && !b: " << c << endl;
	
	c = (a or not b);
	cout << "a or b: " << c << endl;
	
	c = (a or b);
	cout << "a || b: " << c << endl;
	
	c = (not a or b);
	cout << "!a or b: " << c << endl;
	
	c = (not a and not b);
	cout << "!a and !b: " << c << endl;
	
	c = (a and not b or b);
	cout << "a and !b or b: " << c << endl;
	
	c = (a or not b and b);
	cout << "!a or !b and b: " << c << endl;

	string name;
	cout << "What is your name? ";
	cin >> name;
	cout << "Hello," << name << '.' << endl;

	// looping
	// create a while loop that counts from 1 to 100 by 3.
	cout << "\nLooping with while 1-100 by 3" << endl;
	cout << "With a while loop:" << endl;
	// initial condition
	int n = 1;
	while(n <= 100){
		cout << n << endl;
		n += 3;
	}

	// equivalent for loop:
	cout << "\nWith a while loop:" << endl;
	for(n = 1; n <= 100; n+=3){
		cout << n << endl;
	}

	// create a for loop that counts from 0 to 100 by 5.
	cout << "\nLooping with for 0-100 by 5" << endl;
	cout << "With a while loop:" << endl;
	// initial condition
	n = 0;
	while(n <= 100){
		cout << n << endl;
		n += 5;
	}

	// equivalent for loop:
	cout << "\nWith a while loop:" << endl;
	for(n = 0; n <= 100; n+=5){
		cout << n << endl;
	}

	return 0;
}