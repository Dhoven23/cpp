#include <iostream>
#include <vector>
#include "LineFunctions.h"

void IterateWave(std::ve)

int main()
{
	std::vector<GridBlockVector> Grid;
	std::vector<DataVector> Data;
	CreateDataVector(Data,GRIDSIZE*(DEPTH-1)+1);
	CreateGridBlockVector(Grid,GRIDSIZE);



	for (int i = 0; i < DEPTH; ++i)
	{
		int jump = i*25;
		Data[10 + jump].data += -1;
		Data[11 + jump].data += 4;
		Data[12 + jump].data += 1;
		Data[27 + jump].data += 1;
		Data[28 + jump].data += -1;
		Data[29 + jump].data += 1;
	}
	int counter = 0;
	for(auto it = Data.begin(); it != Data.end(); ++it)
	{
		if( it->data != 0 ) counter++;
	}	

	double threshold = .1;

	
	int count1 = 0, count2 = 0;
	GetGridSize(Grid,count1);
	std::cout << "\n - - - - - - - - - Before Elimination - - - - - - - - - [Grid Size: ";
	std::cout << count1 << "]\n";

	PrintGridVectors(Grid,Data);



	DeleteCells(Grid, Data, threshold);

	ReorderData(Grid,Data);

	
	GetGridSize(Grid,count2);
	std::cout << "\n - - - - - - - - - After Elimination  - - - - - - - - - [Grid Size: ";
	std::cout << count2 << "]\n";

	PrintGridVectors(Grid,Data);

	std::cout << "\nCompression Ratio = " << (100 * ((float)count2/(float)count1)) << "%\n";

	std::cout << "\nRetention Ratio = " << (100 * ((float)count2/(float)counter)) << "%\n";
	

	return 0;
}