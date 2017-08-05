//
//  EVTPrint2.0.hpp
//  EverythingLibs
//
//  Created by Daniel Illescas Romero on 05/08/2017.
//  Copyright © 2017 Daniel Illescas Romero. All rights reserved.
//

#pragma once

#include <iostream>
#include <typeinfo>
#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>

namespace evt {
	
	namespace internalPrintEVT {
		
		// - is_container Extracted from prettyprint.hpp -
		//          Copyright Louis Delacroix 2010 - 2014.
		// Distributed under the Boost Software License, Version 1.0.
		//    (See accompanying file LICENSE_1_0.txt or copy at
		//          http://www.boost.org/LICENSE_1_0.txt)
		template<typename T>
		struct has_const_iterator {
		private:
			typedef char yes;
			typedef struct { char array[2]; } no;
			
			template<typename C> static yes test(typename C::const_iterator*);
			template<typename C> static no test(...);
		public:
			static const bool value = sizeof(test<T>(0)) == sizeof(yes);
			typedef T type;
		};
		
		template <typename T>
		struct has_begin_end {
			template<typename C> static char (&f(typename std::enable_if<
												 std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::begin)),
												 typename C::const_iterator(C::*)() const>::value, void>::type*))[1];
			
			template<typename C> static char (&f(...))[2];
			
			template<typename C> static char (&g(typename std::enable_if<
												 std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::end)),
												 typename C::const_iterator(C::*)() const>::value, void>::type*))[1];
			
			template<typename C> static char (&g(...))[2];
			
			static bool const beg_value = sizeof(f<T>(0)) == 1;
			static bool const end_value = sizeof(g<T>(0)) == 1;
		};
		
		template<typename T>
		struct is_container: std::integral_constant<bool, has_const_iterator<T>::value && has_begin_end<T>::beg_value && has_begin_end<T>::end_value>{};
		
		template <typename Type>
		std::string quoted(const Type& value, bool quoteAnything = false) {
			if constexpr (std::is_same<std::string, Type>()) {
				return "\"" + value + "\"";
			}
			else if constexpr (std::is_same<const char*, Type>()) {
				return "\"" + std::string(value) + "\"";
			}
			else if constexpr (std::is_same<char, Type>()) {
				return "'" + std::string(1, value) + "'";
			}
			else if constexpr (std::is_arithmetic<Type>()) {
				return quoteAnything ? ("\"" + std::to_string(value) + "\"") : std::to_string(value);
			}
			else if constexpr (std::is_object<Type>()) {
				return quoteAnything ? "\"[Object]\"" : "[Object]";
			}
			else {
				return "[Error, value is not a valid type to quote]";
			}
		}
		
		// Return a std::string given a priority queue or a stack (no need to use externally)
		template <typename Type>
		std::string toStringPriorityQueueORstack(Type& pqstack) {
			std::string str;
			size_t originalSize = pqstack.size();
			
			str += "[";
			
			for (size_t idx = 0; idx < originalSize; idx++) {
				
				str += internalPrintEVT::quoted(pqstack.top());
				pqstack.pop();
				
				if (idx + 1 < originalSize) {
					str += ", ";
				}
			}
			
			str += "]";
			
			return str;
		}
		
		// Return a std::string given a set
		template <typename Set>
		std::string toStringSET(const Set& cont) {
			
			size_t size = std::distance(std::begin(cont), std::end(cont));
			size_t position = 0;
			std::string str;
			
			str += "{";
			
			for (const auto& value: cont) {
				
				str += internalPrintEVT::quoted(value);
				
				if (position + 1 < size) {
					str += ", ";
				}
				position++;
			}
			
			str += "}";
			
			return str;
		}
		
		// Return a std::string given any map type (no need to use externally!)
		template <typename mapType>
		std::string toStringMAP(const mapType& map) {
			std::string str;
			size_t position = 0;
			
			str += "[";
			
			for (const auto& value: map) {
				str += internalPrintEVT::quoted(value.first) + ": " + internalPrintEVT::quoted(value.second);
				
				if (position + 1 < map.size()) {
					str += ", ";
				}
				position++;
			}
			
			str += "]";
			
			return str;
		}
	}
	
	// Return a std::string given a dynamic array and its size
	template <typename Type>
	std::string toString(const Type * array, const size_t size) {
		
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
	std::string toString(const Type& matrix, const size_t rows, const size_t cols) {
		
		std::string str;
		
		str += "[";
		
		for (size_t i = 0; i < rows; i++) {
			str += "[";
			for (size_t j = 0; j < cols; j++) {
				
				str += internalPrintEVT::quoted(matrix[i][j]);
				
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
	std::string toString(std::queue<Type> queue) {
		
		std::string str;
		size_t originalSize = queue.size();
		
		str += "[";
		
		for (size_t idx = 0; idx < originalSize; idx++) {
			
			str += internalPrintEVT::quoted(queue.front());
			queue.pop();
			
			if (idx + 1 < originalSize) {
				str += ", ";
			}
		}
		
		str += "]";
		
		return str;
	}
	
	// Return a std::string given a priority queue (creates a copy of the queue)
	template <typename Type, typename Container, typename Compare>
	std::string toString(std::priority_queue<Type,Container,Compare> pqueue) {
		return internalPrintEVT::toStringPriorityQueueORstack(pqueue);
	}
	
	// Return a std::string given a stack (creates a copy of the stack)
	template <typename Type>
	std::string toString(std::stack<Type> stack) {
		return internalPrintEVT::toStringPriorityQueueORstack(stack);
	}
	
#define toStringSet(_set_) \
template <typename Type> \
std::string toString(const _set_<Type>& cont) { \
return internalPrintEVT::toStringSET(cont); \
}
	
	toStringSet(std::set);
	toStringSet(std::multiset);
	toStringSet(std::unordered_set);
	toStringSet(std::unordered_multiset);
	
	// Return a std::string given any map type
#define toStringMAP(_map_) \
template <typename KeyType, typename ValueType> \
std::string toString(const _map_<KeyType,ValueType>& map) { \
return internalPrintEVT::toStringMAP(map); \
}
	
	toStringMAP(std::map);
	toStringMAP(std::multimap);
	toStringMAP(std::unordered_map);
	toStringMAP(std::unordered_multimap);
	
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
	
	std::string toString(const char str[]) {
		return std::string(str);
	}
	
	template <typename Container>
	std::string toStringContainer(const Container& cont) {
		
		std::size_t arraySize = std::distance(std::begin(cont), std::end(cont));
		std::size_t position = 0;
		std::string str;
		
		str += "[";
		
		for (const auto& v: cont) {
			
			str += internalPrintEVT::quoted(v);
			
			if (position + 1 < arraySize) {
				str += ", ";
			}
			position++;
		}
		
		str += "]";
		
		return str;
	}
	
	// Main toString for strings, char, classic arrays and STL Containers
	template <typename Type>
	std::string toString(const Type& value) {
		
		if constexpr (std::is_same<Type, std::string>()) {
			return value;
		}
		if constexpr (std::is_same<Type, bool>()) {
			if (PrintSettings::boolalphaEnabled) {
				return value ? "true" : "false";
			}
			return std::to_string(value);
		}
		else if constexpr (std::is_same<Type, char>()) {
			return std::string(1, value);
		}
		else if constexpr (std::is_arithmetic<Type>()) {
			return std::to_string(value);
		}
		else if constexpr (internalPrintEVT::is_container<Type>() || std::is_array<Type>()) {
			return toStringContainer(value);
		}
		else if constexpr (std::is_pointer<Type>()) {
			if (value == nullptr) {
				return "null pointer";
			}
			return toString(*value);
		}
		else if constexpr (std::is_object<Type>()) {
			return "[Object]";
		}
		else {
			return "[Error, not a valid type]";
		}
	}
	
	template <typename Type>
	void print(const Type& message) {
		if constexpr (internalPrintEVT::is_container<Type>() || std::is_array<Type>() || std::is_pointer<Type>() || std::is_same<Type, bool>()) {
			std::cout << toString(message) << PrintSettings::terminator;
		} else {
			std::cout << message << PrintSettings::terminator;
		}
	}
	
	template <typename Type, typename ... Args>
	void print(const Type& message, const Args& ...args) {
		if constexpr (internalPrintEVT::is_container<Type>() || std::is_array<Type>() || std::is_pointer<Type>() || std::is_same<Type, bool>()) {
			std::cout << toString(message) << PrintSettings::separator;
		} else {
			std::cout << message << PrintSettings::separator;
		}
		print(args...);
	}
	
	// Print Error
	
	static bool errorDisplayed = false;
	
	template <typename Type>
	void printError(const Type& message) {
		if (!errorDisplayed) {
			std::cerr << "Error: " << toString(message) << PrintSettings::terminator;
		}
		else {
			std::cerr << toString(message) << PrintSettings::terminator;
			errorDisplayed = false;
		}
	}
	
	template <typename Type, typename ... Args>
	void printError(const Type& message, const Args& ...args) {
		if (!errorDisplayed) {
			std::cerr << "Error: " << toString(message) << PrintSettings::separator;
		} else {
			std::cerr << toString(message) << PrintSettings::separator;
		}
		errorDisplayed = true;
		printError(args...);
	}
}


