#include <ext/rope>
using namespace __gnu_cxx;

crope r(s.c_str());
crope s1 = r.substr(x, l); // x ~ x+l-1의 substring
r.erase(x, l); // x ~ x+l-1 까지 삭제
r = s1 + r; // s1와 r 더하기
