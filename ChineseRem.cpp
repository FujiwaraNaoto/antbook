//https://qiita.com/drken/items/ae02240cd1f8edfc86fd
//中国剰余定理

inline long long  mod(long long  a,long long m){
    return (a%m+m)%m;
}


long long  extGcd(long long  a,long long  b,long long& x,long long& y){
    long long  d=a;
    if(b!=0){
        d=extGcd(b,a%b,y,x);
        y-=(a/b)*x;
    }else{
        x=1;y=0;
    }

    return d;
}



// x ≡ bi (mod mi)
// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
std::pair<long long, long long> ChineseRem(const std::vector<long long> &b, const std::vector<long long> &m) {
  long long r = 0, M = 1;
  for (int i = 0; i < (int)b.size(); ++i) {
    long long p, q;
    long long d = extGcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
    if ((b[i] - r) % d != 0) return std::make_pair(0, -1);
    long long tmp = (b[i] - r) / d * p % (m[i]/d);
    r += M * tmp;
    M *= m[i]/d;
  }
  return std::make_pair(mod(r, M), M);
}
