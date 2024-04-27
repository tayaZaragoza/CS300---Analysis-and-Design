#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>
using namespace std;

int userInput; 
string courseKey;

const unsigned int DEFAULT_SIZE = 179;

// define a structure to hold class information
struct Course {
	string courseId; // unique identifier
	string title;
	string prerequisites;
};

//Define Hashtable class
class HashTable {

private:
	// Define structures to hold class info
	struct Node {
		Course course;
		unsigned int key;
		Node* next;

		// default constructor
		Node() {
			key = UNIT_MAX;
			next = nullptr;
		}

		// initialize with a class
		Node(Course aCourse) : Node() {
			course = aCourse;
		}

		// initialize with a class and a key
		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
			key = aKey;
		}
	};

	vector<Node> nodes;

	unsigned int tableSize = DEFAULT_SIZE;

	unsigned int hash(int key);

public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void Insert(Course course);
	void PrintAll();
	Course Search(string courseId);
};

//Default constructor
HashTable::HashTable() {
	nodes.resize(tableSize);
}

//Constructor for size of table
HashTable::HashTable(unsigned int size) {
	this->tableSize = size;
	nodes.resize(size);
}

//Destructor
HashTable::~HashTable() {
	nodes.erase(nodes.begin());
}

//Calculate hash value of key
unsigned int HashTable::hash(int key) {
	return key % tableSize;
}

//Insert a course
void HashTable::Insert(Course course) {
	unsigned key = hash(atoi(course.courseId.c_str()));
	Node* prevNode = &(nodes.at(key));

	if (prevNode == nullptr) {
		Node* nextNode = new Node(course, key);
		nodes.insert(nodes.begin() + key, (*nextNode));
	}
	else if (prevNode->key == UNIT_MAX) {
		prevNode->key = key;
		prevNode->course = course;
		prevNode->next = nullptr;
	}
	else {
		while (prevNode->next != nullptr) {
			prevNode = prevNode->next;
		}
	}
}


//Print courses
void HashTable::PrintAll() {
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		if (it->key != UNIT_MAX) {
			cout << courseId << ", " << title;
			Node* Node = it->next;
			while (Node != nullptr) {
				cout << courseId << ", " << title;
				Node = Node->next;
			}
		}
	}
}


//Search and return a course
Course HashTable::Search(string courseId) {
	Course course;
	unsigned key = hash(atoi(courseId.c_str()));
	if (Node != nullptr && Node->key != UNIT_MAX && Node->course.courseId.compare(courseId) == 0) {
		return Node->course;
	}
	if (Node == nullptr || node->key == UNIT_MAX) {
		return course;
	}
	while (Node != nullptr) {
		if (Node->key != UNIT_MAX && Node->course.courseId.compare(courseId) == 0) {
			return Node->course;
		}
		Node = Node->next;
	}

	return course;
}

void displayCourse(Course course) {
	cout << course.courseId << ", " << course.title;
}

void loadCourses(HashTable* hashTable) {

	ifstream in("courses.txt");

	string line{};

	while (getline(in, line)) {
		istringstream iss(line);
		string substring;
		vector<string> substrings;

		while (getline(iss, substring, ',')) {
			substrings.push_back(substring);
		}

		Course course;
		course.courseId = substrings[0];
		course.title = substrings[1];
		course.prerequisites = substrings[2];

		hashTable->Insert(course);
	}
}

void askInput() {
	//Print menu
	cout << "Welcome to the course planner." << endl;
	cout << endl;
	cout << "1. Load Data Structure." << endl;
	cout << "2. Print Course List." << endl;
	cout << "3. Print Course." << endl;
	cout << "4. Exit" << endl;
	cout << endl;
	//Ask user input
	cout << "What would you like to do?";
	cin >> userInput;
}

int main() {

	//Define hashtable
	HashTable* courseTable;

	Course course;
	courseTable = new HashTable();

	//Call function to ask user input
	askInput();

	while (userInput != 4) {
		//Verify input
		while (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4) {
			cout << userInput << " is not a valid option." << endl;
			askInput();
		}

		if (userInput == 1) {
			loadCourses(courseTable);
			askInput();
		}

		else if (userInput == 2) {
			//Print course list
			cout << "Here is a sample schedule:" << endl;
			cout << endl;
			courseTable->PrintAll();
			askInput();
		}

		else if (userInput == 3) {
			cout << "What course do you want to know about?" << endl;
			cin >> courseKey;

			//Search table for course and print
			course = courseTable->Search(courseKey);

			if (!course.courseId.empty()) {
				displayCourse(course);
			}
			else {
				cout << "Course Id " << courseKey << " not found." << endl;
			}
			askInput();
		}
	}
	
	cout << "Thank you for using the course planner!";
	

	return 0;
}