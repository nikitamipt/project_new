#include "source/Game1.cpp"
#include "source/MapDrawer.cpp"
#include "source/Game_with_Runners.cpp"
#include "source/Game_war.cpp"


#include <SFML/Graphics.hpp>



int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int i = 0; int j = 1;
    while (j) {
        cout << "Write a number. if..\n1 - to draw map for runners\n2 - Game_with_Runners\n3 - War_Game\n0 - EXIT\n";
        cin >> i;
        if      (i == 1) { Draw();              j = 0;}
        else if (i == 2) { Game_with_Runners(); j = 0;} //çäåñü áîòû ó÷àòñÿ áåãàòü ïî ëàáèðèíòó
        else if (i == 3) { Game_war();          j = 0;}
        else if (i == 0) { j = 0;}
        else {
            cout << "Wrong number. Read again\n\n";
        }
    }

  return 0;
}

