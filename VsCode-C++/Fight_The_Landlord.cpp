//====================================================
// 
//  GYH
//  https://github.com/gyhdtc/Fight-The-Landlord
//   
//====================================================
#include <iostream>
#include <string>
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

bool compare_unique(int a, int b){ return (a == b);}
//  这里挑战一下自己，做一个vector各种类型接口函数
//void outvector(vector)

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
        //void show_information();
        void show_card(poker *begin, poker *end, string);
        void show_player_imformation(player, string);
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
            cout << "发牌  ......" << endl;
            dealcard();
            cout << "------------------------------------" << endl;
            cout << "抢地主 ......" << endl;
            compete_landlord();
            cout << Landlord << " 号玩家 " << gyh[Landlord-1].player_name << " 是地主" << endl;
            show_player_imformation(gyh[0],"");
            show_card(&pack_of_cards[51], &pack_of_cards[53], "地主牌");
        }
        void initcard();
        void initplayer();
        void dealcard(); 
        void compete_landlord();
        void putcard();
};

void fight_with_ficher::show_player_imformation(player t, string es = "0"){
    // 输出基本信息
    cout 
    << t.player_number << "号玩家 " << t.player_name 
    << " 金币：" << t.gold 
    << (t.flag==0?" / 电脑 ":" / 玩家 ")
    << (t.type==0?" / 农名 ":" / 地主 ")
    << "手牌【 " << t.card_number << " 】" << endl;
    // 输出基本信息

    if(es != "0"){
        vector<poker>::iterator it;
        vector<int> temp;
        for(int i = 0; i < es.size(); i++){
            if(es[i] < 58 && es[i] > 47){
                temp.push_back(es[i] - 48);
            }
        }
        sort(temp.begin(), temp.end());
        unique(temp.begin(), temp.end(), compare_unique);
        for(int i = 0; i < temp.size(); i++){
            switch(temp[i]){
                case 1:
                    cout << "\n手牌：";
                    for(it = t.card.begin(); it != t.card.end(); it++){
                        cout << type[(*it).number] << " ";
                    }
                break;
                case 2:
                    cout << "\n上次出牌：";
                    if(t.last_put_card.size() == 0) cout << "吃不起";
                    else{
                        for(it = t.last_put_card.begin(); it != t.last_put_card.end(); it++){
                            cout << type[(*it).number] << " ";
                        }
                    }
                break;
                default: break;
            }
        }
    }

    cout << "\n";
}
void fight_with_ficher::show_card(poker *begin, poker *end, string s){
    int flag = 0;
    for( ; begin != end + 1; begin++){
        if(flag == 0){
            flag = 1;
            cout << s;
            cout << type[begin -> number];
        }
        else{
            cout << " - " << type[begin -> number];
        }
    }
}

// void fight_with_ficher::show_information(){
//     printf("%10s——%10s——%10s",type[pack_of_cards[51].number],type[pack_of_cards[52].number],type[pack_of_cards[53].number]);
//     printf("%10s——%10s——%10s",gyh[0].player_name,gyh[1].player_name,gyh[2].player_name);
//     printf("%10d——%10d——%10d",gyh[0].card_number,gyh[1].card_number,gyh[2].card_number);
// }

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
    cout << "玩家数量：";
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
}
// 暂时忽略了 三个人都不叫地主的情况
void fight_with_ficher::compete_landlord(){
    int number = 0, flag = 0;
    char x;
    player *t;
    if(Landlord == 0) 
        player_head = &gyh[0];
    else{
        player_head = &gyh[Landlord - 1];
    }
    while(flag != 1){
        t = player_head;
        for(int i = 0; i < 3; i ++){
            cout << t -> player_number << "号玩家，是否抢地主：y/n";
            cin >> x;
            if(x == 'y'){
                Landlord = t -> player_number;
                multi *= 2;
                number++;
                cout << "当前倍数：" << multi << endl;
            }
            else{
                cout << "不抢" << endl;
            }
            t = t -> next;
        }
        if(number == 1) flag = 1;
        else          number = 0;
    }
    player_head = &gyh[Landlord - 1];
    gyh[Landlord-1].type = 1;
    for(int i = 51; i <= 53; i++) gyh[Landlord-1].card.push_back(pack_of_cards[i]);
    sort(gyh[Landlord-1].card.begin(), gyh[Landlord-1].card.end(), compare);
}
int main(){
    cout << "hello world !" << endl;
    fight_with_ficher hhh;
    return 0;
}