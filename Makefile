gcc:
	$(CXX) -std=c++14 -O2 -Wall -Wextra Print/main.cpp -I Print -o printExamplec
clang:
	clang++-3.8 -std=c++14 -O2 -Wall -Wextra Print/main.cpp -I Print -o printExample

