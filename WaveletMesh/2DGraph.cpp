#include <iostream>
#include <vector>



void PrintGrid(std::vector<int>& GridX, std::vector<int>& GridY){
	for (int i = 0; i < GridY.size(); ++i){
		for (int j = 0; j < GridX.size(); ++j){
			char c = ((GridY[i] == 1) && (GridX[j] == 1)) ? '*' : ' ';
			c = ((GridY[i] != 0) && (GridX[j] == 0)) ? '-' : c;
			c = ((i > 0) && (GridY[i-1] == 1) && (GridY[i] == 0) && (GridX[j] == 1)) ? '|' : c;
			c = ((i > 0) && (GridY[i+1] == 1) && (GridY[i] == 0) && (GridX[j] == 1)) ? '|' : c;
			c = ((i > 0) && (GridY[i] == 0) && (GridX[j] == 1)) ? '|' : c;
			std::cout << ' ' << c << ' ';

		}
		std::cout << '\n';
	}
} 

int main()
{
	std::vector<int> GridX = {1,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1};
	std::vector<int> GridY = {1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1};
	PrintGrid(GridX,GridY);	
	return 0;
}