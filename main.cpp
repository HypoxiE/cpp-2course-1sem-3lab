#include <iostream>
//#include "hash/hash.h"
#include "my_vectors/vectors.h"

using namespace std;

int main() {
	int arr[] = {1, 2, 3, 4};
    HVector<int> vec2(arr, 4);

	cout << vec2;

	HVector<int> vector;
	vector.append(10);
	vector.append(20);
	vector.append(20);
	vector.append(30);
	vector.append(40);
	vector.append(50);

	cout << vector;

	//SimpleAllocator<int> alloc;

	//int* p = alloc.allconstruct(3);
	//p[0] = 10;
	//p[1] = 20;
	//p[2] = 30;

	//for (int i = 0; i < 3; ++i)
	//	std::cout << p[i] << " ";

	//alloc.dealdestruct(p, 3);

	return 0;
}
