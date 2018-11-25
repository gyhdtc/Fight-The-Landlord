#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Game{
    private:
        /* 改进扑克牌的存储结构 */
        string card[15] = {
            "3", "4", "5", "6", "7", "8", "9", "10",
            "J", "Q", "K", "A", "2",
            "SKing", "BKing"
        };
        /* 改进扑克牌的存储结构 */
        
        Player x[3];
        int dizhupai[3] = {-1, -1, -1};
        int fanbei = 1;     //翻倍
        int winnner = -1;   //胜利者

    public:
        Game(string s1, string s2, string s3, int n){
            playershu = n;
            switch(n){
                case 3 : Player wanjia3(s3, 3, 1);
                         x[2] = wanjia3;

                case 2 : Player wanjia2(s2, 2, 1);
                         x[1] = wanjia2;

                default: Player wanjia1(s1, 1, 1);
                         x[0] = wanjia1;
            }
            switch(3 - n){
                case 2 : Player ai2(s2, 2, 0);
                         x[1] = ai2;

                default: Player ai3(s3, 3, 0);
                         x[2] = ai3;
            }
            cout << s1 << endl << s2 << endl << s3 << endl;
        }

        //发牌，随机数
        void fapai();
        //进行游戏
        void start();
        //判断，对于输入的字符串，判断是否符合出牌，是否符合规矩；判断是否有人胜利
        void panduan();
        //结束，计算得失
        void jieshu();
};

class Player : public Game{
    private:
        string name;
        int number;
        int gold = 0;
        int flag = 0;//0 - 机器人 ， 1 - 人类 ， 2 - 地主
        int shoupaishu = 0;
        int shoupai[20] = {0};
    public:
        void jiaodizhu();
        void chupai();
        void fangqi(); 
}; 

int main(){
    int n = 0;
    cout << "玩家个数：";
    cin >> n;
    string a[3] = {
        "AI-1", "AI-2", "AI-3"
    };
    switch(n){
        case 3 : cout << "player 3 name:";
                 cin >> a[2];
        case 2 : cout << "player 2 name:";
                 cin >> a[1];
        default: cout << "player 1 name:";
                 cin >> a[0];
    }
    Game gyh(a[0], a[1], a[2], n);
    return 0;
}





