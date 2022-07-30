#include<iostream>
#include<vector>
#include<algorithm>


class SCC{

    //後の頂点であればあるほど,強連結成分の番号が小さい
    private:
        //SCC
        int V,M;//頂点と辺数
        std::vector<std::vector<int>> G,rG;
        std::vector<bool> used;
        std::vector<int> cmp;
        std::vector<int> vs;
        std::vector<std::vector<int>> group;


        void dfs(int v){
            used[v]=true;
            for(int to:G[v]){

                if(!used[to]){
                    dfs(to);
                }
            }
            vs.push_back(v);

        }

        void rdfs(int v,int k){
            used[v]=true;
            cmp[v]=k;
            //group[k].push_back(v);
            for(int to:rG[v]){
                if(!used[to]){
                    rdfs(to,k);
                }
            }
        }

    public:

        //constructor
        //頂点数0~nのNこ
        //辺数 m個
        SCC(int v,int m):V(v),M(m){
            G = std::vector<std::vector<int>>(V,std::vector<int>{});
            rG = std::vector<std::vector<int>>(V,std::vector<int>{});
            cmp = std::vector<int>(V,0);//グループ
        }

        SCC(int v):V(v){
            G = std::vector<std::vector<int>>(V,std::vector<int>{});
            rG = std::vector<std::vector<int>>(V,std::vector<int>{});
            cmp = std::vector<int>(V,0);//グループ
        }

        ~SCC(){
            
            std::vector<std::vector<int>>().swap(G);
            std::vector<std::vector<int>>().swap(rG);
            std::vector<int>().swap(cmp);
        }

        void add_edge(int from,int to){
            G[from].push_back(to);
            rG[to].push_back(from);
        }

        std::vector<std::vector<int>> sccgroup;//scc[k]でグループkに属している頂点たち

        int scc(){
            
            used = std::vector<bool>(V,false);

            vs.clear();
            for(int v=0;v<V;v++){
                if(!used[v]) dfs(v);
            }
            std::vector<bool>().swap(used);
            used = std::vector<bool>(V,false);
            int k=0;
            
            reverse(vs.begin(),vs.end());
        
        
            for(int to:vs){
                if(!used[to]) rdfs(to,k++);//rdfsが終わった後でインクリメント
            }

            sccgroup = std::vector<std::vector<int>>(k,std::vector<int>{});
            for(int v=0;v<V;v++){//全ての頂点を一つずつみていく
                //頂点v
                sccgroup[cmp[v]].push_back(v);//
            }
            std::vector<bool>().swap(used);

            return k;
        }

};



using namespace std;


int main(){
    int N=3;
    int M=3;
    vector<int> A={1,2,2},B={2,1,3};

    SCC scc(N,M);//頂点数
    for(int i=0;i<M;i++){
        scc.add_edge(A[i]-1,B[i]-1);//A[i]からB[i]へ辺を張る    
    }

    int num_group = scc.scc();//できるグループ数
    //cout<<"num_group="<<num_group<<endl;
    
    cout<<scc.sccgroup[num_group-1].size()<<endl;
    



}
