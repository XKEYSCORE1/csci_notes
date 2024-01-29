#include <iostream>
using namespace std;

// print out the ascii table
int main(){
	int num = 1;
	while(num < 128){
		cout << num << ": " << static_cast<char>(num) << endl;
		num++;
	}
	return 0;
}