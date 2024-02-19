#include <iostream>
using namespace std;

int main(){

	bool answer1, answer2;
	answer1 = answer2 = true;


	if(!answer1){
		cout << "This never happens." << endl;

	}else if(answer1 == true and answer2 != false){
		cout << "This always happens." << endl;

	}else if(answer1 == true or answer2 != false){
		cout << "This never, ever happens." << endl;
        
	}else{
		cout << "This also never happens." << endl;
	}


	if(true){
		cout << "Hooray!" << endl;
	}


  	int x = 0;



	if(1/x){
		cout << "This is fine." << endl;
	}


	return 0;
}