/*
蟻本P300
*/
#include<iostream>
#include<map>
#include<numeric>
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>
#include<set>
#include<deque>
using namespace std;
typedef long long ll;

int main(){
    int N=5;
    int K=3;
    vector<int> a={1,3,5,4,2};
    //vector<int> a={1,3,4,4,24,3,5,32,32,5,4,5,2,43,32,54,32,53,32,52,53,42,66};
    N=a.size();

    {
        //o(N*logK)

    multiset<int> mst;
    vector<int> ans;
    for(int i=0;i<K;i++){
        mst.insert(a[i]);
    }
    auto it=mst.begin();
    ans.push_back(*it);

    for(int i=1;i+K<=N;i++){
        mst.erase(mst.find(a[i-1]));
        mst.insert(a[i+K-1]);
        auto it=mst.begin();
        ans.push_back(*it);
    }

    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<(i==ans.size()-1?'\n':' ');
    }

    }

    {
        vector<int> ans;
        deque<int> deq;

        for(int i=0;i<N;i++){
                //j=deq.empty()
            while( !deq.empty() &&  a[deq.back()]>=a[i]){
                deq.pop_back();
            }
            deq.push_back(i);
            
            if(i-K+1>=0){
                ans.push_back(a[deq.front()]);
                
                if(deq.front()==i-K+1){
                
                    deq.pop_front();
                }

            }
            
        }


        for(int i=0;i<ans.size();i++){
            cout<<ans[i]<<(i==ans.size()-1?'\n':' ');
        }

    }

    {
        vector<int> ans;
        deque<int> deq;

        for(int i=0;i<K;i++){
            //j=deq.empty()
            while( !deq.empty() &&  a[deq.back()]>=a[i]){
                deq.pop_back();
            }
            deq.push_back(i);
            
        }

        ans.push_back(a[deq.front()]);

        for(int i=K;i<N;i++){

            while( !deq.empty() &&  a[deq.back()]>=a[i]){
                deq.pop_back();
            }
            deq.push_back(i);

            
            
                
            if(deq.front()==i-K){
            
                deq.pop_front();
            }
            ans.push_back(a[deq.front()]);

           

        }


        for(int i=0;i<ans.size();i++){
            cout<<ans[i]<<(i==ans.size()-1?'\n':' ');
        }




    }








}

