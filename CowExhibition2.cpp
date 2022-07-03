/*
dp[i][TS]=FS
失敗
*/
#include<iostream>
#include<vector>
using namespace std;
typedef pair<int,int> P;
const int INF=1<<30;
const int MAX=100000+1000;

int main(){
    int N;
    cin>>N;
    vector<P> cows(N);
    vector<int> S(N),F(N);
    int si,fi;
    for(int i=0;i<N;i++){
        cin>>si>>fi;
        cows[i]=P{si,fi};
        //cin>>S[i]>>F[i];

    }
    sort(cows.begin(),cows.end(),
    [](const P& lhs,const P& rhs){
        return lhs.first>rhs.first;
    });

    vector<vector<int>> dp(N+1,vector<int>(MAX+1,-INF));
    
    //for(int i=0;i<=MAX;i++) dp[0][i]=0;
    for(int i=0;i<=N;i++) dp[i][0]=0;
    
    int ans=0;
    for(int i=0;i<N;i++){
        //auto [si,fi]=cows[i];
        int si=cows[i].first;
        int fi=cows[i].second;
        if(si>=0){
            for(int TS=0;TS+si<=MAX;TS++){
                
                if( (TS+si)>=0 && dp[i][TS]!=-INF){
                    dp[i+1][TS+si]=max(dp[i][TS+si],dp[i][TS]+fi);
                }else{
                    dp[i+1][TS+si]=dp[i][TS+si];
                }
            }        

        }else{//si<0

            for(int TS=0;TS+si<=MAX;TS++){
                
                if( (TS+si)>=0 && dp[i][TS]!=-INF){
                    dp[i+1][TS+si]=max(dp[i][TS+si],dp[i][TS]+fi);
                }      
            }
        }
        
        for(int TS=0;TS+si<=MAX;TS++){
            if(dp[i+1][TS]>=0) ans=max(ans,TS + dp[i+1][TS]);
        }
      
    }    
    /*
    
      for(int TS=0;TS<=MAX;TS++){
            if(dp[N][TS]>=0) ans=max(ans,TS + dp[N][TS]);
        }
*/
    cout<<ans<<endl;
    

    



}