all:
	$(CXX) -pthread -std=c++11 -Wall -Wextra Print/main.cpp -I Print -o example

test:
	 ./example
