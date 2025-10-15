#include "alloc.tpp"
using namespace std;

template <typename T, typename Tlloc = SimpleAllocator<T>>
class HVector {
protected:
	T *vec = nullptr;
	Tlloc allocator;

	size_t length = 0;
	size_t capacity = 0;
public:
	//HVector(T *base_arr) {
	//	vec = base_arr;
	//}
	HVector() : vec(nullptr), length(0), capacity(0) {}
	~HVector() {
		allocator.dealdestruct(&vec, capacity)
	}

	
};