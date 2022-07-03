/*
模範解答
*/
#include<iostream>
#include<vector>
using namespace std;
typedef pair<int,int> P;
const int INF=1<<30;


int main(){
    int T;
    cin>>T;

    for(int t=0;t<T;t++){
        int N;
        cin>>N;
        int l,w;
        vector<P> sticks(N);
        for(int i=0;i<N;i++){
            cin>>l>>w;
            sticks[i]=P{l,w};
        }
        sort(sticks.begin(),sticks.end());//lでソートする lが小さい順

        int ans=0;
        vector<int> lis(N);
        for(int i=0;i<N;i++){
            int ma=0,arg=-1;
            for(int j=0;j<i;j++){
                
                if(ma<lis[j] && lis[j]<=sticks[i].second){
                    ma=lis[j];
                    arg=j;
                }
            }

            if(arg<0) arg=ans;
            lis[arg]=sticks[i].second;
            ans=max(ans,arg+1);

        }

        cout<<ans<<endl;

    }


}