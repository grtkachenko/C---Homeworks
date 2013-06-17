#include <vector>

class my_vector {
private:
	static const size_t size_small = 7;
	// big object
	std::vector<unsigned> *data;
	int *cnt_ref;
	// small object
	unsigned small_object[size_small];
	bool is_empty, is_small;
	int small_data_size;
	
public:
	my_vector();
	my_vector(const my_vector&);
	my_vector(size_t, unsigned);
	~my_vector();
	size_t size() const;
	void push_back(unsigned);
	unsigned& put_to(size_t);
	void pop_back();
	unsigned operator [] (const size_t) const;
	my_vector& operator = (const my_vector&);
	void create_new_vector();
	void clear_vector();
	void small_to_big();
	void big_to_small();
};
