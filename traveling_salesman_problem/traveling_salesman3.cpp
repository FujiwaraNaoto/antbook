/*
n=9
A=0
B=1
C=2
D=3
E=4
F=5
G=6
H=7
I=8

*/
#include<iostream>
#include<vector>
#include<map>
using namespace std;
typedef pair<int,int> P;

const int INF=1<<30;

vector<vector<P>> G;

int n;
vector<vector<int>> dp;


int rec(int S,int v,int start){
    if(dp[S][v]>=0){
        return dp[S][v];
    }

    if(S==(1<<n)-1 && v==start){
        return dp[S][v]=0;
    }

    int res=INF;
    
    for(auto [u,c]:G[v]){//vからuへ
        if(((S>>u)&1)==0){
            res=min(res,rec(S|(1<<u),u,start)+c);
        }
    }

    return dp[S][v]=res;

}




int main(){
    
    n=9;
    G=vector<vector<P>>(n,vector<P>{});

    map<char,int> mp;
    for(char c='A';c<='I';c++){
        mp[c]=c-'A';
    }


    //Aから
    G[mp['A']].emplace_back(mp['B'],10);//Bへコスト10
    G[mp['A']].emplace_back(mp['C'],20);//Cへコスト20
    G[mp['A']].emplace_back(mp['D'],12);//Dへコスト12
    G[mp['A']].emplace_back(mp['E'],15);//Eへコスト15

    //Bから
    G[mp['B']].emplace_back(mp['A'],10);//Aへコスト10
    G[mp['B']].emplace_back(mp['E'],10);//Eへコスト10
    
    //Cから
    G[mp['C']].emplace_back(mp['A'],20);//Aへコスト20
    G[mp['C']].emplace_back(mp['D'],10);//Dへコスト10
    G[mp['C']].emplace_back(mp['H'],30);//Hへコスト30
    G[mp['C']].emplace_back(mp['G'],20);//G
    G[mp['C']].emplace_back(mp['F'],25);//F

    //Dから
    G[mp['D']].emplace_back(mp['A'],12);//A
    G[mp['D']].emplace_back(mp['C'],10);//C
    G[mp['D']].emplace_back(mp['E'],15);//E
    G[mp['D']].emplace_back(mp['H'],20);//H

    //Eから
    G[mp['E']].emplace_back(mp['A'],15);//A
    G[mp['E']].emplace_back(mp['B'],10);//B
    G[mp['E']].emplace_back(mp['D'],15);//D
    G[mp['E']].emplace_back(mp['H'],15);//D
    G[mp['E']].emplace_back(mp['I'],18);//I

    //Fから
    G[mp['F']].emplace_back(mp['C'],25);
    G[mp['F']].emplace_back(mp['G'],5);

    //Gから
    G[mp['G']].emplace_back(mp['F'],5);
    G[mp['G']].emplace_back(mp['H'],35);
    G[mp['G']].emplace_back(mp['C'],20);

    //Hから
    G[mp['H']].emplace_back(mp['C'],30);
    G[mp['H']].emplace_back(mp['D'],20);
    G[mp['H']].emplace_back(mp['I'],12);
    G[mp['H']].emplace_back(mp['G'],35);
    G[mp['H']].emplace_back(mp['E'],15);

    //Iから
    G[mp['I']].emplace_back(mp['E'],18);
    G[mp['I']].emplace_back(mp['H'],12);


    int ans=INF;
    for(int start=0;start<n;start++){
        dp=vector<vector<int>>(1<<n,vector<int>(n,-1));
        
        ans=min(ans,rec(0,start,start));
    }

    cout<<ans<<endl;

}