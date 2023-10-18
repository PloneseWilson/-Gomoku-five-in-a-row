#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "conio.h"
using namespace std;
#define pb emplace_back
#define inf 1000000000
#define rnd srand(time(NULL))
#define endl '\n'
const int len = 9;
double c = 1.414;
int iter_cnt = 500;
int mx[5] = {1,0,-1},my[5] = {1,0,-1};
char alpha[15] = {' ','A','B','C','D','E','F','G','H','I','J','K'};
/*
empty 0
black 1
white -1
*/
void de(){cout<<"?";}

int legalinput(string str){
    if(str.length()!=2)return 0;
    if(str[0]-'A'<0 || str[0]-'A'>len)return 0;
    if(str[1]-'0'<1 || str[1]-'0'>len)return 0;
    return 1;
}

//----------------------------------
// Definition
struct action{
    int x;
    int y;

    action(int a,int b):
        x(a),y(b){}
};vector<action>step;
struct node{
    int board[len+2][len+2];
    int color;
    int visit;
    double win;

    node* father;
    vector<node*> son;
    vector<action>step;
    action mv;

    node(int s[len+2][len+2], int clr, action m, node* f):
        color(clr),mv(m),father(f),visit(0),win(0.0) {
            for(int i = 1;i<=len;i++){
                for(int j = 1;j<=len;j++){
                    board[i][j] = s[i][j];
                    if(board[i][j]!=0)
                        step.pb(action(i,j));
                }
            }
        }
};
//------------------------------------

void prt(node* n){
    cout << "  ";
    for(int i = 1;i<=len;i++)cout << i<<" ";cout <<endl;cout <<endl;

    for(int i = 1;i<=len;i++){
        cout << alpha[i]<<" ";
        for(int j = 1;j<=len;j++){
            if(n->board[i][j]==1)
                cout <<"X"<<" ";
            else if(n->board[i][j]==-1)
                cout <<"O"<<" ";
            else cout << "."<<" ";
        }cout << endl;cout << endl;
    }
}

node* apply(node* n,action a){
    node* newn = new node(n->board,n->color*-1,a,n);
    newn->board[a.x][a.y] = newn->color;
    return newn;
}

void show(node* n){
    cout<< n <<" " << n->father<<endl;
    cout<< n->mv.x << " " << n->mv.y<<endl;
    cout << n->color<<endl;
    prt(n);
}

void del(node* n){
    //show(n);
    if(n->son.empty()==false)
        for(auto a:n->son)
            del(a);
    delete n;
}

// -------------------------------------------------
// detect function

int walk(node* n,int dx,int dy){
    int cnt = 0;
    int x = n->mv.x, y = n->mv.y;
    while(n->board[x][y]==n->color){
        cnt++;x+=dx;y+=dy;
        if(x<=0||x>len)break;if(y<=0||y>len)break;
    }
    x = n->mv.x; y = n->mv.y;
    while(n->board[x][y]==n->color){
        cnt++;x-=dx;y-=dy;
        if(x<=0||x>len)break;if(y<=0||y>len)break;
    }cnt--;
    return cnt;
}

int score(node* n,int dx,int dy){
    int cnt = 0;
    int x = n->mv.x, y = n->mv.y;
    while(n->board[x][y]==n->color){
        cnt+=10;x+=dx;y+=dy;
        if(x<=0||x>len)break;if(y<=0||y>len)break;
    }
    if(n->board[x][y]==n->color*-1||(x<=0||x>len)||(y<=0||y>len))
        cnt-=1;

    x = n->mv.x; y = n->mv.y;
    while(n->board[x][y]==n->color){
        cnt+=10;x-=dx;y-=dy;
        if(x<=0||x>len)break;if(y<=0||y>len)break;
    }cnt-=10;

    if(n->board[x][y]==n->color*-1||(x<=0||x>len)||(y<=0||y>len))
        cnt-=1;

    return cnt;
}

int wincheck(node* n){
    if(walk(n,1,1)>=5)return 1;
    if(walk(n,1,-1)>=5)return 1;
    if(walk(n,1,0)>=5)return 1;
    if(walk(n,0,1)>=5)return 1;
    return 0;
}

int scorecheck(node* n){
    int maxi = 0;
    maxi = max(maxi,score(n,1,1));
    maxi = max(maxi,score(n,1,-1));
    maxi = max(maxi,score(n,1,0));
    maxi = max(maxi,score(n,0,1));
    return maxi;
}

vector<action>dedup(vector<action>v){
    vector<action>output;
    unordered_set<int>s;
    for(action a:v)
        s.insert(100*(a.x)+a.y);
    for(int i:s)
        output.pb(action{i/100,i%100});
    return output;
}

vector<action> legalmove(node* n){
    vector<action>output;
    vector<action>other_first,other_second,other_third;
    vector<action>me_first,me_second,me_third;

    if(n->step.size()==len*len)
        return output;

    for(action a:n->step){
        for(int i = -1;i<=1;i++){
            for(int j = -1;j<=1;j++){
                if(i==0&&j==0)continue;
                if(a.x+i<=0||a.x+i>len)continue;
                if(a.y+j<=0||a.y+j>len)continue;
                if(n->board[a.x+i][a.y+j]!=0)continue;
                action aa(a.x+i,a.y+j);
                output.pb(aa);
            }
        }
    }
    output = dedup(output);

    for(action a:output){
        node* other = apply(n,a);
        other->color*=-1;other->board[a.x][a.y]*=-1;

        int temp = scorecheck(other);

        if(temp>40)other_first.pb(a);
        else if(temp==40)other_second.pb(a);
        else if(temp==30||temp==39)other_third.pb(a);

        node* me = apply(n,a);
        temp = scorecheck(me);

        if(temp>40)me_first.pb(a);
        else if(temp==40)me_second.pb(a);
        else if(temp==30||temp==39)me_third.pb(a);
    }
    if(me_first.empty()==false)return me_first;
    if(other_first.empty()==false)return other_first;
    if(me_second.empty()==false)return me_second;
    if(other_second.empty()==false)return other_second;
    if(me_third.empty()==false)return me_third;
    if(other_third.empty()==false)return other_third;

    return output;
}

action getrandom(vector<action>v){
    rnd;
    int sz = v.size();
    if(sz==0)return {1,1};
    return v[rand()%sz];
}

node* bestson(node* n){
    node* ans = nullptr;
    double maxi = -1;

    for(node* s:n->son){
        double val = 1.0*s->win/s->visit;
        if(val>maxi){
            maxi = val;
            ans = s;
        }
    }
    return ans;
}

// -------------------------------------------------
// process function

double UCB(node* n, node* f){
    if(n->visit == 0)return inf;

    double exp = 1.0*n->win/n->visit;
    double chance = sqrt(log(f->visit)/n->visit);
    return exp + 1.0*c*chance;
}

node* select(node* n){
    while(n->son.empty()==false){
        double maxi = -1.0;
        node* selectson = nullptr;

        for(node* s:n->son){
            double val = UCB(s,n);
            if(val>maxi){
                maxi = val;
                selectson = s;
            }
        }
        n = selectson;
    }
    return n;
}

node* expand(node* n){
    rnd;
    vector<action> legal = legalmove(n);//-------------------------------------legal
    if(legal.empty()==true)return n;
    for(action a:legal){
        node* newn = new node(n->board,n->color*-1,a,n);
        newn->board[a.x][a.y] = newn->color;
        n->son.pb(newn);
    }
    int sz = n->son.size();
    int x = rand();
    return n->son[(x+sz)%sz];
}

double simulate(node* n){
    vector<action> legal;
    while(wincheck(n)==0){
        legal.clear();legal = legalmove(n);//-----------legal
        if(legal.empty()==true)return 0;

        //prt(n);

        action random = getrandom(legal);

        n = apply(n,random);
    }

    if(wincheck(n)==1)
        return 1;
    else
        return 0;
}

void backpropagate(node* n,double result){
    while(n!=nullptr){
        n->visit++;
        n->win += result;
        n = n->father;
    }
}

//-------------------------------------------
node* AI(node* root){
    for(int i = 0;i<iter_cnt;i++){
        node* selectn = select(root);
        node* expandn = expand(selectn);
        double result = simulate(expandn);
        backpropagate(expandn,result);
    }
    node* best = bestson(root);
    return best;
}


int main()
{
    cout << "skip  intro: press 1"<<endl; cout << "watch intro: press Enter"<<endl;char c = getch();

    if(c!='1'){
        system("cls");
        cout << "Five-in-a-row"<<endl;Sleep(2000);
        cout << "Bot goes first"<<endl;Sleep(2000);
        cout << "type in 'END' to stop the game"<<endl;Sleep(3000);
    }system("cls");

    rnd;int flag = 0;int step_cnt = 0;
    int b[len+2][len+2]={0};
    b[len/2+1][len/2+1] = -1;

    cout << "  ";
    for(int i = 1;i<=len;i++)cout << i<<" ";cout <<endl;cout <<endl;

    for(int i = 1;i<=len;i++){
        cout << alpha[i]<<" ";
        for(int j = 1;j<=len;j++)
            if(i==len/2+1&&j==i)
                cout << "O"<<" ";
            else
                cout << "."<<" ";
        cout << endl;cout << endl;
    }

    while(step_cnt<=len*len-1){
        string str;
        cout << "Your next step:(like B2):";
        again:cin >> str;
        if(str=="END"||str=="end")
            return 0;
        if(legalinput(str)==0){
            cout << "Invalid, please enter again:";
            goto again;
        }
        int p = str[0]-'A'+1;int q = str[1]-'0';

        if(b[p][q]!=0){
            cout << "There is a chess here, please enter again:";
            goto again;
        }


        b[p][q] = 1;step_cnt++;
        node* root = new node(b,1,action{p,q},nullptr);

        //cin.get();
        system("cls");
        prt(root);
        if(wincheck(root)==1){
            cout << "You win :)"<<endl;flag = 1;
            system("pause");
            break;
        }
        if(step_cnt==len*len){
            cout << "End in a tie."<<endl;flag = 1;
            system("pause");
            break;
        }

        node* n = AI(root);
        b[n->mv.x][n->mv.y] = -1;step_cnt++;
        //cin.get();
        system("cls");
        prt(n);
        if(wincheck(n)==1){
            cout << "You lose :("<<endl;flag = 1;
            system("pause");
            break;
        }
        del(root);
    }
    if(flag==0){
        cout << "End in a tie."<<endl;
        system("pause");
    }

    return 0;
}
