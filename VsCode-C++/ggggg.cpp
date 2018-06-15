#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef struct arcnode{
	int number;
	double R;
	double Z;
	double P;
	double Q;
	arcnode *next;
};

typedef struct vnode{
	int number;
	int flag;
	double dianya;
	double P;
	double Q;
	arcnode *first;
}vnode, adjlist[8];

typedef struct {
	adjlist ggg;
	int v;
	int arc;
}G;

int main(){
	// 0 0 0.6 0.45 0.4 0.3 0.4 0.28 0.6 0.4 0.4 0.3 0.5 0.35 0.5 0.4   0 1 0.54 0.65 2 0.62 0.5 3 0.6 0.35 2 0.72 0.75 5 1.0 0.55 5 0.65 0.35 2 0.9 0.5 
	// 有向图
	G gyh;
	gyh.arc = 7;
	gyh.v = 8;
	double Un = 10;
	// 初始化 8 个点
	for(int i = 0; i < 8; i++){
		gyh.ggg[i].number = i + 1;
		cout << "输入" << i + 1 << "点有功功率 P & 无功功率 Q ：";
		cin >> gyh.ggg[i].P >> gyh.ggg[i].Q;
		gyh.ggg[i].dianya = 0;
		gyh.ggg[i].flag = 0;
		gyh.ggg[i].first = NULL;
		gyh.ggg[i].dianya = Un;
	}
	for(int i = 0; i < 8; i++) printf("number = %d / flag = %d / dianya = %lf / P = %lf / Q = %lf\n",gyh.ggg[i].number,gyh.ggg[i].flag,gyh.ggg[i].dianya,gyh.ggg[i].P,gyh.ggg[i].Q);
	// 初始化 7 条边
	for(int i = 0; i < 8; i++){
		int s;
		arcnode *a;
		cout << "输入" << i + 1 << "点的孩子节点：";
		cin >> s;
		if(s != 0){
			gyh.ggg[i].first = new arcnode;
			a = gyh.ggg[i].first;
			a->number = s;
			cout << "输入" << i+1 << "到" << s << "点的R & Z";
			cin >> a->R >> a->Z;
			a->next = NULL;
		}
	}
	cout << endl;
	for(int i = 0; i < 8; i++){
		arcnode *p;
		p = gyh.ggg[i].first;
		cout << i + 1 << endl;
		while(p != NULL){
			cout << "NUM " << p->number << " R " << p->R << " Z " << p->Z << endl;
			 p = p->next;
		}
	}
	gyh.ggg[3].flag = 1;
	gyh.ggg[5].flag = 1;
	gyh.ggg[6].flag = 1;
	gyh.ggg[7].flag = 1;
	for(int i = 0; i < 8; i++){
		if(gyh.ggg[i].flag == 1){
			gyh.ggg[i].first->P = (gyh.ggg[i].P * gyh.ggg[i].P)/Un/Un*gyh.ggg[i].first->R + gyh.ggg[i].P;
		}
	}
	system("pause");
	return 0;
}
