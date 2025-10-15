#include <iostream>
//#include "hash/hash.h"
#include "my_vectors/vectors.h"

using namespace std;

int main() {
	//HVector<int> vector;
	SimpleAllocator<int> alloc;

	int* p = alloc.allconstruct(3);
	p[0] = 10;
	p[1] = 20;
	p[2] = 30;

	for (int i = 0; i < 3; ++i)
		std::cout << p[i] << " ";

	alloc.dealdestruct(p, 3);

	return 0;
}
