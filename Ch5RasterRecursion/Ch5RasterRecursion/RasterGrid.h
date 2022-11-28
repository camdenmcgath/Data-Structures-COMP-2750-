#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <functional>

class RasterGrid
{
public:
	struct Cell
	{
		char indata{};
		bool checked{};
		bool burnChecked{};
		bool isBurned{};
		const std::string getClusterData() const { return clusterdata; }
		void setClusterData(std::string);
		std::string burneddata{};
	private:
		std::string clusterdata = " 0 ";
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
	void print(std::function<void(Cell)>);
	void writeOutputs(std::shared_ptr<std::ofstream>, 
		std::function<std::string(Cell)>, std::function<std::string(Cell)>);

};