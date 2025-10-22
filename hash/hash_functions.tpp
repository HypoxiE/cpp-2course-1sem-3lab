#include "../my_vectors/vectors.h"
#include <concepts>
#include <cstdlib>

#define STRING String<SimpleAllocator<char>>
#define NORMALIZE(hash, max) (hash % (max))

using namespace std;

template <typename T>
concept AllowedTypes = same_as<T, HVector<char>> || same_as<T, HVector<int>> || same_as<T, STRING>;

template <AllowedTypes T>
int GetHash1(T vec, size_t hash_max) {
	int hash = 0;
	for (int i = 0; i < vec.len(); i++){
		hash = (hash+(vec[i]*i)) % 1073741824;
	}

	return NORMALIZE(hash, hash_max);
}

template <AllowedTypes T>
int GetHash2(T vec, size_t hash_max) {
	u_int hash = 5381;
	
	for (int i = 0; i < vec.len(); i++) {
		hash = ((hash << 5) + hash) + vec[i] * i;
	}
	return NORMALIZE(hash, hash_max);
}

template <AllowedTypes T>
int GetHash3(T vec, size_t hash_max) {
	u_int64_t hash = 0;
	for (int i = 0; i < vec.len(); i++) {
		hash = hash + vec[i] * i;
	}
	return NORMALIZE(hash*2654435761, hash_max);
}