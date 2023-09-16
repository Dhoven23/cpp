#include <iostream>
#include <vector>

#define DEPTH 17

// Example Vector struct
typedef struct {
	// array index of data
	int dataAddress;

	// indexes (this can definitely be done smarter)
	int coordinate;


} GridVector;

// Example Data struct
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

void DeleteRecursion(std::vector<GridVector>& arr, std::vector<DataVector>& data, std::vector<GridVector>& outputGrid, double threshold, int step)
{
	int index = step;
	int count = step*2;

	while(index != -1)
	{
		double last_point = data[arr[index-step].dataAddress].data;
		double next_point = data[arr[index+step].dataAddress].data;
		double current_point = data[arr[index].dataAddress].data;
		double error = abs(current_point - (last_point + (next_point - last_point)/2));
		
		if ( error > threshold)
		{
			outputGrid[index] = arr[index];

		} else {
			
			outputGrid[index].coordinate = -1;
		}
		
		index += count;

		if (index > (DEPTH-1)) index = -1;

	}

	step <<= 1;

	if (step < 16) 
	{
		DeleteRecursion(arr, data, outputGrid, threshold, step);
	}
}



// Delete cells where derivative is below threshold
void DeleteCells(std::vector<GridVector>& arr, std::vector<DataVector>& data, double threshold)
{
	
	std::vector<GridVector> temp;
	CreateGridVector(temp,arr.size());

	DeleteRecursion(arr,data,temp,threshold,1);
	arr.clear();
	for (int i = 0; i < temp.size(); ++i)
	{
		if (temp[i].coordinate != -1)
		{
			arr.push_back(temp[i]);
		}
	}
	std::vector<DataVector> tempData;

	tempData = data;

	data.clear();
	for (int i = 0; i < arr.size(); ++i)
	{
		data.push_back(tempData[arr[i].dataAddress]);
		arr[i].dataAddress = i;
		
	}
}

// Add Cells where derivative is high
void AddCells(std::vector<GridVector>& arr, std::vector<DataVector>& Data)
{

}

void PrintVectors(std::vector<GridVector>& arr, std::vector<DataVector>& Data)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		if(arr[i].coordinate < 10) std::cout << '0';
		std::cout<< arr[i].coordinate << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1)
		{
			std::cout << "** - ";
			iter--;
		}
		
	}
	std::cout << '\n';
	for (int i = 0; i < arr.size(); ++i)
	{
		if(arr[i].dataAddress < 10) std::cout << '0';
		std::cout<< arr[i].dataAddress << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1)
		{
			std::cout << "** - ";
			iter--;
		}
		
	}
	std::cout << '\n';
	for (int i = 0; i < arr.size(); ++i)
	{
		if((Data[arr[i].dataAddress].data < 10) && (Data[arr[i].dataAddress].data > -1)) std::cout << '0';
		std::cout<< Data[arr[i].dataAddress].data << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1)
		{
			std::cout << "** - ";
			iter--;
		}
		
	}
	std::cout << '\n';
}