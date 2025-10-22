#include <iostream>
#include <memory>
#include <fstream>
#include "hash/hash.h"
#include "my_vectors/vectors.h"
#include "funcs/funcs.h"

using namespace std;

HVector<HVector<size_t>> testbench(size_t hash_size) {

	HVector<String<>> real_data = {"Константин", "ИВБ-411", "VERILOG", "C++", "GOLANG", "Linux", "Dynamic Window Manager"};

	HVector<HVector<size_t>> bench_result;

	std::ofstream file("output.csv");
	if (!file.is_open()) {
		return bench_result;
	}

	HVector<HashTable<String<>>> hash_vector;
	for (int i = 0; i < 9; i++) {
		hash_vector.append(HashTable<String<>>(hash_size));
	}

	for (size_t j = 1; j < 10001; j++){

		HVector<String<>> strings_vector = {String<>(), String<>("!"), real_data[random(0, real_data.len()-1)]};
		//cout << real_data[random(0, real_data.len()-1)];
		for (size_t i = 1; i < 1000; i++) {
			strings_vector[0].append(random(0, 100000));
			for (size_t k = 0; k < random(0, 10); k++) {
				strings_vector[1].append(strings_vector[1][strings_vector[1].len()-1]);
			}
		}


		for (int i = 0; i < 3; i++) {
			hash_vector[0+3*i].add_hash(GetHash1(strings_vector[i], hash_size), strings_vector[i]);
			hash_vector[1+3*i].add_hash(GetHash2(strings_vector[i], hash_size), strings_vector[i]);
			hash_vector[2+3*i].add_hash(GetHash3(strings_vector[i], hash_size), strings_vector[i]);

		}

		if (j % 100 == 0) {
			HVector<size_t> iter_result = {j};
			for (int i = 0; i < 9; i++) {
				iter_result.append(hash_vector[i].get_collision());
				cout << hash_vector[i].get_keys() << " ";
			}
			cout << endl;

			iter_result.to_csv(file);
			iter_result.to_csv(cout);
			file << endl;
			cout << endl;
			bench_result.append(iter_result);
		}
	}
	file.close();
	return bench_result;
}

int main() {
	srand(100);
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

	auto a = testbench(hash_max);
	cout << a << endl;

	//HashTable<String<SimpleAllocator<char>>> hash_table(hash_max);
	//String str;
	//for (int i = 0; i < 1000; i++) {
	//	str.append('!');
	//	hash_table.add_hash(GetHash1(str, hash_max), str);
	//	cout << hash_table.get_collision() << endl;
	//}

	//String str2 = "qwer";

	//cout << hash_table.add_hash(GetHash1(str, hash_max), str) << endl;
	//cout << hash_table.get_collision() << endl;
	//cout << hash_table.add_hash(GetHash1(str, hash_max), str2) << endl;
	//cout << hash_table.get_collision() << endl;

	return 0;
}