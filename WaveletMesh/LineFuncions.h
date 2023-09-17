#include <iostream>
#include <vector>

#define DEPTH 17
#define GRIDSIZE 32

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


typedef struct {
	std::vector<GridVector> GridVector;
} GridBlockVector;

void CreateGridBlockVector(std::vector<GridBlockVector>& arr, int L){
	for (int i = 0; i < L; ++i){
		GridBlockVector gridBlock;
		for (int j = 0; j < DEPTH; ++j){
			// create element
			GridVector a;
			a.dataAddress = (i * 16) + j;
			a.coordinate =  (i * 16) + j;
			// add element to vector
			gridBlock.GridVector.push_back(a);
		}
		arr.push_back(gridBlock);
	}
}




// Create Vector of structured memory
void CreateGridVector(std::vector<GridVector>& arr, unsigned L) {
	for (int i = 0; i < L; ++i){
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
	for (int i = 0; i < L; ++i){
		DataVector a;
		a.data = 0;
		arr.push_back(a);

	}
}

void DeleteRecursion(std::vector<GridVector>& arr, std::vector<DataVector>& data, std::vector<GridVector>& outputGrid, double threshold, int step, int block){
	int index = step;
	int count = step*2;

	while(index != -1){
		double last_point = data[arr[index-step].dataAddress].data;
		double next_point = data[arr[index+step].dataAddress].data;
		double current_point = data[arr[index].dataAddress].data;
		double error = abs(current_point - (last_point + (next_point - last_point)/2));
		
		if ( error > threshold){
			outputGrid[index].dataAddress = arr[index].dataAddress;
			outputGrid[index].coordinate += (16 * block);
		} else {
			
			outputGrid[index].coordinate = -1;
			outputGrid[index].dataAddress = 0;
		}
		
		index += count;

		if (index > (DEPTH-1)) index = -1;
	}

	step <<= 1;

	if (step < 16) {
		DeleteRecursion(arr, data, outputGrid, threshold, step, block);
	}
}

// Delete cells in single where derivative is below threshold
void DeleteVectorCells(std::vector<GridVector>& arr, std::vector<DataVector>& data, int blockID, double threshold){
	
	std::vector<GridVector> temp;
	CreateGridVector(temp,arr.size());
	temp[0].coordinate = arr.front().coordinate;
	temp[16].coordinate = arr.back().coordinate;
	temp[0].dataAddress = arr.front().dataAddress;
	temp[16].dataAddress = arr.back().dataAddress;

	DeleteRecursion(arr,data,temp,threshold,1,blockID);
	arr.clear();
	for (int i = 0; i < DEPTH; ++i){
		if (temp[i].coordinate != -1){
			arr.push_back(temp[i]);
		}
	}
}

// Delete cells for all vectors in Grid
void DeleteCells(std::vector<GridBlockVector>& Grid, std::vector<DataVector>& Data, double threshold){
	for (int i = 0; i < GRIDSIZE; ++i){
		DeleteVectorCells(Grid[i].GridVector,Data,i,threshold);
	}
}

void ReorderData(std::vector<GridBlockVector>& Grid,std::vector<DataVector>& Data){

	std::vector<DataVector> ReorderedData;
	int counter = 0;

	for (int i = 0; i < GRIDSIZE; ++i){
		for (int j = 0; j < (Grid[i].GridVector.size() - 1); ++j){
			int address = Grid[i].GridVector[j].dataAddress;
			ReorderedData.push_back(Data[address]);
		}
	}
	counter = 0;
	Data.clear();
	for(auto it = ReorderedData.begin(); it != ReorderedData.end(); ++it){
		Data.push_back(*it);
	}
	for (int i = 0; i < GRIDSIZE; ++i){

		for (int j = 0; j < (Grid[i].GridVector.size()); j++){
			if (j < (Grid[i].GridVector.size() - 1)){
				Grid[i].GridVector[j].dataAddress = counter;
				++counter;
			} else {
				Grid[i].GridVector[j].dataAddress = counter;
			}
		}
	}
}


// Add Cells where derivative is high
void AddCells(std::vector<GridVector>& arr, std::vector<DataVector>& Data)
{

}

void PrintVectorsSingle(std::vector<GridVector>& arr, std::vector<DataVector>& Data){
	for (int i = 0; i < arr.size(); ++i){
		if(arr[i].coordinate < 10) std::cout << '0';
		std::cout<< arr[i].coordinate << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1){
			std::cout << "** - ";
			iter--;
		}	
	}
	std::cout << '\n';
	for (int i = 0; i < arr.size(); ++i){
		if(arr[i].dataAddress < 10) std::cout << '0';
		std::cout<< arr[i].dataAddress << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1){
			std::cout << "** - ";
			iter--;
		}
	}
	std::cout << '\n';
	for (int i = 0; i < arr.size(); ++i){
		if((Data[arr[i].dataAddress].data < 10) && (Data[arr[i].dataAddress].data > -1)) std::cout << '0';
		std::cout<< Data[arr[i].dataAddress].data << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1){
			std::cout << "** - ";
			iter--;
		}
	}
	std::cout << '\n';
}

void PrintGridVectors(std::vector<GridBlockVector>& Grid, std::vector<DataVector>& Data){
	for (int i = 0; i < GRIDSIZE; ++i){
		std::cout << i << '\n';
		for (int j = 0; j < Grid[i].GridVector.size(); ++j){
			if((Grid[i].GridVector[j].coordinate < 10) 
				&& (Grid[i].GridVector[j].coordinate != -1))
				std::cout << '0';
			if((Grid[i].GridVector[j].coordinate < 100) 
				&& (Grid[i].GridVector[j].coordinate != -1))
				std::cout << '0';
			std::cout << Grid[i].GridVector[j].coordinate << " - ";
			int iter = Grid[i].GridVector[j+1].coordinate - Grid[i].GridVector[j].coordinate;
			while (iter > 1){
				std::cout << "*** - ";
				iter--;
			}
		}
		std::cout << '\n';
		for (int j = 0; j < Grid[i].GridVector.size(); ++j){
			if((Grid[i].GridVector[j].dataAddress < 10) 
				&& (Grid[i].GridVector[j].dataAddress != -1))
				std::cout << '0';
			if((Grid[i].GridVector[j].dataAddress < 100) 
				&& (Grid[i].GridVector[j].dataAddress != -1))
				std::cout << '0';
			std::cout << Grid[i].GridVector[j].dataAddress << " - ";
			int iter = Grid[i].GridVector[j+1].coordinate - Grid[i].GridVector[j].coordinate;
			while (iter > 1){
				std::cout << "*** - ";
				iter--;
			}
		}
		std::cout << '\n';
		for (int j = 0; j < Grid[i].GridVector.size(); ++j){
			double point = Data[Grid[i].GridVector[j].dataAddress].data;
			if((point < 10)
				&& (point >= 0))
				std::cout << '0';
			if((point < 100)
				&& (point >= 0))
				std::cout << '0';
			if(point < 0)
				std::cout << ' ';

			std::cout << point << " - ";
			int iter = Grid[i].GridVector[j+1].coordinate - Grid[i].GridVector[j].coordinate;
			while (iter > 1){
				std::cout << "*** - ";
				iter--;
			}
		} std::cout << '\n';
	}
}

void PrintGridVectors(std::vector<GridVector>& arr, std::vector<DataVector>& Data, int step){
	for (int i = 0; i < arr.size(); ++i){
		if(arr[i].coordinate < 10) std::cout << '0';
		std::cout<< arr[i].coordinate << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1){
			std::cout << "** - ";
			iter--;
		}
	}
	std::cout << '\n';
	for (int i = 0; i < arr.size(); ++i){
		if(arr[i].dataAddress < 10) std::cout << '0';
		std::cout<< arr[i].dataAddress << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1){
			std::cout << "** - ";
			iter--;
		}
	}
	std::cout << '\n';
	for (int i = 0; i < arr.size(); ++i){
		int dataAddress = arr[i].dataAddress;
		if((Data[dataAddress].data < 10) && (Data[dataAddress].data > -1)) std::cout << '0';
		std::cout<< Data[dataAddress].data << " - ";
		int iter = arr[i+1].coordinate - arr[i].coordinate;
		while (iter > 1){
			std::cout << "** - ";
			iter--;
		}
	} std::cout << '\n';
}

void GetGridSize(std::vector<GridBlockVector>& Grid, int& size){
	size = 0;
	for (int i = 0; i < GRIDSIZE; ++i){
		size += (Grid[i].GridVector.size() - 1);
	}
}