#include <iostream>
using namespace std;

int main(){
  int num = 0;

  for(int i=1; i <= 100; i++){
    cout << i << endl;
    num = i;
  }

  cout << "num is: " << num << endl;
  return 0;
}
