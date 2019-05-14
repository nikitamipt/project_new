#pragma once

#include "Entity.cpp"
using namespace sf;



class Line {
public:
    FloatRect rect; //����������
    Sprite sprite; // ���� ��������
    Soldier* owner;
    Line(Texture &image) {
        sprite.setTexture(image);  //������� � sprite �������� �������
        //sprite.setTextureRect(IntRect(0, 244, 40, 50)); // ������ � ����������� ��� �������� ��������� ������������
        rect = FloatRect(0,0,4,4);//������� ����������, ��� � ����������
    //    sprite.setPosition(40, 40); /
        sprite.setTextureRect(IntRect(112, 144, 4, 4));
    }

    void update(float time) {
        sprite.setPosition(rect.left, rect.top ); // ���������� x, y
    }


};
