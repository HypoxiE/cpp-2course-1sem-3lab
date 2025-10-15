template <typename T>
class SimpleAllocator {
public:
	using value_type = T;

	SimpleAllocator() = default;

	[[nodiscard]] T* allocate(unsigned int n) {
		return static_cast<T*>(::operator new(sizeof(T) * n));
	}
	void deallocate(T* p, unsigned int) {
		::operator delete(p);
	}

	[[nodiscard]] T* allconstruct(unsigned int n) {
		return new T [n];
	}
	void dealdestruct(T* p, unsigned int) {
		delete(p);
	}
};
