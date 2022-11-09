#include "RasterGrid.h"
#include <iostream>

//set outdata and adjust the string value to output nicely
void RasterGrid::Cell::setOutData(std::string str)
{
	if (str.length() == 1)
	{
		outdata = " " + str + " ";
	}
	else if (str.length() == 2)
	{
		outdata = str + " ";
	}
	else
	{
		outdata = str;
	}
}
//print the raster grid's initial values without the border
void RasterGrid::printInGrid()
{
	std::cout << "r=" << rows << ", c=" << columns << std::endl;

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			std::cout << ' ' << grid[i][j].indata << ' ';
		}
		std::cout << std::endl;
	}
}
//print the raster grid's output values without the border
void RasterGrid::printOutGrid()
{
	std::cout << "r=" << rows << ", c=" << columns << std::endl;

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			std::cout << grid[i][j].getOutData();
		}
		std::cout << std::endl;
	}
}
//write the raster grid's out data to a file
void RasterGrid::writeOutGrid(std::shared_ptr<std::ofstream> outFile)
{
	*outFile << "r=" << storedRows << ", c=" << storedColumns << std::endl;

	for (std::vector<Cell> rowvec : grid)
	{
		for (Cell c : rowvec)
		{
			*outFile << c.getOutData();
		}
		*outFile << std::endl;
	}
}