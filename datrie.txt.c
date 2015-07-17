--------- original thought ---------
a: 0, b: 1
(0~3 q)(-1~-4 tail pos)
 0  0  0  0   b
-1 -2 -3  0   0~3 (-1~-4 not used)
(0~3 c)(-1~-4 next)
--------- improved thought ---------
c:(0~3 base)(-1~-4 tail pos i)
c:(0~3 prev)(-1~-4 not used)
 v-- 0~3 base (-1~-4 not used)
 0  3  1  2
-1 -2 -3 -1
 ^-- -1~-3 next (0 none)(1~3 not used)
(0~3 src)(-1~-4 next)
 0  0  0  0 (tail indices)
l: 0~2^7(the length of double array of char - 1)
-------------- rule ----------------
if c[0] == -4   => no space
if c[i:1~3] < 0 => c[i] == empty
---- kmp ----
a: 1 3 5   => 2 2   (tail)
c: 1 2 4 6 => 1 2 2 (tail) => 1[2]4 6
   1 3 5   => 2 2          => 1 3 5
     2 4 6 =>   2 2 (i: 1) =>   2 4 6
             [1  ]         =>  [2  ]
              ^                 ^
             [1 2]         =>  [2 4]
                ^                 ^
             [2 2]         =>  [6 4]
              ^                 ^
a: 1 3 5     => 2 2   (tail)
c: 1 2 3 4 6 => 1 1 1 2 (tail) => 1[2]3 4 6
    1 2 3 5
      1 2 4  <= 2
        1 3
          2  <= 2

0 2 2
x o o o o x o
  x   x   x
    x   x   x
0 1 1 1 1 0 1
  1 x 1 x 1
0 1 1 0 1 1 1
  1 x 1 x 1
  1 x 1 x x 1
0 1 0 1 1 0 1
0 1 0 0 0 1 0
  1 x x 1 x
    1 x x 1 x
    ^   ^ 1 x x 1 x
0 1 0 0 0 1 0
  1 x x 1 x
  ^
 
0 1 0 0 0 1 0
  1 x x 1 x
    ^
 -1
0 1 0 0 0 1 0
  1 x x 1 x
      ^
 -1-1
0 1 0 0 0 1 0
  1 x x 1 x
        ^
 -1-1-1
0 1 0 0 0 1 0
        1 x x 1 x
        ^
       
0 1 0 0 0 1 0
          1 x x 1 x
          ^
         
0 1 1 1 0 1 0
  1 x x 1 x
  ^
 
0 1 1 1 0 1 0
  1 x x 1 x
    ^
 -1
0 1 1 1 0 1 0
  1 x x 1 x
      ^
 -1 0
0 1 1 1 0 1 0
  1 x x 1 x
        ^
 -1 0 1
0 1 1 1 0 1 0
    1 x x 1 x
        ^
   -1 0
0 1 1 1 0 1 0
    1 x x 1 x
          ^
   -1 0-1
0 1 0 0 0 1 0
  1 x x 1 x         => 1 4
          1 x x 1 x => base: 4
0 1 1 1 0 1 0
  1 x x 1 x         => 1 4
    1 x x 1 x       => base: 1
1 0 0 0 0 1 0
  0 ? 0 ? 0
    0 ? 0 ? 0
  ^   ^     ^
  ^ ^ ^ ^   ^
  0 0 0 0   0
  0   0   0
    0   0   0
---- dlok: lookup the key ----------
given a1..n, output error
for (i = 0, s = 0;;)
  if ((b = b[s]) < 0)
    for (tail += ~b, a += i, n -= i, j = 0;;j++)
      if (j == n) return tail[n] != 0
      if (tail[j] != a[j] + 1) return 1
  if (i == n) return 1
  if ((c = a[i++]) > l-b) return 2                  # a[i] should < DM
  if ((k = c[b + c]) == s) s = t                    # another way:
  else return 1                                     # 1. store nil into the child node d[b[x]+0] = {value,s},
                                                    #.   if a key is not a prefix to other keys (has no child node),
                                                    #      the nil node can be reduced (reduced double array trie) b[x] = -value (unlike base, base is positive)
                                                    # 2. store nil into the child node d[b[x]+0] = {-tl,s} and the tail[tl+1] = {value(char)}
                                                    #.   if a key is not a prefix to other keys (has no child node) (impossible),
                                                    #      the nil node can be reduced (reduced double array trie) b[x] = -value
--------------- spec ---------------
a: (nil) | 
---- dins: insert new key ---------- tc: tail capacity
given a1..n (unsigned), b[any] (signed), output error
DBAS(a, n): do { if ((nb = dbas(a, n, d, l)) < 0) return -nb } while(0)
DJMP(b, c): t = b + c, k = c[t], p = b[t], c[p] = k, b[-k] = p
            p > t && (c[0] = k) || p == t && (c[0] = 0)
            c[t] = s
DSTR(a, n): do { for (tail += tl, j = 0; j < n && (j[tail] = j[a] + 1); j++);
                 b[t] = ~tl, *tl += n+1; } while(0)
i = 0, s = 0
while (1)
  if (i == n) return 4      # the inserted key is a prefix or duplicated of already stored key
  c = a[i++] + 1            # 1. if DX == 2^7-1, allow '\0' but remove ascii code: 0x7F DEL
  b = b[s]                  # 2. if c and a[i] is same type, c (unsigned) = a[i++] (signed) + 1 (int) may overflow
  if (b < 0)                #      a[i] should < DM
    for (tc = tail[j = ~b, j++]; c == tc; tc = tail[j++], c = a[i++] + 1)
      DBAS({c}, 1); b[s] = nb, DJMP(nb, c), s = t
      if (i == n) return 4
    for (w = n-i; tl >= tc - w;) if (e = dral(tail, tc)) return e  # no enough space to add tail
    if (tc) DBAS({tc,c}, 2); DJMP(nb, tc), b[t] = ~j               # new node
    else    DBAS({c}, 1);
    b[s] = nb, DJMP(nb, c), DSTR(a+i, w); return 0
  while (c > l-b) if (e = drea(&d,&l) return -e
  if ((k = c[b + c]) == s)                                         # jump to next node
    s = t
  else                                                             # add new node
    for (w = n-i; tl >= tc - w;) if (e = dral(tail, tc)) return e  # no enough space to add tail
    if (k >= 0)                                                    # node conflict
      for (j = 1; (c[h = b+j] == s || j == c && (li = l1, 1)) && (h1[l1++] = h), j != DM && h != l; j++)  # assume c != '\0'
      for (j = 1, kb = b[k]; c[h = kb+j] == k && (h2[l2++] = h), j != DM && h != l; j++)
      if (l1 <= l2)
        DBAS(h1, l1);                                              # 1. find new base of children
        for (j = li+1; j < l1; j++) h1[j-1] = h1[j]                # 2. remove the new child from children
        drel(s,b,nb,h1,--l1,d,l), b = nb                           # 3. relocate
      else
        DBAS(h2, l2);                                              # 1. find new base of children
        drel(k,kb,nb,h2,l2,d,l), s = c[b+(h1[0]==c ? h1[1]:h1[0])] # 2. relocate, the parent of child may be relocated, so
    DJMP(b, c), DSTR(a+i, w); return 0                             #              use the newest sibling's parent instead
---- dins: insert new key ---------- tc: tail capacity
given a1..n, output error
i = 0, s = 0
while (1)
  if (i == n) return 4      # the inserted key is a prefix or duplicated of already stored key
  c = a[i++] + 1            # 1. if DX == 2^7-1, allow '\0' but remove ascii code: 0x7F DEL
  b = b[s]                  # 2. if c and a[i] is same type, c (unsigned) = a[i++] (signed) + 1 (int) may overflow
  if (b < 0)
    for (tc = tail[j = ~b, j++]; c == tc; tc = tail[j++], c = a[i++] + 1)
      nb = dbas({c}, 1, d, l); if (nb < 0) return -nb
      b[s] = nb
      t = nb + c, k = c[t], p = b[t], c[p] = k, b[-k] = p
      p > t && (c[0] = k) || p == t && (c[0] = 0)
      c[t] = s, s = t
      if (i == n) return 4  # the inserted key is a prefix or duplicated of already stored key
    while (tl >= tc - (w = n-i)) if (e = dral(tail, tc)) return e  # no enough space to add tail
    if (tc)
      nb = dbas({tc,c}, 2, d, l); if (nb < 0) return -nb
      t = nb + tc, k = c[t], p = b[t], c[p] = k, b[-k] = p         # new node
      p > t && (c[0] = k) || p == t && (c[0] = 0)                  #
      b[t] = ~j, c[t] = s                                          #
    else
      nb = dbas({c}, 1, d, l); if (nb < 0) return -nb
    b[s] = nb
    t = nb + c, k = c[t], p = b[t], c[p] = k, b[-k] = p            # new node
    p > t && (c[0] = k) || p == t && (c[0] = 0)                    #
    memcpy(tail+tl, a+i, w), tl += w+1, b[t] = ~tl, c[t] = s       #
    return 0
  while (c > l-b) if (e = drea(&d,&l) return -e
  if ((k = c[t = b + c]) == s)                                     # jump to next node
    s = t
  else                                                             # add new node
    while (tl >= tc - (w = n-i)) if (e = dral(tail, tc)) return e  # no enough space to add tail
    if (k >= 0)                                                    # node conflict
      for (j = 1; (c[h = b+j] == s || j == c && (li = l1, 1)) && (h1[l1++] = j), j != DM && h != l; j++)  # assume c != '\0'
      for (j = 1, kb = b[k]; c[h = kb+j] == k && (h2[l2++] = j), j != DM && h != l; j++)
      if (l1 <= l2)
        nb = dbas(h1, l1, d, l); if (nb < 0) return -nb            # 1. find new base of children
        for (hl--, j = li+1; j < l1; j++) h1[j-1] = h1[j]          # 2. remove the new child from children
        drel(s,b,nb,h1,l1,d,l), b = nb                             # 3. relocate
      else
        nb = dbas(h2, l2, d, l); if (nb < 0) return -nb            # 1. find new base of children
        drel(k,kb,nb,h2,l2,d,l), s = c[b+(h1[0]==c ? h1[1]:h1[0])] # 2. relocate, the parent of child may be relocated, so
      t = b + c, k = c[t]                                          #              use the newest sibling's parent instead
    p = b[t], c[p] = k, b[-k] = p                                  # new node: 1. delete empty node
    p > t && (c[0] = k) || p == t && (c[0] = 0)                    #           2. update the front pointer
    memcpy(tail+tl, a+i, w), tl += w+1, b[t] = ~tl, c[t] = s       #           3. add tail and node
    return 0
--------------- spec ---------------
a: 0           |  1                  |  2                  | x-1                   | x-1
d: 0  1 # 0 -1 |  0  1 #  0  3 -1  1 |  0  1 #  0  3  1  2 |   0  x  1  2 ...  x-2 |   0  x  1  2 ...  x-2 x-1
  -1 -1 # 0  0 | -1 -1 # -1 -3  0 -1 | -1 -2 # -1 -2 -3 -1 |  -1 -2 -3 -4 ...   -1 |  -1 -2 -3 -4 ...   -1  -1
t: nil  # 0  0
tl: 0   # 1
tc: 0   # 2
---- dral: realloc the tail --------
b = *c
if (*c > dx - *c) return 3                                         <- no enough space to add tail
if (new = realloc(*tail, DS*(e = *c<<=1))) *tail = new; else return 2  <- realloc err
for (;b < e; b++) tail[b] = 0;
return 0
--------------- spec ---------------
c: 1   # 2   | 2   # 4
t: 0   # 0 0 | 1 1 # 0 0 0 0
---- dinl: init the tail -----------
return calloc(DT, c)
---- drel: relocate the node -------
given s, b (old base), nb (new base), a1..n, output none
b[s] = nb, j = 0         #    s   s    s  p nt k   s  nt t    s  nt j  t -k   s  nt j  t -k h
for (i = 0; i < n; i++)  #   ⎡ ⎤ ⎡  ⎤ ⎡     p  p⎤ ⎡   kb<kb⎤ ⎡   kb    j t ⎤ ⎡   kb    j t    ⎤
  c = a[i]               #   ⎣b⎦ ⎣nb⎦ ⎣nb k k   ⎦ ⎣nb s    ⎦ ⎣nb s  -t k   ⎦ ⎣nb s  -t k    nt⎦
  t = b + c              #                         v--^--^    v--^-----^      v--^     v----^
  nt = nb + c, k = c[nt], p = b[nt], c[p] = k, b[-k] = p  # new node: 1. delete empty node
  p > nt && (c[0] = k) || p == nt && (c[0] = 0)           #           2. this cell is first empty cell or final empty cell
  b[nt] = kb = b[t], c[nt] = s                            #           3. add node
  for (; (k = -c[j]) > j && k < t; j = k)
  if (j)       # free the old new node:
    b[t] = j   # there is one empty preceding this cell
    c[t] = -k
    c[j] = -t
    b[k] = t
  else if (k)  # there are no empty preceding this cell and there are one empty following this cell
    b[t] = e = b[k]
    c[t] = -k
    c[e] = c[0] = -t
    b[k] = t
  else         # there are no empty cells
    b[t] = t
    c[t] = -t
    c[j] = -t
  if (k = t, kb >= 0) for (m = 1; c[h = kb+m] == t && (c[h] = nt), m != DM && h != l; m++)  # if this cell has children
--------------- spec ---------------
a: 2                              | 1                        | 1                        | 1
d: 1  4  1 -1  2 #  0  4 -1  1  3 | 0 -1  3  2 #  1  3 -1  1 | 0 -1  2 -1 #  1  1 -1 -1 | 1  1 -1 -1 #  0 -1  2 -1
  -1 -2 -4  0 -1 # -1 -3  0 -4 -1 |-2  0 -3 -2 # -1 -3  0 -1 |-2  0 -2  1 # -1 -1  0  1 |-1 -1  0  1 # -2  0 -2  1
  nb  b                             b nb                       b nb                      nb  b
a: 1  3                           |  1  4
d: 0 -1  4 -2  2 #  1  3 -1  1 -2 |  0  1 -1  6  3 -2  3 #  2  4 -1  1  1 -2  3
  -2  0 -4  0 -2 # -1 -3  0 -1  0 | -2  0  1 -6  0  4 -3 # -1 -4  3  0 -1  6  0
   b nb                              b    nb
---- dbas: find new base, O(T+m) --- i: i >= a0, ft: fail table[m], k: pl, j: el
given a1..n, output base, d: double array, p: pattern[m]
i = 0, f = -1, c = -1
for (k = 0; k < n; k++) p[a[k]] = 1                                       # pattern
for (v = 0; -c[v] == 4 && drea(&d,&l), (v = -c[v]) < a[0];)               # find i >= a0
for (i = 0, w[0] = v; -c[v] == 4 && drea(&d,&l), x=w[i], y=w[i]=-c[v]-v, f < k - 1;
  f += p[f + 1] == y, i = i == 4 ? 0 : i++, v = -c[v])
  while (f >= 0 && p[f + 1] != y) f = f[ft];
return x
---- dbas: find new base, O(m^2) --- dx: smaxt(dl_t), dm: smaxi(dl_t,sizeof(dl_t)/2)
given a1..n, output base, d: double array
i = 0, j = 1
for (; (-c[i] > i || !(e=drea(&d,&l))) && (i = -c[i]) < a[0];)               # find i >= a0
for (; !e & j < n && (-c[i] > i || !(e=drea(&d,&l))); j < n && (i = -c[i]))
  for (j = 1; j < n; j++)
    while (a[j]-a[0] > l-i) if (e = drea(&d,&l)) return -e
    if (c[i-a[0]+a[j]] >= 0) break
return e ? -e : i-a[0]
error: 1. the index of empty cells i exceeds the bound
       2. the index of empty cells i + a[j] - a[0] exceeds the bound
--------------- spec --------------- x: 2^7
a: 0    |  1    |  2                  | x-1                   | x-1
d: 0  1 |  0  1 |  0  1 #  0  3  1  2 |   0  x  1  2 ...  x-2 |   0  x  1  2 ...  x-2 x-1
  -1 -1 | -1 -1 | -1 -2 # -1 -2 -3 -1 |  -1 -2 -3 -4 ...   -1 |  -1 -2 -3 -4 ...   -1  -1
      ^    ^               ^              ^                          -1: len is max
         (2 bit)       (3 bit: 2^3/2=4) (x+1 bit: x)
   zero    one            drea                 max                     drea fail
a: 1  2       |  1  3  5                |  1  3               |  1  x-1
d: 0  3  1  2 |  0  7  1  2  3  4  5  6 |  0  1 #  0  3  1  2 |  0  x  1  2 ...  x-1
  -1 -2 -3 -1 | -1 -2 -3 -4 -5  0 -7 -1 | -1 -2 # -1 -2 -3 -1 | -x -2 -3 -4 ...   -1
   ^                ^                              ^            -1: len is max
 normal         conflict*1                      drea*1              drea fail
a: 1  3  6                                      |  1  3  6  7
d: 0  x  1  2 ...  x-6  x-5  x-4  x-3  x-2  x-1 |  0  x  1  2 ...  x-6  x-5  x-4  x-3  x-2  x-1
  -2  0 -4  0 ... -x+3   0  -x+1   0   -x    -2 | -2  0 -4  0 ... -x+3   0  -x+1   0   -x    -2
                    ^                                 -1: len is max (the key is out of bound)
                   max                                         dcec
---- dcec: check if the key is out of bound ---
dcec(c) ((c) ? 0 : 3)  <- the key is out of bound
---- drea: realloc double array ----
given *d, *l, output used in expression
if (b = *l+1, *l > dx - *l) return 1                                         <- len is max
if (i = *l+1, new = realloc(*d, DS*(*l=2**l+1)+DS)) *d = new; else return 2  <- realloc err
for (f = c[0]; d[i] = (d_t){i-1,-i-1}, i != *l; i++)
return m = f ? (c[b[b] = b[-f]] = -b, -f) : (c[0] = -b, b), c[b[m] = *l] = -m, 0
#  m                       m
# *l     7     1     0    b[-f]   4     5     6
# -1    -2    -s     0    -5     -6    -7    -1
--------------- spec ---------------
d: 0  1 #  0  3  1  2 |  0  2  1  0 #  0  7  1  0  2  4  5  6
  -1 -2 # -1 -2 -3 -1 | -1 -2 -3  0 # -1 -2 -4  0 -5 -6 -7 -1
d: 0  0 #  0  0  3  2
   0  0 # -2  0 -3 -2
---- dini: initial double array ----
given l, output d
if (!l) return
d_t * d = malloc(l*sizeof(d_t)+sizeof(d_t))
for (d[0] = (d_t){0,-1}, i = 1; d[i] = (d_t){i-1,-i-1}, i != l; i++)
return d[1].b = l, d[l].c = -1, d
--------------- spec ---------------
l: 0 | 1
d: 0 | 0  1
     |-1 -1
------------- question -------------

給定兩個 bit array，長度為 n，0 代表為空，1 代表已佔據，請找出能交錯不重疊的擺放方式
暴力解為每移動一格就比較兩個陣列一次，時間複雜度為 O(n^2)，請問有比暴力解更好的作法嗎？

若把第二個 bit array 化為狀態機，邊為 0 或 1，就可以用 DFA 解這個問題，但是失敗後邊要連到哪個狀態？若失敗後邊都連到起始狀態，這樣時間複雜度就跟暴力解一樣了，請問有人知道失敗後邊要連到哪個狀態嗎？

給教授：

我最近在學習 double array trie，想請教您關於 double array trie 插入新的 key 發生衝突時要如何找新的空間來重新調整 trie。

問題是這樣的，給定兩個 bit array，長度為 n，0 代表為空，1 代表已佔據，請找出交錯不重疊的擺放方式。
暴力解為每移動一格就比較兩個陣列一次，時間複雜度為 O(n^2)，是否有更快的作法呢？

若把第二個 bit array 化為狀態機，邊為 0 或 1，就可以用 DFA 解這個問題，但是 DFA 並沒有失敗後邊要連到哪個狀態？
