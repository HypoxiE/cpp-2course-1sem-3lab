#include <iostream>
#include <memory>
#include "hash/hash.h"
#include "my_vectors/vectors.h"
#include "funcs/funcs.h"

using namespace std;

HVector<HVector<size_t>> test_random_hashs(size_t hash_size) {
	HVector<HVector<size_t>> bench_result;

	HashTable<String<SimpleAllocator<char>>> hash_table_1(hash_size);
	HashTable<String<SimpleAllocator<char>>> hash_table_2(hash_size);
	HashTable<String<SimpleAllocator<char>>> hash_table_3(hash_size);

	for (size_t j = 1; j < 10001; j++){

		String str;
		for (size_t i = 1; i < 10000; i++) {
			str.append(random(0, 100000));
		}
		hash_table_1.add_hash(GetHash1(str, hash_size), str);
		hash_table_2.add_hash(GetHash2(str, hash_size), str);
		hash_table_3.add_hash(GetHash3(str, hash_size), str);

		if (j % 100 == 0) {
			HVector<size_t> iter_result = {j, 10000, hash_table_1.get_collision(), hash_table_2.get_collision(), hash_table_3.get_collision()};
			cout << iter_result << endl;
			bench_result.append(iter_result);
		}
	}
	return bench_result;
}

int main() {
	//HVector<int> vec2 = {};
	//HVector<int> vec3 = {1,42,12,4,43};
	//HVector<int> vec4 = {1,1,3,6};

	//HVector<HVector<int>> vec;

	//vec.append(vec2);
	//vec.append(vec3);
	//vec.append(vec4);

	//cout << vec << endl;

	//vec2.merge(vec3);
	//cout << vec2 << endl;

	//cout << vec3 + vec4;
	//cout << vec3;
	//cout << vec4;

	size_t hash_max = 600;
	
	//HashTable<String<SimpleAllocator<char>>> hash_table_2(hash_max);
	//HashTable<String<SimpleAllocator<char>>> hash_table_3(hash_max);

	//String str;
	//for (int i = 0; i < 1000; i++) {
	//	str.append(random(0, 255));
	//}
	//cout << str << endl;

	//cout << GetHash1(str, hash_max) << endl;
	//cout << GetHash2(str, hash_max) << endl;
	//cout << GetHash3(str, hash_max) << endl;

	auto a = test_random_hashs(hash_max);

	cout << a << endl;

	return 0;
}