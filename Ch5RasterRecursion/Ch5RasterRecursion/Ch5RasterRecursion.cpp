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
void isBurnIsland(RasterGrid&, int, int, bool&);
void fillBurnIsland(RasterGrid&, int, int);
void setBurnSquare(RasterGrid&, int, int);
void burnSize(RasterGrid&, int, int, int&);
void fillShadow(RasterGrid&, int, int);


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
		raster.print([](RasterGrid::Cell cell) { cout << ' ' << cell.indata << ' '; });
		cout << "\nHere is the clusters of trees.\n\n";
		raster.print([](RasterGrid::Cell cell) { cout << cell.getClusterData(); });
		cout << "\nHere is the burned raster.\n\n";
		raster.print([](RasterGrid::Cell cell) { cout << cell.burneddata; });
	}
	else if (argc == 2)
	{
		//write output to console
		shared_ptr<ifstream> inFile = make_shared<ifstream>(argv[1]);
		RasterGrid raster(getSquareRows(inFile), getSquareColumns(inFile));
		getSquareInput(inFile, raster, raster.storedRows, raster.storedColumns);
		traverseSquare(raster, raster.storedRows, raster.storedColumns);
		cout << "\nHere is the raster inputted.\n\n";
		raster.print([](RasterGrid::Cell cell) { cout << ' ' << cell.indata << ' '; });
		cout << "\nHere is the clusters of trees.\n\n";
		raster.print([](RasterGrid::Cell cell) { cout << cell.getClusterData(); });
	}
	else if (argc == 3)
	{
		//write to output file
		shared_ptr<ifstream> inFile = make_shared<ifstream>(argv[1]);
		RasterGrid raster(getSquareRows(inFile), getSquareColumns(inFile));
		getSquareInput(inFile, raster, raster.storedRows, raster.storedColumns);
		traverseSquare(raster, raster.storedRows, raster.storedColumns);
		shared_ptr<ofstream> outFile = make_unique<ofstream>(argv[2]);
		raster.writeOutputs(outFile, 
			[](RasterGrid::Cell c) { return c.getClusterData(); }, [](RasterGrid::Cell c) { return c.burneddata; });
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
	square.grid[row][column].setClusterData(to_string(clusterNum));

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
//traverses the raster searching for burned islands and shadows, finding tree clusters 
void traverseSquare(RasterGrid& square, int rows, int columns)
{
	int clusterNum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			//unckecked tree, check and mark cluster
			if ((square.grid[i][j].indata == 't') && (square.grid[i][j].checked == false))
			{
				clusterNum++;
				getClusters(square, i, j, clusterNum);
			}
			//tree unchecked as being enclosed in burn perimeter
			if ((square.grid[i][j].indata == 't') && (square.grid[i][j].burnChecked == false))
			{
				bool burned = true;
				isBurnIsland(square, i, j, burned);
				if (burned)
				{
					fillBurnIsland(square, i, j);
				}
			}
			//burn pixel not already checked as island perimeter, check for shadow
			if ((square.grid[i][j].indata == 'b') && (square.grid[i][j].burnChecked == false))
			{
				int size = 0;
				burnSize(square, i, j, size);
				if (size < 4) 
				{
					fillShadow(square, i, j);
				}
			}
		}
	}
	setBurnSquare(square, rows, columns);
}
//checks to make sure a cluster of trees is enclused by burned cells and contains no grass cells
//pass bool as true, will modify bool to false if grass found
void isBurnIsland(RasterGrid& square, int row, int column, bool& burned)
{
	//a grass cell found automatically means that the island is not completely burned
	//grass found catches finding the border also indicating a leak in the burned perimeter
	if (square.grid[row][column].indata == 'g')
	{
		burned = false;
	}
	else
	{
		square.grid[row][column].burnChecked = true;
		//check left of current cell
		if ((square.grid[row][column - 1].indata != 'b') && (square.grid[row][column - 1].burnChecked == false))
		{
			isBurnIsland(square, row, column - 1, burned);
		}
		//check above current cell
		if ((square.grid[row - 1][column].indata != 'b') && (square.grid[row - 1][column].burnChecked == false))
		{
			isBurnIsland(square, row - 1, column, burned);
		}
		//check right of current cell
		if ((square.grid[row][column + 1].indata != 'b') && (square.grid[row][column + 1].burnChecked == false))
		{
			isBurnIsland(square, row, column + 1, burned);
		}
		//check below current cell
		if ((square.grid[row + 1][column].indata != 'b') && (square.grid[row + 1][column].burnChecked == false))
		{
			isBurnIsland(square, row + 1, column, burned);
		}
	}
}
//function to tag all burnt idland pixels as burnt
void fillBurnIsland(RasterGrid& square, int row, int column)
{
	square.grid[row][column].isBurned = true;
	if ((square.grid[row][column - 1].indata != 'b') && (square.grid[row][column - 1].isBurned == false))
	{
		fillBurnIsland(square, row, column - 1);
	}
	//check above current cell
	if ((square.grid[row - 1][column].indata != 'b') && (square.grid[row - 1][column].isBurned == false))
	{
		fillBurnIsland(square, row - 1, column);
	}
	//check right of current cell
	if ((square.grid[row][column + 1].indata != 'b') && (square.grid[row][column + 1].isBurned == false))
	{
		fillBurnIsland(square, row, column + 1);
	}
	//check below current cell
	if ((square.grid[row + 1][column].indata != 'b') && (square.grid[row + 1][column].isBurned == false))
	{
		fillBurnIsland(square, row + 1, column);
	}
}
//returns size of burn cluster, useful for checking if burn cluster is small enough to be shadow
void burnSize(RasterGrid& square, int row, int column, int& size)
{
	size++;
	square.grid[row][column].burnChecked = true;
	//check left of current cell
	if ((square.grid[row][column - 1].indata == 'b') && (square.grid[row][column - 1].burnChecked == false))
	{
		burnSize(square, row, column - 1, size);
	}
	//check above current cell
	if ((square.grid[row - 1][column].indata == 'b') && (square.grid[row - 1][column].burnChecked == false))
	{
		burnSize(square, row - 1, column, size);
	}
	//check right of current cell
	if ((square.grid[row][column + 1].indata == 'b') && (square.grid[row][column + 1].burnChecked == false))
	{
		burnSize(square, row, column + 1, size);
	}
	//check below current cell
	if ((square.grid[row + 1][column].indata == 'b') && (square.grid[row + 1][column].burnChecked == false))
	{
		burnSize(square, row + 1, column, size);
	}
	else
	{
		return;
	}
}
//tags shadow pixels as burnt, changes burneddata to grass
void fillShadow(RasterGrid& square, int row, int column)
{
	square.grid[row][column].isBurned = true;
	square.grid[row][column].burneddata = " g ";
	//check behind
	if ((square.grid[row][column - 1].indata == 'b') && (square.grid[row][column - 1].isBurned == false))
	{
		fillShadow(square, row, column - 1);
	}
	//check above
	if ((square.grid[row - 1][column].indata == 'b') && (square.grid[row - 1][column].isBurned == false))
	{
		fillShadow(square, row - 1, column);
	}
	//check in front
	if ((square.grid[row][column + 1].indata == 'b') && (square.grid[row][column + 1].isBurned == false))
	{
		fillShadow(square, row, column + 1);
	}
	//check below
	if ((square.grid[row + 1][column].indata == 'b') && (square.grid[row + 1][column].isBurned == false))
	{
		fillShadow(square, row + 1, column);
	}
}
//sets burneddata values of each cell
void setBurnSquare(RasterGrid& square, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (square.grid[i][j].burneddata == " g ")
			{
				continue;
			}
			else if (square.grid[i][j].isBurned)
			{
				square.grid[i][j].burneddata = " b ";
			}
			else
			{
				string str(1, square.grid[i][j].indata);
				square.grid[i][j].burneddata = " " + str + " ";
			}
		}
	}
}