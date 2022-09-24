// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

//Marianna Matousek 2/15/19 

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readStudentEntries(list<list<string>>&  , string );

// printing a list out
void printStudentEntries(const list<list<string>> & roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last"
			<< endl; exit(1);
	}

	// vector of lists of courses of students
	//vector <list<list<string>>> courseStudent
	
	list<list<string>> studentEntries;
	for (int i = 1; i < argc - 1; ++i) {
		//list<string> roster;
		 
		readStudentEntries(studentEntries, argv[i]);
		
		//cout << "\n\n" << argv[i] << "\n";
		//printStudentEntries(studentEntries);

		
	}

	//All student with dropouts
	//cout << "All Students dropouts included: " << endl;
	//printStudentEntries(studentEntries);

	
	// reading in dropouts
	list<list<string>> dropouts;
	readStudentEntries(dropouts, argv[argc - 1]);
	//cout << "\n\n dropouts \n"; printStudentEntries(dropouts);
	

	

	// sorting master list
	studentEntries.sort();
	//cout << "\n\n all students sorted \n";
	//printStudentEntries(studentEntries);


	
	

	//make a drop out list will elements identical to studenEntries
	list<list<string>> newdropouts; 
	//removing individual dropouts
	for (const auto& studentToDrop : dropouts) {//for every dropout
			//compare names
			for (const auto & studentInClass : studentEntries) {
			if (studentToDrop.front() == studentInClass.front()) {
				newdropouts.push_back(studentInClass);
			}
		}
	}

	for (const auto& studentToDrop : newdropouts) {
		studentEntries.remove(studentToDrop);
	}

	cout << "\nAll students: " << endl;//dropouts removed
	printStudentEntries(studentEntries);
	

	
	
}


void readStudentEntries(list<list<string>>& studentEntries, string fileName) {
	//   ifstream course(fileName.c_str());
	ifstream course(fileName); // I am trying it

	string first, last;
	string classname = fileName.erase(fileName.find(".txt")); 
	while (course >> first >> last) {
		//roster.push_back(
			//move(first + ' ' + last));
		string name = first + ' ' + last;
		bool found = false;
		list< list<string>>::iterator it;
		for (it = studentEntries.begin(); it != studentEntries.end(); ++it) {
			if (it->front() == name) {
				it->push_back(classname);
				found = true;
			}
		}
		if (!found) {
			list<string> * newStudent = new list<string>; 
			newStudent->push_back(name);
			newStudent->push_back(classname);

			studentEntries.push_back(*newStudent); // do I need to dealocate memory??


		}


		 
	}
	course.close();
}

// printing a list out
void printStudentEntries(const list<list<string>>& roster) {
	for (const auto& student : roster) {
		for (const auto & str : student) {
			if (str == student.front()) {
				cout << str << ": "; //adding that colon after name for formating
			}
			else {
				cout << str << " ";
			}
		}
		cout << endl; 
	}
}