#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <map>


#include <iostream>

#include "Player.cpp"
#include "Entity.cpp"
#include "Bullet.cpp"
#include "Enemy.cpp"
#include "Lines.cpp"
#include "Dijkstra.cpp"
#include "Person.cpp"
#include "Bot_war_soldier.cpp"
#include "Bot_stupid_runner.cpp"
#include "Player.cpp"
#include "Neuron_Net.cpp"


//-31 -50 -8 -47 -48 4 33 -37 0 34 36 46 -49 -11 9 25 46 20 45 -23 -48 23 47 49
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <string>


//#include <SFML/Audio.hpp>

using namespace sf;


void RunGame() {
/*

bool visual = true;
bool who = true; //\F0\E5\F9\E0\E5\F2, \E1\F3\E4\E5\F2 \EB\E8 \F2\F3\F2 \F0\F3\F7\ED\EE\E5 \F3\EF\F0\E0\E2\EB\E5\ED\E8\E5 \E8\EB\E8 \ED\E5\F2.
const int num_of_bots = 10;
int inputs =  5; int outs = 1; int mids = 3; // number of neurons in the net of the bots.

    RenderWindow window(VideoMode(960, 960), "SFML works!");

    Texture t;
    t.loadFromFile("1.png");
    Sprite tile(t);

     // ���� � �������� ���� �����. ������
    ofstream f_net_out;
    f_net_out.open("f_net_out.txt");
    ifstream f_net_in;
    f_net_in.open("f_net_in.txt");
    int mas_weights[inputs * mids + mids * outs + 10];


    //����� �����
    ifstream f_map("map1.txt");
    for (int i = 0; i < H; i++) {
        std::string str;
        std::getline(f_map, str);
        TileMap[i] = str;
    }

    //���������, ��� ���������� ��� �����
    int x_start = 0; int y_start = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (TileMap[i][j] == '3') {
                x_start = j; y_start = i;
                break;
            }
        }
    }


    Line L(t);  //����� ��� ��������� ������� � ��������� ���������� �� ������

    //������ ���� �������� ����� (�����, ����, ������)
    std::list<Entity*>  entities;
    std::list<Bot*>  Bots_life;//����� � ����� ����� �����. ������ ���� � �������� �� ������� ���������
    std::list<Bot*> Bots_death;//����� � ����� �������. ���, ��� ����������� �� ������. ����� ��� ���� �������, � ������� �� ����� ������ ����� ����, ������� �������� ����� ���� � ������.
    std::list<Entity*>::iterator it;
    std::list<Bot*>::iterator Bbot;
 //   map <int, Bot*> Best_bots; //����� ����� �������� ��� 5 ��������� �� �����.

    Person p(1);
    p.Player_maker(t, x_start, y_start);

//���������� ������� � ��������. ��� ������?
    for (int i = 0; i < num_of_bots; i++) {
        Bots_life.push_back(new Bot(t, x_start, y_start));
    }
  /*  for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
        (*Bbot)->Net.fGetKohonet(f_net_in);
//   } */
   /*




    Enemy Enemy(t); //�����, � ������� � �������. ���� ������



    //Driver Driver(0); // �����, ������� ��������� �������!  (��-��-��, ����!)

    bool space = false; //���������, ����� �� SPACE ��� ���. ���� �� ��������, ����� ������� �� ����
    bool Right_key = false; //���������, ����� �� Right ��� ���. ���� ��� ����� ��������� �����.
    Clock clock; // ����� �������� ���� ��������� �� �������, � �� � �������� ������� ����������

    bool next_generation = false; //����� true - ������ ���� ����� � ���������� ������!

    while (window.isOpen()){


        float time = clock.getElapsedTime().asMicroseconds();
        time = time / 500; //���� ��������� �����.
        if (time > 20) time = 20;
    time = 20;
        clock.restart(); //������������� �����. ��� �� ������� �������� �����.

        Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		//std::cout << pixelPos.x << "\n";//������� �� ���������� � ������� ������� � ������� (��� �� ����� ������ ������ ����)
		//std::cout << pos.x << "\n";//������� �� �,������� ��������������� � ������� ����������


        //������� �������� ���� (���� ��������� �����)
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (who) {
    //����� ���������� ����������� ����������. p.control == true, ���� ��������� �������.
            int sp = p.control(pos);
            if (sp && !space) {
                space = true;
                float dx2 = pos.x-p.rect.left; float dy2 = pos.y - p.rect.top;
                float m = sqrt(dx2*dx2 + dy2 * dy2);
                entities.push_back(new Bullet(p.rect.left, p.rect.top, t, speed_bul*dx2/m, speed_bul*dy2/m, &p));
            }
        }

//�������� ��� ������� ������. ������ b->update  !!!


//����� � ��������� ���! NO_HUMAN!
        bool qqq = false;//��������, ���� �� ��� ����� ����
        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();){

            qqq = true;
            if (next_generation) {qqq = false;}
            Bot *b = *Bbot;//��� ��������, ����� �� ������ (*it)->
            b->control();
            b->life = (b->update(time)); //��� �������, ��� ������ ���������� �� ������
        //���� ��� ���������� �� ������, �� "������� ���", ������� � ������ ������� �����, �������� ��������� �� �������.
            if ((b->life == false) || (next_generation))	{
                b->dist_to_finish = Dijkstra(int((b->rect.left)/ 16), int((b->rect.top)/16));
                Bots_death.push_back(b);
                b->life = false;
             //   if (b->dist_to_finish < best_dist) {best_dist = b->dist_to_finish;}
                Bbot = Bots_life.erase(Bbot);

            }
            else Bbot++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}


//������ �������� �����, ���� ��� ���� ��������� ������.
		if (!qqq) {
            next_generation = false;
            unsigned long long int best_rot = 0;
            Bot *bb;
        //    printf("A1\n");
            int best_dist = 10000; // ���� ��� ���������� ������� ���� (������ �������� � ������.

//������ �������� "���������" ����
            for (Bbot = Bots_death.begin(); Bbot != Bots_death.end(); Bbot++){
                Bot *b = *Bbot;
                if ((b->dist_to_finish < (best_dist + 1)) && (b->score > best_rot)) {
                    best_rot = b->score;
                    if (b->dist_to_finish < (best_dist)) {best_dist = b->dist_to_finish;}
                    bb = b;
                }
            }
            bb->Net.mSaveKohonet(5, 3, 1, mas_weights);
            bb->Net.fSaveKohonet(5, 3, 1, f_net_out);
            printf("bb->dist_to_finish = %d  bb->score = %lld\n",  Dijkstra(int((bb->rect.left)/ 16), int((bb->rect.top)/16)), bb->score);


            int rrr = -5; //������ ��� ����� ��� ���������. ��� ����������� ����������
            for (Bbot = Bots_death.begin(); Bbot != Bots_death.end();){
                (*Bbot)->Net.mGetKohonet(mas_weights, rrr); rrr++;
                (*Bbot)->rect.left = float(x_start * 16);
                (*Bbot)->rect.top = float(y_start * 16);
                (*Bbot)->score = 0;
                Bots_life.push_back(*Bbot);
                Bbot = Bots_death.erase(Bbot);
            }
         /*   for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
                (*Bbot)->Net.rSaveKohonet();
                printf("\n");
      //      }*/
/*

        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {  window.close(); }

        //����� ��������� ����� ��� (����� ���� ����������� �� �����)
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (Right_key == false) {
                Right_key = true;
                for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
                    (*Bbot)->life = false;
                }
                next_generation = true;
            }
        } else {
            Right_key = false;
        }



        if (who) {p.update(time);}
        Enemy.update(0);

//�������� ������� ��������� �������� ����� (����� ��� ����, ����� �������)
        for (it = entities.begin(); it != entities.end();){
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false)	{ it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}


//������, �� ��������� �� ��� ����� ���� ������� �� �����. intersects - �������� �� ��� ��������?
        if (who) {if (p.rect.intersects(Enemy.rect) && Enemy.life) {
            Enemy.life = false;
        }}
        for (it = entities.begin(); it != entities.end(); it++){
			if ((*it)->rect.intersects(Enemy.rect) && Enemy.life) {
                Enemy.life = false;
            }
		}

if (visual)  {
        window.clear(Color::White);

        for (int i=0; i<H; i++) {
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='1')  tile.setTextureRect( IntRect(143-16*3,112,16,16) );
                if (TileMap[i][j]=='2')  tile.setTextureRect( IntRect(143-16*2,112 + 16,16,16) );
                if (TileMap[i][j]=='3')  tile.setTextureRect( IntRect(143-16*3,112 + 16,16,16) );
                if (TileMap[i][j]=='4')  tile.setTextureRect( IntRect(143-16*2,112,16,16) );
				if (TileMap[i][j]=='0') continue;

  			    tile.setPosition(j*16,i*16) ;
		        window.draw(tile);
		     }
        }

        //����� ������
        if(who) {L.rect.left = p.rect.left; L.rect.top = p.rect.top + 4;
        while (TileMap[int(L.rect.top/16)][int(L.rect.left/16)] == '0') {
            L.rect.left += 8 * cos(p.da); L.rect.top += 8 * sin(p.da); L.update(0);
            window.draw(L.sprite);
        }}

        window.draw(Enemy.sprite);
        if (who) {window.draw(p.sprite);}


        for (it = entities.begin(); it != entities.end(); it++){ window.draw((*it)->sprite);}

        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++) {
            window.draw((*Bbot)->sprite);
        }
        window.display();
}

    }


    /*Bot.Net.GetKohonet(f_net_in);
    Bot.Net.SaveKohonet(f_net_out);  // */  /*sss
    f_net_out.close();

*/

}

