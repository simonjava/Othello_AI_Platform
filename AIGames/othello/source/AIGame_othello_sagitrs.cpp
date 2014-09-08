#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int decisionX[8]={-1,-1,0,1,1,1,0,-1};
int decisionY[8]={0,1,1,1,0,-1,-1,-1};
int globalError = 0;
typedef unsigned int int32;
#define MYMAX 12011031

#define WHITE 1
#define BLACK 0
#define EXIST 2

#define	NO_CHESS	0b00
#define	UNDEFINED	0b01
#define BLACK_CHESS	0b10
#define WHITE_CHESS	0b11

#define STABLE_CHESS	0b100
#define IN_CHESS		0b010
#define OUT_CHESS		0b001

#define POS(i,j) ((unsigned long long)1<<((8*i)+j))
#define ILLEGAL(x,y) (!(0<=x&&x<8&&0<=y&&y<8))
#define CHESS(k) ((bool)(k&0b10))
#define COLOR(k) ((bool)(k&0b01))

//#define SHOW_PROCESS 1
typedef unsigned long long LL;
void message(string s){
#ifndef SHOW_PROCESS
		return;
#endif
	cout<<s<<endl;
}
void error(string s){
	cout<<"Error Report From : "<<s<<endl;
	++globalError;
}
struct Randomizer{
	Randomizer(){
		srand((unsigned int)time(0));
	}
	int random(int k){
		return rand()%k;
	}
};
Randomizer R;
struct Pair{
	int x,y;
	Pair(int X=0,int Y=0){
		x=X;y=Y;
	}
	static Pair make(int x,int y){
		Pair t(x,y);
		return t;
	}
	string toString(){
		string s;
		s="( ";
		s+=x+49;
		s+=" , ";
		s+=y+49;
		s+=" )";
		return s;
	}
	Pair operator + (Pair b){
		return make(x+b.x,y+b.y);
	}
	Pair&operator +=(Pair b){
		x+=b.x;y+=b.y;
		return *this;
	}
	bool operator ==(Pair b){
		return x==b.x&&y==b.y;
	}
};
ostream& operator << (ostream& os, Pair a){
	return os<<a.toString();
}
Pair D[8];

struct Board{
private:
	LL	chessRec,colorRec;
	static const LL 		BLANK = 0x0000000000000000;
//	static const LL DEFAULT_CHESS = 0x0000001818000000;
//	static const LL DEFAULT_COLOR = 0x0000001008000000;
	bool boardcast;
	void setChess(int x, int y, int k){
		if (chess(x,y)!=k) chessRec^=POS(x,y);
	}
	void setColor(int x, int y, int k){
		if (color(x,y)!=k) colorRec^=POS(x,y);
	}
	void setState(int x, int y, int st){
		int oldSt = state(x,y);
		if (oldSt==UNDEFINED) {error("setState");return;}
		setChess(x,y,CHESS(st));
		setColor(x,y,COLOR(st));
		if (state(x,y)!=st) {
			printf("%d!=%d, ",state(x,y),st);
			error("setState");
			return;
		}
	}
	void setState(Pair t, int st){
		setState(t.x,t.y,st);
	}
	int reverse(int x, int y){
		if (state(x,y)==UNDEFINED||state(x,y)==NO_CHESS){
			error("reverse");
			return 0;
		}
		setState(x,y,EXIST|(!color(x,y)));
		if (boardcast)
			cout<<"Reverse : "<<Pair::make(x,y)<<endl;
		return 1;
	}
	int reverse(Pair t){
		return reverse(t.x,t.y);
	}
	int checkLine(Pair t, bool k, int d){
		if (ILLEGAL(t.x,t.y)) {error("checkLine");return 0;}
		int temp=0;
		for (t+=D[d];!ILLEGAL(t.x,t.y);t+=D[d]){
			if (chess(t)==0) break;
			if (color(t)==k) return temp;
			if (color(t)!=k) ++temp;
		}
		return 0;
	}
	int checkLine(int x, int y, bool k, int d){
		return checkLine(Pair::make(x,y),k,d);
	}
	int reverseLine(Pair t,bool k, int d){//Be careful! Illegal action will be passed.
		for (t+=D[d];1;t+=D[d]){
			if (state(t)==UNDEFINED){
				error("reverseLine");
				message("At edge.");
				return 0;
			}
			if (state(t)==NO_CHESS){
				error("reverseLine");
				message("Illegal reverse.");
				return 0;
			}
			if (state(t)==(EXIST|!k)){
				reverse(t);
				continue;
			}
			if (state(t)==(EXIST| k)) 
				return 1;
			error("reverseLine");
			message("Unknown error occured.");
			break;
		}
		return 0;
	}
	int reverseLine(int x, int y, bool k, int d){
		return reverseLine(Pair::make(x,y),k,d);
	}
public:
	Board (bool toPublic = 0){
		init();
		boardcast = toPublic;
		boardcast = 0;//Stop Boardcasting.
	}
	void clear(){
		chessRec = BLANK;
		colorRec = BLANK;
	}
	void init(){
		clear();
		setState(3,3,WHITE_CHESS);
		setState(3,4,BLACK_CHESS);
		setState(4,3,BLACK_CHESS);
		setState(4,4,WHITE_CHESS);
	}	
	bool chess(int x,int y){
		if (ILLEGAL(x,y)) {error("chess");return 0;}
		return (bool)(chessRec&POS(x,y));
	}
	bool chess(Pair t){
		return chess(t.x,t.y);
	}
	bool color(int x, int y){
		if (ILLEGAL(x,y)) {error("color");return 0;}
		return (bool)(colorRec&POS(x,y));
	}
	bool color(Pair t){
		return color(t.x,t.y);
	}
	int state(int x, int y){
		if (ILLEGAL(x,y)) return UNDEFINED;
		if (chess(x,y)) return EXIST|color(x,y);
		if (!color(x,y)) return NO_CHESS;
		error("state");
		message("Undefined state exist.");
		return UNDEFINED;
	}
	int state(Pair t){
		return state(t.x,t.y);
	}
	int check(int x,int y,bool k){
		if (ILLEGAL(x,y)) return 0;
		if (chess(x,y)) return 0;		
		int total=0;
		for (int l=0;l<8;++l)
			total+=checkLine(x,y,k,l);
		return total;
	}
	int check(Pair t,int k){
		return check(t.x,t.y,k);
	}
	int put(int x,int y,bool k){
		if (ILLEGAL(x,y)) {
			error("put : illegal.");
			cout<<"Trying to put a "<<(k?"white":"black");
			cout<<" chess at "<<Pair::make(x,y)<<endl;
			return 0;
		}
		if (chess(x,y)) {
			error("put : illegal.(chess alread exist)");
			cout<<"Trying to put a "<<(k?"white":"black");
			cout<<" chess at "<<Pair::make(x,y)<<endl;
			return 0;
		}
		int t=check(x,y,k);
		if (t==0) {
			error("put : illegal.(no reversable chess)");
			cout<<"Trying to put a "<<(k?"white":"black");
			cout<<" chess at "<<Pair::make(x,y)<<endl;
			return 0;
		}
		for (int l=0;l<8;++l) 
			if (checkLine(x,y,k,l)) reverseLine(x,y,k,l);
		setState(x,y,EXIST|k);
		return t;
	}
	int put(Pair t, bool k){
		return put(t.x,t.y,k);
	}
	static int upDate(int x){
		if (x==0) return NO_CHESS;
		if (x==1) return BLACK_CHESS;
		if (x==2) return WHITE_CHESS;
		return UNDEFINED;
	}
	void read(){
		int x;
		for(int i=0;i<8;++i)
			for(int j=0;j<8;++j){
				scanf("%d",&x);
				setState(i,j,upDate(x));
			}
	}
	string toString(){
#ifndef SHOW_PROCESS
		return "";
#endif
		const string whiteChess = "1 ",blackChess = "0 ";
		const string noChess = "_ ", rightLine = "| ";
		const string top = "+ 1 2 3 4 5 6 7 8 + \n";
		string s=top;
		for (int i=0;i<8;++i){
			s+=i+49;s+=' ';
			for (int j=0;j<8;++j) 
				s+=chess(i,j)?(color(i,j)?whiteChess:blackChess):noChess;	
			s+=i+49;s+=' ';
			s+='\n';
		}
		s+=top;
		return s;
	}
	void print(){
		cout<<toString();
	}
/*	int game(){
		for (bool i=0;1;i=!i){
			cout<<toString();
			if (!play(i%2)) return 0;
		}
	}
	int play(int k){
		int x,y,t;
		string s;
		do{
			cin>>x>>y;	
			if (x==0&&y==0) {
				s="Game over. Player ";
				s+=k+48;s+=" resigned.";
				message(s);return 0;
			}
			t=put(x-1,y-1,k);
		}while(t==0);
		return 1;
	}
	static bool edge(int x, int y){
		return x==0||x==7||y==0||y==7;
	}
	static bool edge(Pair t){
		return edge(t.x,t.y);
	}
	static bool corner(int x, int y){
		int k=0;
		k+=x==0||x==7;
		k+=y==0||y==7;
		return k==2;
	}
	static bool corner(Pair t){
		return corner(t.x,t.y);
	}
*/
};
ostream& operator << (ostream& os, Board b){
	return os<<b.toString();
}

struct Analysist{
	bool stableChessCheck(Pair t, Board B){
		if (!B.chess(t)) return 0;
		if (t.x==0||t.x==7){
		if (t.y==0||t.y==7) return 1;
		if ((B.state(t.x,t.y-1)^B.state(t.x,t.y))==0b01) 
			if ((B.state(t.x,t.y+1)^B.state(t.x,t.y))==0b01) 
				return 1;
		return 0;
		}
		if (t.y==0||t.y==7){
			if (t.x==0||t.x==7) return 1;
			if ((B.state(t.x-1,t.y)^B.state(t.x,t.y))==0b01)
				if ((B.state(t.x+1,t.y)^B.state(t.x,t.y))==0b01) 
					return 1;
			return 0;
		}
		return 1;
	}
	bool stableChessCheck(int x, int y, Board B){
		return stableChessCheck(Pair::make(x,y),B);
	}
	bool inChessCheck(Pair t, Board B){
		for (int i=-1;i<=1;++i)
			for (int j=-1;j<=1;++j){
				if (B.state(t.x+i,t.y+j)==UNDEFINED) return 0;
				if (B.state(t.x+i,t.y+j)==NO_CHESS)  return 0;
			}
		return 1;
	}
	bool inChessCheck(int x, int y, Board B){
		return inChessCheck(Pair::make(x,y),B);
	}
	int typeOfChess(Pair t, Board B){
		if (stableChessCheck(t,B)) 
			return STABLE_CHESS;
		if (inChessCheck(t,B))
			return IN_CHESS;
		return OUT_CHESS;
	}
	int typeOfChess(int x, int y, Board B){	
		return typeOfChess(Pair::make(x,y),B);
	}
	void findChoice(vector<Pair> &Choice, Board B, int color){
		Choice.clear();
		for (int i=0;i<8;++i)
			for (int j=0;j<8;++j)
				if (B.check(i,j,color)>0) 
					Choice.push_back(Pair::make(i,j));
	}
	int choices(Board B, int color){
		vector<Pair> Choice;
		findChoice(Choice,B,color);
		return Choice.size();
	}
	int silence(Pair t, Board B, bool k){
		Board newB = B;
		if (newB.check(t,k)==0) return MYMAX;
		newB.put(t,k);
		vector<Pair> a1,a2,b1,b2;
		findChoice(a1,B,k);
		findChoice(a2,newB,k);
		findChoice(b1,B,!k);
		findChoice(b2,newB,!k);
		return (a2.size()-a1.size())-(b2.size()-b1.size());
	}
};
Analysist A;


struct Player{
public:
	string name;
	bool hasName;
	bool color;
	int AI;
	void setColor(bool k){
		color = k;
		if (hasName==0) setName();
	}
	void setMode(int mode){
		AI = mode;
	}
	void setName(string s=""){
		if (s==""){
			hasName = 0;
			if (AI == 0) name = "Player";
//			if (AI == 1) name = "Simple Computer";
//			if (AI == 2) name = "Normal Computer";
//			if (AI == 3) name = "Clever Computer";
			if (AI >= 1) {
				name = "Lv.";
				name+=(AI+48);
				name+=" Computer";
			}
			name+=color?" 0":" 1";
		}
		else {
			hasName = 1;
			name = s;
		}
	}			
	Player(bool k = 0, int mode = 1, string s = ""){
		setColor(k);
		setMode(mode);
		setName(s);
	}
	int chessOfBoard(Board B, int k){
		int a[2]={0,0};
		for (int i=0;i<8;++i)
			for (int j=0;j<8;++j) 
				if (B.chess(i,j))	
					++a[B.color(i,j)];
		return a[k];
	}
	Pair bestChoice(vector<Pair> &Choice, Board B){
		vector<int> value;
		value.clear();
		int max = -12011031;
		for (int32 i=0;i<Choice.size();++i){
			int t=evaluate(B,Choice[i]);
			if (t>max) max=t;
			value.push_back(t);
		}
		for (int32 i=0;i<Choice.size();++i)
			while (i<Choice.size()&&value[i]<max){
				Choice.erase(Choice.begin()+i);
				value.erase(value.begin()+i);
			}
		if (Choice.empty()) 
			return Pair::make(-1,-1);
		return Choice[R.random(Choice.size())];
	}
	int safetyOfBoard(Board B){
		int safety = 0;
		for (int i=0;i<8;++i)
			for (int j=0;j<8;++j){
				Pair t(i,j);
				if (B.state(i,j)==(EXIST|color))
					safety+=safetyOfChess(t,B);
			}
		return safety;
	}
	int safetyOfChess(Pair t, Board B){
		if (AI<=10){
			if (A.typeOfChess(t,B)==STABLE_CHESS) 
				return 2;
			vector<Pair> Choice;
			Player c(!color,1);
			A.findChoice(Choice,B,c.color);
			Board newB = B;
			for (int32 i=0;i<Choice.size();++i){
				newB.put(Choice[i],!color);
				if (newB.color(t)==!color) return 0;
				newB = B;
			}
			return 1;
		}
		return 0;	
	}
/*	int valueOfBoard(Board B){
		int value = chessOfBoard(B,color);
		if (AI==1) return value;
		Player c;
		c.setColor(!color);
		c.setMode(2);
		value-=c.safetyOfBoard(B);
		return value;
		
		int minValue = 12011031;
		Player c;
		c.setMode(1,1);c.setColor(!color);
		setMode(1,1);
		vector<Pair> Choice;
		findChoice(Choice);
		for (int i=0;i<Choice.size();++i){
			Board newB = B;
			newB.put(Choice[i],color);
			newB.put(c.analysis(newB),!color);
			if (valueOfBoard(newB)<minValue)
				minValue = valueOfBoard();
		}
	}*/
	int evaluate(Board B, Pair t){
		Board newB = B;
		//	Lv.1, 最多得子贪心策略
		if (!newB.check(t,color)) return -MYMAX;
		newB.put(t,color);
		int score = 0;
		score+=(chessOfBoard(newB,color)-chessOfBoard(B,color));
		if (AI==1)
			return score;
		//	Lv.2, 简单估计棋局的稳定性
		score+=3*(safetyOfBoard(newB)-safetyOfBoard(B));
		if (AI==2)
			return score;
		//	Lv.3, 强化当前步的价值
		score+=5*safetyOfChess(t,newB);
		bool tmp0=(t.x<=1||t.x>=6)&&(t.y<=1||t.y>=6);
		bool tmp1=(t.x==1||t.x==6)&&(t.y==1||t.y==6);
		bool tmp2=(t.x==0||t.x==7)&&(t.y==0||t.y==7);
		if (tmp0) score-=2;
		if (tmp1) score-=3;
		if (tmp2) score+=10;
		if (AI==3)
			return score;
		//	Lv.4, 强化当前步对棋局稳定性的影响
		score+=7*A.silence(t,B,color);
		if (AI==4)
			return score;
		//	Lv.5, 站在对方的角度思考,使对手最优决策最劣化
		Player c(!color,4);
		Pair sln = c.analysis(newB);
		if (!newB.check(sln,!color)) return score;
		score-=c.evaluate(newB,sln)/3;
		if (AI==5)
			return score;
		//	Lv.6, 测试用
		if (AI==6) 
			return score;
		return score;
	}
	Pair play(Board B){
		Pair d;
		int t=0;
		if (AI) return analysis(B);
		do{
			cout<<"Please input your decision:";
			cin>>d.x>>d.y;
			--d.x;--d.y;
			if (d.x==-1&&d.y==-1) return d;
			if (d.x==MYMAX-1) return d;
			t=B.check(d,color);
			if (t!=0) return d;
			error(name+" : Illegal operation.");			
		}while (t==0);
		return d;//avoid warning.
	}
	Pair analysis(Board B){
		vector<Pair> Choice;
		A.findChoice(Choice,B,color);
		return bestChoice(Choice,B);
	}
	void resign(){
		string s=name+" resigned.";
		message(s);
	}
	void announce(int x, int y){
#ifndef SHOW_PROCESS
		return;
#endif
		Pair decision(x,y);
		cout<<name<<" put a "<<(color?"white":"black");
		cout<<" chess at "<<decision<<"."<<endl;
	}
	void announce(Pair t){
		announce(t.x,t.y);
	}
};

struct Game{
	Player P[2];
	bool order;
	bool random;
	Board B;
	vector<Board> Boards;
	void setOrder(int k = 0){
		order = k;
	}
	Game(int AI1 = 2, int AI2 = 2, int o = -1){
		P[0].setMode(AI1);	P[1].setMode(AI2);
		P[0].setColor(0);	P[1].setColor(1);
		if (o==-1) random = 1;
		else order = o;
	}
	int checkBoard(bool color){
		for (int i=0;i<8;++i)
			for (int j=0;j<8;++j)
				if (B.check(i,j,color)!=0) 
					return 1;
		return 0;
	}
	Board regret(int k){
		return Boards[Boards.size()-1-2*k];
	}
	int start(){
		int holder;
		bool stepColor;
		Pair decision;
		B.init();
		if (random) setOrder(R.random(2));
		Boards.clear();
		for (int i=order;1;++i){
			holder = i%2;
			cout<<B;
			Boards.push_back(B);
			stepColor	= P[holder].color;
			if (!checkBoard(stepColor)) 
				return gameOver(-1);
			decision	= P[holder].play(B);
			if (decision == Pair::make(-1,-1)) {
				P[holder].resign();
				return gameOver(1-holder);
			}
			if (decision.x==MYMAX-1) {
				B=regret(2);
				i-=3;
				continue;
			}
			if (!B.put(decision,stepColor)){
				error("Game received a bad input.");
				P[holder].resign();
				return gameOver(1-holder);
			}
			P[holder].announce(decision);
		}
	}
	int calcChess(){
		int a[2]={};
		for (int i=0;i<8;++i)
			for (int j=0;j<8;++j)
				if (B.chess(i,j)) ++a[B.color(i,j)];
		if (P[0].color!=0) {int t=a[0];a[0]=a[1];a[1]=t;}
#ifndef SHOW_PROCESS 
		return a[0]==a[1]?-1:a[1]>a[0];
#endif
		cout<<"Chess of "<<P[0].name<<" : "<<a[0]<<endl;
		cout<<"Chess of "<<P[1].name<<" : "<<a[1]<<endl;
		return a[0]==a[1]?-1:a[1]>a[0];
	}
	int gameOver(int winner){
		message("Game over.");
		string s = "";
		if (winner == -1) 
			winner = calcChess();
		else
			calcChess();
		if (winner != -1)
			s+=P[winner].name;
		else 
			s+="Nobody";
		s+=" won the game.";
		message(s);
		if (globalError!=0)
			cout<<"Till now, "<<globalError<<" errors have occured."<<endl;
		return winner;
	}
};

void decisionInit(){
	for (int i=0;i<8;++i){
		D[i].x=decisionX[i];
		D[i].y=decisionY[i];
	}
}
void test(int AI1, int AI2, int battle = 20){
	Game G(AI1,AI2);
	int a[2]={},draw=0;
	for (int i=0;i<battle;++i) {
		int ans = G.start();
		if (ans!=-1)
			++a[ans];
		else 
			++draw;
	}
	cout<<"Solution :"<<endl;
	cout<<"\t"<<G.P[0].name<<" : "<<a[0]<<endl;
	cout<<"\t"<<G.P[1].name<<" : "<<a[1]<<endl;
	cout<<"\tDraw : "<<draw<<endl;
}
void smallTest(){
	Game G(3,2);
	G.P[0].setName("Sagitrs");
	G.start();
}
int work(){
	Board B;
	B.read();
	Player Sagitrs;
	Sagitrs.setMode(5);
	Sagitrs.setColor(0);
	Pair decision = Sagitrs.analysis(B);
	cout<<decision.x<<" "<<decision.y<<endl;
	return 1;
}
int main(){
	decisionInit();
//	smallTest();
//	test(5,4,100);
//	test(5,3,100);
//	test(4,3,100);
//	test(6,3,100);
//	test(3,1);
	return work();
	return 0;
}