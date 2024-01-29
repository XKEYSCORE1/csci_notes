#include <iostream>
#include <cmath>
#include <iomanip> //setprecision(), setw(), justification left/center/right
using namespace std;

void letterGrade(float grade){
	cout << "Grade: " << setprecision(5) << setw(10) << right << grade << " for the course." << endl;
	cout << "They get a(n): ";
	if (grade >= 90){
		cout << 'A' << endl;
	}else if (80 <= grade and grade < 90){
		cout << 'B' << endl;
	}else if (70 <= grade and grade < 80){
		cout << 'C' << endl;
	}else if (60 <= grade and grade < 70){
		cout << 'D' << endl;
	}else{
		cout << 'F' << endl;
	}
	return;
}

int main(){
	float grade = 0.0;

	while(grade >= 0){
		cout << "Enter the grade percentage or -1 to quit (omit percent symbol): ";
		cin >> grade;
		grade = round(grade); // easy rounding
		// grade = floor(grade); // for the cruel grader
		// grade = ceil(grade); // for the easy grader
		letterGrade(grade);
	}

	return 0;
}

// a simpler version (no function call):
// int main(){
// 	float finalGrade;
// 	cout << "Please enter the final grade percentage: ";
// 	cin >> finalGrade;
//
// 	if(finalGrade >= 90){
// 		cout << "Your grade is: A (" << finalGrade << "%)\n";
// 	}else if(finalGrade >= 80){
// 		cout << "Your grade is: B (" << finalGrade << "%)\n";
// 	}else if(finalGrade >= 70){
// 		cout << "Your grade is: C (" << finalGrade << "%)\n";
// 	}else if(finalGrade >= 60){
// 		cout << "Your grade is: D (" << finalGrade << "%)\n";
// 	}else{
// 		cout << "Your grade is: F (" << finalGrade << "%)\n";
// 	}
//
// 	return 0;
// }
