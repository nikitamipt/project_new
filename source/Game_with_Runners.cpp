#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <map>


#include <iostream>
/*
#include "Player.cpp"
#include "Entity.cpp"
#include "Bullet.cpp"
#include "Enemy.cpp"
#include "Lines.cpp"
#include "Dijkstra.cpp"
#include "Person.cpp"
#include "Bot.cpp"
#include "Bot_stupid_runner.cpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <string>
*/

/*
 \CF\EE\F1\F2\E0\ED\EE\E2\EA\E0 \E7\E0\E4\E0\F7\E8: \ED\E0\E4\EE \EE\E1\F3\F7\E8\F2\FC \E1\EE\F2\E0 \E1\E5\E3\E0\F2\FC \EF\EE \EB\E0\E1\E8\F0\E8\ED\F2\F3.
 \D3 \E1\EE\F2\E0 \E5\F1\F2\FC 5 \E2\F5\EE\E4\EE\E2 - \F0\E0\F1\F1\F2\EE\FF\ED\E8\FF \E4\EE \E1\EB\E8\E6\E0\E9\F8\E8\F5 \F1\F2\E5\ED\EE\EA. \C2\EE \E2\F0\E5\EC\FF \EE\EF\E5\F0\E0\F6\E8\E8 control \EA\E0\E6\E4\FB\E9 \E8\E7 \E1\EE\F2\EE\E2 \E4\EE\EB\E6\E5\ED \E2\FB\E4\E0\F2\FC \F7\E8\F1\EB\EE - \F3\E3\EE\EB, \ED\E0 \EA\EE\F2\EE\F0\FB\E9 \EE\ED \EF\EE\E2\E5\F0\ED\E5\F2\F1\FF\EE\F2\ED\EE\F1\E8\F2\E5\EB\FC\ED\EE \F2\E5\EA\F3\F9\E5\E3\EE \ED\E0\EF\F0\E0\E2\EB\E5\ED\E8\FF.
 \DD\F2\EE\F2 \F3\E3\EE\EB \ED\E0\F5\EE\E4\F2\F1\FF \F1 \EF\EE\EC\EE\F9\FC\FE \ED\E5\E9\F0\EE\ED\ED\EE\E9 \F1\E5\F2\E8, \EE\E1\F3\F7\E0\FE\F9\E5\E9\F1\FF \EF\EE \EF\F0\E8\ED\F6\E8\EF\F3 \E3\E5\ED\E5\F2\E8\F7\E5\EA\EE\E3\EE \E0\EB\E3\EE\F0\E8\F2\EC\E0 - \EF\EE\E1\E5\E6\E4\E0\E5\F2 \EB\F3\F7\F8\E8\E9.
 1) \C7\E0\EF\F3\F1\EA\E0\FE \EC\ED\EE\E3\EE \E1\EE\F2\EE\E2 \F1 \F0\E0\ED\E4\EE\EC\ED\FB\EC\E8 \EA\EE\FD\F4\F4\E8\F6\E8\E5\ED\F2\E0\EC\E8 \E2 \ED\E5\E9\F0\EE\ED\EA\E5
 2) \C1\EE\F2\FB \EF\F0\EE\E1\E5\E3\E0\FE\F2 \ED\E5\EA\EE\F2\EE\F0\EE\E5 \F0\E0\F1\F1\F2\EE\FF\ED\E8\E5 \E8, \EA\E0\F1\E0\FF\F1\FC \F1\F2\E5\ED\EE\EA, \EF\EE\EC\E8\F0\E0\FE\F2.
 3) \C2\FB\E1\E8\F0\E0\E5\EC \E1\EE\F2\E0, \EA\EE\F2\EE\F0\FB\E9 \EF\F0\EE\E1\E5\E6\E0\EB \E4\E0\EB\FC\F8\E5 \E2\F1\E5\F5 \E8 \EF\F0\E8 \FD\F2\EE\EC \E7\E0\F0\E0\E1\EE\F2\E0\EB \E1\EE\EB\FC\F8\E5 \E2\F1\E5\F5 \EE\F7\EA\EE\E2 (\F1\EC\EE\F2\F0\E8 score \E2 \EA\EB\E0\F1\F1\E5 Bot)
 4) \C1\E5\F0\E5\EC \E5\E3\EE \EA\EE\FD\F4\F4\E8\F6\E8\E5\ED\F2\FB \ED\E5\E9\F0\EE\ED\EA\E8.
 5) \D1\EE\E7\E4\E0\E5\EC \ED\EE\E2\F3\FE \EF\E0\F0\F2\E8\FE \E1\EE\F2\EE\E2, \F2\EE\EB\FC\EA\EE \F2\E5\EF\E5\F0\FC \E8\F5 \ED\E5\E9\F0\EE\ED\EA\E8 \E8\EC\E5\FE\F2 \EA\EE\FD\F4\F4\E8\F6\E8\E5\ED\F2\E0 \EF\F0\E5\E4\FB\E4\F3\F9\E5\E3\EE \E1\EE\F2\E0 \F1 \F0\E0\ED\E4\EE\EC\ED\FB\EC \E8\E7\EC\E5\ED\E5\ED\E8\E5\EC 30% \EE\F2 \EE\E1\F9\E5\E3\EE \F7\E8\F1\EB\E0 \EA\EE\FD\F4\F4\E8\F6\E8\E5\ED\F2\EE\E2.
 6) \CF\E5\F0\E5\F5\EE\E6\F3 \EA \EF\F3\ED\EA\F2\F3 2), \EF\EE\EA\E0 \ED\E5 \E4\EE\F1\F2\E8\E3\ED\F3 \F4\E8\ED\E8\F8\E0.
*/


//#include <SFML/Audio.hpp>

using namespace sf;


void Game_with_Runners() {

bool visual = true;
bool who = true; //\F0\E5\F9\E0\E5\F2, \E1\F3\E4\E5\F2 \EB\E8 \F2\F3\F2 \F0\F3\F7\ED\EE\E5 \F3\EF\F0\E0\E2\EB\E5\ED\E8\E5 \E8\EB\E8 \ED\E5\F2.
const int num_of_bots = 10000;
int inputs =  5; int mids = 3; int outs = 1; // number of neurons in the net of the bots.


    RenderWindow window(VideoMode(960, 960), "SFML works!");

    Texture t;
    t.loadFromFile("2.png");
    Sprite tile(t);

     // \EA\F3\E4\E0 \FF \F1\EE\F5\F0\E0\ED\FF\FE \ED\E0\F8\F3 \F1\E5\F2\EA\F3. \EE\F2\EA\F3\E4\E0
    ofstream f_net_out;
    f_net_out.open("f_net_out_Runner.txt");
    ifstream f_net_in;
    f_net_in.open("f_net_in_Runner.txt");
    int mas_weights[inputs * mids + mids * outs + 10];


    //\F7\E8\F2\E0\FE \EA\E0\F0\F2\F3
    ifstream f_map("map1.txt");
    for (int i = 0; i < H; i++) {
        std::string str;
        std::getline(f_map, str);
        TileMap[i] = str;
    }

    //\EE\EF\F0\E5\E4\E5\EB\FF\FE, \E3\E4\E5 \E2\EE\E7\F0\E0\E4\E8\F2\F1\FF \ED\E0\F8 \E3\E5\F0\EE\E9
    int x_start = 0; int y_start = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (TileMap[i][j] == '3') {
                x_start = j; y_start = i;
                break;
            }
        }
    }


    Line L(t);  //\ED\F3\E6\ED\EE \E4\EB\FF \F0\E8\F1\EE\E2\E0\ED\E8\FF \EF\F0\E8\F6\E5\EB\E0 \E8 \ED\E0\F5\EE\E6\E4\ED\E8\E9 \F0\E0\F1\F1\F2\EE\FF\ED\E8\E9 \E4\EE \F1\F2\E5\ED\EE\EA

    std::list<Runner*>  Bots_life;//\E7\E4\E5\F1\FC \FF \F5\F0\E0\ED\FE \E6\E8\E2\FB\F5 \E1\EE\F2\EE\E2. \CA\E0\E6\E4\FB\E9 \F2\E0\EA\F2 \FF \EE\E1\ED\EE\E2\EB\FF\FE \E8\F5 \F2\E5\EA\F3\F9\E5\E5 \EF\EE\EB\EE\E6\E5\ED\E8\E5
    std::list<Runner*> Bots_death;//\E7\E4\E5\F1\FC \FF \F5\F0\E0\ED\FE \EC\E5\F0\F2\E2\FB\F5. \D2\E5\F5, \F7\F2\EE \F1\F2\EE\EB\EA\ED\F3\EB\E8\F1\FC \F1\EE \F1\F2\E5\ED\EE\E9. \CA\EE\E3\E4\E0 \E2\F1\E5 \E1\EE\F2\FB \F3\EC\E8\F0\E0\FE\F2, \FF \E2\FB\E1\E8\F0\E0\FE \E8\E7 \FD\F2\EE\E3\EE \F1\EF\E8\F1\EA\E0 \E1\EE\F2\EE\E2 \E1\EE\F2\E0, \EA\EE\F2\EE\F0\FB\E9 \EE\EA\E0\E7\E0\EB\F1\FF \E1\EB\E8\E6\E5 \E2\F1\E5\F5 \EA \F4\E8\ED\E8\F8\F3.
    std::list<Entity*>::iterator it;
    std::list<Runner*>::iterator Bbot;


//\F1\EE\E7\E4\E0\FE \E2\F1\E5\F5 \E1\EE\F2\EE\E2 \E2 \ED\E0\F7\E0\EB\E5
    for (int i = 0; i < num_of_bots; i++) {
        Bots_life.push_back(new Runner(t, x_start, y_start, inputs, mids, outs));
    }


    bool Right_key = false; //\EA\EE\ED\F2\F0\EE\EB\E8\F2, \ED\E0\E6\E0\F2 \EB\E8 Right \E8\EB\E8 \ED\E5\F2. \CD\E0\E4\EE \E4\EB\FF \ED\EE\E2\EE\E9 \E3\E5\ED\E5\F0\E0\F6\E8\E8 \E1\EE\F2\EE\E2. \C5\E5 \ED\E0\E6\E8\EC\E0\F2\FC \EC\EE\E6\ED\EE \F2\EE\E3\E4\E0, \EA\EE\E3\E4\E0 \E2\F1\E5 \E1\EE\F2\FB \F1\F2\EE\FF\F2 \ED\E0 \EC\E5\F1\F2\E5 \E8 \ED\E5 \EF\EE\EC\E8\F0\E0\FE\F2.
    Clock clock; // \F7\F2\EE\E1\FB \F1\EA\EE\F0\EE\F1\F2\FC \E1\FB\EB\E0 \EF\F0\E8\E2\FF\E7\E0\ED\E0 \EA\EE \E2\F0\E5\EC\E5\ED\E8, \E0 \ED\E5 \EA \F2\E0\EA\F2\EE\E2\EE\E9 \F7\E0\F1\F2\EE\F2\E5 \EF\F0\EE\F6\E5\F1\F1\EE\F0\E0


    bool next_generation = false; //\EA\EE\E3\E4\E0 true - \F3\E1\E8\E2\E0\FE \E2\F1\E5\F5 \E1\EE\F2\EE\E2 \E8 \EF\E5\F0\E5\F0\EE\E6\E4\E0\FE \EB\F3\F7\F8\C5\C3\CE!

    while (window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds(); // time \ED\F3\E6\E5\ED \E4\EB\FF \F2\EE\E3\EE, \F7\F2\EE\E1\FB \E8\E3\F0\E0 \E7\E0\EF\F3\F1\EA\E0\EB \F1 \EE\E4\ED\EE\E9 \E8 \F2\EE\E9 \E6\E5 \F1\EA\EE\F0\EE\F1\F2\FC\FE \E2\ED\E5\E7\E0\E2\E8\F1\E8\EC\EE\F1\F2\E8 \EE\F2 \E7\E0\E3\F0\F3\E6\E5\ED\ED\EE\F1\F2\E8 \EF\F0\EE\F6\E5\F1\F1\EE\F0\E0
        time = time / 500; //\E4\E0\F2\FC \EF\F0\EE\F8\E5\E4\F8\E5\E5 \E2\F0\E5\EC\FF.
        if (time > 20) time = 20;
   // time = 20;
        clock.restart(); //\EF\E5\F0\E5\E7\E0\E3\F0\F3\E6\E0\E5\F2 \E2\F0\E5\EC\FF. \D2\E0\EA \EC\FB \E8\E7\EC\E5\F0\E8\EC \F1\EA\EE\F0\EE\F1\F2\FC \F2\E0\EA\F2\E0.

        //\F1\EE\E1\FB\F2\E8\E5 \E7\E0\EA\F0\FB\F2\E8\FF \EE\EA\ED\E0 (\F1\EB\E5\E4 \ED\E5\F1\EA\EE\EB\FC\EA\EE \F1\F2\F0\EE\EA)
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

//\E7\E4\E5\F1\FC \F3\EF\F0\E0\E2\EB\FF\E5\F2 \E1\EE\F2! NO_HUMAN!
        bool qqq = false;//\EF\F0\EE\E2\E5\F0\FF\FE, \E5\F1\F2\FC \EB\E8 \E5\F9\E5 \E6\E8\E2\FB\E5 \E1\EE\F2\FB
        bool window_close = false; //for closing window...
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close(); window_close = true;
        }

        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();){
            qqq = true;
            Runner *b = *Bbot;//\E4\EB\FF \F3\E4\EE\E1\F1\F2\E2\E0, \F7\F2\EE\E1\FB \ED\E5 \EF\E8\F1\E0\F2\FC (*it)->
            b->control();
            b->life = (b->update_walls(time)); //\E1\EE\F2 \F3\EC\E8\F0\E0\E5\F2, \EA\E0\EA \F2\EE\EB\FC\EA\EE \F1\F2\EE\EB\EA\ED\F3\EB\F1\FF \F1\EE \F1\F2\E5\ED\EE\E9
        //\E5\F1\EB\E8 \E1\EE\F2 \F1\F2\EE\EB\EA\ED\F3\EB\F1\FF \F1\EE \F1\F2\E5\ED\EE\E9, \F2\EE "\F3\E1\E8\E2\E0\E5\EC \E5\E3\EE", \E7\E0\ED\EE\F1\E8\EC \E2 \F1\EF\E8\F1\EE\EA \EC\E5\F0\F2\E2\FB\F5 \E1\EE\F2\EE\E2, \F1\F7\E8\F2\FB\E2\E0\FF \E4\E8\F1\F2\E0\ED\F6\E8\FE \E4\EE \F4\E8\ED\E8\ED\F8\E0.

            if ((b->life == false) || (next_generation) || (window_close))	{
                b->dist_to_finish = Dijkstra(int((b->rect.left)/ 16), int((b->rect.top)/16));
                Bots_death.push_back(b);
                b->life = false;
                Bbot = Bots_life.erase(Bbot);
            }
            else Bbot++;//\E8 \E8\E4\E5\EC \EA\F3\F0\F1\EE\F0\EE\EC (\E8\F2\E5\F0\E0\F2\EE\F0\EE\EC) \EA \F1\EB\E5\E4 \EE\E1\FA\E5\EA\F2\F3. \F2\E0\EA \E4\E5\EB\E0\E5\EC \F1\EE \E2\F1\E5\EC\E8 \EE\E1\FA\E5\EA\F2\E0\EC\E8 \F1\EF\E8\F1\EA\E0
		}

        if (next_generation) {qqq = false;}  //\D2\EE \E5\F1\F2\FC \E5\F1\EB\E8 \E1\FB\EB\E0 \ED\E0\E6\E0\F2\E0 \EA\ED\EE\EF\EE\F7\EA\E0 Right

// \C5\F1\EB\E8 \E2\F1\E5 \E1\EE\F2\FB \EE\EA\E0\E7\E0\EB\E8\F1\FC \EC\E5\F0\F2\E2\FB, \E7\E0\ED\EE\E2\EE \E7\E0\EF\F3\F1\EA\E0\FE \E1\EE\F2\EE\E2
        if (!qqq && !window_close) {


            next_generation = false;
            unsigned long long int best_rot = 0;
            Runner *bb;
            int best_dist = 10000; // \ED\E0\E4\EE \E4\EB\FF \EE\EF\F0\E5\E4\E5\EB\ED\E8\FF \EB\F3\F7\F8\E5\E3\EE \E1\EE\F2\E0 (\F1\E0\EC\EE\E3\EE \E1\EB\E8\E6\ED\E5\E3\EE \EA \F4\E8\ED\E8\F8\F3.
//\ED\E0\F5\EE\E6\F3 \ED\E0\E8\E1\EE\EB\E5\E5 "\F3\F1\EF\E5\F8\ED\EE\E3\EE" \E1\EE\F2\E0
            for (Bbot = Bots_death.begin(); Bbot != Bots_death.end(); Bbot++){
                Runner *b = *Bbot;
//printf("b->dist_to_finish = %d, best_dist = %d, b->score = %lld, best_rot = %lld", b->dist_to_finish, best_dist, b->score, best_rot);
                if ((b->dist_to_finish < (best_dist + 1)) && (b->score >= best_rot)) {
                    best_rot = b->score;
                    if (b->dist_to_finish < (best_dist)) {best_dist = b->dist_to_finish;}
                    bb = b;
                }
            }
            bb->Net.mSaveKohonet(mas_weights);
            bb->Net.fSaveKohonet(f_net_out);
           // printf("bb->dist_to_finish = %d  bb->score = %lld\n",  Dijkstra(int((bb->rect.left)/ 16), int((bb->rect.top)/16)), bb->score);
          //  bb->Net.rSaveKohonet();

            int rrr = -2; //\EF\E5\F0\E2\FB\E9 \E3\E5\ED \E1\F3\E4\E5\F2 \E1\E5\E7 \E8\E7\EC\E5\ED\E5\ED\E8\E9. \E2\F1\E5 \EF\EE\F1\EB\E5\E4\F3\FE\F9\E8\E5 \E7\E0\EC\E5\ED\FF\F2\FC\F1\FF
            for (Bbot = Bots_death.begin(); Bbot != Bots_death.end();){

                (*Bbot)->Net.mGetKohonet(mas_weights, rrr++);
                (*Bbot)->rect.left = float(x_start * 16);
                (*Bbot)->rect.top = float(y_start * 16);
                (*Bbot)->score = 0;
                Bots_life.push_back(*Bbot);
                Bbot = Bots_death.erase(Bbot);
            }
        }


        //\F7\F2\EE\E1\FB \E7\E0\EF\F3\F1\F2\E8\F2\FC \ED\EE\E2\FB\E9 \F0\EE\E4 (\F3\E1\E8\F2\FC \E2\F1\E5\F5 \E2\F0\E0\F9\E0\FE\F9\E8\F5\F1\FF \ED\E0 \EC\E5\F1\F2\E5)
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (Right_key == false) {
                Right_key = true;
                for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
                    (*Bbot)->life = false;
                }
                next_generation = true;
            }
        } else { Right_key = false; }



if (visual)  {
        window.clear(Color::White);

        for (int i=0; i<H; i++) {
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='1')  tile.setTextureRect( IntRect(143-ZZ*3,112,ZZ,ZZ) );
                if (TileMap[i][j]=='2')  tile.setTextureRect( IntRect(143-ZZ*2,112 + 16,ZZ,ZZ) );
                if (TileMap[i][j]=='3')  tile.setTextureRect( IntRect(143-ZZ*3,112 + 16,ZZ,ZZ) );
                if (TileMap[i][j]=='4')  tile.setTextureRect( IntRect(143-ZZ*2,112,ZZ,ZZ) );
				if (TileMap[i][j]=='0') continue;

  			    tile.setPosition(j*ZZ,i*ZZ) ;
		        window.draw(tile);
		     }
        }

        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++) {
            window.draw((*Bbot)->sprite);
        }
        window.display();
}

    }
    f_net_out.close();

    int eee = 0;
    for (Bbot = Bots_death.begin(); Bbot != Bots_death.end();) {
        Runner *b = *Bbot;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
        Bbot = Bots_life.erase(Bbot); delete b; // åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
      //  printf("delete#%d", eee++);
    }


}

