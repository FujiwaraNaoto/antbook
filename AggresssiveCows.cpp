/*
蟻本 P131
*/
#include<iostream>
#include<vector>
using namespace std;
const int INF = 1<<30;

int N,M;
vector<int> x;

//distance
int C(int dis){
    int posx=x[0];
    int idx=1;
    int cnt=1;//すでに0番の小屋に牛を一頭入れているので
    while(idx<N){
        if((x[idx]-posx)>=dis){
            posx=x[idx];
            cnt++;//x[idx]に牛を入れる
        }
        idx++;
    }

    return cnt;

}


int main(){
    
    cin>>N>>M;
    x=vector<int>(N);
    for(int i=0;i<N;i++)cin>>x[i];
    sort(x.begin(),x.end());

    /*
    lbの時は必ず成立
    */
    int lb=0,ub=INF;
    while((ub-lb)>1){
        int mid = (ub+lb)/2;
        //最短距離midをとることが出来るか否か
        if(C(mid)>=M){
            //等号成立の際はまだ距離を延ばせるため
            lb=mid;//距離の下限を上げてみる
        }else{
            ub=mid;
        }
    }

    cout<<lb<<endl;


}