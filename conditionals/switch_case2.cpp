#include <iostream>
using namespace std;

int main(){
  char n = ' ';
  cout << "Enter a character (A-Z): ";
  cin >> n;
  switch(n){
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
      cout << "VOWEL!!!\n";
      break;
    default:
      cout << "CONSONANT!!!\n";
      break;
  }
  cout << "Yay, I made it!\n";
  return 0;
}