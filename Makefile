all:
	$(CXX) -pthread -std=c++14 -O2 -Wall -Wextra Print/main.cpp -I Print -o printExample

test:
	 ./printExample
