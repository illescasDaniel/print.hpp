//  print.hpp
//  Created by Daniel Illescas Romero on 09/09/2016.

#pragma once

#include <iostream>
#include <typeinfo>

#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <array>
#include <list>
#include <initializer_list>
#include <forward_list>

namespace std {
	// Stub function (don't use externally) (useful when trying to pass a std::string to the 'to_string' function, to avoid problems)
	std::string to_string(const std::string& str) {
		return str;
	}
	
	// Convert char to std::string
	std::string to_string(const char& chr) {
		return std::string(1,chr);
	}
}
namespace evt {
	
	// To know if a given container is a set or not
	#define type__(_cont_) typeid(_cont_) == typeid(cont)
	#define is_(_cont_) type__(_cont_<int>) || type__(_cont_<double>) || type__(_cont_<bool>) || type__(_cont_<float>) || type__(_cont_<std::string>) || type__(_cont_<char>)

	template <typename Container>
	bool isSet(const Container& cont) {
		return (is_(std::set) || is_(std::multiset) || is_(std::unordered_set) || is_(std::unordered_multiset));
	}

	/* to_string functions */
	
	// Stub function (don't use externally) (useful when trying to pass a std::string to the 'to_string' function, to avoid problems)
	std::string to_string(const std::string& str) {
		return str;
	}

	// Convert char to std::string
	std::string to_string(const char& chr) {
		return std::string(1,chr);
	}
 
	// Return a single or double quoted std::string IF the data is a std::string or a char
	template <typename Type>
	std::string quotedString(const Type& data) {
		
		if (typeid(data) == typeid(std::string)) {
			return ("\"" + evt::to_string(data) + "\"");
		}
		else if (typeid(data) == typeid(char)) {
			return ("\'" + evt::to_string(data) + "\'");
		}
		else {
			return std::to_string(data);
		}
	}

	// Return a std::string given a container (vector, array, list, initializer_list, deque, set, multiset, unordered_set, unordered_multiset, forward list)
	template <typename Container>
	std::string to_string(const Container& cont) {
		
		size_t size = std::distance(std::begin(cont), std::end(cont)); // Necessary for forward_list, because it doesn't have a size function
		size_t position = 0;
		std::string str;
		
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

	// Return a std::string given any map type (no need to use externally!)
	template <typename mapType>
	std::string to_stringMAP(const mapType& map) {
		std::string str;
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

	// Return a std::string given any map type
	#define to_stringMAP(_map_) \
	template <typename KeyType, typename ValueType> \
	std::string to_string(const _map_<KeyType,ValueType>& map) { \
		return to_stringMAP(map); \
	}

	to_stringMAP(std::map);
	to_stringMAP(std::multimap);
	to_stringMAP(std::unordered_map);
	to_stringMAP(std::unordered_multimap);


	// Return a std::string given a classic array and its size
	template <typename Type>
	std::string to_string(const Type * array, const size_t& size) {
		
		std::string str;
		
		str += "[";
		
		for (size_t idx = 0; idx < size; idx++) {
			
			str += std::to_string(array[idx]);
			
			if (idx + 1 < size) {
				str += ", ";
			}
		}
		
		str += "]";
		
		return str;
	}

	// Return a std::string given a matrix and its size
	template <typename Type>
	std::string to_string(const Type& matrix, const size_t& rows, const size_t& cols) {
		
		std::string str;
		
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

	// Return a std::string given a queue (creates a copy of the queue)
	template <typename Type>
	std::string to_string(std::queue<Type> queue) {
		
		std::string str;
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

	// Return a std::string given a priority queue or a stack (no need to use externally)
	template <typename Type>
	std::string to_stringPriorityQueueORstack(Type& pqstack) {
		std::string str;
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

	// Return a std::string given a priority queue (creates a copy of the queue)
	template <typename Type, typename Container, typename Compare>
	std::string to_string(std::priority_queue<Type,Container,Compare> pqueue) {
		return to_stringPriorityQueueORstack(pqueue);
	}

	// Return a std::string given a stack (creates a copy of the stack)
	template <typename Type>
	std::string to_string(std::stack<Type> stack) {
		return to_stringPriorityQueueORstack(stack);
	}

	/* Operator<< overload */

	#define ostreamOperator(_container_) \
	template <typename Type> \
	std::ostream & operator<<(std::ostream& os, const _container_<Type>& cont) { \
		return os << to_string(cont); \
	}

	#define ostreamOperatorMap(_container_) \
	template <typename Key, typename Value> \
	std::ostream & operator<<(std::ostream& os, const _container_<Key, Value>& cont) { \
		return os << to_string(cont); \
	}

	ostreamOperator(std::vector) ostreamOperator(std::list)		 ostreamOperator(std::forward_list)		ostreamOperator(std::initializer_list)
	ostreamOperator(std::deque)	ostreamOperator(std::stack)		 ostreamOperator(std::queue)				ostreamOperator(std::priority_queue)
	ostreamOperator(std::set)	ostreamOperator(std::multiset)	 ostreamOperator(std::unordered_set)		ostreamOperator(std::unordered_multiset)
	ostreamOperatorMap(std::map) ostreamOperatorMap(std::multimap) ostreamOperatorMap(std::unordered_map)  ostreamOperatorMap(std::unordered_multimap)
	
	template <typename Type, size_t size>
	std::ostream & operator<<(std::ostream& os, const std::array<Type,size>& cont) {
		return os << to_string(cont);
	}

	/* Print functions */

	struct PrintSettings {
		static bool boolalphaEnabled;
		static std::string separator;
		static std::string terminator;
		const static std::string defaultSeparator;
		const static std::string defaultTerminator;
	};

	bool PrintSettings::boolalphaEnabled = true;
	std::string PrintSettings::separator = " ";
	std::string PrintSettings::terminator = "\n";
	const std::string PrintSettings::defaultSeparator = " ";
	const std::string PrintSettings::defaultTerminator = "\n";

	template <typename Type>
	void print(const Type& message) {
		
		PrintSettings::boolalphaEnabled ? boolalpha(std::cout) : noboolalpha(std::cout);
		std::cout << message << PrintSettings::terminator;
	}

	template <typename Type, typename ... Args>
	void print(const Type& message, const Args& ...args) {
		
		PrintSettings::boolalphaEnabled ? boolalpha(std::cout) : noboolalpha(std::cout);
		std::cout << message << PrintSettings::separator;
		print(args...);
	}
	
	// Print Error

	bool errorDisplayed = false;

	template <typename Type>
	void printError(const Type& message) {
		
		PrintSettings::boolalphaEnabled ? boolalpha(std::cout) : noboolalpha(std::cout);
		if (!errorDisplayed) {
			std::cerr << "Error: " << message << PrintSettings::terminator;
		}
		else {
			std::cerr << message << PrintSettings::terminator;
			errorDisplayed = false;
		}
	}

	template <typename Type, typename ... Args>
	void printError(const Type& message, const Args& ...args) {
		
		PrintSettings::boolalphaEnabled ? boolalpha(std::cout) : noboolalpha(std::cout);
		
		if (!errorDisplayed) {
			std::cerr << "Error: " << message << PrintSettings::separator;
		}
		else {
			std::cerr << message << PrintSettings::separator;
		}
		
		errorDisplayed = true;
		printError(args...);
	}
}

#undef type__
#undef is_
#undef ostreamOperator
#undef ostreamOperatorMap
#undef to_stringMAP
