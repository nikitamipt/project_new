#include "Player.cpp"


using namespace sf;


class Person : public Player {
public:
    Person(int i) {}

    bool control(Vector2f pos) {
        bool space1 = false;
        if (Keyboard::isKeyPressed(Keyboard::Right) or (Keyboard::isKeyPressed(Keyboard::D))) { da += 0.03; }
        if (Keyboard::isKeyPressed(Keyboard::Left)  or (Keyboard::isKeyPressed(Keyboard::A))) { da -= 0.03; }
        if (Keyboard::isKeyPressed(Keyboard::Up)    or (Keyboard::isKeyPressed(Keyboard::W))) { dsp = 1;  }
        if (Keyboard::isKeyPressed(Keyboard::Down)  or (Keyboard::isKeyPressed(Keyboard::S))) { dsp = -1; }
        if (Keyboard::isKeyPressed(Keyboard::Space) and (clock() - last_shot > 3000000)) { //перезадрядка 1000милисек
            space1 = true;
            last_shot = clock();
        }
        else {space1 = false;}

        unsigned int lll = clock();
//while (clock() - lll < 10000) {}
        dx = dsp*cos(da); dy = dsp*sin(da); dsp = 0;

        return space1;
    }


};


