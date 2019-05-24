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

    ifstream f_map("Map_war_withot_walls.txt");
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
    to_x_step = (static_cast<int>(rect.left + dx * 16))%(60*16);
    if(to_x_step < 0) to_x_step += 60*16;
    to_y_step = (static_cast<int>(rect.top  + dy * 16))%(60*16);
    if(to_y_step < 0) to_y_step += 60*16;
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
//cout << "to_x_step = " << to_x_step << "to_y_step = " << to_y_step << endl;
    pair<int,int> to = nearest_opponent(opponents, (int)rect.left, (int)rect.top);
    int to_x = to.first;
    int to_y = to.second;
    nearest_opponent_x = to_x;
    nearest_opponent_y = to_y;
    condition_upd(to_x, to_y, bullets);
    perezarydka++;
    return true;
}

bool DETBot::update(float time) {

    int result = 0;
    rect.left += (dx * time / 10); rect.top  += (dy * time / 10);
    if (rect.left < 0) {rect.left += (16 * W);} else if (rect.left >= (16 * W)) {rect.left -= (16 * W);}
    if (rect.top  < 0) {rect.top  += (16 * H);} else if (rect.top  >= (16 * H)) {rect.top  -= (16 * H);}
    sprite.setPosition(rect.left, rect.top );





/*
    int result = 0;
    rect.left += dx * time / 10;
    //result += Collision(1);
    rect.top += dy * time / 10; //координата y
    //result += Collision(0);
    sprite.setPosition(rect.left, rect.top ); // координаты x, y

    if (result) return false;
   */
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

pair<int, int> nearest_opponent(const vector<DETBot>& opponents,const int my_x,const int my_y)// возвращает to_x, to_y ближайшего противника
{
    //cout << "nearest_opponent(my_x = " << my_x << ")" << endl;
    //cout << " = " << my_x/16 << " = " << my_y/16;
    int res_to_x;
    int res_to_y;
    long long int min_length = 1000000000;
    for(const auto& i : opponents)
    {
        if((my_x == i.rect.left) && (my_y == i.rect.top)) continue; // себ€ не рассматриваем в векторе противников//////////////////////////////////”Ѕ–ј“№**”Ѕ–ј“№**”Ѕ–ј“№

        long long int length00 = (i.rect.left-60*16 - my_x)*(i.rect.left-60*16 - my_x) + (i.rect.top-60*16 - my_y)*(i.rect.top-60*16 - my_y);
        long long int length01 = (i.rect.left - my_x)*(i.rect.left - my_x)             + (i.rect.top-60*16 - my_y)*(i.rect.top-60*16 - my_y);
        long long int length02 = (i.rect.left+60*16 - my_x)*(i.rect.left+60*16 - my_x) + (i.rect.top-60*16 - my_y)*(i.rect.top-60*16 - my_y);

        long long int length10 = (i.rect.left-60*16 - my_x)*(i.rect.left-60*16 - my_x) + (i.rect.top - my_y)*(i.rect.top - my_y);
        long long int length11 = (i.rect.left - my_x)*(i.rect.left - my_x)             + (i.rect.top - my_y)*(i.rect.top - my_y);
        long long int length12 = (i.rect.left+60*16 - my_x)*(i.rect.left+60*16 - my_x) + (i.rect.top - my_y)*(i.rect.top - my_y);

        long long int length20 = (i.rect.left-60*16 - my_x)*(i.rect.left-60*16 - my_x) + (i.rect.top+60*16 - my_y)*(i.rect.top+60*16 - my_y);
        long long int length21 = (i.rect.left - my_x)*(i.rect.left - my_x)             + (i.rect.top+60*16 - my_y)*(i.rect.top+60*16 - my_y);
        long long int length22 = (i.rect.left+60*16 - my_x)*(i.rect.left+60*16 - my_x) + (i.rect.top+60*16 - my_y)*(i.rect.top+60*16 - my_y);

        vector<long long int> length_v(9);
        length_v[0] = length00;
        length_v[1] = length01;
        length_v[2] = length02;
        length_v[3] = length10;
        length_v[4] = length11;
        length_v[5] = length12;
        length_v[6] = length20;
        length_v[7] = length21;
        length_v[8] = length22;

        sort(length_v.begin(), length_v.end());
        long long int length = length_v[0];

        if(length < min_length)
        {
            min_length = length;
            if(length == length00)
            {
                res_to_x = i.rect.left - 60*16;
                res_to_y = i.rect.top  - 60*16;
            }
            else if(length == length01)
            {
                res_to_x = i.rect.left;
                res_to_y = i.rect.top  - 60*16;
            }
            else if(length == length02)
            {
                res_to_x = i.rect.left + 60*16;
                res_to_y = i.rect.top  - 60*16;
            }


            else if(length == length10)
            {
                res_to_x = i.rect.left - 60*16;
                res_to_y = i.rect.top;
            }
            else if(length == length11)
            {
                res_to_x = i.rect.left;
                res_to_y = i.rect.top;
            }
            else if(length == length12)
            {
                res_to_x = i.rect.left + 60*16;
                res_to_y = i.rect.top;
            }


            else if(length == length20)
            {
                res_to_x = i.rect.left - 60*16;
                res_to_y = i.rect.top  + 60*16;
            }
            else if(length == length21)
            {
                res_to_x = i.rect.left;
                res_to_y = i.rect.top  + 60*16;
            }
            else if(length == length22)
            {
                res_to_x = i.rect.left + 60*16;
                res_to_y = i.rect.top  + 60*16;
            }
        }
    }
    //cout << "near_ done!" << endl;
    //cout <<  " = " << res_to_x/16 << " = " <<res_to_y/16 << endl;
    return {res_to_x, res_to_y};
}

inline int to_cell(int x)// переводит координаты в <x, y> клетки
{
    x /= 16;
    if(x < 0) x += 60;
    return x % 60;
}

inline int to_position(int x)
{
    if(x < 0) x += 60;
    x %= 60;
    return (x*16 + 8)%(60*16);
}
/*
inline bool look(vector<vector<char>>& mymap, int my_x, int my_y, int to_x, int to_y)//возвращает 1, если есть преграда
{

    // привожу координаты к центрам квадратиков
    my_x = to_position(my_x);
    my_y = to_position(my_y);
    to_x = to_position(to_x);
    to_y = to_position(to_y);
    ////////////////////////////////


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
*/


Steps first_step(vector<vector<char>> mymap, int my_x, int my_y, int to_x, int to_y, Bot_conditions condition, const vector<Bullet>& bullets)
{

    long long int length   = (my_x - to_x)*(my_x - to_x)           + (my_y - to_y)*(my_y - to_y);
    long long int length_L = (my_x - 16 - to_x)*(my_x - 16 - to_x) + (my_y - to_y)*(my_y - to_y);
    long long int length_R = (my_x + 16 - to_x)*(my_x + 16 - to_x) + (my_y - to_y)*(my_y - to_y);
    long long int length_U = (my_x - to_x)*(my_x - to_x)           + (my_y - 16 - to_y)*(my_y - 16 - to_y);
    long long int length_D = (my_x - to_x)*(my_x - to_x)           + (my_y + 16 - to_y)*(my_y + 16 - to_y);
    //cout << bullets.size() << endl;
    for(const auto& i : bullets)
    {
        int to_rect_left = i.rect.left;
        int to_rect_top = i.rect.top;

        for(int dt = 0; dt < 15; dt++)
        {

            int x_1 = (to_rect_left/16)%60;
            int x_2 = (static_cast<int>((to_rect_left + i.rect.width)/16))%60;
            int y_1 = (to_rect_top/16)%60;
            int y_2 = (static_cast<int>((to_rect_top + i.rect.height)/16))%60;

            if(x_1 < 0) x_1 += 60;
            if(x_2 < 0) x_2 += 60;
            if(y_1 < 0) y_1 += 60;
            if(y_2 < 0) y_2 += 60;

            mymap[y_1][x_1] = 'B';
            mymap[y_1][x_2] = 'B';
            mymap[y_2][x_1] = 'B';
            mymap[y_2][x_2] = 'B';

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
    int zzz;
    if(bullets.size() > 0) cin >> zzz;
    cout << "****************" << endl;
*/
    bool cond;
    if(condition == START) cond = 1;
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
        //cout << "x = 1!!" << endl;
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
    while(!Q.empty() && kol <= 4000)
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
        int i_down = (i + 1)%60;
        int i_up = (i - 1)%60;
        int j_right = (j + 1)%60;
        int j_left = (j - 1)%60;

        if(i_down < 0) i_down += 60;
        if(i_up < 0) i_up += 60;
        if(j_right < 0) j_right += 60;
        if(j_left < 0) j_left += 60;

        /*
            L - пришли слева
            R - пришли справа
            U - пришли сверху
            D - пишли снизу
        */
        if(mymap[i][j_right] == '0' || mymap[i][j_right] == 'P' || (x && mymap[i][j_right] == 'B'))
        {
//cout << i << "," << j <<"->" << endl;
            Q.push(std::make_pair(j_right, i));

            bool y = 0;
            bool p = 0;
            if(x && mymap[i][j_right] == '0') y = 1;
            if(mymap[i][j_right] == 'P') p = 1;
            if(p && kol <= 164) break;

            mymap[i][j_right] = 'L';
//cout << "******* "<< mymap[i][j_right] << endl;
            if(y || p)
            {
//cout << "+" << endl;
                res_i = i;
                res_j = j_right;
                break;
            }
        }
        if(mymap[i][j_left] == '0' || mymap[i][j_left] == 'P' ||(x && mymap[i][j_left] == 'B'))
        {
//cout << i << "," << j << "<-" << endl;
            Q.push(std::make_pair(j_left, i));

            bool y = 0;
            bool p = 0;
            if(x && mymap[i][j_left] == '0') y = 1;
            if(mymap[i][j_left] == 'P') p = 1;
            if(p && kol <= 164) break;

            mymap[i][j_left] = 'R';
            if(y||p)
            {
//cout << "++" << endl;
                res_i = i;
                res_j = j_left;
                break;
            }
        }
        if(mymap[i_up][j] == '0' || mymap[i_up][j] == 'P' ||(x && mymap[i_up][j] == 'B'))
        {
//cout << i << "," << j << "^" << endl;
            Q.push(std::make_pair(j, i_up));

            bool y = 0;
            bool p = 0;
            if(x && mymap[i_up][j] == '0') y = 1;
            if(mymap[i_up][j] == 'P') p = 1;
            if(p && kol <= 164) break;

            mymap[i_up][j] = 'D';
            if(y||p)
            {
//cout << "+++" << endl;
                res_i = i_up;
                res_j = j;
                break;
            }
        }
        if(mymap[i_down][j] == '0' || mymap[i_down][j] == 'P' ||(x && mymap[i_down][j] == 'B'))
        {
//cout << i << "," << j << "V" << endl;
            Q.push(std::make_pair(j, i_down));

            bool y = 0;
            bool p = 0;
            if(x && mymap[i_down][j] == '0') y = 1;
            if(mymap[i_down][j] == 'P') p = 1;
            if(p && kol <= 164) break;

            mymap[i_down][j] = 'U';
            if(y||p)
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
if(!x)
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
cout << "res_i = " << res_i << "res_j = " << res_j << endl;
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
            res_i %= 60;
            if(res_i < 0) res_i += 60;
        }
        if(res == 'D')
        {
            res_i++;
            res_i %= 60;
            if(res_i < 0) res_i += 60;
        }
        if(res == 'R')
        {
            res_j++;
            res_j %= 60;
            if(res_j < 0) res_j += 60;
        }
        if(res == 'L')
        {
            res_j--;
            res_j %= 60;
            if(res_j < 0) res_j += 60;
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
    //cout << res << endl;
    if(res == 'U') return DOWN;
    else if(res == 'D') return UP;
    else if(res == 'R') return LEFT;
    else if(res == 'L') return RIGHT;
    else
    {
        int r = rand()%40;
        if(r == 0 && length_D >= length) return DOWN;
        else if(r == 1 && length_U >= length) return UP;
        else if(r == 2 && length_L >= length) return LEFT;
        else if(r == 3 && length_R >= length) return RIGHT;
        else return STOP;
    }
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
