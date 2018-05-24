//====================================================
// 
//  GYH
//  https://github.com/gyhdtc/Fight-The-Landlord
//   
//====================================================
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

struct poker{
    int number = 0;
};
struct player{
    vector<poker> card;  
    vector<poker> last_put_card;
    player *next; 
    int flag = 0; // 0 电脑 1 人类
    int type = 0; // 0 农名 1 地主
    int gold = 0; // 金币
    int card_number = 0; // 手牌
    int player_number; 
    string player_name;  
};

bool compare(poker a, poker b){
    return a.number <= b.number;
}

class fight_with_ficher{
    private:
        int number_of_human = 1;
        int number_of_ai = 2;
        int number_of_cards = 17;
        int multi = 1;
        int Landlord = 0;
        poker pack_of_cards[54];
        player *player_head;
        player gyh[3];
        string type[15] = { "3", "4", "5", "6", "7", "8", "9",
                            "10", "J", "Q", "K", "A", "2", 
                            "Small_king", "Big_king"}; 
        void myrandom(); // 待写
        void show_information();
    public:
        fight_with_ficher(){// 倍数还要显示出来，我想倍数改变的时候就要输出一次
            cout << "------------------------------------" << endl;
            cout << "形成套牌......" << endl;
            initcard();
            cout << "------------------------------------" << endl;
            cout << "玩家落座......" << endl;
            initplayer();
            for(int i = 0; i < 3; i++){
                cout << gyh[i].player_number << "号玩家，" << gyh[i].player_name 
                << " 持有金币：" << gyh[i].gold 
                << (gyh[i].flag==0?" 电脑 ":" 人类 ")
                << (gyh[i].type==0?" 农名 ":" 地主 ")
                << endl;
            }
            cout << "------------------------------------" << endl;
            dealcard();
            cout << "------------------------------------" << endl;
            compete_landlord();
            cout << Landlord << " 号玩家 " << gyh[Landlord-1].player_name << " 是地主" << endl;

        }
        void initcard();
        void initplayer();
        void dealcard(); 
        void compete_landlord();
        void putcard();
};

void fight_with_ficher::show_information(){
    printf("%10s——%10s——%10s",type[pack_of_cards[51].number],type[pack_of_cards[52].number],type[pack_of_cards[53].number]);
    printf("%10s——%10s——%10s",gyh[0].player_name,gyh[1].player_name,gyh[2].player_name);
    printf("%10d——%10d——%10d",gyh[0].card_number,gyh[1].card_number,gyh[2].card_number);
}

void fight_with_ficher::initcard(){
    pack_of_cards[0].number  = 13;
    pack_of_cards[53].number = 14;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            pack_of_cards[i * 13 + j + 1].number = j;
        }
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
            cout << "玩家姓名：";
            cin >> gyh[i].player_name;
        }
        else{
            gyh[i].player_number = i + 1;
            gyh[i].flag = 0;
            gyh[i].player_name = "AI_player";
        }
    }
    //player_head = &gyh[0];
    gyh[0].next = &gyh[1];
    gyh[1].next = &gyh[2];
    gyh[2].next = &gyh[0];
}
/*
    发牌程序
    函数【random_shuffle】每次运行结果都一样
    可能涉及到seed的问题
    这个一定要改改，可以参考下 天天斗地主 的程序，不知道能否找到233
*/
void fight_with_ficher::dealcard(){
    random_shuffle(pack_of_cards, pack_of_cards + 54);
    for(int i = 0; i < 3; i++){
        gyh[i].card.assign(&pack_of_cards[i*number_of_cards], &pack_of_cards[(i+1)*number_of_cards]);
        sort(gyh[i].card.begin(), gyh[i].card.end(), compare);
    }
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < number_of_cards; j++){
    //         cout << type[gyh[i].card[j].number] << " ";
    //     }
    //     cout << endl;
    // }
    cout << "地主牌：" << type[pack_of_cards[51].number] << "-" << type[pack_of_cards[52].number] << "-" << type[pack_of_cards[53].number] << endl;
}
// 一号抢地主，二号和三号不枪地主，还会循环到一号
// 抢地主的模式要核实一下
void fight_with_ficher::compete_landlord(){
    int i = 0;
    char x;
    player *t;
    if(Landlord == 0) 
        player_head = &gyh[0];
    else{
        player_head = &gyh[Landlord - 1];
    }
    t = player_head;
    do{
        if(t == player_head)
            i++;
        cout << t -> player_number << "号玩家，是否抢地主：y/n";
        cin >> x;
        if(x == 'y'){
            Landlord = t -> player_number;
            multi *= 2;
        }
        else{
            cout << "不抢" << endl;
        }
        t = t -> next;
    }while(i != 2);
    gyh[Landlord-1].type = 1;
    for(int i = 51; i <= 53; i++) gyh[Landlord-1].card.push_back(pack_of_cards[i]);
    sort(gyh[Landlord-1].card.begin(), gyh[Landlord-1].card.end(), compare);
}
int main(){
    cout << "hello world !" << endl;
    fight_with_ficher hhh;
    return 0;
}