// Ch4DelimeterMatching.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Description: This program utilizes a stack to check for matching delimeters in a .cpp file
// uses command line arguments to chose file to be checked and where to write the error messages
// Sources: https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
// https://cplusplus.com/articles/DEN36Up4/, Data Structure and Algorithms in C++ Drozdek
// https://stackoverflow.com/questions/4813129/how-to-get-the-line-number-from-a-file-in-c

#include <iostream>
#include <fstream>
#include <string>
#include "LLStack.h"

using namespace std;

string delimetersMatch(ifstream &, LLStack<char> *);
int lineNum(ifstream&);

int main(int argc, char *argv[])
{
	// driver for debugging
	if (argc == 1)
	{
		LLStack<char> *delimeters = new LLStack<char>();
		ifstream inFile;
		inFile.open("C:\\Users\\clm29\\source\\repos\\COMP-2750\\Ch4DelimeterMatching\\x64\\Debug\\Proj4Test_good.cpp");
		bool isopen = inFile.is_open();
		cout << "You are using the default of this program.\n";
		cout << delimetersMatch(inFile, delimeters);
		inFile.close();
	}
	// one command line parameter passed, read from file and cout
	else if (argc == 2)
	{
		// output to console
		LLStack<char> *delimeters = new LLStack<char>();
		ifstream inFile;
		bool isopen = inFile.is_open();
		inFile.open(argv[1]);
		cout << delimetersMatch(inFile, delimeters);
		inFile.close();
	}
	// two command line parameters passed, read from file, output to file
	else if (argc == 3)
	{
		// write to file
		LLStack<char> *delimeters = new LLStack<char>();
		ifstream inFile;
		ofstream outFile;
		inFile.open(argv[1]);
		outFile.open(argv[2]);
		outFile << delimetersMatch(inFile, delimeters);
		inFile.close();
		outFile.close();
	}
	else
	{
		cout << "Next time, please pass zero, one (file to be read), or two (file to be read, file to be written to) parameters";
	}

	return 0;
}

string delimetersMatch(ifstream &file, LLStack<char> *stack)
{
	//make sure file is open
	bool fileopen = file.is_open();
	if (fileopen)
	{
		//make sure iterator is not at the end of the file
		char ch;
		while (!file.eof())
		{
			//get next character in the file
			ch = file.get();
			//Check for opening delimetrs to add to the stack
			if ((ch == '(') || (ch == '[') || (ch == '{'))
			{
				stack->push(ch);
			}
			//check for closing delimeters
			else if ((ch == ')') || (ch == ']') || (ch == '}'))
			{
				char popped{};
				if (!stack->isEmpty())
				{
					popped = stack->pop();
				}
				//make sure closing delimter is the right delimeter 
				switch (ch)
				{
				case ')':
					if (popped != '(')
					{
						return "Error on line " + to_string(lineNum(file)) + " due to unmatched parenthesis.";
					}
					break;
				case ']':
					if (popped != '[')
					{
						return "Error on line " + to_string(lineNum(file)) + " due to unmatched brackets.";
					}
					break;
				case '}':
					if (popped != '{')
					{
						return "Error on line " + to_string(lineNum(file)) + " due to unmatched braces.";
					}
					break;
				}
			}
			//check for comments
			else if (ch == '/')
			{
				//check for multiline comments
				char next = file.peek();
				if (next == '*')
				{
					//ignore characters until comment closed
					string comment;
					do
					{
						getline(file, comment, '*');
					} while ((file.peek() != '/') && !file.eof());

					if (file.eof())
					{
						return "Error, multiline comment unclosed before end of file.";
					}
				}
				//check for single line comment
				else if (next == '/')
				{
					//ignore cahracters until end of line
					string comment;
					getline(file, comment, '\n');
				}
			}
			//check for string or character literals
			else if ((ch == '"') || (ch == '\''))
			{
				stack->push(ch);
				char topEl = stack->topEl();
				do
				{
					//search for matching closing literal delimeter
					ch = file.get();
					if (ch == '"' || ch == '\'')
					{
						//move iterator back to check pravious character
						file.unget();
						file.unget();
						//check if closing literal delimeter is escaped
						if (file.get() == '\\')
						{
							//move iterator back to check pravious character
							file.unget();
							file.unget();
							//check if escape character is escaped
							if (file.get() == '\\')
							{
								//escaped character is escaped, so closing literal delimeter is valid
								file.get();
								file.get();
								if (!stack->isEmpty())
								{
									stack->pop();
								}
								break;
							}
							else
							{
								//closing literal delimeter is escaped
								//continue checking for closing literal delimeter
								file.get();
								file.get();
								continue;
							}
						}
						//closing literal delimeter not escaped
						//so check if it matches top of stack
						else if (topEl == ch)
						{
							file.get();
							if (!stack->isEmpty())
							{
								stack->pop();
								if (!stack->isEmpty())
								{
									topEl = stack->topEl();
								}
								else
								{
									topEl = '\0';
								}
							}
						}
						//if closing literal delimeter is not closed and doesn't match 
						else
						{
							//add it to top of stack to be matched next
							stack->push(ch);
							topEl = stack->topEl();
						}
					}
				} while ((topEl == '"' || topEl == '\'') && !file.eof());
				if (file.eof())
				{
					if (topEl == '"')
					{
						return "Error, string literal unclosed before end of file.";
					}
					else if (topEl == '\'')
					{
						return "Error, character literal unclosed before end of file.";
					}
				}
			}
		}
		if (stack->isEmpty())
		{

			return "All delimeters match!";
		}
		else
		{
			switch (stack->topEl())
			{
			case '(':
				return "Error. Parenthesis left unclosed.";
				break;
			case '[':
				return "Error. Bracket left unclosed.";
				break;
			case '{':
				return "Error. Brace left unclosed.";
				break;
			}
		}
	}
}
//function derived from https://stackoverflow.com/questions/4813129/how-to-get-the-line-number-from-a-file-in-c
//returns the line of currently at in the given file passed as a parameter
int lineNum(ifstream& file)
{
	int lineCount = 1;
	file.clear();     // need to clear error bits otherwise tellg returns -1.
	auto originalPos = file.tellg(); //get position of iterator in the file
	if (originalPos < 0)
	{
		return -1;
	}
	file.seekg(0); //sets iterator at beginning of file
	char c;
	while ((file.tellg() <= originalPos) && file.get(c))
	{
		if (c == '\n')
		{
			++lineCount;
		}
	}
	return lineCount;
}