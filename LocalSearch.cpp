// LocalSearch.cpp: определяет точку входа для консольного приложения.
//
//

#include "stdafx.h"
#define N 9
using namespace std;
resultLS localSearch(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect);
int* genSolVect(int size);
int localSearchImplementation(int numVariables, int numBrackets, int variablesInBracket);

int main(int argc, char** argv[])
{
    srand(time(0));
    int numVariables = 50; //кол-во переменных
	cout<<"Result is " << localSearchImplementation(numVariables, 218, 4) <<endl;
	//localSearch(numVariables ,91, 4, genSolVect(numVariables));
	
    //system("pause");
	return 0;
}

