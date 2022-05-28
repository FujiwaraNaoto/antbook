<!--
https://qiita.com/tanabe13f/items/6c723c29a121de760790

https://zenn.dev/masutech/articles/compro-cowgame-theory
-->
## この問題が双対問題となる理由

数直線上に$N$個の点$d_{i}(i=1,2,3,...,N)$を順番に配置することを考える.

以下の制約がある.

- 1. $d_{i} \leq d_{i+1} (i=1,2,..,N-1)$
- $(u,v,c)$,ただし$ u < v$で表現される以下の$M$個の制約条件
- 2. $d_{v}-d{u} \leq c$

- $(u,v,c)$,ただし$ u < v$で表現される以下の$L$個の制約条件
- 3. $d_{v}-d{u} \geq c$

$d_{N}-d_{1}$を最大化せよ.

　不等式1ついては $d_{i} - d_{i+1} \leq 0$
と変形できる.
ここから.1.2.3は

$d_{v_{i}} - d_{u_{i}} \leq c_{i}$ $(i=1,2,...,N+M+L)$
と一般化できる.

$M \coloneqq N+M+L$と置き直し,
- ${\bf{d}} \coloneqq (d_{1},d_{2},..,d_{N-1},d_{N})^T \in {\bf{R}}^N$

- ${\bf{b}} \coloneqq (-1,0,..,0,1)^T \in {\bf{R}}^N$

- ${\bf{c}} \coloneqq (c_{1},c_{2},..,c_{M-1},c_{M})^T \in {\bf{R}}^M$


最後に,行列${\bf{A}} \in {\bf{R}}^{M \times N}$を以下のように定義する.

$a_{i,j}=1 (if 　v_{i}=j)$　

$a_{i,j}=-1 (if　 u_{i}=j)$

$a_{i,j}=0  (otherwise 　0)$

従って,以下の問題に落とし込める.

maximize ${\bf{b}}^T {\bf{d}}$

subject to ${\bf{A}} {\bf{d}} \leq   {\bf{c}}$



## 証明

$G$に不閉路がある場合,制約を満たす解はない

理由:

$i_{0} \rightarrow　i_{1} \rightarrow i_{2}\rightarrow　... \rightarrow　i_{k} \rightarrow i_{0}$の距離合計が$c<0$とする.この時 解として $a_{i}$ $(i \in V)$が存在すると仮定すると

$ a_{i_{j+1}} - a_{i_{j}} \leq c_{i_{j},i_{j+1}}$

が成立する.
それぞれの右辺と左辺を$j=0,1,2,...,k$で足し合わせると
$0 \leq c$
となり,矛盾


