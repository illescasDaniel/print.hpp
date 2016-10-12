gcc:
	g++-5 -pthread -std=c++14 -O2 -Wall -Wextra Print/main.cpp -I Print -o printExample
clang:
	clang++-3.8 -pthread -std=c++14 -O2 -Wall -Wextra Print/main.cpp -I Print -o printExampleClang
