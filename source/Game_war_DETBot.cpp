/*
git add .
git commit -m "draw+map_war"
git push origin master
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <time.h>

#include <iostream>


using namespace sf;


void Game_war_DETBot() {
int yyy = 0;




bool visual = true;
bool who = false;


    RenderWindow window(VideoMode(960, 960), "SFML works!");

    Texture t;
    t.loadFromFile("2.png");
    Sprite tile(t);



    //÷èòàþ êàðòó
    ifstream f_map("Map_war_withot_walls.txt");
    for (int i = 0; i < H; i++) {
        std::string str;
        std::getline(f_map, str);
        TileMap[i] = str;
    }


//printf("A  3\n");/*


    //îïðåäåëÿþ, ãäå âîçðàäèòñÿ íàø ãåðîé
    int x_start = 0; int y_start = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (TileMap[i][j] == '3') {
                x_start = j; y_start = i;
                break;
            }
        }
    }




/*
    //ìàññèâ âñåõ îáúåêòîâ êàðòû (ïðèöåë). Âîçìîæíî, íå íóæåí, ïîêà õç
//    std::list<Entity*>  entities;
    std::list<Bullet*>  bullets; //ìàññèâ ïóëü, êîòîðûå åñòü íà êàðòå
//    std::list<Soldier*> Bots_death;//çäåñü ÿ õðàíþ ìåðòâûõ. Òåõ, ÷òî ñòîëêíóëèñü ñî ñòåíîé. Êîãäà âñå áîòû óìèðàþò, ÿ âûáèðàþ èç ýòîãî ñïèñêà áîòîâ áîòà, êîòîðûé îêàçàëñÿ áëèæå âñåõ ê ôèíèøó.
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it1;
  ::list<Bullet*>::iterator bul;
    std::list<Bullet*>::iterator bul1;*/
    Line line(t);

    Line L(t);  //íóæíî äëÿ ðèñîâàíèÿ ïðèöåëà è íàõîæäíèé ðàññòîÿíèé äî ñòåíîê
    Person p(1);
    p.Player_maker(t, 10, 10);




    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "H = " << H << " W = " << W << endl;
    int DETBot_x_start = 0; int DETBot_y_start = 0;
    list<Bullet> detbots_bullets;
    vector<DETBot> detbots;
    std::list<Bullet>::iterator it_DETBot_bullets;
    std::vector<DETBot>::iterator it_DETBot;
    int num_Detbots = 150;
    for(int i = 0; i < num_Detbots; i++)
    {
        //îïðåäåëÿþ, ãäå âîçðîäèòñÿ DETBot

        bool ok = 0;
        while(!ok)
        {
            DETBot_x_start = rand()%W;
            DETBot_y_start = rand()%H;
            if(TileMap[DETBot_y_start][DETBot_x_start] == '0')
            {
                ok = 1;
            }
        }

        DETBot I(t, DETBot_x_start, DETBot_y_start, i);
        detbots.push_back(I);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    bool space = false; //êîíòðîëèò, íàæàò ëè SPACE èëè íåò. Íàäî äëÿ ñòðåëüáû, ÷òîáû î÷åðåäè íå áûëî
    bool Right_key = false; //êîíòðîëèò, íàæàò ëè Right èëè íåò. Íàäî äëÿ íîâîé ãåíåðàöèè áîòîâ.
    Clock clock; // ÷òîáû ñêîðîñòü áûëà ïðèâÿçàíà êî âðåìåíè, à íå ê òàêòîâîé ÷àñòîòå ïðîöåññîðà




    while (window.isOpen()){


//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNEW\n");
        float time = clock.getElapsedTime().asMicroseconds();
        time = time / 500; //äàòü ïðîøåäøåå âðåìÿ.
        if (time > 20) time = 20;
        time = 20;
        clock.restart(); //ïåðåçàãðóæàåò âðåìÿ. Òàê ìû èçìåðèì ñêîðîñòü òàêòà.

        Vector2i pixelPos = Mouse::getPosition(window);//çàáèðàåì êîîðä êóðñîðà
		Vector2f pos = window.mapPixelToCoords(pixelPos);//ïåðåâîäèì èõ â èãðîâûå (óõîäèì îò êîîðä îêíà)
		//std::cout << pixelPos.x << "\n";//ñìîòðèì íà êîîðäèíàòó Õ ïîçèöèè êóðñîðà â êîíñîëè (îíà íå áóäåò áîëüøå øèðèíû îêíà)
		//std::cout << pos.x << "\n";//ñìîòðèì íà Õ,êîòîðàÿ ïðåîáðàçîâàëàñü â ìèðîâûå êîîðäèíàòû



        bool window_close = false; //for closing window...
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close(); window_close = true;
        }



        /*if (who) {
    //çäåñü ïðîèñõîäèò ñ÷èòûâàèíèå êëàâèàòóðû. p.control == true, åñëè ïðîèçîøåë âûñòðåë.
            if (p.control(pos)) {
                float dx2 = pos.x-p.rect.left; float dy2 = pos.y - p.rect.top;
                float m = sqrt(dx2*dx2 + dy2 * dy2);
                bullets.push_back(new Bullet(p.rect.left, p.rect.top, t, speed_bul*dx2/m, speed_bul*dy2/m, nullptr));
            }
            p.update(time);
        }*/



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //cout << "========================================" << endl;
        for(auto& i : detbots)
        {
            //cout << "dx = " << i.dx << "dy = " << i.dy << endl;
            int to_x = i.fire().first;
            int to_y = i.fire().second;
            if(!(to_x == 0 && to_y == 0) && i.get_perez() > 70)
            {

                long long int length = (i.rect.left - to_x)*(i.rect.left - to_x) + (i.rect.top - to_y)*(i.rect.top - to_y);
                float dx = to_x - i.rect.left;
                float dy = to_y - i.rect.top;
                dx /= sqrt(length + 0.0);
                dy /= sqrt(length + 0.0);
                //cout << "BULLET " << dx << " <-> " << dy << endl;
                Bullet b(i.rect.left, i.rect.top, t, dx/2,  dy/2, i.get_id());
                detbots_bullets.push_back(b);
                i.update_perez(0);
            }

            vector<Bullet> nearest_bullets;

            for(const auto& b : detbots_bullets)
            {
                long long int length = (b.rect.left - i.rect.left)*(b.rect.left - i.rect.left) + (b.rect.top - i.rect.top)*(b.rect.top - i.rect.top);
                if(length <= 2304 && b.owner_DETBot != i.get_id())
                {
                    Bullet new_bullet = b;
                    nearest_bullets.push_back(new_bullet);
                }
            }

            i.control(detbots, nearest_bullets);
            i.update(time);
        }
        //cout << "========================================" << endl;
        //stolknovenie PULA + PULA
        std::list<Bullet>::iterator it_DETBot_bullet_1;
        std::list<Bullet>::iterator it_DETBot_bullet_2;
        for (it_DETBot_bullet_1 = detbots_bullets.begin(); it_DETBot_bullet_1 != detbots_bullets.end(); it_DETBot_bullet_1++)
        {
            for (it_DETBot_bullet_2 = detbots_bullets.begin(); it_DETBot_bullet_2 != detbots_bullets.end(); it_DETBot_bullet_2++)
            {
                if ((*it_DETBot_bullet_1).owner_DETBot != (*it_DETBot_bullet_2).owner_DETBot && (*it_DETBot_bullet_2).rect.intersects((*it_DETBot_bullet_1).rect) && (*it_DETBot_bullet_1).life && (*it_DETBot_bullet_2).life)
                {
                    (*it_DETBot_bullet_1).life = false;
                    (*it_DETBot_bullet_2).life = false;
                }
            }
        }

        // stolknovenie PULA + BOT
        for (it_DETBot_bullet_1 = detbots_bullets.begin(); it_DETBot_bullet_1 != detbots_bullets.end(); it_DETBot_bullet_1++)
        {
            for (it_DETBot = detbots.begin(); it_DETBot != detbots.end(); it_DETBot++)
            {
                if ( (*it_DETBot_bullet_1).owner_DETBot != (*it_DETBot).get_id()&&
                    (*it_DETBot_bullet_1).rect.intersects((*it_DETBot).rect) &&
                    (*it_DETBot_bullet_1).life && (*it_DETBot).life)
                {
                    (*it_DETBot_bullet_1).life = false;
                    (*it_DETBot).life = false;
                }
            }
        }





        for (it_DETBot_bullets = detbots_bullets.begin(); it_DETBot_bullets != detbots_bullets.end();){
            (*it_DETBot_bullets).update(time);//âûçûâàåì ô-öèþ update äëÿ âñåõ îáúåêòîâ (ïî ñóòè äëÿ òåõ, êòî æèâ)

            if ((*it_DETBot_bullets).life == false) { it_DETBot_bullets = detbots_bullets.erase(it_DETBot_bullets); }// åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
            else it_DETBot_bullets++;//è èäåì êóðñîðîì (èòåðàòîðîì) ê ñëåä îáúåêòó. òàê äåëàåì ñî âñåìè îáúåêòàìè ñïèñêà
        }

        for (it_DETBot = detbots.begin(); it_DETBot != detbots.end();){
            if ((*it_DETBot).life == false) { it_DETBot = detbots.erase(it_DETBot); }// åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
            else it_DETBot++;//è èäåì êóðñîðîì (èòåðàòîðîì) ê ñëåä îáúåêòó. òàê äåëàåì ñî âñåìè îáúåêòàìè ñïèñêà
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







        if (visual)  {
            window.clear(Color::White);
            for (int i=0; i<H; i++) {
                 for (int j=0; j<W; j++) {
                    if (TileMap[i][j]=='1')  tile.setTextureRect( IntRect(143-ZZ*3,112,ZZ,ZZ) );
                    if (TileMap[i][j]=='2')  tile.setTextureRect( IntRect(143-ZZ*2,112 + 16,ZZ,ZZ) );
                    if (TileMap[i][j]=='3')  tile.setTextureRect( IntRect(143-ZZ*3,112 + 16,ZZ,ZZ) );
                    if (TileMap[i][j]=='4')  tile.setTextureRect( IntRect(143-ZZ*2,112,ZZ,ZZ) );
                    if (TileMap[i][j]=='0') continue;
                    tile.setPosition(j*ZZ,i*ZZ) ;
                    window.draw(tile);
                 }
            }

    //printf("C420\n");

            //ðèñóþ ïðèöåë
            if(who) {L.rect.left = p.rect.left; L.rect.top = p.rect.top + 4; int s = 0; L.dx = cos(p.da); L.dy = sin(p.da);
                while (s < 50) {
                    L.update(0); s++; window.draw(L.sprite);
                }
            }


            if (who) {window.draw(p.sprite);}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        for(auto& i : detbots)
        {
            window.draw(i.sprite);
        }
        for (it_DETBot_bullets = detbots_bullets.begin(); it_DETBot_bullets != detbots_bullets.end(); it_DETBot_bullets++){ window.draw((*it_DETBot_bullets).sprite);}
        //window.draw(I.sprite);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



            window.display();

    //printf("C453\n");


        }

    }

//printf("A   %d\n", yyy++);


/*
    for (bul = bullets.begin(); bul != bullets.end(); ){
        Bullet *b = *bul;
        bul = bullets.erase(bul); delete b;
    }

    for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); ){
        Soldier_without_walls/*Soldier/ *b = *Bbot;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
        Bbot = Bots_life.erase(Bbot); delete b; // åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
    }

//printf("A   %d\n", yyy++);

*/

}



