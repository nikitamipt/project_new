#pragma once


#include "Entity.cpp"

using namespace sf;


float offsetX = 0, offsetY = 0;

const int W = 60;

const int speed_bul = 3;
const int H = 60;

String TileMap[H];


class Player : public Entity {
public:
    float dsp;  //����� �� �� ��������� ��� ���?
    float da;   //���� ������������ Ox
    int last_shot; // less than 1 shot in 20 days..

    bool onGround; // �� ������ �� �� ���������?
    float currentFrame; // ������ ��������� ��������
    int num_of_kills; //����� ������� ���� ����������. "� ������ ���� ������� �� ����������� � ������, ��������� � ������ ������"

    void Player_maker(Texture &image, int x_start, int y_start) {
        sprite.setTexture(image);  //������� � sprite �������� �������
        rect = FloatRect(int(x_start * 16), int(y_start * 16),int(16),int(16));//������� ����������, ��� � ����������
        sprite.setPosition(rect.left, rect.top);
        sprite.setTextureRect(IntRect(5*16, 9*16, 16, 16));
        dx = 0; dy = 0; da = 0;
        currentFrame = 0;
        last_shot = 0; //��� ��� ���������� ��� �������� �� �������!
       // sprite.setOrigin(16/2, 16 / 2);
    }

// ���������� true, ��� ��������� ������������ �� ������..
    bool update(float time) {
        int result = 0;
        rect.left += (dx * time / 10); rect.top  += (dy * time / 10);
        if (rect.left < 0) {rect.left += (16 * W);} else if (rect.left >= (16 * W)) {rect.left -= (16 * W);}
        if (rect.top  < 0) {rect.top  += (16 * H);} else if (rect.top  >= (16 * H)) {rect.left -= (16 * H);}
        sprite.setPosition(rect.left, rect.top );

      //  sprite.setRotation(da * 180 /3.1415);
        dx = 0; dy = 0;

        return true;
    }

};


