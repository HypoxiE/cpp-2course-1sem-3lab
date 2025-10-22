#include "../my_vectors/vectors.h"


template <typename TVal>
class HashTable {
protected:
	HVector<HVector<TVal>> values;
	size_t collision_counter = 0;
	size_t elements_counter = 0;
public:
	HashTable(size_t hash_size) {
		for (size_t i = 0; i < hash_size; i++) {
			values.append(HVector<TVal>());
		}
	};

	bool add_hash(size_t hash, TVal key, bool maybe_repeated = true) {
		bool is_collision = (values[hash].len() != 0);
		bool is_duplicate = false;

		if (is_collision && maybe_repeated) {
			for (size_t i = 0; i < values[hash].len(); i++) {
				if (values[hash][i] == key) {
					is_duplicate = true;
					break;
				}
			}
		}

		if (is_duplicate) {
			return false;
		}

		if (is_collision) {
			collision_counter++;
		}
		values[hash].append(key);
		elements_counter++;
		return true;
	}

	HVector<HVector<TVal>>& operator[](size_t index) {
		return values[index];
	}
	const HVector<HVector<TVal>>& operator[](size_t index) const {
		return values[index];
	}

	size_t get_keys() { return elements_counter; }

	size_t get_collision() { return collision_counter; }
};