// Ch5RasterRecursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int getSquareSize(ifstream&);
void getSquareInput(ifstream&, vector<vector<char>>&, int);
void printSquare(vector<vector<char>>);
void printTrees(vector<vector<char>>);
void printClusters(vector<vector<char>>);
void getClusters(vector<vector<char>>&, int, int, int);

int main(int argc, char* args[])
{
	if (argc == 1)
	{
		//default case
		cout << "You are using the default of this program.\n";
		ifstream inFile;
		inFile.open("Ch5p_fa.asc");
		int size = getSquareSize(inFile);
		cout << size << endl;
		size += 2;
		vector<vector<char>> square(size);
		getSquareInput(inFile, square, size);
		cout << "Here is the square with a broder of grass added.\n";
		printSquare(square);
		cout << endl << endl;
		cout << "Here is the tree layout of the inputted square\n";
		printTrees(square);
		cout << endl << endl;

		//traverse through square to find clusters
		int clusterNum = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; i < size; j++)
			{
				if (square[i][j] = 't')
				{
					clusterNum++;
					getClusters(square, i, j, clusterNum);
				}
			}
		}
	}
	else if (argc == 2)
	{
		//write output to console
		ifstream inFile;
		inFile.open("Ch5p_fa.asc");
		cout << getSquareSize(inFile);

	}
	else if (argc == 3)
	{
		//write to output file
		
	}
	return 0;
}

int getSquareSize(ifstream& file)
{
	string str{};
	getline(file, str);
	getline(file, str);
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str.size();
}

void getSquareInput(ifstream& file, vector<vector<char>>& square, int size)
{
	file.seekg(0);
	string str{};
	getline(file, str);
	square[0] = vector<char>(size);
	generate(square[0].begin(), square[0].end(), []() {return 'g'; });
	for (int i = 1; i < size - 1; i++)
	{
		getline(file, str);
		str = "g " + str + " g";
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		square[i] = vector<char>(size);
		for (int j = 0; j < size; j++)
		{
			square[i][j] = str[j];
		}
	}
	square[size - 1] = vector<char>(size);
	generate(square[size - 1].begin(), square[size - 1].end(), []() {return 'g'; });

}

void printSquare(vector<vector<char>> square)
{
	for (vector<char> rowvec : square)
	{
		for (char c : rowvec)
		{
			cout << c << ' ';
		}
		cout << endl;
	}
}

void printTrees(vector<vector<char>> square)
{
	for (vector<char> rowvec : square)
	{
		for (char c : rowvec)
		{
			if (c == 't')
			{
				cout << c << ' ';
			}
			else
			{
				cout << ' ' << ' ';
			}
		}
		cout << endl;
	}
}

void printClusters(vector<vector<char>> square)
{

}

void getClusters(vector<vector<char>>& square, int row, int column, int clusterNum)
{
	//checks squqre behind current square
	if (square[row][column - 1] == 't')
	{
		column--;
		return getClusters(square, row, column, clusterNum);
	}
	//checks square above current square
	else if (square[row + 1][column] == 't')
	{
		row++;
		return getClusters(square, row, column, clusterNum);
	}
	//checks square in front of current square
	else if (square[row][column + 1] == 't')
	{
		column++;
		return getClusters(square, row, column, clusterNum);
	}
	//checks square below current square
	else if (square[row - 1][column] == 't')
	{
		row--;
		return getClusters(square, row, column, clusterNum);
	}
	//no squares around current square are trees
	else
	{
		return;
	}
}