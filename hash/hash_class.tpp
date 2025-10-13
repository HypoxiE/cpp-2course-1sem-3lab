
template <typename TKey, typename TVal>
class HashTable {
private:
	std::allocator<TKey> key_alloc;
	TKey *keys;
	std::allocator<TVal> val_alloc;
	TVal *values;

	size_t length;
	size_t size;
public:
	HashTable() : keys(nullptr), values(nullptr), length(0), size(0) {}
	~HashTable() {
		if (size > 0) {
			
		}
		if (length > 0) {

		}
	}
	TVal operator[] (TKey key) {
		index = -1;
		for (int i = 0; i < length; i++){
			if (keys[i] == key) {
				return values[i];
			}
		}
		if (index == -1) {
			if (length >= size) {
				size_t new_size = 0;
				if (size == 0) {
					new_size = 1;
				} else {
					new_size = size * 2;
				}
				TKey *new_keys = key_alloc.allocate(new_size);
				TVal *new_values = val_alloc.allocate(new_size);

				for (int i = 0; i < length; i++) {
					new_keys[i] = keys[i];
					new_values[i] = values[i];
				}

				//dealocate keys, values

				keys = new_keys;
				values = new_values;
			}
			length++;
			keys[length] = key;
			return values[length-1];
		}
	}
};