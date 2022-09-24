
//Marinna Matoutsek
//2/1/2019
//I'm not sure if the class does it in the correct order but it does accept a file 
//name and outputs the words and the number of times they occur in the file
//with some punctuation eradication

#include <iostream>
#include <fstream>
#include <string>
#include "WordCount.h"

using std::ifstream; using std::string;
using std::cout; using std::cin; using std::endl;

int main(int argc, char* argv[]) {
	ifstream file;

	WordList fileWords; 

	file.open("test.txt");
	string word; 
	while(file>>word) {
		//remove some punctuation
		int found = word.find_first_of(".,?!");
		while (found != string::npos)
		{
			//word[found] = '*';
			word = word.erase(found, 1);
			found = word.find_first_of(".,?!", found + 1);
		}
		
		fileWords.addWord(word);
		
	}

	fileWords.print(); 
}
