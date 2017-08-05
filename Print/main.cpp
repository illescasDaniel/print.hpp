#include "print.hpp"
#include <list>
#include <forward_list>
#include <array>

using namespace std;
using namespace evt;

int main() {
	
	// Classic way...
	vector<int> vect1 = {1,2,3,4};

	for (int value: vect1) {
		cout << value << ' ';
	}
	cout << '\n' << endl;
	
	// New way:
	
	// std::vector
	print(toString(vect1));
	
	// classic array of fixed lenghth
	const size_t size = 6;
	int testArray[size] = {1,2,3,4,5,6};
	print(toString(testArray));
	
	print("Hi", toString(testArray), "cool, hah?");
	
	int testArray2[] = {99,98};
	print(toString(testArray2));
	
	string arrayString[2] = {"hello", "bye"};
	print(toString(arrayString));
	
	// classic array, pointer
	int * array2 = new int[3] {1,2,3};
	print(toString(array2, 3));
	delete[] array2;
	
	// Matrix
	const size_t rows = 3, cols = 2;
	
	int matr[rows][cols] = {{1,2},{3,4},{5,6}};
	print(toString(matr,rows,cols));
	
	size_t ** matrix = new size_t * [rows];
	for (size_t i = 0; i < rows; i++) {
		matrix[i] = new size_t[cols];
		
		for (size_t j = 0; j < cols; j++) {
			matrix[i][j] = j + i;
		}
	}

	print(toString(matrix,rows,cols));
	
	for (size_t i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	
	// std::map
	map<string,int> dic;
	dic["hola"] = 10;
	dic["adios"] = 20;
	
	print(toString(dic));
	
	map<float,string> dic2;
	dic2[1.20] = "low";
	dic2[100.8] = "high";
	
	print(toString(dic2));
	
	// std::multimap
	multimap<string, int> mp;
	mp.insert({"abc", 10});
	mp.insert({"xyz", 20});
	mp.insert({"def", 5});
	print(toString(mp));
	
	// std:unordered_map
	unordered_map<string,int> dic3;
	dic3["hi"] = 10;
	dic3["bye :D"] = 20;
	print(toString(dic3));
	
	// std:unordered_multimap
	unordered_map<string,int> umm;
	umm["hi again"] = 140;
	umm["bye!"] = 210;
	print(toString(umm));
	
	// std::list
	list<int> list1 = {1,2,3,4,5};
	print(toString(list1));
	
	// std::initializer_list
	initializer_list<float> il = {0.1, 2, 5, 9.0};
	print(toString(il));
	
	// std::queue
	queue<string> q;
	q.push("first");
	q.push("second");
	print(toString(q));
	
	// std::deque
	deque<double> dq = {1, 1.0, 9.12, 90};
	print(toString(dq));
	
	// std::priority_queue
	priority_queue<int, std::vector<int>, std::greater<int> > pq;
	pq.push(10);
	pq.push(20);
	pq.push(5);
	print(toString(pq));
	
	// std::stack
	stack<string> s;
	s.push("second");
	s.push("first");
	print(toString(s));
	
	// std::forward_list
	forward_list<int> fl = {9, 20, 5, 40, 100};
	fl.remove_if([](int n){ return n > 10; });
	print(toString(fl));
	
	// std::set
	set<char> abcd = {'d', 'e', 'f'};
	abcd.insert({'d', 'g'});
	print(toString(abcd));
	
	set<string> abc = {"aa", "bb", "cc"};
	abc.insert({"dd", "aa", "ee"});
	print(toString(abc));

	// std::multiset
	multiset<int> ms = {40, 20, 10};
	ms.insert({90, 10});
	print(toString(ms));
	
	// std::unordered_set
	unordered_set<string> names = {"Daniel ir", "John ma", "Test one"};
	names.insert({"Daniel ir", "Test two"});
	print(toString(names));
	
	// std::unordered_multiset
	unordered_multiset<string> names2 = {"Daniel ir", "John ma", "Test one"};
	names2.insert({"Daniel ir", "Test two"});
	print(toString(names2));
	
	print(1 < 2, 2 > 10, 20 == 21);
	
	PrintSettings::boolalphaEnabled = false;
	
	print(1 < 2, 2 > 10, 20 == 21);
	
	// Use of "let" and "var"
	const auto numbers = {1,2,3};
	print("This is my array:", numbers);
	
	auto languages = vector<string>({"C++", "C", "Swift", "Java"});
	languages.insert(languages.end(), "JavaScript");
	print("Programming languages:", languages);
	
	array<int,3> numbers2 = {4,5,6};
	print(numbers2);
	
	map<string,float> mapInit { {"hi", 10.1}, {"bye", 20.2} };
	print(mapInit);
	
	vector<double> numbers3 = {1.2, 2.3, 7.8};
	print(toString(numbers3));
	
	PrintSettings::boolalphaEnabled = true;
	cout << (1 == 2) << endl; // PrintSettings' boolalphaEnabled doesn't affect std::boolalpha
	print("???", (1 == 2));
	
	// Print errors
	int* i = nullptr;
	if (i == nullptr) {
		printError("null pointer", i);
	}
	
	PrintSettings::terminator = " :ENDLINE\n";
	print("hola", "terminator?", "lol", bool(1));
	
	PrintSettings::terminator = PrintSettings::defaultTerminator;
	PrintSettings::separator = "-";
	printError("hola", 10);
	
	//
	
	PrintSettings::separator = "\n ·";
	print("Shopping list:", "tomatoes", "salt", "sugar");
	
	cout << "Shopping list:\n" << " · tomatoes\n" << " · salt\n" << " · sugar\n" << endl;
	
    return 0;
}
