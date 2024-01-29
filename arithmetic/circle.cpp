#include <iostream>
#include <cmath>
using namespace std;
// # define M_PI 3.14159265358979323846;  /* pi const in math library */
// const float PI = 3.14159265358979323846;

int main(){
	float radius,circ,area;
	cout << "Enter the radius of the circle: ";
	cin >> radius;
	circ = M_PI * 2 * radius;
	area = M_PI * pow(radius,2);
	// circ = PI * 2 * radius;
	// area = PI * pow(radius,2);
	cout << "The circumference is:" << circ << endl;
	cout << "The area is: " << area << endl;
}
