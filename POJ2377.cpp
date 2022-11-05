/*
無名関数とnumericが使用できない
AC

コスト最大なので,－をつけて処理すると最小の議論が使える
*/
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
//#include<numeric>
using namespace std;
typedef long long ll;
const ll INF=1LL<<60;

struct edge{
    int u;
    int v;
    ll cost;
};

class UnionFind{

public:
    std::vector<int> par;
    std::vector<int> rank;
    std::vector<int> sz;//sz[i]で,頂点iが含まれているグループのサイズ


    UnionFind(int size){
        rank=std::vector<int>(size+1,0);
        
        par = std::vector<int>(size+1,0);
        //iota(par.begin(),par.end(),0);//#include<numeric>
        for(int i=0;i<=size;i++){
            par[i]=i;
        }
        sz = std::vector<int>(size+1,1);
    }  

    

    ~UnionFind(){
        std::vector<int>().swap(rank);
        std::vector<int>().swap(par);
        std::vector<int>().swap(sz);
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

        if(rank[u]>rank[v]){
            par[v]=u;
            //uの傘下へvが入る
            sz[u]+=sz[v];

        }else{
            par[u]=v;
            //vの傘下へuが入る
            sz[v]+=sz[u];
            if(rank[u]==rank[v]) rank[v]++;
        }
    }

    int size(int u){//頂点uが属すグループの大きさを表す.
        u=find(u);
        return sz[u];
    }
};


bool comp(const edge &lhs,const edge &rhs){
    return lhs.cost<rhs.cost;
}


int main(){
    int N,M;
    cin>>N>>M;
    UnionFind uf(N);
    vector<edge> edges;
    int u,v;
    ll cost;
    for(int i=2;i<=M+1;i++){
        cin>>u>>v>>cost;
        u--;v--;
        edges.push_back((edge){u,v,-cost});//コストが大きい程,値が小さい
    }
    /*
    sort(edges.begin(),edges.end(),
    [](const edge &lhs,const edge &rhs){
        return lhs.length<rhs.length;
    });
    */

   sort(edges.begin(),edges.end(),comp);

    ll ans=0;
    for(int i=0;i<M;i++){
        edge e = edges[i];
        if(!uf.issame(e.u,e.v)){
            uf.merge(e.u,e.v);
            ans+=(-1)*e.cost;
        }
    }
    bool flag=true;
    for(int v=1;v<N;v++){
        //0とvが同じ連結成分でない場合
        if(!uf.issame(0,v))flag=false;
    }

    cout<<(flag ? ans:-1)<<endl;
}