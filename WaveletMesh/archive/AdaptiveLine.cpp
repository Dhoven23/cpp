#include <iostream>
#include <vector>

#define DEPTH 16

// This code is a test of the Deletion technique. A first pass at the idea, needs improvement

// Example Vector struct
typedef struct {
	// array index of data
	int dataAddress;

	// indexes (this can definitely be done smarter)
	int coordinate;
	int priorIndex;
	int nextIndex;

} GridVector;

typedef struct {
	// data
	double data;
	double data_last;
} DataVector;

// Create Vector of structured memory
void CreateGridVector(std::vector<GridVector>& arr, unsigned L) {
	for (int i = 0; i < L; ++i)
	{
		// create element
		GridVector a;
		a.dataAddress = i;
		a.coordinate = i;

		// set prior index to -1 to signal start of chain
		a.priorIndex = -1;

		// set next index to -1 to indicate end of chain
		a.nextIndex = -1;

		// if not start of chain
		if (i > 0)
		{
			a.priorIndex = i-1;

		}

		// if not end of chain
		if (i < (L-1))
		{
			a.nextIndex = i+1;
		}

		// add element to vector
		arr.push_back(a);
	}
}

// Create Vector of Data
void CreateDataVector(std::vector<DataVector>& arr, int L) {
	for (int i = 0; i < L; ++i)
	{
		DataVector a;
		a.data = 0;
		arr.push_back(a);

	}
}

// Loop Over Array and 'delete' cells from simulation with minimal E derivative
void DeleteCells(std::vector<GridVector>& arr, std::vector<DataVector>& data, double Threshold)
{
	int index = 1;
	int significant_index = 0;
	int boundary = 0;

	while (boundary != -1)
	{
		if (index == DEPTH) break;

		GridVector a = arr[index];

		// index of last significant point
		
		// gradient of E around point
		// double E_grad = (arr[a.priorIndex].E - arr[a.nextIndex].E)/2;
		double priorData = data[arr[a.priorIndex].dataAddress].data;
		double nextData  = data[arr[a.nextIndex].dataAddress].data;
		double grad = (priorData - nextData)/2;

		// interpolated value of E

		double E_interp = priorData + grad;
		// actual value of E
		double E_actual = data[arr[index].dataAddress].data;
		// error
		double E_error = abs(E_actual - E_interp);

		// If point is significant
		if (E_error > Threshold)
		{
			// save point index
			significant_index = index;
			// go to next Index
			index = a.nextIndex;
			boundary = arr[index].nextIndex;

		}
		else
		{
			// set next index of last significant point to the next point
			arr[significant_index].nextIndex = index + 1;
			// aet prior index of next point to last significant point
			arr[index + 1].priorIndex = significant_index;
			// step index forward
			index = a.nextIndex;
			boundary = arr[index].nextIndex;
		}

	}
	
}



void ReorderGrid(std::vector<GridVector>& arr, std::vector<DataVector>& data){

	// Count remaining cells (yes these steps can be combined duh)
	int index = 0;
	int count = 0;
	while(index != -1)
	{

		index = arr[index].nextIndex;
		
		count++;
	}
	index = 0;
	// Reorder Grid pointers
	for (int i = 0; i < count; i++)
	{
		int newDataAddress = arr[index].dataAddress;
		int newCoordinate = arr[index].coordinate;
		int newPriorindex = i-1;
		int newNextIndex = ( (i + 1) * (i != (count - 1))) + ( (-1) * (i == (count-1)));
		index = arr[index].nextIndex;
		arr[i].dataAddress = newDataAddress;
		arr[i].coordinate = newCoordinate;
		arr[i].priorIndex = newPriorindex;
		arr[i].nextIndex = newNextIndex;	
	}

	// Reorder Data
	for (int i = 0; i < count; i++)
	{
		data[i].data = data[arr[i].dataAddress].data;
		arr[i].dataAddress = i;
	}
}


void printVector(std::vector<GridVector>& arr, std::vector<DataVector>& data)
{


	int boundary = 0;
	int index = 0;
	
	while(index != -1)
	{
		if ( (( arr[index].dataAddress > 9) || (arr[index].coordinate > 9)) && (arr[index].dataAddress < 9))std::cout << " ";
		std::cout << arr[index].dataAddress;
		for(int i = 0; i<(arr[index].nextIndex - index); i++)
		{
				std::cout << " - ";
		}
		
		
		index = arr[index].nextIndex;
		
	}
	std::cout << "\n";

	index = 0;
	while(index != -1)
	{
		//if(arr[index].dataAddress > 9) std::cout << " ";
		std::cout << arr[index].coordinate;
		for(int i = 0; i<(arr[index].nextIndex - index); i++)
		{
				std::cout << " - ";
		}
		
		
		index = arr[index].nextIndex;
		
	}
	std::cout << "\n";

	index = 0;
	while(index != -1)
	{
		if ( ( arr[index].dataAddress > 9) || (arr[index].coordinate > 9) )std::cout << " ";
		
		std::cout << data[arr[index].dataAddress].data;
		for(int i = 0; i<(arr[index].nextIndex - index); i++)
		{
				std::cout << " - ";
		}
		
		
		index = arr[index].nextIndex;
	}
	std::cout << "\n";
}

// entry point
int main()
{
	// Create vectors
	std::vector<GridVector> Grid;
	std::vector<DataVector> Data;

	CreateGridVector(Grid,DEPTH);
	CreateDataVector(Data, DEPTH);

	// set test data
	Data[10].data = 5;
	Data[3].data = 8;

	// print test data
	std::cout << "Before Elimination:\n";
	printVector(Grid,Data);

	// perform compression
	DeleteCells(Grid,Data,.01);
	ReorderGrid(Grid,Data);

	// print compressed Vector
	std::cout << "\nAfter Elimination:\n";
	printVector(Grid,Data);
	

	return 0;


}