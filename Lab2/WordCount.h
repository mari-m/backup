//Marinna Matousek	
//1/31/2019

#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <iostream>
#include <string>
using std::string;
using std::cout; using std::cin; using std::endl;


class WordOccurrence {
public:
	WordOccurrence(const string& word = "", int num = 0);
	bool matchWord(const string &); // returns true if word matches stored
	bool greaterNum(const int&);//return true if num is greater thatn stored
	void increment(); // increments number of occurrences
	string getWord() const;
	int getNum() const;
	
	

private:
	string word_;
	int num_;
};

class WordList {
public:
	WordList(int size = 0, WordOccurrence *a = nullptr); 

	//copy constructor, 
	WordList(const WordList& other); 

	//swap
	friend void swap(WordList& first, WordList& second);

	//add overloaded assignment
	WordList& operator=(WordList other); 

	//destructor
	~WordList() { delete[]wordArray_; }

	// comparison
	friend bool equal(const WordList&, const WordList&);

	void addWord(const string &);
	void print();
private:
	WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
								
	int size_;
};

#endif // WORDCOUNT_H