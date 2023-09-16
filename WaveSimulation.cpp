#include <iostream>
#include <vector>
#include "LineFunctions.h"




int main()
{
	std::vector<GridVector> Grid;
	std::vector<DataVector> Data;

	CreateDataVector(Data, DEPTH);
	CreateGridVector(Grid, DEPTH);

	Data[3].data = -3;
	Data[4].data = 1;

	Data[15].data = 8;
	std::cout << "Before Deleting Cells: \n";
	PrintVectors(Grid,Data);	

	DeleteCells(Grid, Data, .01);

	std::cout << "\nAfter Deleting Cells: \n";
	PrintVectors(Grid,Data);

	return 0;
}