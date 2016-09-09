#include <iostream>
#include <vector>
#include "print.h"

using namespace std;

int main(int argc, const char * argv[]) {
	
	// Classic way...
	vector<int> vect1 = {1,2,3,4};
	
	cout << "Vector: ";
	
	for (int value: vect1) {
		cout << value << ' ';
	}
	cout << '\n' << endl;
	
	// New way
	print("Vector:", to_string(vect1));
	
	int array[6] = {1,2,3,4,5,6};
	
	print("My array:", to_string(array,6));
	
	print("Random number:", arc4random_uniform(1000));
	
    return 0;
}
