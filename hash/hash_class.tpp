#include "../my_vectors/vectors.h"


template <typename TVal>
class HashTable {
protected:
	HVector<HVector<TVal>> values;
	size_t collision_counter = 0; 
public:
	HashTable(size_t hash_size) {
		for (size_t i = 0; i < hash_size; i++) {
			values.append(HVector<TVal>());
		}
	};

	bool add_hash(size_t hash, TVal key, bool maybe_repeated = false) {
		if (hash < 0) {
			throw "add_hash: hash<0";
		} else if (hash >= values.len()) {
			throw "add_hash: hash>max";
		}

		if (values[hash].len() != 0) {
			if (maybe_repeated){
				for (int i = 0; i < values[hash].len(); i++) {
					if (values[hash][i] == key) {
						return false;
					}
				}
			}
			collision_counter++;
		}
		values[hash].append(key);
		return true;
	}

	size_t get_collision() { return collision_counter; }
};