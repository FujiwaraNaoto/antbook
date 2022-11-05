//AC
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
class DisjointSet {
  private:
    vector<int> parent;
  
     int root(int x)
     {
       if (parent[x] < 0) {
         return x;
       } else {
         parent[x] = root(parent[x]);
         return parent[x];
       }
    }
 
   public:
     DisjointSet(int size) : parent(size, -1) {}
 
     bool unite(int x, int y)
     {
       const int a = root(x);
       const int b = root(y);
       if (a != b) {
         if (parent[a] < parent[b]) {
           parent[a] += parent[b];
           parent[b] = a;
         } else {
           parent[b] += parent[a];
           parent[a] = b;
         }
         return true;
       } else {
         return false;
       }
     }
 
     bool find(int x, int y)
     {
       return root(x) == root(y);
     }
 
    int size(int x)
     {
       return -parent[root(x)];
     }
 };
 
 struct Edge {
   int from, to, weight;
   Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
   
   bool operator<(const Edge& e) const
   {
     return weight > e.weight;
   }
 };
 
 int kruskal(priority_queue<Edge> edges, const int N)
 {
   DisjointSet s(N);
   int ttl = 0;
   while (s.size(0) < N) {
     const Edge e = edges.top();
     edges.pop();
     if (s.unite(e.from, e.to)) {
       ttl += e.weight;
     }
   }
   return ttl;
 }
 
 int main(void)
 {
   int N;
  while (cin >> N) {
     priority_queue<Edge> edges;
     for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++) {
         int w;
         cin >> w;
         edges.push(Edge(i, j, w));
       }
     }
     cout << kruskal(edges, N) << endl;
   }
 }


 //NG
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
    int N;
    cin>>N;
    //ll dist[105][105];
    ll cst;
    //vector<vector<ll> > dist(N,vector<ll>(N));
    vector<edge> edges;
    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            cin>>cst;
            edges.push_back((edge){y,x,cst});
            
        }
    }
    
   

    sort(edges.begin(),edges.end(),comp);
    UnionFind uf(N);
    ll ans=0;
    for(int i=0;i<(int)edges.size();i++){
        edge e = edges[i];
        if(!uf.issame(e.u,e.v)){
            uf.merge(e.u,e.v);
            ans+=e.cost;
        }
    }

    cout<<ans<<endl;


}