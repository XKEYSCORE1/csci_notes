#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    char my_list[10]; // declaring an array of size 10
    srand(time(0)); // seeding the random number generator with current time

    for (int i = 0; i < 10; i++) { // iterating through the array
        int random_num = rand() % 26 + 1; // generating a random number between 1 and 26
        char random_char = random_num + 64; // converting the random number to the range 65-90
        my_list[i] = random_char; // storing the character in the array
    }

    for (int i = 0; i < 10; i++) { // iterating through the array
        cout << my_list[i] << endl; // printing the contents of the array, one item per line
    }

    return 0;
}
