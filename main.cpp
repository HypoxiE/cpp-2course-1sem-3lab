#include <iostream>
//#include "hash/hash.h"
#include "my_vectors/vectors.h"

using namespace std;

int main() {
	//HashTable<int, >

	int arr[] = {1,2,3,4};
	HVector vec2(arr, 4);

	cout << vec2;

	HVector<HVector<int>> vec;

	cout << vec2;

	vec.append(vec2);

	cout << vec;

	return 0;
}
