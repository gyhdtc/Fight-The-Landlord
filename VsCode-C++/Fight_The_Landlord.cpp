//====================================================//
// 
//  GYH
//  https://github.com/gyhdtc/Fight-The-Landlord
//
//====================================================
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
    player *next; 
    int flag = 0; 
    int gold = 0; 
    int type = 0; 
    int card_number = 0; 
    int player_number; 
    string name;  
};

class fight_with_ficher{
    private:
        int number_of_human = 1;
        int number_of_ai = 2;
        int number_of_cards = 17;
        int multi = 1;
        poker pack_of_cards[54];
        player *player_head;
        player gyh[3];
        map<int, string> poker_numberTo_type;
        string type[15] = { "3", "4", "5", "6", "7", "8", "9",
                            "10", "J", "Q", "K", "A", "2", 
                            "king1", "king2"}; 
    public:
        void initcard();
        void initplayer();
        void dealcard(); 
        void compete_landlord();
        void sendcard();
};

void fight_with_ficher::initcard(){
    pack_of_cards[0].number  = 13;
    pack_of_cards[53].number = 14;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            pack_of_cards[i * 13 + j].number = j;
        }
    }

    for(int i = 0; i < 15; i++){
        poker_numberTo_type[i] = type[i];
    }
    //  输出测试 
    cout << " 牌堆 " << endl;
    for(int i = 0; i < 54; i++){
        cout << pack_of_cards[i].number << " ";
        if(pack_of_cards[i].next == NULL)
            cout << "NULL ";
    }
    for(int i = 0; i < 15; i++){
        cout << poker_numberTo_type[i] << " ";
    }
}

void fight_with_ficher::initplayer(){
    cout << "\n玩家数量：";
    cin >> number_of_human;
    number_of_ai = 3 - number_of_human;
    for(int i = 0; i < 3; i++){
        if(i < number_of_human){
            gyh[i].player_number = i + 1;
            gyh[i].flag = 1;
            cout << "\n玩家姓名：";
            cin >> gyh[i].name;
        }
        else{
            gyh[i].player_number = i + 1;
            gyh[i].flag = 0;
            gyh[i].name = "AI_player";
        }
    }
    player_head = &gyh[0];
    gyh[0].next = &gyh[1];
    gyh[1].next = &gyh[2];
    gyh[2].next = &gyh[0];
}

int main(){
    cout << "hello world !";
    fight_with_ficher hhh;
    hhh.initcard();
    hhh.initplayer();
    return 0;
}