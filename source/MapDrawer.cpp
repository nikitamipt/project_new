// file.cpp: определяет точку входа для консольного приложения.
#pragma once




#include <iostream>
#include <fstream> // подключаем библиотеку




#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>


#include <iostream>


#include <unistd.h>
//#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//#include <SFML/Audio.hpp>

using namespace sf;

const int H1 = 60;//высота
const int W1 = 60;//ширина

const int ZZ = 16;

void Draw() {
    RenderWindow window(VideoMode(960, 960), "SFML works!");

    int MapGame[H1 * W1];
    for (int i = 0; i < H1; i++) {
        for (int j = 0; j < W1; j++) {
            MapGame[j + i * W1] = 1;
        }
    }

    bool click = false;

    Texture t;
    t.loadFromFile("2.png");
    Sprite tile(t);

     // куда я сохраняю нашу сетку. откуда

    ofstream fout;
    fout.open("map1.txt");

    ifstream fin;
    fin.open("map2.txt");

    printf("To change range:\nR = 3\nT = 5\nY = 7\n");

    int hhh = 1;


    Clock clock; // чтобы скорость была привязана ко времени, а не к тактовой частоте процессора

    bool space1 = false; //отслеживает залипания пробела
    int Drawer = false; // это переменная показывает, нажо ли рисовать
    int waller = false; // for making walls.
    int wal = false; // just as space1
    while (window.isOpen()){



        Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		//std::cout << pixelPos.x << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
		//std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты

        //событие закрытия окна (след несколько строк)
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

//Øèðèíà êèñòè, ÿ íå ñìîã ñäåëàòü íàïðÿìóþ ÷åðåç öèôðû, ïîýòîìó íàïèñàíî ÷åðåõ æîïó. êàê êîñòûëü ñîéäåò))
        if (Keyboard::isKeyPressed(Keyboard::R)) {hhh = 1;}
        if (Keyboard::isKeyPressed(Keyboard::T)) {hhh = 2;}
        if (Keyboard::isKeyPressed(Keyboard::Y)) {hhh = 4;}
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (!space1) {      space1 = true;
                                if (Drawer) {Drawer = false;}
                                else        {Drawer = true;}
            }
        } else { space1 = false; }
        if (Drawer) {
            int xxx = int(pos.x/16) % W1; if (xxx < 0) {xxx = W1 + xxx;}
            int yyy = int(pos.y/16) % H1; if (yyy < 0) {yyy = H1 + yyy;}
            for (int i = -hhh; i <= hhh; i++) {
                for (int j = - hhh; j <= hhh; j++) {
                    MapGame[(xxx + i + W1) % W1 + ((yyy + j + H1) % H1) * W1] = 0;
                }
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            if (!wal) {     wal = true;
                            if (waller) {waller = false;}
                            else        {waller = true;   }
            }
        } else {wal = false;}

        int xxx = int(pos.x/16) % W1; if (xxx < 0) {xxx = W1 + xxx;}
        int yyy = int(pos.y/16) % H1; if (yyy < 0) {yyy = H1 + yyy;}

        if (waller) {MapGame[xxx + yyy * W1] = 1;}

        if (Keyboard::isKeyPressed(Keyboard::X)) {
            MapGame[xxx + yyy * W1] = 2; //финишняя черта
        }
        if (Keyboard::isKeyPressed(Keyboard::C)) {
            MapGame[xxx + yyy * W1] = 3; //место старта человечка
        }
        if (Keyboard::isKeyPressed(Keyboard::V)) {
            MapGame[xxx + yyy * W1] = 4; //эта штука нужна для корректной работы Дейкстры. Между стартом человека и линией финиша должна быть линия этой штуки
        }



        if (Keyboard::isKeyPressed(Keyboard::Escape)) {  window.close(); }


        window.clear(Color::White);

        for (int i = 0; i < H1; i++) {
			 for (int j = 0; j < W1; j++)
			  {
				if (MapGame[j + i * W1]== 1)  tile.setTextureRect( IntRect(143-ZZ*3,112,ZZ,ZZ) );
                if (MapGame[j + i * W1]== 2)  tile.setTextureRect( IntRect(143-ZZ*2,112 + 16,ZZ,ZZ) );
                if (MapGame[j + i * W1]== 3)  tile.setTextureRect( IntRect(143-ZZ*3,112 + 16,ZZ,ZZ) );
                if (MapGame[j + i * W1]== 4)  tile.setTextureRect( IntRect(143-ZZ*2,112,ZZ,ZZ) );

				if (MapGame[j + i * W1]== 0) continue;
  			    tile.setPosition(j*ZZ,i*ZZ) ;
		        window.draw(tile);
		     }
        }
        window.display();


    }

    for (int i = 0; i < H1; i++) {
        for (int j = 0; j < W1; j++) {
            fout << MapGame[j + i * W1];
        }
        fout << "\n";
    }
    fout.close();
}


