#include <iostream>
#include <cmath>
#include <iomanip> // output formatting
using namespace std;

int main() {

  unsigned long long bignum;
  int x = 0;

  do{
    bignum = pow(2,x); // pow(x,y) from cmath
    // right and setw(x) from iomanip
    cout << "2^" << setw(2) << x << ": ";
    cout << right << setw(20) << bignum << endl;
    x++;
  }while(x <= 64); // note where the overflow occurs

  return 0;
}
