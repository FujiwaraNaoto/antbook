/*
AC
warshal floyd
*/
#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
//#include<tuple>//-std=c++11
#include<cmath>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int INF=1<<29;


struct edge{
    int to;
    int cost;
};

int main(){

    

    while(true){
        int n;
        cin>>n;
        if(n==0)break;
        vector<int> a(n),b(n),c(n);
        
        int maxCity=-1;
        for(int i=0;i<n;i++){
            cin>>a[i]>>b[i]>>c[i];
            maxCity=max(maxCity,a[i]);
            maxCity=max(maxCity,b[i]);
        }

        //c++11
        vector<vector<int> > dp(maxCity+1,vector<int>(maxCity+1,INF));
        for(int i=0;i<=maxCity;i++){
            dp[i][i]=0;
        }
        for(int i=0;i<n;i++){
            dp[a[i]][b[i]]=min(dp[a[i]][b[i]],c[i]);
            dp[b[i]][a[i]]=min(dp[b[i]][a[i]],c[i]);            
        }


        for(int k=0;k<=maxCity;k++){
            for(int u=0;u<=maxCity;u++){
                for(int v=0;v<=maxCity;v++){
                    if(dp[u][k]!=INF && dp[k][v]!=INF){
                        dp[u][v]=min(dp[u][v],dp[u][k]+dp[k][v]);
                    }
                }
            }
        }

        
        int ansCity=-1;
        int ansSum=INF;
        for(int start=0;start<=maxCity;start++){
            int tmpSum=0;
            for(int to=0;to<=maxCity;to++){
                
                tmpSum+=dp[start][to];
            }

            if(ansSum>tmpSum){
                ansSum=tmpSum;
                ansCity=start;
            }

        }

        

        //cout<<"ansCity="<<ansCity<<' '<<ansSum<<endl;
        cout<<ansCity<<' '<<ansSum<<endl;





    }

}