/*
POJ2385
AC

dp[time][w][which tree] = timeの時に 現在までの移動回数がw どちらの木(0 or 1)にいるか
その時のりんごの個数のmax
*/
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<cstdio>
using namespace std;
int main(){
    int T,W;
    cin>>T>>W;
    vector<int> apple(T);
    for(int i=0;i<T;i++){
        cin>>apple[i];
        apple[i]--;//木0からに補正する
    }
    vector<vector<vector<int>>> dp(T+1,vector<vector<int>>(W+1,vector<int>(2,0)));
    
    //最初は木0から始める

    for(int t=0;t<T;t++){

        for(int w=0;w<=W;w++){
           
            dp[t+1][w][0]=max(dp[t][w][0]+(apple[t]==0?1:0), dp[t+1][w][0]);//0にとどまる場合
            dp[t+1][w][1]=max(dp[t][w][1]+(apple[t]==1?1:0), dp[t+1][w][1]);

            if(0<=w-1){
                dp[t+1][w][0]=max(dp[t][w-1][1]+(apple[t]==0?1:0), dp[t+1][w][0]);//1から0へ移動する場合
                dp[t+1][w][1]=max(dp[t][w-1][0]+(apple[t]==1?1:0), dp[t+1][w][1]);//0から1へ移動する場合
            
            }

        }
    }

    int ans=0;
    for(int w=0;w<=W;w++){
        for(int j=0;j<=1;j++){
            //cout<<"dp[T]["<<w<<"]["<<j<<"]="<<dp[T][w][j]<<",";
            ans=max(ans,dp[T][w][j]);
        }
        //cout<<endl;
    }
    cout<<ans<<endl;


}

