#include"DETBot_h.hpp"

DETBot::DETBot(Texture &image, int x_start, int y_start, int id)
{
    bot_id = id;

    sprite.setTexture(image);  //сначала в sprite загружаю картину
    rect = FloatRect(x_start * 16, y_start * 16,16,16);//текущие координаты, где € заспамлюсь
    sprite.setPosition(rect.left, rect.top);
    sprite.setTextureRect(IntRect(5*16, 9*16, 16, 16));
    dx = 0; dy = 0; da = 0;
    currentFrame = 0;
    condition = START;
    dsp = 0; da = 0;
    life = true;

    mymap.resize(H);
    for(auto& i : mymap) {i.resize(H);}

    ifstream f_map("map1.txt");
    for (int i = 0; i < H; i++)
    {
        for(int j = 0; j < H; j++)
        {
            f_map >> mymap[i][j];
        }
    }
}

int DETBot::get_perez()
{
    return perezarydka;
}
void DETBot::update_perez(int t)
{
    perezarydka = t;
}

int DETBot::get_id()
{
    return bot_id;
}
void DETBot::Print_mymap()
{
    for(const auto& i : mymap)
    {
        for(const auto& j : i)
        {
            cout << j;
        }
        cout << endl;
    }
}


void DETBot::condition_upd(int to_x, int to_y, const vector<Bullet>& bullets)
{
    switch(condition)
    {
    case START:
        {
        Steps step = first_step(mymap, rect.left, rect.top, to_x, to_y, WORNING, bullets);
        condition = GO;
        Go(step);
        break;
        }
    case GO:

        if(dx < 0 && rect.left < to_x_step)
        {
            dx = 0;
            dy = 0;
            rect.left = to_x_step;
            condition = START;
        }
        if(dx > 0 && rect.left > to_x_step)
        {
            dx = 0;
            dy = 0;
            rect.left = to_x_step;
            condition = START;
        }
        if(dy < 0 && rect.top < to_y_step)
        {
            dx = 0;
            dy = 0;
            rect.top = to_y_step;
            condition = START;
        }
        if(dy > 0 && rect.top > to_y_step)
        {
            dx = 0;
            dy = 0;
            rect.top = to_y_step;
            condition = START;
        }
        if(rect.left == to_x_step && rect.top == to_y_step)
        {
            dx = 0;
            dy = 0;
            condition = START;
        }
        if(dx == 0 && dy == 0)
        {
            condition = START;
        }
        break;
    }
}

void DETBot::Go(Steps step)
{
    switch(step)
    {
    case UP:
        dx = 0;
        dy = -1;
        break;
    case DOWN:
        dx = 0;
        dy = 1;
        break;
    case RIGHT:
        dx = 1;
        dy = 0;
        break;
    case LEFT:
        dx = -1;
        dy = 0;
        break;
    case STOP:
        dx = 0;
        dy = 0;
    }
    to_x_step = rect.left + dx * 16;
    to_y_step = rect.top  + dy * 16;
}


/*
bool DETBot::control(int to_x, int to_y)
{
    condition_upd(to_x, to_y);
}
*/
bool DETBot::control(const vector<DETBot>& opponents, const vector<Bullet>& bullets)
{
    if(opponents.size() == 1) return 0;
    pair<int,int> to = nearest_opponent(opponents, rect.left, rect.top);
    int to_x = to.first;
    int to_y = to.second;
    nearest_opponent_x = to_x;
    nearest_opponent_y = to_y;
    condition_upd(to_x, to_y, bullets);
    return true;
}

bool DETBot::update(float time) {
    int result = 0;
    rect.left += dx * time / 10;
    //result += Collision(1);
    rect.top += dy * time / 10; //координата y
    //result += Collision(0);
    sprite.setPosition(rect.left, rect.top ); // координаты x, y

    if (result) return false;
    return true;
}

pair<int, int> DETBot::fire()
{
    if(condition == START)
    {
        return {nearest_opponent_x, nearest_opponent_y};
    }
    else
    {
        return{0, 0};
    }
}




using namespace std;

pair<int, int> nearest_opponent(const vector<DETBot>& opponents, int my_x, int my_y)// возвращает to_x, to_y ближайшего противника
{
    //cout << "nearest_opponent(my_x = " << my_x << ")" << endl;
    int res_to_x;
    int res_to_y;
    long long int min_length = 1000000000;
    for(const auto& i : opponents)
    {
        if((my_x == i.rect.left) && (my_y == i.rect.top)) continue; // себ€ не рассматриваем в векторе противников//////////////////////////////////”Ѕ–ј“№**”Ѕ–ј“№**”Ѕ–ј“№
        long long int length = (i.rect.left - my_x)*(i.rect.left - my_x) + (i.rect.top - my_y)*(i.rect.top - my_y);
        if(length < min_length)
        {
            min_length = length;
            res_to_x = i.rect.left;
            res_to_y = i.rect.top;
        }
    }
    //cout << "near_ done!" << endl;
    return {res_to_x, res_to_y};
}

inline int to_cell(int x)// переводит координаты в <x, y> клетки
{
    return x/16;
}

inline int to_position(int x)
{
    return x*16 + 8;
}

inline bool look(vector<vector<char>>& mymap, int my_x, int my_y, int to_x, int to_y)//возвращает 1, если есть преграда
{
    /*
    // привожу координаты к центрам квадратиков
    my_x = to_position(my_x);
    my_y = to_position(my_y);
    to_x = to_position(to_x);
    to_y = to_position(to_y);
    ////////////////////////////////
    */

    // перехожу к центрам фигурок
    my_x += 0;
    my_y += 0;
    to_x += 0;
    to_y += 0;
    /////////////////////////////

//cout << "my_x = " << my_x << " my_y = " << my_y << endl;
//cout << "to_x = " << to_x << " to_y = " << to_y << endl;

    // определ€ю минимальные и максимальные координаты
    int min_x = std::min(to_x, my_x);
    int max_x = std::max(to_x, my_x);
    int min_y = std::min(to_y, my_y);
    int max_y = std::max(to_y, my_y);
    ////////////////////////////////
    bool res = 0;

    // Y = KX + B
    double dy = to_y - my_y;
    double dx = to_x - my_x;

    if(dx == 0 && dy == 0) return 0; // если человечки совпали
//cout << "dx = " << dx << " dy = " << dy << endl;
    if(dx == 0) dx += 0.00001;
    double K = dy / (dx + 0.);
    double B = to_y - K * to_x;

//cout << "K = " << K << " B = " << B << endl;
    double L2 = dy*dy + dx*dx;

    double phi = atan(K);
    double cos_phi = abs(cos(phi));
    //if(dx < 0 && dy == 0) cos_phi *= -1;
    double sin_phi = abs(sin(phi));

//cout <<"cos_phi = " << cos_phi << " sin_phi = " << sin_phi << endl;

    for(double i = 0; i <= L2; i += 250)
    {
//int k;
//cin >> k;
        int naprx = 0, napry = 0;

        if(dx > 0) naprx = 1;
        else naprx = -1;

        if(dy > 0) napry = 1;
        else napry = -1;

        int x1 = my_x + static_cast<int>(sqrt(i) * cos_phi) * naprx;
        int y1 = my_y + static_cast<int>(sqrt(i) * sin_phi) * napry;
        int x2 = x1 + 12;
        int y2 = y1 + 12;
//cout << "min_x = " <<min_x << " y0 = " << y <<endl;
//cout <<"x = " << x << " y = " << y <<endl;
        int cell_x1 = to_cell(x1);
        int cell_y1 = to_cell(y1);
        int cell_x2 = to_cell(x2);
        int cell_y2 = to_cell(y2);

//cout << "cell_x = " << cell_x1 << " cell_y = " << cell_y1 << endl;
        if(mymap[cell_y1][cell_x1] == '1' ||
           mymap[cell_y1][cell_x2] == '1' ||
           mymap[cell_y2][cell_x1] == '1' ||
           mymap[cell_y2][cell_x2] == '1' )
        {
            res = 1;
            break;
        }
    }
//cout <<"-----" <<endl;
//cout << res << endl;
    return res;
}



Steps first_step(vector<vector<char>> mymap, int my_x, int my_y, int to_x, int to_y, Bot_conditions condition, const vector<Bullet>& bullets)
{
    //cout << bullets.size() << endl;
    for(const auto& i : bullets)
    {
        int to_rect_left = i.rect.left;
        int to_rect_top = i.rect.top;

        for(int dt = 0; dt < 15; dt++)
        {

            int x_1 = to_rect_left/16;
            int x_2 = (to_rect_left + i.rect.width)/16;
            int y_1 = to_rect_top/16;
            int y_2 = (to_rect_top + i.rect.height)/16;
            //cout << "x_1 = " << x_1 << " x_2 = " << x_2 << " y_1 = " << y_1 << " y_2 = " << y_2 << endl;
            if(mymap[y_1][x_1] != '1') mymap[y_1][x_1] = 'B';
            else break;
            if(mymap[y_1][x_2] != '1') mymap[y_1][x_2] = 'B';
            else break;
            if(mymap[y_2][x_1] != '1') mymap[y_2][x_1] = 'B';
            else break;
            if(mymap[y_2][x_2] != '1') mymap[y_2][x_2] = 'B';
            else break;

            to_rect_left += static_cast<int>(i.dx * 10);
            to_rect_top  += static_cast<int>(i.dy * 10);
        }
    }
/*
    cout << "****************" << endl;

    for(auto& xline : mymap)
    {
        for(auto& yline : xline)
        {
            cout << yline;
        }
        cout << endl;
    }
    cout << "****************" << endl;
*/
    bool cond;
    if(condition == WORNING) cond = 1;
    else cond = 0;

//cout << "cond = " << cond << endl;

    //перехожу к клеткам
    int my_i = to_cell(my_y);
    int my_j = to_cell(my_x);
    int to_i = to_cell(to_y);
    int to_j = to_cell(to_x);
    ////////////////////

//cout << "my_i = " << my_i <<" my_j = " << my_j << endl;
//cout << "to_i = " << to_i <<" to_j = " << to_j << endl;


    bool x = 0;// бьетс€ ли пулей или нет?
    mymap[to_i][to_j] = 'P'; //место противника
    if(mymap[my_i][my_j] == 'B')
    {
        x = 1;
    }
    mymap[my_i][my_j] = 'I'; //место, где стою
    std::queue<pair<int, int>> Q; //ќчередь дл€ обхода в ширину
    Q.push(std::make_pair(my_j, my_i)); // «апихиваем в очередь первую клетку

    //координаты клетки, которую ищем
    int res_i = my_i;
    int res_j = my_j;
    /////////////////////////////////
    int kol = 0;
    while(!Q.empty() && kol <= 40)
    {
    kol++;
//////////***********************
/*
cout << Q.size() << endl;
cout << "****************" << endl;

    for(auto& xline : mymap)
    {
        for(auto& yline : xline)
        {
            cout << yline;
        }
        cout << endl;
    }
cout << "****************" << endl;
*/
/////////***********************


        int i = Q.front().second;
        int j = Q.front().first;
        int i_down = i + 1;
        int i_up = i - 1;
        int j_right = j + 1;
        int j_left = j - 1;

        /*
            L - пришли слева
            R - пришли справа
            U - пришли сверху
            D - пишли снизу
        */

        if(mymap[i][j_right] == '0' || (x && mymap[i][j_right] == 'B'))
        {
//cout << i << "," << j <<"->" << endl;
            bool y = 0;
            Q.push(std::make_pair(j_right, i));
            if(x && mymap[i][j_right] == '0') y = 1;
            mymap[i][j_right] = 'L';
            if(look(mymap, j_right * 16, i * 16, to_x, to_y) == cond || y)// *16 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            {
//cout << "+" << endl;
                res_i = i;
                res_j = j_right;
                break;
            }
        }
        if(mymap[i][j_left] == '0' || (x && mymap[i][j_right] == 'B'))
        {
//cout << i << "," << j << "<-" << endl;
            bool y = 0;
            Q.push(std::make_pair(j_left, i));
            if(x && mymap[i][j_left] == '0') y = 1;
            mymap[i][j_left] = 'R';
            if(look(mymap, j_left * 16, i * 16, to_x, to_y) == cond || y)// *16 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            {
//cout << "++" << endl;
                res_i = i;
                res_j = j_left;
                break;
            }
        }
        if(mymap[i_up][j] == '0' || (x && mymap[i][j_right] == 'B'))
        {
//cout << i << "," << j << "^" << endl;
            bool y = 0;
            Q.push(std::make_pair(j, i_up));
            if(x && mymap[i_up][j] == '0') y = 1;
            mymap[i_up][j] = 'D';
            if(look(mymap, j * 16, i_up * 16, to_x, to_y) == cond || y)// *16 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            {
//cout << "+++" << endl;
                res_i = i_up;
                res_j = j;
                break;
            }
        }
        if(mymap[i_down][j] == '0' || (x && mymap[i][j_right] == 'B'))
        {
//cout << i << "," << j << "V" << endl;
            bool y = 0;
            Q.push(std::make_pair(j, i_down));
            if(x && mymap[i_down][j] == '0') y = 1;
            mymap[i_down][j] = 'U';
            if(look(mymap, j * 16, i_down * 16, to_x, to_y) == cond || y)// *16 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            {
//cout << "++++" << endl;
                res_i = i_down;
                res_j = j;
                break;

            }
        }
        //res_i = i;
        //res_j = j;
        Q.pop();
    }

     //////////***********************
/*
if(x)
{
    cout << "****************" << endl;
    for(auto& xline : mymap)
    {
        for(auto& yline : xline)
        {
            cout << yline;
        }
        cout << endl;
    }
cout << "****************" << endl;
}
*/

    /////////***********************

    char res = 'N'; // N- ничего
    while(mymap[res_i][res_j] != 'I' && mymap[res_i][res_j] != 'P')
    {
        res = mymap[res_i][res_j];

//cout << "res = " << res << endl;
        if(res == 'U')
        {
            res_i--;
        }
        if(res == 'D')
        {
            res_i++;
        }
        if(res == 'R')
        {
            res_j++;
        }
        if(res == 'L')
        {
            res_j--;
        }
    }

    //////////***********************
    /*
cout << "****************" << endl;
    for(auto& xline : mymap)
    {
        for(auto& yline : xline)
        {
            cout << yline;
        }
        cout << endl;
    }
cout << "****************" << endl;
*/
    /////////***********************

    if(res == 'U') return DOWN;
    else if(res == 'D') return UP;
    else if(res == 'R') return LEFT;
    else if(res == 'L') return RIGHT;
    else return STOP;
}






/*



int main()
{
    vector<vector<char>> v = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                              {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
                              {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                              {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                              {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
                              {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                              {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                              {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                              {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
                              {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                              {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

    Steps step = first_step(v, 1*16, 13*16, 11*16, 1*16, BRAVE);

    if(step == UP) cout << "UP";
    if(step == DOWN) cout << "DOWN";
    if(step == LEFT) cout << "LEFT";
    if(step == RIGHT) cout << "RIGHT";
    return 0;
}
*/
