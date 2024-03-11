/*
Exam 1 Lab Section
author: mdfusco@student.ysu.edu
Please rename this file to YOUR_USERNAME_exam1_lab.cpp
and send as an attachment to james.dittrich+YSU@gmail.com 
*/

#include <iostream> // basic i/o
#include <iomanip> // output formatting
#include <cmath> // math functions
#include <cstdlib> // rand() and srand()
#include <ctime> // system time

using namespace std;

void lab1(void){
/* 
L1: Descending the Staircase (10 pts.)
Produce the output sequence
100, 81, 64, 49, 36, 25, 16, 9, 4, 1
using only a single variable and without using multiplication (*) or addition (+)
*/
	cout << "\n*** L1: Descending the Staircase ***" << endl;

    for(int i = 10; i >= 1; --i) { // start with the power of 10 and decrement until i is greater than or equal to 1

        cout << static_cast<int>(pow(i, 2)); // cast the result of i^2 to an integer and print it

        if (i > 1) { // if i is greater than 1, 
            cout << ", "; // print a comma and a space
        }
    }
    cout << "\n" << endl; // print a newline to separate the output from the next lab

	return;
}



void lab2(int n){
/*
L2: Echoes of Gauss (20 pts.)
Write a function that takes an integer n as input, 
calculates the sum of the first n integers, e.g.:
when n = 3, 1 + 2 + 3 = 6
and prints out the correct value.
It may be helpful to print out intermediate values while 
debugging, comment those statements out afterwards.
*/
	cout << "\n*** L2: Echoes of Gauss ***" << endl;

    int sum = 0; // declare a variable to hold the sum of the first n integers

    cout << "Enter a positive integer: "; // prompt the user to enter a positive integer
    cin >> n; // get the user's input for n

    for(int z = 1; z <= n ; z++) { // for when z is 1 and less than or equal to n, increment z by 1
        sum += z; // add the current integer to the sum
    }
    cout << "The sum of the first " << n << " integers is: " << sum << endl; // print the sum of the first n integers  

	return;
}



void lab3(void){
/*
L3: Fight Club (10 pts.)
*/
    char sysTime = time(0); // get the system time
    
    srand(static_cast<unsigned int>(sysTime)); // seed the random number generator with the system time

	cout << "\n*** L3: Fight Club **" << endl;
	cout << "Welcome to Fight Club" << endl;


	int tyler = 0; // initialize Tyler's score to 0 so that the game can be replayed
        int t_random = rand(); // generate a random number
        tyler = t_random % 6 + 1 + rand() % 6 + 1; // add two random numbers between 1 and 6 to get the sum of the two dice

	int robert = 0; // initialize Robert's score to 0 so that the game can be replayed
        int r_random = rand(); // generate a random number
        robert = r_random % 6 + 1 + rand() % 6 + 1; // add two random numbers between 1 and 6 to get the sum of the two dice


    // print the scores and the winner
    if (tyler > robert){ // if Tyler's score is higher than Robert's score
        cout << "Tyler: " << tyler << " | " << " Robert: " << robert << endl; // print the scores
        cout << "Tyler Durden wins!" << endl; // print Tyler as the  winner
    }
    else if (tyler < robert){ // if Tyler's score is lower than Robert's score
        cout << "Tyler: " << tyler << " | " << " Robert: " << robert << endl; // print the scores
        cout << "Robert Paulson wins!" << endl; // print Robert as the winner
    }
    else if (tyler == robert){ // if Tyler's score is equal to Robert's score
        cout << "Tyler: " << tyler << " | " << " Robert: " << robert << endl; // print the scores  
        cout << "It's a draw." << endl; // print that it's a draw
    } 
    else { // if none of the above conditions are met
        cout << "Error: Something went wrong." << endl; // print an error message
    }

	return;
}

int main(){

    lab1(); // call "Descending the Staircase" function
    lab2(0); // call "Echoes of Gauss" function with a placeholder value for int n

char replay = '0'; // declare a variable to hold the user's input

    do { // loop through the game until the user decides to stop
        
        lab3(); // call "Fight Club" function

        cout << "play again (y/n): "; // prompt the user to play again
        cin >> replay; // get the user's input

    } while (replay == 'y'); // repeat the game if the user enters 'y'
   
	return 0; // return 0 to end the program
}

