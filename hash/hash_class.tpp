
template <typename TKey, typename TVal>
class HashTable {
private:
	TKey *keys;
	TVal *values;

	size_t lenght;
	size_t size;
public:
	HashTable(std::string p_name, unsigned p_age)
	{
		keys = nullptr;
		values = nullptr;
		lenght = 0;
		size = 0;
	}
};