#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
// 큰 상수는 문자열로 초기화
cpp_int a = 1, b("123456789012345678901234567890");
cpp_int c = a + b, d = b * b, e = d / b, f = d % b; // 사칙연산 지원
cpp_int g = pow(b, 10); // 거듭제곱
cout << b << "\n"; // cin/cout 그대로 사용 가능
