#include <iostream> // basic i/o
#include <cstdlib> // rand() and srand()
#include <ctime> // system time
using namespace std;

int main() {
  cout << "Hello Adventurer!\n";

  unsigned int scores[6];
  string attr[] = {
    "STR", //strength
    "DEX", //dexterity
    "INT", //intelligence
    "WIS", //wisdom
    "CON", //constitution
    "CHA"  //charisma
  };
  string name = "";
  unsigned int die1,die2,die3;
  unsigned int seed = time(0);
  srand(seed);

  // TODO: loop 6 times, one iteration per attribute
  int count = 0;
  int total = 0;
  while(count < 6){
    // TODO: each attribute is the total of 3d6
    die1 = (rand() % 6) + 1;
    die2 = (rand() % 6) + 1;
    die3 = (rand() % 6) + 1;
    // TODO: show the individual die rolls
    cout << "\n*** ROLL " << count+1 << "***\n";
    cout << "1st d6: " << die1 << endl;
    cout << "2nd d6: " << die2 << endl;
    cout << "3rd d6: " << die3 << endl;

    total = die1 + die2 + die3;
    cout << "Total: " << total << endl;
    // TODO: assign the total value to the scores array at the correct index.
    scores[count] = total;
    count++;
  }
  
  // TODO: print out the string label and scores in order.
  cout << "\nWhat is your character's name? ";
  cin >> name;
  cout << "\n" << name << "'s Character Sheet\n";
  count = 0;
  while(count < 6){
    cout << attr[count] << ": " << scores[count] << endl;
    count++;
  }

  return 0;
}