
## 蟻本P202 ポテンシャルのお話

始点を頂点$s$とした時に数式に落とし込むと,以下のような定義になる.

$d_{s}=0$とする.
全ての辺$(i,j)$において$d_{i}+dist(i,j) \geq d_{j}$が成立する時,$d_{i}$のそれぞれ取れる最大値.

## ポテンシャル

ある$p_{i}$を用意する(これがのちのポテンシャルとなる).距離を

$dist'(i,j)=dist(i,j)+p_{i}-p{j}$

とした際のグラフを考える.

長さ$dist'$のグラフで頂点$s$を視点とした最短距離を計算して,$d'_{i}$を求めたとする.
この時，当然$d'_{s}=0$となる.
この際,以下の等式が成り立つ.

$d'_{i} +dist'(i,j) \geq d'_{j}$

これより,以下変形

$d'_{i} +dist'(i,j) +p_{i}-p_{j} \geq d'_{j}$

$d'_{i} + p_{i} + dist'(i,j) \geq d'_{j}+p_{j}$

ここで$ans_{i} = d'_{i}+p_{i}$とすると最短距離の定義を満たしている.しかし,このとき,

$ans_{s}=d'_{s}+p_{s}=p_{s}$

であるから$ans_{s}=0$を満たさない．

そこで,全ての頂点$i$について

$ans_{i}=d'_{i}+p_{i}-p_{s}$を計算すると

$ans_{s}=d'_{s}+p_{s}-p_{s}=d'_{s}=0$

であり,$ans$は最短経路を示すことになる.

また,上記で定義された新しい辺の距離$dist'_{i}$でダイクストラ法を用いたいため,$dist'_{i}$が$0$以上であることが必須

$dist'(i,j)=dist(i,j)+p_{i}-p{j} \geq 0$

ここから

$dist(i,j)+p_{i} \geq p{j}$

であり,$p_{i}$は最短経路の定義そのままとなる.
以上より,最短距離を求めて,それを$p$とし,辺の距離$dist$を更新していく.