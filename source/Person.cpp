//#include "Player.cpp"
#include "Player_without_walls.cpp"


using namespace sf;


class Person : public Player {
public:
    Person(int i) {}

    bool control(Vector2f pos) {
        last_shot++;
        bool space1 = false;
        if (Keyboard::isKeyPressed(Keyboard::Right) or (Keyboard::isKeyPressed(Keyboard::D))) { da += 0.03; }
        if (Keyboard::isKeyPressed(Keyboard::Left)  or (Keyboard::isKeyPressed(Keyboard::A))) { da -= 0.03; }
        if (Keyboard::isKeyPressed(Keyboard::Up)    or (Keyboard::isKeyPressed(Keyboard::W))) { dsp = 1;  }
        if (Keyboard::isKeyPressed(Keyboard::Down)  or (Keyboard::isKeyPressed(Keyboard::S))) { dsp = -1; }
        if (Keyboard::isKeyPressed(Keyboard::Space) and (last_shot > 10)) { //������������ 1000�������
            space1 = true;
            last_shot = 0;
        }
        else {space1 = false;}


//while (clock() - lll < 20000) {}
        dx = dsp*cos(da); dy = dsp*sin(da); dsp = 0;

        return space1;
    }


};


