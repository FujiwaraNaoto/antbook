#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>


//継承を用いたパターン
class SCC{

    public:
    
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
            cmp[v]=k;//のちのクラスでcmpを仕様するので
            //group[k].push_back(v);
            for(int to:rG[v]){
                if(!used[to]){
                    rdfs(to,k);
                }
            }
        }

    //public:
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
            std::vector<bool>().swap(used);
            sccgroup = std::vector<std::vector<int>>(k,std::vector<int>{});
            for(int v=0;v<V;v++){//全ての頂点を一つずつみていく
                //頂点v
                sccgroup[cmp[v]].push_back(v);//
            }
            return k;
        }

};
/*
まず基本クラスのコンストラクタ 次に 派生クラスのコンストラクタ
*/


//protected派生
//SCCでのpublicはこちらではprotectedになる
class TwoSAT: protected SCC{
    
    public:
        
        int N;//見掛け状の頂点数 SCCではこの2倍の数の頂点がある

        TwoSAT(int v_):SCC(2*v_),N(v_){
            //2倍の数の頂点が必要
            //SCC scc(2*v);
            //constructor 
           
        }


        bool istrue(){
            //全体が真になるかどうか
            for(int i=0;i<N;i++){
                if(cmp[i]==cmp[N+i]){
                    return false;
                }
            }
            return true;
        }

        std::vector<bool> whichtrue(){

            std::vector<bool> ret(N);
            
            for(int i=0;i<N;i++){
                ret[i]=cmp[i]>cmp[N+i];
                
            }
            return ret;
        }

    using SCC::add_edge;//権限をprotectedからpublicへ移行
    using SCC::scc;
    using SCC::cmp;//一応.
};




using namespace std;



int main(){
    int N=2;
    vector<int> S(N),T(N),D(N);
    S={60*8+0*60,60*8+15};
    T={60*9+0*60,60*9+0*60};
    D={30,20};

    TwoSAT twosat(N);

    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            if(min(S[i]+D[i],S[j]+D[j])>max(S[i],S[j])){
                twosat.add_edge(i,N+j);
                twosat.add_edge(j,N+i);
                
            }

            if(min(S[i]+D[i],T[j])>max(S[i],T[j]-D[j])){
                twosat.add_edge(i,j);
                twosat.add_edge(N+j,N+i);
            }

            if(min(T[i],S[j]+D[j])>max(T[i]-D[i],S[j])){
                twosat.add_edge(N+i,N+j);
                twosat.add_edge(j,i);
            }

            if(min(T[i],T[j])>max(T[i]-D[i],T[j]-D[j])){
                twosat.add_edge(N+i,j);
                twosat.add_edge(N+j,i);
            }


        }
    }

    twosat.scc();
    
    
    cout<<(twosat.istrue()?"Yes":"No")<<endl;
    auto ret = twosat.whichtrue();
    for(int i=0;i<N;i++){
        if(ret[i]){
            printf("%02d:%02d %02d:%02d\n",S[i]/60,S[i]%60,(S[i]+D[i])/60,(S[i]+D[i])%60);
        }else{
            printf("%02d:%02d %02d:%02d\n",(T[i]-D[i])/60,(T[i]-D[i])%60,T[i]/60,T[i]%60);
            
        }
    } 

    /*
    for(int i=0;i<N;i++){
        if(twosat.cmp[i]==twosat.cmp[N+i]){
            cout<<"No"<<endl;
            return 0;
        }
    }

    //従属な場合
    cout<<"Yes"<<endl;

    for(int i=0;i<N;i++){
        if(twosat.cmp[i]>twosat.cmp[N+i]){
            printf("%02d:%02d %02d:%02d\n",S[i]/60,S[i]%60,(S[i]+D[i])/60,(S[i]+D[i])%60);
        }else{
            printf("%02d:%02d %02d:%02d\n",(T[i]-D[i])/60,(T[i]-D[i])%60,T[i]/60,T[i]%60);
            
        }
    } 
    */


}
