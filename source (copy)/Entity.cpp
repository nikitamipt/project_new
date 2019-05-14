#pragma once

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>

#include <iostream>

#include <SFML/Graphics.hpp>

using namespace sf;



class Entity {
public:
    float dx, dy; //��������
    FloatRect rect; //���������� ������ �������� (x,y,������ ������)
    Sprite sprite; // ���� ��������
    virtual bool update(float time) = 0; //���������� true, ���� �� ����� ������������ �� �������� ������������ �� ������.
    bool life;
    int VIN; //����� ��������. �����, ����� �������� ���� ������ �����

};

