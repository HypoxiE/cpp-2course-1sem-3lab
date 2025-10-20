template <typename T>
class SimpleAllocator {
public:
	using value_type = T;

	SimpleAllocator() = default;

	[[nodiscard]] T* allocate(size_t n) {
		return static_cast<T*>(::operator new(sizeof(T) * n));
	}
	void deallocate(T* p, size_t) {
		::operator delete(p);
	}

	template <typename ForwType>
	ForwType&& my_forward(typename std::remove_reference<ForwType>::type& t) noexcept {
		return static_cast<ForwType&&>(t);
	}
	template <typename... Args>
	void construct(T* p, Args&&... args) {
		::new ((void*)p) T(my_forward<Args>(args)...);
	}
	void destroy(T* p) {
		p->~T();
	}

	//[[nodiscard]] T* allconstruct(size_t n) {
	//	return new T [n];
	//}
	//void dealdestruct(T* p, size_t) {
	//	delete(p);
	//}
};
