#pragma once

#include "Entity.cpp"
using namespace sf;



class Line {
public:
    FloatRect rect; //����������
    Sprite sprite; // ���� ��������
    Soldier_without_walls* owner;
    float dx; float dy;
    Line(Texture &image) {
        sprite.setTexture(image);  //������� � sprite �������� �������
        //sprite.setTextureRect(IntRect(0, 244, 40, 50)); // ������ � ����������� ��� �������� ��������� ������������
        rect = FloatRect(0,0,4,4);//������� ����������, ��� � ����������
    //    sprite.setPosition(40, 40); /
        sprite.setTextureRect(IntRect(112, 144, 4, 4));
    }

    void update(float time) {
        rect.left += dx; rect.top  += dy;
        if (rect.left < 0) {rect.left += (16 * W);} else if (rect.left >= (16 * W)) {rect.left -= (16 * W);}
        if (rect.top  < 0) {rect.top  += (16 * H);} else if (rect.top  >= (16 * H)) {rect.top  -= (16 * H);}
        sprite.setPosition(rect.left, rect.top ); // ���������� x, y
    }


};
