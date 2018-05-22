#include <iostream>
#include <string>
#include <map>
using namespace std;
typedef struct poker{
    int number = 0;
};
class fight_with_ficher{
    private:
    int number_of_human = 1;
    int number_of_ai = 2;
    int number_of_cards = 17;
    int multi = 1;
    poker pack_of_cards[54];
    string type[15] = {"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "king1", "king2"};
    map<int, string> poker_numberTo_type; 
    public:
        void init();
        void deal(); 
};

 void fight_with_ficher::init(){
//  [ King1 ] [ 0 1 2 3 4 5 6 7 8 9 10 11 12 ] * 4 [ king2 ]
    pack_of_cards[0].number  = 13;
    pack_of_cards[53].number = 14;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            pack_of_cards[i * 13 + j].number = j;
        }
    }
//  初始化 玩家数量 & 电脑数量
    cout << "输入玩家人数：";
    cin >> number_of_human;
    number_of_ai = 3 - number_of_human;
    cout << "电脑数量 " << number_of_ai << " 名";
//  初始化 编号 ——> 扑克种类 的映射
    for(int i = 0; i < 15; i++) poker_numberTo_type[i] = type[i];
}
int main(){
    cout << "hello world ! ";
    return 0;
}