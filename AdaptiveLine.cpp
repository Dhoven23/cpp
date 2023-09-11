#include <iostream>
#include <vector>

#define DEPTH 16

// Example Vector struct
typedef struct {
	// E Vector
	double E;
	// B vector
	double B;

	// indexes (this can definitely be done smarter)
	int priorIndex;
	int nextIndex;

} EmVector;

// Create Vector of structured memory
void CreateEmVector(std::vector<EmVector>& arr, double b, double e,unsigned L) {
	for (int i = 0; i < L; ++i)
	{
		// create element
		EmVector a;
		a.E = e;
		a.B = b;

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

// Loop Over Array and 'delete' cells from simulation with minimal E derivative
void DeleteCellsbyE(std::vector<EmVector>& arr, double Threshold)
{
	int index = 1;
	int significant_index = 0;
	int boundary = 0;

	while (boundary != -1)
	{
		if (index == DEPTH) break;

		EmVector a = arr[index];

		// index of last significant point
		
		// gradient of E around point
		double E_grad = (arr[a.priorIndex].E - arr[a.nextIndex].E)/2;
		// interpolated value of E
		double E_interp = arr[a.priorIndex].E + E_grad;
		// actual value of E
		double E_actual = a.E;
		// error
		double E_error = abs(E_actual - E_interp);

		// If point is significant
		if (E_error > Threshold)
		{
			// save point index
			significant_index = index;
			// go to next Index
			index = a.nextIndex;
			boundary = arr[index+1].nextIndex;

		}
		else
		{
			// set next index of last significant point to the next point
			arr[significant_index].nextIndex = index + 1;
			// aet prior index of next point to last significant point
			arr[index + 1].priorIndex = significant_index;
			// step index forward
			index = a.nextIndex;
			boundary = arr[index+1].nextIndex;
		}



	}
}


void printVector(std::vector<EmVector>& arr)
{


	int boundary = 0;
	int index = 0;
	
	while(index != -1)
	{
		std::cout << "Point[" << index << "] = " << arr[index].B << "\n";
		index = arr[index].nextIndex;
		
	}
}

// Loop over Array and replace cells if gradient is detected
void AddCells(){}

// Iterate FE simulation
void IterateCells(){}


// entry point
int main()
{
	std::vector<EmVector> EMF;

	double b = 1;
	double e = 2;
	CreateEmVector(EMF,b,e,DEPTH);
	std::cout << "Before Elimination:\n";
	printVector(EMF);

	DeleteCellsbyE(EMF,.01);
	std::cout << "\nAfter Elimination:\n";
	printVector(EMF);


}