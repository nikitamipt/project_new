#pragma once
#include "Player_without_walls.cpp"
#include <bits/stdc++.h>
#include <ctime>
using namespace sf;


inline bool look(vector<vector<char>>& mymap, int my_x, int my_y, int to_x, int to_y);
enum Bot_conditions {BRAVE, WORNING, GO, START};
enum Steps {UP, DOWN, RIGHT, LEFT, STOP};
inline int to_cell(int x);// ��������� ���������� � <x, y> ������
Steps first_step(vector<vector<char>> mymap, int my_x, int my_y, int to_x, int to_y, Bot_conditions condition, const vector<Bullet>& bullets);

//BRAVE -- ���� � ����������
//WORNING -- ��������
//GO -- �������������
//START -- ��������� ���������

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DETBot : public Player {
private:
    int perezarydka = 0;
    int bot_id;
    Bot_conditions condition;//��������� ����
    vector<vector<char>> mymap; //�����
    int to_x_step, to_y_step; //���������� � ������ ������ ���� ����.
    int warning_time = 0; // �������� � �������
    int nearest_opponent_x = -1, nearest_opponent_y = -1; //���������� � ������ ���������� ����������.
public:
    int get_perez();
    void update_perez(int t);
    DETBot(Texture &image, int x_start, int y_start, int id);
    int get_id();
    void Print_mymap();
    void condition_upd(int to_x, int to_y, const vector<Bullet>& nearest_bullets);
    void Go(Steps step);
    //bool control(int to_x, int to_y);
    bool control(const vector<DETBot>& opponents, const vector<Bullet>& nearest_bullets);
    bool update(float time);
    pair<int,int> fire();
};
pair<int, int> nearest_opponent(const vector<DETBot>& opponents,const int my_x,const int my_y);// ���������� to_x, to_y ���������� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
