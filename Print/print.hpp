//  print.hpp
//  Created by Daniel Illescas Romero on 09/09/2016.

#ifndef print_hpp
#define print_hpp

#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <typeinfo>

using namespace std;

/* PRINT functions */

template <typename Type>
void print(const Type& value) {
	cout << value << endl;
}

template <typename Type, typename ... Args>
void print(const Type& value, const Args& ...args) {
	cout << value << ' ';
	print(args...);
}

// To know if a given container is a set or not (Doesn't look good, this is just a temporary way to do it) 
template <typename Container>
bool isSet(const Container& cont) {
	
	if (typeid(set<int>) == typeid(cont) || typeid(set<double>) == typeid(cont) || typeid(set<bool>) == typeid(cont) ||
		typeid(set<float>) == typeid(cont) || typeid(set<string>) == typeid(cont) || typeid(set<char>) == typeid(cont) ||
		
		typeid(multiset<int>) == typeid(cont) || typeid(multiset<double>) == typeid(cont) || typeid(multiset<bool>) == typeid(cont) ||
		typeid(multiset<float>) == typeid(cont) || typeid(multiset<string>) == typeid(cont) || typeid(multiset<char>) == typeid(cont) ||
		
		typeid(unordered_set<int>) == typeid(cont) || typeid(unordered_set<double>) == typeid(cont) || typeid(unordered_set<bool>) == typeid(cont) ||
		typeid(unordered_set<float>) == typeid(cont) || typeid(unordered_set<string>) == typeid(cont) || typeid(unordered_set<char>) == typeid(cont) ||
		
		typeid(unordered_multiset<int>) == typeid(cont) || typeid(unordered_set<double>) == typeid(cont) || typeid(unordered_set<bool>) == typeid(cont) ||
		typeid(unordered_set<float>) == typeid(cont) || typeid(unordered_set<string>) == typeid(cont) || typeid(unordered_set<char>) == typeid(cont)) {
		
		return true;
	}
	
	return false;
}

/* TO_STRING functions */

// Stub function (don't use externally) (useful when trying to pass a string to the 'to_string' function, to avoid problems)
string to_string(const string& str) {
	return str;
}

// Convert char to string
string to_string(const char& chr) {
	return string(1,chr);
}

// Return a single or double quoted string IF the data is a string or a char
template <typename Type>
string quotedString(const Type& data) {
	
	if (typeid(data) == typeid(string)) {
		return ("\"" + to_string(data) + "\"");
	}
	else if (typeid(data) == typeid(char)) {
		return ("\'" + to_string(data) + "\'");
	}
	else {
		return to_string(data);
	}
}

// Return a string given a container (vector, array, list, initializer_list, deque, set, multiset, unordered_set, forward list)
template <typename Container>
string to_string(const Container& cont) {
	
	size_t size = distance(cont.begin(), cont.end()); // Necessary for forward_list, because it doesn't have a size function
	size_t position = 0;
	string str;
	
	str += isSet(cont) ? "{" : "[";
	
	for (auto value: cont) {

		str += quotedString(value);
		
		if (position + 1 < size) {
			str += ", ";
		}
		position++;
	}
	
	str += isSet(cont) ? "}" : "]";
	
	return str;
}

// Return a string given any map type (no need to use externally)
template <typename mapType>
string to_stringMAP(const mapType& map) {
	string str;
	size_t position = 0;
	
	str += "[";
	
	for (auto value: map) {
		
		str += quotedString(value.first) + ": " + quotedString(value.second);
		
		if (position + 1 < map.size()) {
			str += ", ";
		}
		
		position++;
	}
	
	str += "]";
	
	return str;
}

// Return a string given a map
template <typename KeyType, typename ValueType>
string to_string(const map<KeyType,ValueType>& map) {
	return to_stringMAP(map);
}

// Return a string given a multimap
template <typename KeyType, typename ValueType>
string to_string(const multimap<KeyType,ValueType>& map) {
	return to_stringMAP(map);
}

// Return a string given an unordered map
template <typename KeyType, typename ValueType>
string to_string(const unordered_map<KeyType,ValueType>& map) {
	return to_stringMAP(map);
}

// Return a string given an unordered multimap
template <typename KeyType, typename ValueType>
string to_string(const unordered_multimap<KeyType,ValueType>& map) {
	return to_stringMAP(map);
}

// Return a string given a classic array and its size
template <typename Type>
string to_string(const Type * array, size_t size) {
	
	string str;
	
	str += "[";
	
	for (size_t idx = 0; idx < size; idx++) {
		
		str += quotedString(array[idx]);
		
		if (idx + 1 < size) {
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

			str += quotedString(matrix[i][j]);
			
			if (j + 1 < cols) {
				str += ", ";
			}
		}
		
		if (i + 1 < rows) {
			str += "], ";
		}
		else {
			str += "]";
		}
		
	}
	
	str += "]";
	
	return str;
}

// Return a string given a queue (creates a copy of the queue)
template <typename Type>
string to_string(queue<Type> queue) {
	
	string str;
	size_t originalSize = queue.size();

	str += "[";

	for (size_t idx = 0; idx < originalSize; idx++) {

		str += quotedString(queue.front());
		queue.pop();
		
		if (idx + 1 < originalSize) {
			str += ", ";
		}
	}
	
	str += "]";
	
	return str;
}

// Return a string given a priority queue or a stack (no need to use externally)
template <typename Type>
string to_stringPriorityQueueORstack(Type& pqstack) {
	string str;
	size_t originalSize = pqstack.size();
	
	str += "[";
	
	for (size_t idx = 0; idx < originalSize; idx++) {
		
		str += quotedString(pqstack.top());
		pqstack.pop();
		
		if (idx + 1 < originalSize) {
			str += ", ";
		}
	}
	
	str += "]";
	
	return str;
}

// Return a string given a priority queue (creates a copy of the queue)
template <typename Type, typename Container, typename Compare>
string to_string(priority_queue<Type,Container,Compare> pqueue) {
	return to_stringPriorityQueueORstack(pqueue);
}

// Return a string given a stack (creates a copy of the stack)
template <typename Type>
string to_string(stack<Type> stack) {
	return to_stringPriorityQueueORstack(stack);
}

#endif /* print_hpp */
