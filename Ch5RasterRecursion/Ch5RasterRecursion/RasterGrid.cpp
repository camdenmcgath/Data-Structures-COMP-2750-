#include "RasterGrid.h"
#include <iostream>
#include <functional>

//set outdata and adjust the string value to output nicely
void RasterGrid::Cell::setClusterData(std::string str)
{
	if (str.length() == 1)
	{
		clusterdata = " " + str + " ";
	}
	else if (str.length() == 2)
	{
		clusterdata = str + " ";
	}
	else
	{
		clusterdata = str;
	}
}
//print the raster grid's initial values without the border
void RasterGrid::print(std::function<void(Cell)> output)
{
	std::cout << "r=" << rows << ", c=" << columns << std::endl;

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			output(grid[i][j]);
		}
		std::cout << std::endl;
	}
}
//write the raster grid's out data to a file
void RasterGrid::writeOutputs(std::shared_ptr<std::ofstream> outFile,
	std::function<std::string(Cell)> output1, std::function<std::string(Cell)> output2)
{
	*outFile << "r=" << rows << ", c=" << columns << std::endl;

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			*outFile << output1(grid[i][j]);
		}		 
		*outFile << std::endl;
	}

	*outFile << std::endl;

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			*outFile << output2(grid[i][j]);
		}
		*outFile << std::endl;
	}
}