/*
模範解答
*/
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int ll;
const ll INF = 1LL << 60;

int N, a[2010], h[2010];
ll dp[2010][2010];

ll solve() {
    for(int i=0; i<N; i++) {
        fill(dp[i], dp[i] + N + 1, INF);
    }

    ll ret = INF;
    dp[0][0] = 0;
    for(int i=0; i<N; i++) {
        ll mi = INF;
        for(int j=0; j<N; j++) {
            mi = min(mi, dp[i][j]);
            dp[i+1][j] = mi + abs(a[i] - h[j]);
            if(i+1 == N) ret = min(ret, dp[i+1][j]);
        }
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%d", &a[i]);
        h[i] = a[i];
    }
    sort(h, h+N);

    ll ans = INF;
    ans = min(ans, solve());
    reverse(a, a+N);
    ans = min(ans, solve());
    printf("%lld\n", ans);
    return 0;
}