// LocalSearch.cpp: определяет точку входа для консольного приложения.
//
//

#include "stdafx.h"
#define N 9
using namespace std;
int* localSearch(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect);
int* genSolVect(int size);

int main(int argc, char** argv[])
{
    int numVariables = 20; //кол-во переменных

	localSearch(numVariables ,91, 4, genSolVect(numVariables));

    //system("pause");
	return 0;
}

