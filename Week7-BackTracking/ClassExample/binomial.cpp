#include <iostream>
#include <cctype>
using namespace std;

uint64_t binomial(unsigned n, unsigned k);

int main()
{
	binomial(25, 100);
	return 0;
}

uint64_t binomial(unsigned n, unsigned k)
{
	if (k == 0 || k == n)
	{
		return 1;
	}
	return binomial(n-1, k-1) + binomial(n-1, k);
}
