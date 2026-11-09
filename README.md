# Teamnote

ICPC 스타일 팀노트. `teamnote.tex`가 `codes/` 아래의 C++ 스니펫들을 모아 한 권의 인쇄용 PDF로 조립합니다.

**Last updated:** 2026-11-09 (v1.1)

## 목차

- **Mathematics**: Bit Function, XOR / Linear Basis, FWT, Modular Inverse, Extended Euclidean Algorithm, CRT, Miller Rabin + Pollard Rho, Discrete Log, Discrete Sqrt, Polynomial, Power Sums via NTT, Berlekamp Massey, Floor Sum, Kitamasa
- **Dynamic Programming**: Deque trick, CHT, DnC Optimization, Knuth Optimization, Slope Trick, Submask Enumeration, SOS DP, Connection Profile DP, Alien's Trick
- **Data Structure**: Splay Tree, EER Tree, Link-Cut Tree, Li-Chao Tree
- **Geometry**: CCW, Convex Hull, 3D Convex Hull, Rotating Callipers, Closest Point on Convex Polygon to a Line, Minimum Bounding Rectangle, Closest Pair of Points, KD-Tree, 2D/3D Minimum Enclosing Circle, Point in Polygon / Segment-Polygon Intersection, Point/Segment Reflection and Rotation, 3D Distances, Cut Polygon by Line, Polygon Union Area, Polygon Centroid, Circle-Line/Circle-Circle/Segment-Circle Intersection, Half Plane Intersection, Planar Graph, Shamos-Hoey, Voronoi Diagram
- **Graph**: SPFA, SCC + 2-SAT, BCC, Cactus, Euler Path/Circuit, Articulation Point/Bridge, Dominator Tree, Offline Dynamic Connectivity, Online Dynamic MST, $k$th Shortest Path (Eppstein)
- **Tree**: HLD, Centroid Decomposition, Tree Compression, Tree Isomorphism
- **Flow / Matching**: Hopcroft-Karp, Matching/Matroid Lemmas, Dinic, MCMF (Dijkstra+Potentials), Stable Marriage, Circulation, Stoer-Wagner, Gomory-Hu Tree, General Matching (Blossom), Hungarian Algorithm
- **String**: KMP, Aho-Corasick, Hashing (Rabin Karp), Manacher, Suffix Array + LCP, Suffix Automaton, Z Algorithm, LCS - Hirschberg
- **Miscellaneous**: Random Generator, Rope, PBDS, Big Integer, Mo's, CDQ, Faker's Algorithm, Matroid Intersection, Primes and Divisors Number, Lemma (자주 쓰는 정리/공식 모음)
- **Template**: 대회 제출용 기본 템플릿

## 빌드 방법

`-shell-escape`가 필요합니다 (`minted`이 문법 강조를 위해 Pygments를 셸에서 호출).

```bash
latexmk -pdf -shell-escape teamnote.tex
```

또는 직접:

```bash
pdflatex -shell-escape teamnote.tex
```

목차/페이지 참조를 정확히 맞추려면 두 번 실행하세요 (`latexmk`는 자동으로 재실행합니다). 생성물 정리:

```bash
latexmk -c
```

**페이지 제한**: 컴파일된 PDF는 **25페이지 이하**를 유지해야 합니다 (대회 인쇄물 규정). 빌드 로그 마지막 줄(`Output written on teamnote.pdf (25 pages, ...)`) 또는 아래 명령으로 확인:

```bash
grep -oE "\([0-9]+ pages" teamnote.log
```

## 구조

- `teamnote.tex` — 문서 전체를 조립하는 단일 LaTeX 소스 (2단 레이아웃, minted 스타일, 여백 등 설정 포함)
- `codes/<category>/<algorithm>.cpp` — 알고리즘별 파일 (`mathematics`, `dp`, `data_structure`, `geometry`, `graph`, `tree`, `flow_matching`, `string`, `miscellaneous`, `template`)
- `codes/flow_matching/lemma.tex`, `codes/miscellaneous/lemma.tex`, `codes/miscellaneous/primes.tex` — 코드가 아닌 산문/수식 모음 (`\input`으로 삽입)
- `codes/flow_matching/mcmf_spfa.cpp`, `codes/miscellaneous/parallel_binary_search.cpp` — 코드만 보관 (`teamnote.tex`에서 주석 처리되어 PDF에는 포함되지 않음)
