#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//class to store and handle a word and its corresponding verses
class Word {
	std::string word{};
	//assumes verses will be added in numerical order
	std::vector<int> verses;

public:
	Word(std::string name) {
		//makes sure word member is lowercase for easy comparisons and ordering
		transform(name.cbegin(), name.cend(), name.begin(),
			[](char c) {return tolower(c);});
		word = name;
	}

	std::string getWord() const { return word; }
	void addVerse(const int verse) 
	{
		//only adds verse if not already in list
		if (!std::binary_search(verses.begin(), verses.end(), verse)) {
			verses.push_back(verse);
		}
	}
	//print to console
	void printVerses() const
	{
		for (int i = 0; i < verses.size() - 1; i++) {
			std::cout << verses[i] << ", ";
		}
		//removes last comma from output
		std::cout << verses[verses.size() - 1] << "\n";
	}
	//prints to a specified file
	void printVerses(std::shared_ptr<std::ofstream> file) const
	{
		for (int i = 0; i < verses.size() - 1; i++) {
			*file << verses[i] << ", ";
		}
		//removes last comma from output
		*file << verses[verses.size() - 1] << "\n";
	}
};