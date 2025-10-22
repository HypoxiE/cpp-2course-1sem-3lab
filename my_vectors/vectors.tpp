#include "alloc.tpp"
using namespace std;

template <typename T, typename Tlloc = SimpleAllocator<T>>
class HVector {
protected:
	T* vec = nullptr;
	Tlloc allocator;

	size_t length = 0;
	size_t capacity = 0;
public:
	HVector() = default;

	HVector(T* base_arr, size_t n) : vec(nullptr), length(0), capacity(0) {
		for (size_t i = 0; i < n; i++) {
			append(base_arr[i]);
		}
	}

	HVector(const HVector& v) {
		vec = allocator.allocate(v.capacity);
		for (int i = 0; i < v.length; i++) {
			std::allocator_traits<decltype(allocator)>::construct(allocator, &vec[i], v.vec[i]);
		}
		length = v.length;
		capacity = v.capacity;
	}

	~HVector() {
		if (vec) {
			for (size_t i = 0; i < length; i++) {
				std::allocator_traits<decltype(allocator)>::destroy(allocator, &vec[i]);
			}
			allocator.deallocate(vec, capacity);
		}

		vec = nullptr;
		length = capacity = 0;
	}

	HVector(std::initializer_list<T> init) {
		for (const auto& elem : init) {
			append(elem);
		}
	}

	void append(T elem) {
		if (length >= capacity) {
			size_t new_cap = capacity ? capacity * 2 : 1;
			T* new_vec = allocator.allocate(new_cap);
			for (size_t i = 0; i < length; i++) {
				std::allocator_traits<decltype(allocator)>::construct(allocator, &new_vec[i], vec[i]);
				std::allocator_traits<decltype(allocator)>::destroy(allocator, &vec[i]);
			}

			std::allocator_traits<decltype(allocator)>::construct(allocator, &new_vec[length], elem);

			allocator.deallocate(vec, capacity);

			length++;
			capacity = new_cap;
			vec = new_vec;
		} else {
			std::allocator_traits<decltype(allocator)>::construct(allocator, &vec[length++], elem);
		}
	}

	void insert(T elem, size_t index) {

		if (index > length) {
			cout << endl << "Вы чувствуете, что что-то пошло не так..." << endl;
		}
		else if (index == length) {
			append(elem);
			return;
		}
		size_t new_cap = !capacity ? 1 : capacity > length ? capacity * 2 : capacity;

		T* new_vec = allocator.allocate(new_cap);
		for (size_t i = 0; i < length; i++) {
			if (i == index){
				std::allocator_traits<decltype(allocator)>::construct(allocator, &new_vec[index], elem);
			}
			std::allocator_traits<decltype(allocator)>::construct(allocator, &new_vec[i + (i>=index)], vec[i]);
		}

		for (size_t i = 0; i < length; i++) {
			std::allocator_traits<decltype(allocator)>::destroy(allocator, &vec[i]);
		}
		allocator.deallocate(vec, capacity);

		length++;
		capacity = new_cap;

		vec = new_vec;
	}

	size_t len() {
		return length;
	}
	size_t len() const {
		return length;
	}

	friend std::ostream& operator<<(std::ostream& os, const HVector& p) {
		if (p.vec == nullptr) {
			os << "[]";
		} else {
			os << "[";
			for (size_t i = 0; i < p.length; i++) {
				os << p.vec[i];
				if (i != p.length - 1) os << ", ";
			}
			os << "]";
		}
		return os;
	}

	T& operator[](size_t index) {
		if (index > length) {
			cout << endl << "Вы чувствуете, что что-то пошло не так..." << endl;
		}

		return vec[index];
	}
	const T& operator[](size_t index) const {
		if (index > length) {
			cout << endl << "Вы чувствуете, что что-то пошло не так..." << endl;
		}

		return vec[index];
	}

	T pop(size_t index) {

		if (index >= length) {
			cout << endl << "Вы чувствуете, что что-то пошло не так..." << endl;
		}

		T elem = vec[index];

		size_t new_cap = length <= capacity / 2 ? capacity / 2 : capacity;
		T* new_vec = allocator.allocate(new_cap);

		for (size_t i = 0; i < length; i++) {
			if (i != index){
				std::allocator_traits<decltype(allocator)>::construct(allocator, &new_vec[i - (i>index)], vec[i]);
			}
		}

		for (size_t i = 0; i < length; i++) {
			std::allocator_traits<decltype(allocator)>::destroy(allocator, &vec[i]);
		}
		allocator.deallocate(vec, capacity);


		capacity = new_cap;
		length--;

		vec = new_vec;

		return elem;
	}
	void merge(HVector other) {
		for (int i = 0; i < other.len(); i++) {
			append(other[i]);
		}
	}
	HVector operator+(HVector other) {
		HVector new_vec = *this;
		for (int i = 0; i < other.len(); i++) {
			new_vec.append(other[i]);
		}
		return new_vec;
	}
	HVector operator+(std::initializer_list<T> init) {
		HVector new_vec = *this;
		for (int i = 0; i < init.size(); i++) {
			new_vec.append(init[i]);
		}
		return new_vec;
	}
	HVector& operator=(const HVector& other) {
		for (int i = 0; i < other.len(); i++) {
			append(other[i]);
		}
		return *this;
	}
	bool operator==(const HVector& other) const {
		if (length != other.length)
			return false;
		for (int i = 0; i < length; i++) {
			if (vec[i] != other[i])
				return false;
		}
		return true;
	}
};

template <typename Tlloc = SimpleAllocator<char>>
class String : public HVector<char, Tlloc> {
public:
	String() : HVector<char, Tlloc>() {}
	String(const HVector<char, Tlloc>& other) : HVector<char, Tlloc>(other) {}


	String(const char* s) {
		for (size_t i = 0; s[i] != '\0'; i++) {
			this->append(s[i]);
		}
	}

	using HVector<char, Tlloc>::operator=;
	using HVector<char, Tlloc>::operator+;

	friend std::ostream& operator<<(std::ostream& os, const String& p) {
		if (p.vec == nullptr) {
			os << "\"\"";
		} else {
			os << "\"";
			for (size_t i = 0; i < p.length; i++) {
				os << p.vec[i];
			}
			os << "\"";
		}
		return os;
	}
};