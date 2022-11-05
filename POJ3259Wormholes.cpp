//AC
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const ll INF=1LL<<60;


struct Edge{
    int from;
    int to;
    ll t;
};

int main(){
    int N;//n fields
    int M;//path
    int W;// the number of wholes

    int F;
    cin>>F;
    
    int S,E;
    ll T;

    for(int f=0;f<F;f++){
        cin>>N>>M>>W;

        vector<Edge> Edges; 
        for(int i=2;i<=M+1;i++){
            cin>>S>>E>>T;
            S--;E--;
            
            Edges.push_back((Edge){S,E,T});
            Edges.push_back((Edge){E,S,T});
            

        }
     
        for(int i=M+2;i<=M+W+1;i++){
            cin>>S>>E>>T;
            S--;E--;          
            Edges.push_back((Edge){S,E,-T});
        }

            bool isCycle=false;
            vector<ll> dp(N,INF);
            dp[0]=0;
            int cnt=0;
            bool isUpdate=true;
            while(isUpdate){
                isUpdate=false;

                //for(Edge e:Edges){
                for(int i=0;i<(int)Edges.size();i++){
                    Edge e = Edges[i];
                    if(dp[e.from]!=INF && dp[e.to]>(dp[e.from]+e.t)){
                        dp[e.to]=(dp[e.from]+e.t);
                        isUpdate=true;
                    }
                }

                if(!isUpdate)break;

                if(cnt>=N){
                    isCycle=true;
                    break; }
                else{
                    cnt++;
                }

            }

            if(isCycle){
                //startから出発すると時間を戻せる.
                cout<<"YES"<<endl;
            }else{
                cout<<"NO"<<endl;
            }


    }//for f



    
}