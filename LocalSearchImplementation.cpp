//
// Created by alex on 05.06.17.
//
#include "stdafx.h"

struct Cluster
{
    int* center;
    int lengthVect;
    int radius;
};

int* genSolVect(int size);
int* localSearch(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect);

//расстояние между двумя векторами
int distance(int* vect1, int* vect2, int vectLength)
{
    int distance = 0;
    for (int i=0; i< vectLength; i++)
    {
        if (vect1[i] == vect2[i])
            distance++;
    }
    return distance;
}



int LocalSearchImplementation(int numVariables, int numBrackets, int variablesInBracket)
{
    int* startSolVect = genSolVect(numBrackets);
    int* localMax = localSearch(numVariables ,numBrackets, variablesInBracket, startSolVect);
    Cluster clusterLocal;
    clusterLocal.center = localMax;
    clusterLocal.lengthVect = numVariables;
    clusterLocal.radius = distance(startSolVect, localMax);
    list <Cluster> localMaxs;
    localMaxs.push_back(clusterLocal);

}