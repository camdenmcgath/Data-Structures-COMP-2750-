// C6VerseNumbers.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//program reads in a textfile containing a chapter from Bible and creates a cross reference

#include <iostream>
#include <fstream>
#include "BSTree.cpp"
#include "Word.h"

using namespace std;

void processChapter(shared_ptr<ifstream>, shared_ptr<BSTree<Word>>);
void printInput(shared_ptr<ifstream>);

int main(int argc, char* argv[])
{
	//default, no parameter except program execution
	if (argc == 1) {
		string filename = "John4.txt";
		cout << "You are using the default of this program\n";
		cout << "Here is the input from " << filename << ":\n\n";
		shared_ptr<ifstream> chapter = make_shared<ifstream>(filename);
		printInput(chapter);
		cout << "Here is the cross reference:\n";
		shared_ptr<BSTree<Word>> words = make_shared<BSTree<Word>>
			([](const Word& w, BSTree<Word>::BSTNode* n) {return w.getWord() < n->el.getWord(); },
				[](const Word& w, BSTree<Word>::BSTNode* n) {return w.getWord() == n->el.getWord(); });
		processChapter(chapter, words);
		words->print([](BSTree<Word>::BSTNode*& n)
			{cout << n->el.getWord() << ": "; n->el.printVerses(); });
	}
	//input file specified
	else if (argc == 2) {
		cout << "Here is the input from " << argv[1] << ":\n\n";
		shared_ptr<ifstream> chapter = make_shared<ifstream>(argv[1]);
		printInput(chapter);
		cout << "Here is the cross reference:\n\n";
		shared_ptr<BSTree<Word>> words = make_shared<BSTree<Word>>
			([](const Word& w, BSTree<Word>::BSTNode* n) {return w.getWord() < n->el.getWord(); },
				[](const Word& w, BSTree<Word>::BSTNode* n) {return w.getWord() == n->el.getWord(); });
		processChapter(chapter, words);
		words->print([](BSTree<Word>::BSTNode*& n)
			{cout << n->el.getWord() << ": "; n->el.printVerses(); });
	}
	//input and output files specified
	else if (argc == 3) {
		shared_ptr<ifstream> chapter = make_shared<ifstream>(argv[1]);
		shared_ptr<ofstream> output = make_shared<ofstream>(argv[2]);
		shared_ptr<BSTree<Word>> words = make_shared<BSTree<Word>>
			([](const Word& w, BSTree<Word>::BSTNode* n) {return w.getWord() < n->el.getWord(); },
				[](const Word& w, BSTree<Word>::BSTNode* n) {return w.getWord() == n->el.getWord(); });
		processChapter(chapter, words);
		words->print([&output](BSTree<Word>::BSTNode*& n)
			{*output << n->el.getWord() << ": "; n->el.printVerses(output); });
		cout << "Cross reference for " << argv[1] << " in " << argv[2] << "!\n";
	}
	//incorrect parameter count
	else {
		cout << "Invalid parameter count.\n";
		cout << "0: run '.\\C6VerseNumbers' to run default.\n";
		cout << "1: run '.\\C6VerseNumbers <inputfilepath>' to specifiy input file and output to console.\n";
		cout << "2: run '.\\C6VerseNumbers <inputfilepath> <outputfilepath>' to output to file.\n";
	}
	return 0;
}
void processChapter(shared_ptr<ifstream> chapter, shared_ptr<BSTree<Word>> words)
{
	char ch{};
	int verse{};
	chapter->clear();
	chapter->seekg(0);
	while (!chapter->eof()) {
		chapter->get(ch);
		//checks if arrived at new verse
		if (isdigit(ch)) {
			string versestr{};
			versestr += ch;
			chapter->get(ch);
			if (isdigit(ch))
			{
				versestr += ch;
				chapter->get(ch);
			}
			verse = stoi(versestr);
		}
		//checks if charcater is a letter
		else if (isalpha(ch)) {
			string str{};
			while (isalpha(ch) || ch == '\'') {
				if (ch == '\'' && chapter->peek() == 's') {
					string trash{};
					getline(*chapter, trash, ' ');
					break;
				}
				str += ch;
				chapter->get(ch);
			}
			Word word(str);
			//if word already in tree, just add verse
			if (words->search(word) != 0) {
				words->search(word)->el.addVerse(verse);
			}
			//if word not yet in tree, add word and verse
			else {
				word.addVerse(verse);
				words->insert(word);
			}
		}
	}
}
void printInput(shared_ptr<ifstream> file)
{
	char c{};
	file->clear();
	file->seekg(0);
	while (!file->eof()) {
		file->get(c);
		cout << c;
	}
	cout << "\n\n";
}