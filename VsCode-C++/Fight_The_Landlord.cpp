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
    int flag = 0;           // 0 ���� 1 ����
    int type = 0;           // 0 ũ�� 1 ����
    int gold = 0;           // ���
    int card_number = 0;    // ����
    int player_number; 
    string player_name;  
};

bool compare(poker a, poker b){
    return a.number <= b.number;
}

bool compare_unique(int a, int b){ 
    return (a == b);
}

class fight_with_ficher{
    private:
        int number_of_human = 1;
        int number_of_ai = 2;
        int number_of_cards = 17;
        int multi = 1;
        int Landlord = 0;
        int winnner = 0;
        poker pack_of_cards[54];
        player *player_head;
        player gyh[3];
        string type[15] = { "3", "4", "5", "6", "7", "8", "9",
                            "10", "J", "Q", "K", "A", "2", 
                            "Small_king", "Big_king"}; 
        void myrandom(); // ��д
        void show_card(poker *begin, poker *end, string);
        void show_player_imformation(player, string);
        
    public:
        fight_with_ficher(){
            cout << "         ++                            ++         " << endl;
            cout << "     ++++++++++                    ++++++++++     " << endl;
            cout << " +++++++++++++++++++          +++++++++++++++++++ " << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << " ++++++++________________________________++++++++ " << endl;
            cout << "   ++++++|Thank you for playing my game!|++++++   " << endl;
            cout << "      +++********************************+++      " << endl;
            cout << "         ++++++++++++++++++++++++++++++++         " << endl;
            cout << "           ++++++++++++++++++++++++++++           " << endl;
            cout << "             ++++++++++++++++++++++++             " << endl;
            cout << "               ++++++++++++++++++++               " << endl;
            cout << "                 ++++++++++++++++                 " << endl;
            cout << "                     ++++++++                     " << endl;
            cout << "                        ++                        " << endl;
        }
        void start();
        void initcard();
        void initplayer();
        void dealcard(); 
        void compete_landlord();
        void putcard();
        int  JudgeWin();
        void loseandwin();
};

void fight_with_ficher::show_player_imformation(player t, string es = "0"){
    // ���������Ϣ
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf(" %d����� %10s | ��ң�%4d | %s | %s | ���ơ� %02d ��"
            , t.player_number, t.player_name.c_str(), t.gold, (t.flag==0?"����":"���"), (t.type==0?"ũ��":"����"), t.card_number);
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    // ���������Ϣ
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
                    cout << "\n���ƣ�";
                    for(it = t.card.begin(); it != t.card.end(); it++){
                        cout << type[(*it).number] << " ";
                    }
                break;
                case 2:
                    cout << "\n�ϴγ��ƣ�";
                    if(t.last_put_card.size() == 0) cout << "�Բ���";
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
    cout << endl;
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

void fight_with_ficher::start(){
    cout << "------------------------------------" << endl;
    cout << "�γ�����......" << endl;
    initcard();
    cout << "------------------------------------" << endl;
    cout << "�������......" << endl;
    initplayer();
    cout << "------------------------------------" << endl;
    cout << "����  ......" << endl;
    dealcard();
    cout << "------------------------------------" << endl;
    cout << "������ ......" << endl;
    compete_landlord();
    cout << "------------------------------------" << endl;
    for(int i = 0;i < 3; i++) show_player_imformation(gyh[i],"");
    show_card(&pack_of_cards[51], &pack_of_cards[53], "������: ");
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
    cout << "���������";
    cin >> number_of_human;
    number_of_ai = 3 - number_of_human;
    for(int i = 0; i < 3; i++){
        if(i < number_of_human){
            gyh[i].player_number = i + 1;
            gyh[i].flag = 1;
            cout << "���������";
            cin >> gyh[i].player_name;
        }
        else{
            gyh[i].player_number = i + 1;
            gyh[i].flag = 0;
            gyh[i].player_name = "AI_player";
        }
    }
    gyh[0].next = &gyh[1];
    gyh[1].next = &gyh[2];
    gyh[2].next = &gyh[0];
}
/*
    ���Ƴ���
    ������random_shuffle��ÿ�����н����һ��
    �����漰��seed������
    ���һ��Ҫ�ĸģ����Բο��� ���춷���� �ĳ��򣬲�֪���ܷ��ҵ�233
*/
void fight_with_ficher::dealcard(){
    random_shuffle(pack_of_cards, pack_of_cards + 54);
    for(int i = 0; i < 3; i++){
        gyh[i].card.assign(&pack_of_cards[i*number_of_cards], &pack_of_cards[(i+1)*number_of_cards]);
        sort(gyh[i].card.begin(), gyh[i].card.end(), compare);
    }
}
// ��ʱ������ �����˶����е��������
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
            cout << t -> player_number << "����ң��Ƿ���������y/n";
            cin >> x;
            if(x == 'y'){
                Landlord = t -> player_number;
                multi *= 2;
                number++;
                cout << "��ǰ������" << multi << endl;
            }
            else{
                cout << "����" << endl;
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
    //  ��������
    for(int i = 0; i < 3; i++) gyh[i].card_number = gyh[i].card.size();
}

void fight_with_ficher::putcard(){

}

int fight_with_ficher::JudgeWin(){
    for(int i = 0; i < 3; i++){
        if(gyh[i].card_number == 0) return i + 1;
    }
    return 0;
}

void fight_with_ficher::loseandwin(){

}

int main(){
    char q;
    fight_with_ficher game;
    cout << " ���� q ��ʼ��Ϸ��" << endl;
    cin >> q;
    while(q == 'q'){
        game.start();
        while(game.JudgeWin()){
            game.putcard();
        }
        cin >> q;
    }
    return 0;
}