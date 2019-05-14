#pragma once

#include "Entity.cpp"
#include "Bot_war_soldier.cpp"
using namespace sf;



class Bullet : public Entity {
public:
    Soldier* owner;
    Bullet(float x, float y, Texture &image, float _dx, float _dy, Soldier *_owner) {
        owner = _owner;
        life = true;
        sprite.setTexture(image);  //������� � sprite �������� �������
        //sprite.setTextureRect(IntRect(0, 244, 40, 50)); // ������ � ����������� ��� �������� ��������� ������������
        rect = FloatRect(x,y,12,12);//������� ����������, ��� � ����������
    //    sprite.setPosition(40, 40); /
        sprite.setTextureRect(IntRect(112, 144, 12, 12));
        dx = _dx; dy = _dy;
    }

    bool update(float time) {
        rect.left += dx * time / 10;
        Collision(1);
        rect.top += dy * time / 10; //���������� y
        Collision(0);
        sprite.setPosition(rect.left, rect.top ); // ���������� x, y
        return true; //�� �� �����. ����� �� �����������.
    }

    void Collision(int dir) {
        for (int i = rect.top/16; i < (rect.top + rect.height)/16; i++) {
            for (int j = rect.left/16; j < (rect.left + rect.width)/16; j++) {
				 if (TileMap[i][j]=='1') {life = false;       }

            }
        }
    }
};

