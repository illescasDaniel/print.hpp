//  print.h
//  Created by Daniel Illescas Romero on 09/09/2016.

#ifndef print_h
#define print_h

#include <iostream>
#include <map>

using namespace std;

/* PRINT functions */

template <typename Type>
void print(const Type& value) {
	cout << value << endl;
}

template<typename Type, typename ... Args>
void print(const Type& value, const Args& ...args) {
	cout << value << ' ';
	print(args...);
}

/* TO_STRING functions */

// Stub function (don't use externally) (useful when trying to pass a string to the 'to_string' function, to avoid problems)
string to_string(string str) {
	return str;
}

// Return a string given a container (vector, array, list...)
template <typename Container>
string to_string(const Container& cont) {
	
	string str;
	size_t position = 0;
	
	str += "[";
	
	for (auto value: cont) {
		str += to_string(value);
		
		if (position+1 < cont.size()) {
			str += ", ";
		}
		
		position++;
	}
	
	str += "]";
	
	return str;
}

// Return a string given a map
template <typename Key, typename Type>
string to_string(const map<Key,Type>& map) {

	string str, key, type;
	size_t position = 0;
	
	str += "[";
	
	for (auto value: map) {
		
		if (typeid(value.first) == typeid(string)) {
			key = "\"" + to_string(value.first) + "\"";
		}
		else {
			key = to_string(value.first);
		}

		if (typeid(value.second) == typeid(string)) {
			type = "\"" + to_string(value.second) + "\"";
		}
		else {
			type = to_string(value.second);
		}
		
		str += to_string(key) + ": " + to_string(type);
		
		if (position+1 < map.size()) {
			str += ", ";
		}
		
		position++;
	}
	
	str += "]";
	
	return str;
}

// Return a string given a classic array and its size
template <typename Type>
string to_string(const Type * array, size_t size) {
	
	string str;
	
	str += "[";
	
	for (size_t i = 0; i < size; i++) {
		str += to_string(array[i]);
		
		if (i+1 < size) {
			str += ", ";
		}
	}
	
	str += "]";
	
	return str;
}

// Return a string given a matrix and its size
template <typename Type>
string to_string(const Type& matrix, size_t rows, size_t cols) {
	
	string str;
	
	str += "[";
	
	for (size_t i = 0; i < rows; i++) {
		str += "[";
		for (size_t j = 0; j < cols; j++) {
			str += to_string(matrix[i][j]);
			
			if (j+1 < cols) {
				str += ", ";
			}
		}
		
		if (i+1 < rows) {
			str += "], ";
		}
		else {
			str += "]";
		}
		
	}
	
	str += "]";
	
	return str;
}

#endif /* print_h */
