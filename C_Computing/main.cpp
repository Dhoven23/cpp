#include <iostream>
#include <vector>
#include <array>

#define DEPTH 100
//#include "Mesh.h"

typedef struct {
	// B field vector
	double B[3]; 
	// E field vector
	double E[3];
} EmField;

// Initialize 
int init_EMfield(EmField *obj, double b[3], double e[3])
{
	if (!obj)
		return 1;
	for (int i = 0; i < 3; ++i)
	{
		obj->B[i] = b[i];
		obj->E[i] = e[i];
	}
	
	return 0;
}

int clear_EMfield(EmField *MemArray[], size_t length){
	if (!MemArray)
		return 1;
	for (int i = 0; i < length; ++i)
		free(MemArray[i]);
	return 0;
}

void Create_EMfield(EmField *EMF[], double b[3], double e[3], int L){


	for (int i=0;i<L;i++)
	{
		EMF[i] = (EmField*)malloc(sizeof(EmField));
		if (init_EMfield(EMF[i],b,e) == 1) {
			fprintf(stderr,"[ERROR] init_EMfield() failed\n");
			break;
		}
	}
}

void print_EMfield(EmField *EMF[])
{
	for (int j = 0; j < DEPTH; ++j)
	{
		for (int i=0;i<3;i++)
		{
			std::cout << "B[" << j << "] field [" << i << "] = " << EMF[254]->B[i];
			std::cout << ", E[254] field [" << i << "] = " << EMF[254]->E[i] << "\n";
		}
	}
}


void get_EMF_atPoint(EmField *EMF[], double* E, double* B, int x){
	double point_E[3];
	double point_B[3];

	for (int i = 0; i < 3; ++i)
	{
		point_B[i] = EMF[x]->B[i];
		point_E[i] = EMF[x]->E[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		*(E+i) = point_E[i];
		*(B+i) = point_B[i];
	}
}

int main()
{
	

	double b[3] = {1,1,1};
	double e[3] = {2,2,2};

	int X = DEPTH;
	int Y = DEPTH;
	int Z = DEPTH;

	int L = X * Y * Z;

	EmField *EMF[L];

	Create_EMfield(EMF,b,e,L);


	//print_EMfield(EMF);

	double Earr[3];
	double Barr[3];
	double *Eptr = Earr;
	double *Bptr = Barr;



	for (int i = 0; i < L; ++i)
	{
		get_EMF_atPoint(EMF,Eptr,Bptr,i);

	
		std::cout << "B field at index: " << i 
									<< " -> <x,y,z> = [" 
									<< *(Bptr + 0) << ","
									<< *(Bptr + 1) << ","
									<< *(Bptr + 2) << "]\n"
		;
		std::cout << "E field at index: " << i 
									<< " -> <x,y,z> = [" 
									<< *(Eptr + 0) << ","
									<< *(Eptr + 1) << ","
									<< *(Eptr + 2) << "]\n"
		;
	}

	
	


	
	clear_EMfield(EMF,L);
		printf("Finished\n");
	return 0;
}

