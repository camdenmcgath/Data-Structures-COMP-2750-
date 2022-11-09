#pragma once

#include <string>
#include <vector>
#include <fstream>

class RasterGrid
{
public:
	struct Cell
	{
		char indata{};
		bool checked{};
		const std::string getOutData() const { return outdata; }
		void setOutData(std::string);
	private:
		std::string outdata = " 0 ";
	};

	std::vector<std::vector<Cell>> grid;
	int rows{};
	int columns{};
	//increased dimensions to store the raster grid with a default border 
	int storedRows{};
	int storedColumns{};

	RasterGrid(int initrows, int initcolumns)
		: rows(initrows), columns(initcolumns)
		, storedRows(initrows + 2), storedColumns(initcolumns + 2)
	{
		grid.resize(storedRows);
		for (int i = 0; i < storedRows; i++)
		{
			grid[i].resize(storedColumns);
		}
	}
	void printInGrid();
	void printOutGrid();
	void writeOutGrid(std::shared_ptr<std::ofstream>);
};