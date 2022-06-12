# エラトステネスの篩


pを固定するとfor文がn回実行される.iはたかだか $\lfloor \frac{K}{p^n} \rfloor$回であるから
計算量 $\sum_{n=1}^\infty \frac{K}{p^n} = \frac{K}{p-1}$

$p$が$K$以下の素数全体を動く時,計算量 $\sum_{p\le K\le p_{prime}}\frac{K}{p-1} = \mathcal{O(KloglogK)}$