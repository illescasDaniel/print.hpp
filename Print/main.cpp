#include <vector>
#include "print.h"

int main() {
	
	// Classic way...
	vector<int> vect1 = {1,2,3,4};
	
	cout << "Vector: ";
	
	for (int value: vect1) {
		cout << value << ' ';
	}
	cout << '\n' << endl;
	
	// New way
	print("Random number:", arc4random_uniform(1000));
	
	print("Vector:", to_string(vect1));
	
	const size_t size = 6;
	int array[size] = {1,2,3,4,5,6};
	print("My array:", to_string(array,size));
	
	int * array2 = new int[3] {1,2,3};
	print("Array2:", to_string(array2,3));
	delete[] array2;
	
	// Matrix
	const size_t rows = 3, cols = 2;
	
	int matr[rows][cols] = {{1,2},{3,4},{5,6}};
	print("This is a matrix:", to_string(matr,rows,cols));
	
	int ** matrix = new int * [rows];
	for (size_t i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
		
		for (size_t j = 0; j < cols; j++) {
			matrix[i][j] = arc4random_uniform(10000);
		}
	}

	print("Dynamic matrix:", to_string(matrix,rows,cols));
	
	for (size_t i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	
    return 0;
}
