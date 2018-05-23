//==============================================
//  作者：GYH
//  查看更新：https://github.com/gyhdtc/Fight-The-Landlord
//  程序：  【 斗地主程序 】
//      poker ——> 扑克牌：number 用整数表示，对应map中的【键值对 map】，得到卡牌的种类J、Q、K之类的;
//      poker ——> 扑克牌：*next  链表指针内存，可以将扑克牌数组中的54个元素，串成一副卡牌，因为玩家不可能重复拥有同一张卡牌;
//      player——> 玩家  ：*card  手牌链表头指针;
//      player——> 玩家  ：flag   整数表示玩家，0为农名，1为地主;  
//==============================================
#include <iostream>
#include <string>
#include <map>
#include <list>
using namespace std;

struct poker{
    int number = 0;
    poker *next = NULL;
};
struct player{
    poker *card;
    int flag = 0;
    string name;
};

class fight_with_ficher{
    private:
        int number_of_human = 1; // 初始玩家数量
        int number_of_ai = 2;    // 初始电脑数量
        int number_of_cards = 17;// 初始手牌数量
        int multi = 1;           // 翻倍
        poker pack_of_cards[54]; // 一套牌
        map<int, string> poker_numberTo_type;
        string type[15] = { "3", "4", "5", "6", "7", "8", "9",
                            "10", "J", "Q", "K", "A", "2", 
                            "king1", "king2"}; 
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