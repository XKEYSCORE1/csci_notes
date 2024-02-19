#include <iostream> // basic i/o
using namespace std;

int main(){

	int nums[] = {4,3,2,1};
	int temp;
	// this is a trick to get the number of elements
	int size = sizeof(nums)/sizeof(nums[0]);
	bool atEnd = false;

	cout << "initial array:\n";
	for(int count=0; count < size; count++){
		cout << "[" << count << "]: " << nums[count] << endl; 
	}

	for(int count=0; count < size; count++){
		if(count+1 == size){
			cout << "I'm at the end.\n";
			atEnd = true;
		}

		if(nums[count] > nums[count+1] and not atEnd){
			temp = nums[count];
			nums[count] = nums[count+1];
			nums[count+1] = temp;
		}
	}

	cout << "sorted array:\n";
	for(int count=0; count < size; count++){
		cout << "[" << count << "]: " << nums[count] << endl; 
	}
	// NOTE: It's not all the way sorted!

	return 0;
}