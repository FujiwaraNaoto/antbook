
#include<iostream>
#include<vector>
using namespace std;
const int INF = 1<<30;

int main(){
    int N = 5;
    vector<vector<int>> dist(N,vector<int>(N,INF));
    //for(int v=0;v<N;v++)dist[v][v]=0;

    dist[0][1]=3;//0から1へ3
    dist[1][2]=5;
    dist[2][0]=4;
    dist[4][1]=6;
    dist[4][0]=7;
    dist[3][4]=3;
    dist[2][3]=5;
    dist[0][3]=4;

    vector<vector<int>> dp(1<<N,vector<int>(N,INF));
    /*
    dp[S][v]= 訪れた頂点集合S,今いる頂点をvとする
    本とは異なり,dp[(1<<n)-1][0]を正解とする
    なので. ループを逆にする
    */   
    dp[0][0]=0;//まだどこに訪れていないので
    
    for(int S=0;S<(1<<N);S++){
        for(int u=0;u<N;u++){
            for(int v=0;v<N;v++){
                if(dist[u][v]==INF) continue;
                //Sの中にvがない
                if(((S>>v)&1)==1){
                //uからvへ            
                    dp[S][v] = min(dp[S][v],dp[S^(1<<v)][u]+dist[u][v]);
                }
                    
            }
        }
    }
    

    for(int S=0;S<(1<<N);S++){
        for(int v=0;v<N;v++){
            cout<<"dp["<<S<<"]["<<v<<"]="<<dp[S][v];
        }
        cout<<endl;
    }

    cout<<dp[(1<<N)-1][0]<<endl;


    /*
    //これは成功 
    dp[(1<<N)-1][0]=0;
   
    for(int S=(1<<N)-2;S>=0;S--){
        for(int v=0;v<N;v++){
            for(int u=0;u<N;u++){
                if( !((S>>u)&1) ){
                if(dist[v][u]!=INF){
                    
                    //今いるからvへ移動.
                    dp[S][v] = min(dp[S][v],dp[S|(1<<u)][u]+dist[v][u]);//逆向きにしている
                    }
                }
            }
        }
    }


    for(int S=0;S<(1<<N);S++){
        for(int v=0;v<N;v++){
            cout<<"dp["<<S<<"]["<<v<<"]="<<dp[S][v];
        }
        cout<<endl;
    }

    cout<<dp[0][0]<<endl;
    */

}