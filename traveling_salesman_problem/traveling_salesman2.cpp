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
vector<vector<P>> G;
const int INF=1<<30;

int main(){
    int n;
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

        vector<vector<int>> dp((1<<n),vector<int>(n,INF));
        dp[(1<<n)-1][start]=0;//startから始める

        for(int S=(1<<n)-2;S>=0;S--){
            for(int v=0;v<n;v++){
                    for(auto [u,c]:G[v]){//uからvへ コストc
                        if(((S>>u)&1)==0){//S
                            dp[S][v]=min(dp[S][v],dp[S|(1<<u)][u]+c);
                        }
                    }
                    
                }
            }

        ans=min(ans,dp[0][start]);
    }

    cout<<ans<<endl;

}