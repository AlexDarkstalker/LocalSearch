//
// Created by alex on 05.06.17.
//
#include <iterator>
#include <algorithm>
#include "stdafx.h"


int* genSolVect(int size);
resultLS localSearch(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect);

int getMax(list <Cluster> list);

//расстояние между двумя векторами
int distance(int* vect1, int* vect2, int vectLength)
{
    int distance = 0;
    for (int i=0; i< vectLength; i++)
    {
        if (vect1[i] != vect2[i])
            distance++;
    }
    return distance;
}

//сравнение списков (проверка на изменение)
bool equalLists(list <Cluster> list1, list <Cluster> list2)
{
    if (list1.size() != list2.size())
        return false;
    list<Cluster>::iterator listIt1 = list1.begin();
    list<Cluster>::iterator listIt2 = list2.begin();
    for(int i = 0; i < list1.size(); i++) {
        std::advance(listIt1, i);
        std::advance(listIt2, i);
        Cluster cluster1 = *listIt1;
        Cluster cluster2 = *listIt2;
        if(cluster1.radius != cluster2.radius)
            return false;
    }
    return true;
}

list<Cluster> copyList(list<Cluster> list1)
{
    list <Cluster> copy;
    for_each(list1.begin(), list1.end(), [] (Cluster cluster){copy.push_back(cluster);});
    return copy;
}

int* getInversion (int* vect, int vectLength)
{
    int* result = new int[vectLength];
    for (int i = 0; i<vectLength; i++)
        result[i] = !vect[i];
    return result;
}

int isInCluster (int* vect, list<Cluster> clusters)
{
    list<Cluster>::iterator listIt = clusters.begin();
    for (int i = 0; i<clusters.size(); i++)
    {
        std::advance(listIt, i);
        Cluster cluster = *listIt;
        if (distance(vect, cluster.center, cluster.lengthVect) <= cluster.radius)
            return i;
    }
    return  -1;
}

int isClusterCenter (int* localMax, list <Cluster> clusters)
{
    bool isEqual;
    list<Cluster>::iterator listIt = clusters.begin();
    for (int i = 0; i<clusters.size(); i++)
    {
        isEqual = true;
        std::advance(listIt, i);
        Cluster cluster = *listIt;
        for(int j=0; j<cluster.lengthVect; j++)
        {
            if(localMax[j] != cluster.center[j]) {
                isEqual = false;
                break;
            }
        }
        if (isEqual)
            return i;
    }
    return -1;
}

int getMax(std::list<Cluster> clusters) {
    int max = 0;
    clusters.sort();
    Cluster res = *clusters.end();
    return res.value;
}

void localSearchIter(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect, int* localMax, list<Cluster> clusters)
{
    resultLS resLS = localSearch(numVariables ,numBrackets, variablesInBracket, startSolVect);
    localMax = resLS.solVect;
    int res = isClusterCenter(localMax, clusters);
    if ( res < 0) {
        Cluster clusterLocal;
        clusterLocal.center = localMax;
        clusterLocal.lengthVect = numVariables;
        clusterLocal.radius = distance(startSolVect, localMax);
        clusterLocal.value = resLS.localMax;
        clusters.push_back(clusterLocal);
    }
    else {
        list <Cluster>::iterator listIt = clusters.begin();
        std::advance(listIt, res);
        Cluster cluster = *listIt;
        clusters.remove(cluster);
        cluster.radius = distance(localMax, startSolVect);
        clusters.insert(listIt, cluster);
    }
}

int localSearchImplementation(int numVariables, int numBrackets, int variablesInBracket)
{
    unsigned int startTime = clock(); //начальное время
    int* startSolVect = genSolVect(numBrackets);
    resultLS resLS = localSearch(numVariables ,numBrackets, variablesInBracket, startSolVect);
    int* localMax = resLS.solVect;
    Cluster clusterLocal;
    clusterLocal.center = localMax;
    clusterLocal.lengthVect = numVariables;
    clusterLocal.radius = distance(startSolVect, localMax);
    clusterLocal.value = resLS.localMax;
    list <Cluster> localMaxs;
    localMaxs.push_back(clusterLocal);
    list <Cluster> currentIterMaxs;
    do{
        currentIterMaxs = copyList(localMaxs);
        startSolVect = getInversion(localMax, numVariables);
        int res = isInCluster(startSolVect, currentIterMaxs);
        if (res > -1)
        {
            int count = 0;
            while ((isInCluster(startSolVect, currentIterMaxs) > -1)&&(count<10)) {
                startSolVect = genSolVect(numBrackets);
                count++;
            }
            if (count < 10)
                localSearchIter(numVariables ,numBrackets, variablesInBracket, startSolVect, localMax, localMaxs);
            else
            {
                break;

            }
        }
        else
            localSearchIter(numVariables ,numBrackets, variablesInBracket, startSolVect, localMax, localMaxs);

    } while (!equalLists(localMaxs, currentIterMaxs));
    unsigned int endTime = clock(); // конечное время
    unsigned int searchTime = endTime - startTime; // искомое время
    cout << "time [mc] -  " << searchTime << endl;


    return getMax(localMaxs);

}

