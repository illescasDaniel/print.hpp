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
#define type__(_cont_) typeid(_cont_) == typeid(cont)
#define is_(_cont_) type__(_cont_<int>) || type__(_cont_<double>) || type__(_cont_<bool>) || type__(_cont_<float>) || type__(_cont_<string>) || type__(_cont_<char>)

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
	
	size_t size = distance(begin(cont), end(cont)); // Necessary for forward_list, because it doesn't have a size function
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

struct PrintSettings {
	static bool boolalphaEnabled;
	static string separator;
	static string terminator;
	const static string defaultSeparator;
	const static string defaultTerminator;
};

bool PrintSettings::boolalphaEnabled = true;
string PrintSettings::separator = " ";
string PrintSettings::terminator = "\n";
const string PrintSettings::defaultSeparator = " ";
const string PrintSettings::defaultTerminator = "\n";

//bool boolalphaEnabled = true;

template <typename Type>
void print(const Type& message) {
	
	PrintSettings::boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	cout << message << PrintSettings::terminator;
}

template <typename Type, typename ... Args>
void print(const Type& message, const Args& ...args) {
	
	PrintSettings::boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	cout << message << PrintSettings::separator;
	print(args...);
}

// Print Error

bool errorDisplayed = false;

template <typename Type>
void printError(const Type& message) {
	
	PrintSettings::boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	if (!errorDisplayed) {
		cerr << "Error: " << message << PrintSettings::terminator;
	}
	else {
		cerr << message << PrintSettings::terminator;
		errorDisplayed = false;
	}
	
}

template <typename Type, typename ... Args>
void printError(const Type& message, const Args& ...args) {
	
	PrintSettings::boolalphaEnabled ? boolalpha(cout) : noboolalpha(cout);
	
	if (!errorDisplayed) {
		cerr << "Error: " << message << PrintSettings::separator;
	}
	else {
		cerr << message << PrintSettings::separator;
	}
	
	errorDisplayed = true;
	printError(args...);
}

#undef type__
#undef is_
#undef ostreamOperator
#undef ostreamOperatorMap
#undef to_stringMAP
