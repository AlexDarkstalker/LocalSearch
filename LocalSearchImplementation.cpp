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
    list<Cluster>::iterator listIt1;
    list<Cluster>::iterator listIt2;
    for(listIt1 = list1.begin(), listIt2 = list2.begin(); listIt1 != list1.end(), listIt2 != list2.end() ; listIt1++, listIt2++) {
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
	list<Cluster>::iterator it;
   // for_each(list1.begin(), list1.end(), [] (Cluster cluster){copy.push_back(cluster);});
	for (it = list1.begin(); it != list1.end(); ++it)
	{ 
		copy.push_back(*it);
	}
	return copy;
}

int* getInversion (int* vect, int vectLength)
{
    int* result = new int[vectLength];
    cout << "Inverted vector is: ";
    for (int i = 0; i<vectLength; i++) {
        result[i] = !vect[i];
        cout << result[i] << " ";
    }
    cout << endl;
    return result;
}

int isInCluster (int* vect, list<Cluster> clusters)
{
    list<Cluster>::iterator listIt = clusters.begin();
    for (int i = 0; i < clusters.size(); i++)
    {
        listIt = clusters.begin();
        std::advance(listIt, i);
        Cluster cluster = *listIt;
        if (distance(vect, cluster.center, cluster.lengthVect) <= cluster.radius) {
            cout << "isInCluster number: " << i << endl;
            return i;
        }

    }
    cout << "Isn't in any cluster " << endl;
    return  -1;
}

int isClusterCenter (int* localMax, list <Cluster> clusters)
{
    bool isEqual;
    list<Cluster>::iterator listIt = clusters.begin();
    for (int i = 0; i<clusters.size(); i++)
    {
        listIt = clusters.begin();
        std::advance(listIt, i);
        isEqual = true;
        Cluster cluster = *listIt;
        for(int j=0; j<cluster.lengthVect; j++)
        {
            if(localMax[j] != cluster.center[j]) {
                isEqual = false;
                break;
            }
        }
        if (isEqual) {
            cout << "isClusterCenter number: " << i << endl;
            cout << "Cluster center ";
            for(int i = 0; i < cluster.lengthVect; i++)
                cout << cluster.center[i] << " ";
            cout << endl;
            cout << "Local max ";
            for(int i = 0; i < cluster.lengthVect; i++)
                cout << localMax[i] << " ";
            cout << endl;
            return i;
        }
    }
    return -1;
}

int getMax(std::list<Cluster> clusters) {
    int max = 0;
    clusters.sort();
	list <Cluster>::iterator iter = clusters.begin();
	std::advance(iter, clusters.size() - 1);
    Cluster res = *iter;
    return res.value;
}

void copyVect(int* vect1, int* vect2, int vectSize) {
    for(int i = 0; i < vectSize; i++)
        vect1[i] = vect2[i];
}

void printList(list<Cluster> clusters) {
    //list<Cluster>::iterator it;
    for_each(clusters.begin(), clusters.end(), [](Cluster cluster) {cout << "Cluster radius: " << cluster.radius << " Value: " << cluster.value << endl;} );


}

void localSearchIter(int numVariables, int numBrackets, int variablesInBracket, int* startSolVect, int* localMax, list<Cluster>* clusters)
{
    cout << "Start vector: ";
    for(int i = 0; i < numVariables; i++)
        cout << startSolVect[i] << " ";
    cout << endl;
    resultLS resLS = localSearch(numVariables ,numBrackets, variablesInBracket, startSolVect);
    //localMax = resLS.solVect;
    copyVect(localMax, resLS.solVect, numVariables);
    cout << "Local max: ";
    for(int i = 0; i < numVariables; i++)
        cout << localMax[i] << " ";
    cout << endl;
    cout << "Value: " << resLS.localMax << endl;
    int res = isClusterCenter(localMax, *clusters);
    if ( res < 0) {
        Cluster clusterLocal;
        clusterLocal.lengthVect = numVariables;
        clusterLocal.radius = distance(startSolVect, localMax, numVariables);
        clusterLocal.value = resLS.localMax;
        clusterLocal.center = new int[numVariables];
        copyVect(clusterLocal.center, localMax, clusterLocal.lengthVect);
//        clusterLocal.center = localMax;

        clusters->push_back(clusterLocal);
        cout << "New cluster added: " << clusters->size() << endl;
    }
    else {
        list <Cluster>::iterator listIt = clusters->begin();
        std::advance(listIt, res);
        Cluster cluster = *listIt;

        cout << endl;
        cout << "Cluster radius changed:" << endl;
        cout << "Old value: " << cluster.radius << endl;
        clusters->remove(cluster);
		cluster.radius = distance(localMax, startSolVect, numVariables);
        cout << "New value: " << cluster.radius << endl;
        //listIt = clusters->begin();
        std::advance(listIt, -1);
        clusters->insert(listIt, cluster);
    }
}

int localSearchImplementation(int numVariables, int numBrackets, int variablesInBracket)
{
    unsigned int startTime = clock(); //начальное время
    int* startSolVect = genSolVect(numVariables);
    resultLS resLS = localSearch(numVariables ,numBrackets, variablesInBracket, startSolVect);
//    int* localMax = resLS.solVect;
    int* localMax = new int[numVariables];
    copyVect(localMax, resLS.solVect, numVariables);

    Cluster clusterLocal;
    clusterLocal.center = new int[numVariables];
    copyVect(clusterLocal.center, localMax, clusterLocal.lengthVect);
//    clusterLocal.center = localMax;
    clusterLocal.lengthVect = numVariables;
    clusterLocal.radius = distance(startSolVect, localMax, numVariables);
    clusterLocal.value = resLS.localMax;
    cout << "Just created local max: ";
    for(int i = 0; i < numVariables; i++)
        cout << localMax[i] << " ";
    cout << endl;
    cout << "ClusterLocal center ";
    for(int i = 0; i < clusterLocal.lengthVect; i++)
        cout << clusterLocal.center[i] << " ";
    cout << endl;
    list <Cluster> localMaxs;
    localMaxs.push_back(clusterLocal);
    list <Cluster> currentIterMaxs;
    do{
        currentIterMaxs = copyList(localMaxs);
        printList(currentIterMaxs);
        startSolVect = getInversion(localMax, numVariables);
        int res = isInCluster(startSolVect, currentIterMaxs);
        if (res > -1)
        {
            int count = 0;
            while ((isInCluster(startSolVect, currentIterMaxs) > -1)&&(count<5)) {
                startSolVect = genSolVect(*&numVariables);
                for(int i = 0; i < numVariables; i++)
                    cout << startSolVect[i] << " ";
                cout << endl;
                count++;
            }
            if (count < 5)
                localSearchIter(numVariables ,numBrackets, variablesInBracket, startSolVect, localMax, &localMaxs);
            else
            {
                break;

            }
        }
        else
            localSearchIter(numVariables ,numBrackets, variablesInBracket, startSolVect, localMax, &localMaxs);

    } while (!equalLists(localMaxs, currentIterMaxs));
    unsigned int endTime = clock(); // конечное время
    unsigned int searchTime = endTime - startTime; // искомое время
    cout << "time [mc] =  " << searchTime << endl;
	cout << "num of max = " << localMaxs.size() << endl;

    return getMax(localMaxs);

}

