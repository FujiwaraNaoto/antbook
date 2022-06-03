/*
P 39 40

vectorを用いた場合
*/
#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;

int main(){
    int N;
    vector<int>order(N);

    //0から連番になるようにする
    iota(order.begin(),order.end(),0);

    do{
        /*
        perm2に対する操作
        */
    }while(next_permutation(order.begin(),order.end()));

    return 0;
}