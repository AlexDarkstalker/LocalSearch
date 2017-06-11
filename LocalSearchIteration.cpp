//локальный поиск. метрика Хе
// numBrackets - количество скобок
// variablesInBracket - количество переменных в скобке

#include "stdafx.h"


int** fileMatr(int nRows, int nCol)
{
	int** matrix = new int*[nRows];
	for (int i = 0; i < nRows; i++)
		matrix[i] = new int[nCol];

	ifstream  Matrix("data//20_91_15.txt");
	for (int i = 0; i < nRows; i++)	{
		for (int j = 0; j < nCol; j++)
			Matrix >> matrix[i][j];
	}
	return matrix;
}

int** genMatrix(int nRows, int nCol, int limit)
{
	srand(time(NULL));

	int** matrix = new int*[nRows];
	for (int i = 0; i < nRows; i++)
		matrix[i] = new int[nCol];

	for (int i = 0; i < nRows; i++)
	for (int j = 0; j < nCol; j++)
	{
		matrix[i][j] = 0;
	}

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			while (!matrix[i][j])
					matrix[i][j] = (((rand() % (2 * limit + 1))) - limit);
		}

		
	}
		return matrix;
}

int* genSolVect(int size)
{
	srand(time(NULL));

	int* solVect = new int[size];
	for (int i = 0; i < size; i++)
		solVect[i] = rand() % 2;

	return solVect;
}

bool isExecuted(int* bracket, int bracketSize, int* solVect, int solVectSize)
{
	bool result = false;
	for (int i = 0; i < bracketSize; i++)
	{
		if ((solVect[abs(bracket[i]) - 1] && (bracket[i] > 0)) || (!solVect[abs(bracket[i]) - 1] && (bracket[i] < 0)))
			result = true;
	}

	return result;
}

int countExecutedBrackets(int** formula, int bracketSize, int numBrackets, int* solVect, int solVectSize)
{
	int count = 0;
	for (int i = 0; i < numBrackets; i++)
	{
		if (isExecuted(formula[i], bracketSize, solVect, solVectSize))
			count++;
	}
	return count;
}

int* getNeighbourAtIndex(int* vect, int index, int solVectSize)//
{
	int* neighbVect = new int[solVectSize];
	for (int i = 0; i < solVectSize; i++)
		neighbVect[i] = vect[i];
	neighbVect[index] = !neighbVect[index];

	return neighbVect;
}


int* localRecords(int** formula, int bracketSize, int numBrackets, int* solVect, int solVectSize)
{
	int* records = new int[solVectSize + 1];
	records[0] = countExecutedBrackets(formula, bracketSize, numBrackets, solVect, solVectSize);
	for (int i = 1; i <= solVectSize + 1; i++)
	{
		records[i] = countExecutedBrackets(formula, bracketSize, numBrackets, getNeighbourAtIndex(solVect,i-1, solVectSize), solVectSize);
	}

	return records;
}

void printFormula(int** formula, int numBrackets, int variablesInBracket)
{
	for (int i = 0; i < numBrackets; i++)
	{
		for (int j = 0; j < variablesInBracket; j++)
		{
			std::cout << formula[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void printSolVect(int* startSolVect, int numVariables)
{
	for (int j = 0; j < numVariables; j++)
	{
		std::cout << startSolVect[j] << " ";
	}
	std::cout << std::endl;
}

void printRecords(int* records, int numVariables)
{
	for (int j = 0; j < numVariables + 1; j++)
	{
		std::cout << records[j] << " ";
	}
	std::cout << std::endl;
}

int getMaxElemIndex(int* records, int numVariables)
{
	int indexRecord = -1;
	int max = records[0];
	for (int i = 1; i < numVariables; i++)
	{
		if (max < records[i])
		{
			max = records[i];
			indexRecord = i-1;
		}
	}
	return indexRecord;
}
int localSearchProc(int** formula, int bracketSize, int numBrackets, int* solVect, int solVectSize, int* records, int& iterCount)
{
	//int* records = localRecords(formula, bracketSize, numBrackets, solVect, solVectSize);
	int indexRecord = getMaxElemIndex(records, solVectSize + 1);
	while (indexRecord >= 0)
	{
		solVect[indexRecord] = !solVect[indexRecord];
	    records = localRecords(formula, bracketSize, numBrackets, solVect, solVectSize);
		indexRecord = getMaxElemIndex(records, solVectSize + 1);
		iterCount++;
	}
	//printRecords(records, solVectSize);
	return records[0];
}


resultLS localSearch(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect)
{
    resultLS res;
	int** formula = genMatrix(numBrackets, variablesInBracket, numVariables);
    int* startVect = new int[numVariables];
    for (int i = 0; i<numVariables; i++)
        startVect[i] = startSolVect[i];
	//int** formula = fileMatr(numBrackets, variablesInBracket);
	//printFormula(formula, numBrackets, variablesInBracket);
	//startSolVect = genSolVect(numVariables);
	//printSolVect(startSolVect, numVariables);
	int* records = localRecords(formula, variablesInBracket, numBrackets, startVect, numVariables);
	//printRecords(records, numVariables);
	int iterCount = 0;

	res.localMax = localSearchProc(formula, variablesInBracket, numBrackets, startVect, numVariables, records, iterCount);
    res.solVect = startVect;
	//printSolVect(startVect, numVariables);
	//std::cout << localSearchMax << std::endl;
    cout << "iterCount =  " << iterCount << endl;

	return res;
}