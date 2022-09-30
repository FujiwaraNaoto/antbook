/*
順列で解く.
137
A B E I H G F C D

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
#include<set>
#include<numeric>
#include<algorithm>
using namespace std;
typedef pair<int,int> P;
vector<vector<P>> G;
const int INF=1<<30;

int main(){
    int n;
    n=9;
    G=vector<vector<P>>(n,vector<P>{});

    map<char,int> mp;
    map<int,char> mp_rev;
    vector<int> order(n);
    iota(order.begin(),order.end(),0);
    /*
    for(int x:order){
        cout<<x<<' ';
    }
    cout<<endl;
    */

    vector<vector<int>> graph(n,vector<int>(n,INF));

    for(char c='A';c<='I';c++){
        mp[c]=c-'A';
        mp_rev[(int)(c-'A')]=c;
        graph[c-'A'][c-'A']=0;
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


    for(int now=0;now<n;now++){
        for(auto [to,v]:G[now]){
            graph[now][to]=v;//nowからtoへvの値
        }
    }

    int ans=INF;
    vector<int> path;

    sort(order.begin(),order.end());//すでにソートされてるから必要ないけど
    do{
        vector<int> tmp_path;
        int path_weight=0;
        set<int> st;
        bool flag=true;
        
        for(int i=0;i<n;i++){
                
            int now = order[i];
            st.insert(now);//頂点nowをいれる
            tmp_path.push_back(now);
            int next = order[(i+1)%n];
            //nowからnextがinfの道でない.かつ i!=n-1のときにnextをまだ訪れていない場合
            if(graph[now][next]==INF || ((i+1)%n!=0 && st.count(next)) ){
                flag=false;
            }else{
                //頂点nowから頂点nextへ
                path_weight+=graph[now][next];
            }
        }

        if(flag && ans>path_weight){
            path=tmp_path;
            ans=path_weight;

        }


        //cout<<"*"<<endl;
    }while(next_permutation(order.begin(),order.end()));




    if(!path.empty()){
        cout<<ans<<endl;
        
        for(int v:path){
            cout<<mp_rev[v]<<' ';
        }
        cout<<endl;
        
        
    }else{
        cout<<"No such path"<<endl;
    }




}