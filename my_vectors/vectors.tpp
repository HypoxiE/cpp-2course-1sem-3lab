#include "alloc.tpp"
using namespace std;

template <typename T, typename Tlloc = SimpleAllocator<T>>
class HVector {
protected:
	T* vec = nullptr;
	Tlloc allocator;

	size_t lenght = 0;
	size_t capacity = 0;
public:
	HVector() = default;

	HVector(T* base_arr, size_t n) : vec(nullptr), lenght(0), capacity(0) {
		for (size_t i = 0; i < n; i++) {
			append(base_arr[i]);
		}
	}
	~HVector() {
		allocator.dealdestruct(vec, capacity);
	}

	void append(T elem) {
		if (lenght >= capacity) {
			size_t new_cap = capacity ? capacity * 2 : 1;
			T* new_vec = allocator.allconstruct(new_cap);
			for (size_t i = 0; i < lenght; i++) {
				new_vec[i] = vec[i];
			}

			new_vec[lenght++] = elem;

			allocator.dealdestruct(vec, capacity);
			capacity = new_cap;

			vec = new_vec;
		} else {
			vec[lenght] = elem;
			lenght++;
		}
	}

	size_t len() {
		return lenght;
	}

	friend std::ostream& operator<<(std::ostream& os, const HVector& p) {
		if (p.vec == nullptr) {
			os << "[]";
		} else {
			os << "[";
			for (size_t i = 0; i < p.lenght; i++) {
				os << p.vec[i];
				if (i != p.lenght - 1) os << ", ";
			}
			os << "]";
		}
		return os;
	}

	T& operator[](size_t index) {
        return vec[index];
    }
    const T& operator[](size_t index) const {
        return vec[index];
    }

	//HVector operator+(const HVector& other) const {
	//    size_t new_cap = capacity ? capacity : 1;
	//	while (new_cap < lenght + other.lenght) {
	//		new_cap = new_cap * 2;
	//	}
	//	T* new_vec = allocator.allconstruct(new_cap);
	//	for (size_t i = 0; i < lenght; i++) {
	//		new_vec[i] = vec[i];
	//	}
	//    return result;
	//}
};