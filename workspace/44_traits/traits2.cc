#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#if 0//当T=char时,计算字符串“abc”,结果为Sigma(szNames) = 38，错误
template<typename T>
inline T Sigma(const T *start, const T *end)
{
	T total = T();
	while( start != end ){
		total += *start++;
	}

	return total;
}
#endif

template<typename T> class SigmaTraits{};
template<> class SigmaTraits<char>{
	public: typedef int ReturnType;
};
template<> class SigmaTraits<short>{
	public: typedef int ReturnType;
};
template<> class SigmaTraits<int>{
	public: typedef long ReturnType;
};
template<> class SigmaTraits<unsigned int>{
	public: typedef unsigned long ReturnType;
};
template<> class SigmaTraits<float>{
	public: typedef double ReturnType;
};

template<typename T>
inline typename SigmaTraits<T>::ReturnType Sigma(const T *start, const T *end)
{
	typedef typename SigmaTraits<T>::ReturnType ReturnType;
	ReturnType s = ReturnType();
	while( start != end ){
		s += *start++;
	}

	return s;
}

int main()
{
	char szNames[] = "abc";
	std::size_t nLength = strlen(szNames);
	char *p = szNames;
	char *q = szNames + nLength;
	printf("Sigma(szNames) = %d\n", Sigma(p,q));
}