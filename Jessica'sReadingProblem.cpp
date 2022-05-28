/*
蟻本 P137
尺取り法

*/
#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
const int INF = 1<<30;

int main(){
    int P;
    cin>>P;
    vector<int>book(P);
    set<int> kind;
    for(int i=0;i<P;i++){
        cin>>book[i];
        kind.insert(book[i]);
    }

    int num_kind=kind.size();
    
    int l=0,r=0;
    //[l,r)
    set<int> st;
    map<int,int> mp;
    int ans = INF;
    while(l<P){

        //端に到達していない かつ　内容の種類数がnum_kind未満
        while(r<P && st.size()<num_kind){
            
            if(st.find(book[r])==st.end()){
                //新種だった場合
                st.insert(book[r]);
                mp[book[r]]++;
            }else{
                mp[book[r]]++;
            }
            r++;
        }

        //[l,r)
        if(st.size()==num_kind){//種類が揃っている時のみカウントする
            ans = min(r-l,ans);
        }

        mp[book[l]]--;
        if(mp[book[l]]==0){
            //[l+1,r)の範囲の中でbook[l]が存在しなくなるので
            st.erase(book[l]);
        }
        l++;
    }

    cout<<ans<<endl;

}