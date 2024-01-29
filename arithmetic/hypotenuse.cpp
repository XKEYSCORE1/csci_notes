#include <iostream>
#include <cmath>
using namespace std;

// make our own
float hypotenuse(float a, float b){
	return sqrt(pow(a,2) + pow(b,2));
}

int main(){
	float a,b;

	cout << "\t*** Hypotenuse Calculator ***" << endl;
	cout << "Enter side A: ";
	cin >> a;
	cout << "Enter side B: ";
	cin >> b;

	cout << "The hypotenuse is: " << hypotenuse(a,b) << endl;
  // compare against the cmath lib:
  cout << "The hypotenuse is: " << hypot(a,b) << endl;
  
	return 0;
}
