/*
模範解答
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_DIGIT = 100;
struct BigInt {
    typedef long long int ll;
    static const ll BASE = 1e17;
    vector<ll> buf;
    BigInt() {}
    BigInt(ll x) {
        //位が低いところから詰めていく
        for(; x; x/=BASE) buf.push_back(x%BASE);
    }

    BigInt& operator+=(const BigInt &x) {
        if(buf.size() < x.buf.size()) buf.resize(x.buf.size());
        ll tmp = 0LL;
        for(int i=0; i<buf.size(); i++) {
            //くりあがり分がtmp
            buf[i] += (i < x.buf.size() ? x.buf[i] : 0) + tmp;
            tmp = buf[i] / BASE;
            buf[i] %= BASE;
        }

        if(tmp) buf.push_back(tmp);
        return *this;
    }

    void print() {
        int S = (int)buf.size() - 1;
        for(int i=S; i>=0; i--) {
            if(i == S) printf("%lld", buf[i]);
            else printf("%016lld", buf[i]);
        }
        printf("\n");
    }
};

int N, K;

int main() {
    scanf("%d%d", &N, &K);

    vector<BigInt> dp(N+1, 0LL);
    dp[0] += BigInt(1LL);
    /*
    for(int c=1; c<=K; c++) {
        for(int i=c; i<=N; i++) {
            dp[i] += dp[i-c];
        }
    }
    */
   
   //配るDP
    for(int c=1; c<=K; c++) {
        for(int i=0; i+c<=N; i++) {
            dp[i+c] += dp[i];
        }

    }




    dp[N].print();
    return 0;
}