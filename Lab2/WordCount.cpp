//Marianna Matousek
//2/1/2019
#include "WordCount.h"

WordOccurrence::WordOccurrence(const string& word, int num) {
	word_ = word;
	num_ = num;
}

// returns true if word matches stored
bool WordOccurrence::matchWord(const string & s){
	if (word_ == s) {
		return true;
	}
	else {
		return false;
	}
}

// increments number of occurrences
void WordOccurrence::increment() {
	num_++;
}

string WordOccurrence::getWord() const {
	return word_;
}

int WordOccurrence::getNum() const {
	return num_;
}




//I think you said it didn't need a default but the test code
//would run without it so heres a default constructor.. it think
//Check this!!
WordList::WordList(int size, WordOccurrence *a) {
	size_ = size;
	wordArray_ = a; //rethink this
}

//overload assignment
WordList&  WordList::operator=(WordList other) {
	if (this != &other) { //needed?
		swap(*this, other);
	}
	return *this;

}

void swap(WordList& first, WordList& second) {
	std::swap(first.size_, second.size_);
	std::swap(first.wordArray_, second.wordArray_);
}

//copy constructor
WordList::WordList(const WordList& other) {
	size_ = other.size_;
	if (size_ > 0) {
		wordArray_ = new WordOccurrence[size_];
		for (int i = 0; i < size_; i++) {
			wordArray_[i] = other.wordArray_[i]; //just added
		}
	}
	else {
		wordArray_ = nullptr;
	}

}

bool WordOccurrence::greaterNum(const int& n) {
	if (n > num_) {
		return true;
	}
	else {
		return false;
	}
}



bool equal(const WordList& left, const WordList& right) {//check this
	if (left.size_ != right.size_) {
		return false;
	}
	else {
		for (int i = 0; i < left.size_; i++) {

			if (!(left.wordArray_[i].getWord() == right.wordArray_[i].getWord() &&
				left.wordArray_[i].getNum() == right.wordArray_[i].getNum()))
				return false;
		}
		//if all the words matched in the wordArray
		return true;
	}


}

void WordList::print() {
	for (int i = 0; i < size_; i++) {
		cout << wordArray_[i].getWord() << ", " << wordArray_[i].getNum() << endl;
	}
}

void WordList::addWord(const string & w) {
	//if w is in wordArray
	//increace num by using (increment)
	//check if position needs to be changed?
	//else
	//declare new wordOccurance(w, 1) 
	//place at the begining of the array
	bool changed = false; //if word found in array will be set to true
	int change_index;
	for (int i = 0; i < size_; i++) {

		//my attempt at sorting the word but it doesn't work so I'm commenting it out :(
		/*
		//if the words has been found and the current num is greater than changed word
		if (changed == true && wordArray_[change_index].greaterNum(wordArray_[i].getNum())) {
			//switch their positions?  
			sim not sure if this is the right thing to do though
			WordOccurrence temp = wordArray_[i];
			wordArray_[i] = wordArray_[change_index];
			wordArray_[change_index] = temp; 
		}
		*/


		//checks if word in inthe list
		if (wordArray_[i].getWord() == w) {
			wordArray_[i].increment();
			changed = true; 
			change_index = i; 
		}
	}
	//if word is not in the array
	WordOccurrence* tempWordArray = new WordOccurrence[size_ + 1];
	//adding the new word as the first element
	if (changed == false) {
		tempWordArray[0] = WordOccurrence(w, 1); //is this right.. i really don't remember
		//copying over old elements
		for (int i = 0; i < size_; i++) {
			tempWordArray[i + 1] = wordArray_[i];
		}

		//dealocate old array
		delete[]wordArray_;

		//point array at new array
		wordArray_ = tempWordArray;
		size_++; //setting new size
	}

}