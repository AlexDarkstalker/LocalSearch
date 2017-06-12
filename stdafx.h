// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <fstream>
#include <list>
#include <cstdlib>

using namespace std;


struct resultLS
{
    int* solVect;
    int localMax;
};

struct Cluster
{
    int* center;
    int lengthVect;
    int radius;
    int value;
    bool operator < (const Cluster &point) const {
        return this->value < point.value;
    }
	bool operator == (const Cluster &point) const {
		return (this->value == point.value) && (this->radius == point.radius) && (this->lengthVect == point.lengthVect);
	}
};


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
