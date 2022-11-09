// Ch5RasterRecursion.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "RasterGrid.h"

using namespace std;

int getSquareRows(shared_ptr<ifstream>);
int getSquareColumns(shared_ptr<ifstream>);
void getSquareInput(shared_ptr<ifstream>, RasterGrid&, int, int);
void getClusters(RasterGrid&,int, int, int);
void traverseSquare(RasterGrid&, int, int);

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		//default case
		cout << "You are using the default of this program.\n";
		shared_ptr<ifstream> inFile = make_shared<ifstream>("Ch5p_fa.asc");
		int totalRows = getSquareRows(inFile);
		int totalColumns = getSquareColumns(inFile);
		RasterGrid raster(totalRows, totalColumns);
		getSquareInput(inFile, raster, raster.storedRows, raster.storedColumns);
		traverseSquare(raster, raster.storedRows, raster.storedColumns);
		cout << "\nHere is the raster inputted.\n\n";
		raster.printInGrid();
		cout << "\nHere is the clusters of trees.\n\n";
		raster.printOutGrid();
	}
	else if (argc == 2)
	{
		//write output to console
		shared_ptr<ifstream> inFile = make_shared<ifstream>(argv[1]);
		RasterGrid raster(getSquareRows(inFile), getSquareColumns(inFile));
		getSquareInput(inFile, raster, raster.storedRows, raster.storedColumns);
		traverseSquare(raster, raster.storedRows, raster.storedColumns);
		cout << "\nHere is the raster inputted.\n\n";
		raster.printInGrid();
		cout << "\nHere is the clusters of trees.\n\n";
		raster.printOutGrid();

	}
	else if (argc == 3)
	{
		//write to output file
		shared_ptr<ifstream> inFile = make_shared<ifstream>(argv[1]);
		RasterGrid raster(getSquareRows(inFile), getSquareColumns(inFile));
		getSquareInput(inFile, raster, raster.storedRows, raster.storedColumns);
		traverseSquare(raster, raster.storedRows, raster.storedColumns);
		shared_ptr<ofstream> outFile = make_unique<ofstream>(argv[2]);
		raster.writeOutGrid(outFile);
	}
	return 0;
}
//returns number of rows in the raster in the given file
int getSquareRows(shared_ptr<ifstream> file)
{
	string str{};
	string rownum{};
	char c{};
	file->clear();
	file->seekg(0);
	getline(*file, str, '=');
	getline(*file, rownum, ',');

	return stoi(rownum);
}
//returns number of columns in the raster in the given file
int getSquareColumns(shared_ptr<ifstream> file)
{
	string str{};
	string colnum{};
	char c{};
	file->clear();
	file->seekg(0);
	getline(*file, str, '=');
	getline(*file, str, '=');
	getline(*file, colnum, '\n');
	return stoi(colnum);
}
//reads in the raster grid from the given file in to RasterGrid class
void getSquareInput(shared_ptr<ifstream> file, RasterGrid& square, int rows, int columns)
{
	file->seekg(0);
	string str{};
	getline(*file, str);
	for (int i = 1; i < rows - 1; i++)
	{
		getline(*file, str);
		str.erase(remove(str.begin(), str.end(), ' '), str.end());

		for (int j = 1; j < columns - 1; j++)
		{
			square.grid[i][j].indata = str[j - 1];
		}
	}

}
//Recursive function for assigning clusters of trees
void getClusters(RasterGrid& square, int row, int column, int clusterNum)
{
	//sets boolean for checked to true and set the out value of the cell
	square.grid[row][column].checked = true;
	square.grid[row][column].setOutData(to_string(clusterNum));

	//checks square behind current square
	if ((square.grid[row][column - 1].indata == 't') && (square.grid[row][column - 1].checked == false))
	{
		getClusters(square, row, column - 1, clusterNum);
	}
	//checks square above current square
	if ((square.grid[row - 1][column].indata == 't') && (square.grid[row - 1][column].checked == false))
	{
		getClusters(square, row - 1, column, clusterNum);
	}
	//checks square in front of current square
	if ((square.grid[row][column + 1].indata == 't') && (square.grid[row][column + 1].checked == false))
	{
		getClusters(square, row, column + 1, clusterNum);
	}
	//checks square below current square
	if ((square.grid[row + 1][column].indata == 't') && (square.grid[row + 1][column].checked == false))
	{
		getClusters(square, row + 1, column, clusterNum);
	}
	//no squares around current square are trees
	else
	{
		return;
	}
}
//check each cell in the raster grid, calling getClusters for each unchecked tree found
void traverseSquare(RasterGrid& square, int rows, int columns)
{
	//traverse through square to find clusters
	int clusterNum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if ((square.grid[i][j].indata == 't') && (square.grid[i][j].checked == false))
			{
				clusterNum++;
				getClusters(square, i, j, clusterNum);
			}
		}
	}
}