#include <iostream> // basic i/o
using namespace std;

bool isSorted(int nums[], int size){
	int i = 0;
	while(i < size-1){
		// cout << "\nchecking indexes: [" << i << "] & [" << i+1 << "].\n";
		if(nums[i] > nums[i+1]){
			return false; // it's not in increasing order
		}else{
			i++;
		}
	}
	return true; // it must be in increasing order
}

int main(){

	int nums[] = {5,4,3,6,2,1,0};
	int temp; // the SWAP CONTAINER
	// this is a trick to get the number of elements
	int size = sizeof(nums)/sizeof(nums[0]);
	int swapcount = 0;
	
	cout << "initial array:\n";
	for(int count=0; count < size; count++){
		cout << "[" << count << "]: " << nums[count] << endl; 
	}
	cout << "size of the nums array: " << size << endl;

	while(not isSorted(nums, size)){
		for(int count=0; count < size; count++){
			// if the current item is bigger than the next
			// AND not past the end of the list.
			if(nums[count] > nums[count+1] and count+1 < size){
				// SWAP THE VALUES:
				temp = nums[count];
				nums[count] = nums[count+1];
				nums[count+1] = temp;
				swapcount++;
			}
		}
		// UNCOMMENT BELOW TO SEE WHAT HAPPENS.
		// cout << "Sort status: ";
		// if(isSorted(nums,size)){
		//   cout << "True.\n";
		// }else{
		//   cout << "False.\n";
		// }
		// cout << "\ncurrent array state:\n";
		// for(int x=0; x < size; x++){
		//   cout << "[" << x << "]: " << nums[x] << endl; 
		// }
	}

	cout << "sorted array:\n";
	for(int count=0; count < size; count++){
		cout << "[" << count << "]: " << nums[count] << endl; 
	}
	cout << "\nUsed " << swapcount << " swap operations.\n";
	return 0;
}