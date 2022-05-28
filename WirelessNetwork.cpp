/*
AC
c++17以降の機能が POJでは使えないみたい
iota  auto [] = など
*/
#include<iostream>
#include<map>
//#include<numeric>
#include<vector>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;


class UnionFind{

public:
    vector<int> par;
    vector<int> rank;

/*
    UnionFind(int size){
        rank=vector<int>(size+1,0);
        
        for(int i=0;i<=size;i++){
            par.push_back(i);
        }
    }  
*/
    UnionFind(int size){
        rank=vector<int>(size+1,0);
        
        par = vector<int>(size+1,0);
        //iota(par.begin(),par.end(),0);//#include<numeric>
        for(int i=0;i<=size;i++) par[i]=i;
    }  

    int find(int x){
        if(par[x]==x)return x;
        else return par[x] = find(par[x]);
    }

    bool issame(int u,int v){
        return find(u)==find(v);
    }


    void merge(int u,int v){
        u = find(u);
        v = find(v);
        if(u==v) return;
        
        if(rank[u]>rank[v]) par[v]=u;
        else{
            par[u]=v;
            if(rank[u]==rank[v]) rank[v]++;
        }
    }


};



int main(){
    int N;
    ll D;
    cin>>N>>D;
    UnionFind uf(N);
    vector<P> position(N);
   
    for(int i=0;i<N;i++){
        int x,y;
        cin>>x>>y;
        //position[i]=P{x,y};
        position[i].first=x;
        position[i].second=y;
    }

    vector<bool> is_operation(N,false);
    char c;int p,u,v;
    
    while(cin>>c){

       
        if(c=='O'){
            cin>>p;
            p--;//0からに補正
            is_operation[p]=true;

            //auto [px,py]=position[p];
            int px = position[p].first;
            int py = position[p].second;

            for(int i=0;i<N;i++){
                if(i==p)continue;
                if(!is_operation[i])continue;
                //auto [ix,iy] =  position[i];
                int ix = position[i].first;
                int iy = position[i].second;
                ll sqr = 1LL*(ix-px)*(ix-px) +  1LL*(iy-py)*(iy-py);
                if(sqr<=D*D){
                    uf.merge(i,p);
                }
            }
        }
        else{
            //c==S
            
            cin>>u>>v;
            u--;v--;
            cout<<(uf.issame(u,v)?"SUCCESS":"FAIL")<<endl;
        }

    }



}