// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

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


class Student {
public:
	Student(string firstName, string lastName, string classname="") {
		firstName_ = firstName;
		lastName_ = lastName;
		classes_.push_back(classname);//should I have used classes_ = {classname} and left it in the old format?

	}
		//firstName_(firstName), lastName_(lastName) {}

	// move constructor, not really needed, generated automatically
	Student(Student && org) :
		firstName_(move(org.firstName_)),
		lastName_(move(org.lastName_)),
		classes_(move(org.classes_))//is this okay?
	{}

	// force generation of default copy constructor
	Student(const Student & org) = default;


	void addClass(string classname) { classes_.push_back(classname); };

	//returns just the first and last name concatinated
	string getName()const { return firstName_ + ' ' + lastName_; }

	//returns name and classes
	string print() const;

	// needed for unique() and for remove()
	friend bool operator== (Student left, Student right) {
		return left.lastName_ == right.lastName_ &&
			left.firstName_ == right.firstName_;
	}

	//I changed it to sort by first name
	// needed for sort()
	friend bool operator< (Student left, Student right) {
		return left.firstName_ < right.firstName_ ||
			(left.firstName_ == right.firstName_ &&
				left.lastName_ < right.lastName_);
	}
	
	/*
	//old sort by last name
	// needed for sort()
	friend bool operator< (Student left, Student right) {
		return left.lastName_ < right.lastName_ ||
			(left.lastName_ == right.lastName_ &&
				left.firstName_ < right.firstName_);
	}
	*/
private:
	list<string> classes_; 
	string firstName_;
	string lastName_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);

// printing student their classes out
void printRoster(const list<Student>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last" << endl; exit(1);
	}

	// vector of courses of students
	vector <list<Student>> courseStudents; 
	
	list<Student> allStudents; 

	//creates a vector of classes with student rosters for each class
	//as well as a master list of students with all student's classes
	for (int i = 1; i < argc - 1; ++i) {
		list<Student> roster;
		readRoster(roster, argv[i]);
		readRoster(allStudents, argv[i]);
		
		//cout << "\n\n" << argv[i] << "\n";
		//printRoster(roster);
		//it makes sense to keep a vector of individual class rosters..maybe
		courseStudents.push_back(move(roster)); 
	}
	
	

	// reading in dropouts
	list<Student> dropouts;
	readRoster(dropouts, argv[argc - 1]);
	//cout << "\n\n dropouts \n"; printRoster(dropouts);
	
	/*
	//this is not needed since I make the 
	//masterlist in the for loop
	list<Student> allStudents;  // master list of students
	
	for (auto& lst : courseStudents) {
		allStudents.splice(allStudents.end(), lst);

	}
	*/
	
	//cout << "\n\n all students unsorted dropouts included \n";
	//printRoster(allStudents);

	
	
	allStudents.sort(); // sorting master list 
	//cout << "\n\n all students sorted by last name dropout included \n"; printRoster(allStudents);

	//not needed since readroster() makes sure the additions are unique
	//allStudents.unique(); // eliminating duplicates
	//cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
	

	//this doesn't see quite right but it works..
	// removing individual dropouts
	list<Student> dropList; 
	for (const auto& studentToDrop : dropouts) {
		for (const auto& studentInRoster : allStudents) {
			if (studentToDrop.getName() == studentInRoster.getName()) {
				dropList.push_back(studentInRoster);
			}	
		}
	}

	for (const auto& student : dropList) {
		allStudents.remove(student);
	}
		
		
		
	//dropouts removed 	
	cout << "\n\nAll students \n"; printRoster(allStudents);
	

}


//Student Memeber Functions
//returns name and classes
string Student::print() const {
	string classes = "";
	for (const auto & str : classes_) {
		classes = classes + str + " ";
	}
	return firstName_ + " " + lastName_ + ": " + classes;
}

void readRoster(list<Student>& roster, string fileName) {
	ifstream course(fileName);

	string first, last;

	string classname = fileName.erase(fileName.find(".txt"));

	while (course >> first >> last) {
		string name = first + ' ' + last;
		list<Student>::iterator it;
		bool found = false;
		for (it = roster.begin(); it != roster.end(); ++it) {
			if (it->getName() == name) {
				it->addClass(classname);
				found = true;
			}
		}
		if (!found) {
			roster.push_back(Student(first, last, classname));
		}
		
	}
	course.close();
}

// printing a list out
void printRoster(const list<Student>& roster) {
	for (const auto& student : roster)
		cout << student.print() << endl;

}


