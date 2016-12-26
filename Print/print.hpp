//  print.hpp
//  Created by Daniel Illescas Romero on 09/09/2016.

#pragma once

#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <typeinfo>
#include <array>
#include <list>
#include <initializer_list>
#include <forward_list>
	
using namespace std;

// To know if a given container is a set or not
#define __t(_cont_) typeid(_cont_) == typeid(cont)
#define is_(_cont_) __t(_cont_<int>) || __t(_cont_<double>) || __t(_cont_<bool>) || __t(_cont_<float>) || __t(_cont_<string>) || __t(_cont_<char>)

template <typename Container>
bool isSet(const Container& cont) {
	return (is_(set) || is_(multiset) || is_(unordered_set) || is_(unordered_multiset));
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

// Return a string given a container (vector, array, list, initializer_list, deque, set, multiset, unordered_set, unordered_multiset, forward list)
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

// Return a string given any map type (no need to use externally!)
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

// Return a string given any map type
#define to_stringMAP(_map_) \
template <typename KeyType, typename ValueType> \
string to_string(const _map_<KeyType,ValueType>& map) { \
	return to_stringMAP(map); \
}

to_stringMAP(map);
to_stringMAP(multimap);
to_stringMAP(unordered_map);
to_stringMAP(unordered_multimap);


// Return a string given a classic array and its size
template <typename Type>
string to_string(const Type * array, const size_t& size) {
	
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
string to_string(const Type& matrix, const size_t& rows, const size_t& cols) {
	
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

// "let" is a constant of any type
// "var" is a variable of any type
#define let const auto
#define var auto

/* Operator<< overload */

#define ostreamOperator(_container_) \
template <typename Type> \
ostream & operator<<(ostream& os, const _container_<Type>& cont) { \
	return os << to_string(cont); \
}

#define ostreamOperatorMap(_container_) \
template <typename Key, typename Value> \
ostream & operator<<(ostream& os, const _container_<Key, Value>& cont) { \
	return os << to_string(cont); \
}

ostreamOperator(vector) ostreamOperator(list)		 ostreamOperator(forward_list)		ostreamOperator(initializer_list)
ostreamOperator(deque)	ostreamOperator(stack)		 ostreamOperator(queue)				ostreamOperator(priority_queue)
ostreamOperator(set)	ostreamOperator(multiset)	 ostreamOperator(unordered_set)		ostreamOperator(unordered_multiset)
ostreamOperatorMap(map) ostreamOperatorMap(multimap) ostreamOperatorMap(unordered_map)  ostreamOperatorMap(unordered_multimap)

template <typename Type, size_t size>
ostream & operator<<(ostream& os, const array<Type,size>& cont) {
	return os << to_string(cont);
}

/* Print functions */

bool boolalphaEnabled = true;

template <typename Type>
void print(const Type& message) {
	
	boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	cout << message << endl;
}

template <typename Type, typename ... Args>
void print(const Type& message, const Args& ...args) {
	
	boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	cout << message << ' ';
	print(args...);
}

// Print Error

bool errorDisplayed = false;

template <typename Type>
void printError(const Type& message) {
	
	boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	if (!errorDisplayed) {
		cerr << "Error: " << message << ' ' << endl;
	}
	else {
		cerr << message << ' ' << endl;
		errorDisplayed = false;
	}
	
}

template <typename Type, typename ... Args>
void printError(const Type& message, const Args& ...args) {
	
	boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	
	if (!errorDisplayed) {
		cerr << "Error: " << message << ' ';
	}
	else {
		cerr << message << ' ';
	}
	
	errorDisplayed = true;
	printError(args...);
}

#undef __t
#undef is_
#undef ostreamOperator
#undef ostreamOperatorMap
#undef to_stringMAP
