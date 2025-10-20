#include "../my_vectors/vectors.h"


template <typename TKey, typename TVal>
class HashTable {
private:
	std::allocator<TKey> key_alloc;
	TKey *keys;
	std::allocator<TVal> val_alloc;
	TVal *values;

	size_t length;
	size_t capacity;
public:
	HashTable() : keys(nullptr), values(nullptr), length(0), capacity(0) {}
	~HashTable() {
		if (capacity > 0) {
			
		}
		if (length > 0) {

		}
	}
	TVal& operator[] (const TKey& key) {
		index = -1;
		for (int i = 0; i < length; i++){
			if (keys[i] == key) {
				return values[i];
			}
		}
		if (index == -1) {
			if (length >= capacity) {
				size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
				TKey *new_keys = key_alloc.allocate(new_capacity);
				TVal *new_values = val_alloc.allocate(new_capacity);

				for (int i = 0; i < length; i++) {
					std::allocator_traits<decltype(key_alloc)>::construct(key_alloc, &new_keys[i], keys[i]);
					std::allocator_traits<decltype(key_alloc)>::destroy(key_alloc, &keys[i]);
					std::allocator_traits<decltype(val_alloc)>::construct(val_alloc, &new_values[i], values[i]);
					std::allocator_traits<decltype(val_alloc)>::destroy(val_alloc, &values[i]);
				}

				std::allocator_traits<decltype(key_alloc)>::construct(key_alloc, &new_keys[length], key);

				if (keys) alloc.deallocate(keys, capacity);
				if (values) alloc.deallocate(values, capacity);
				keys = new_keys;
				values = new_values;
				length++;
			} else {
				length++;
				keys[length] = key;
			}
			return values[length-1]
		}
	}
};