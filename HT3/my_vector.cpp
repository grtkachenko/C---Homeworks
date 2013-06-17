#include "my_vector.h"
#include <vector>

my_vector::my_vector() {
	is_empty = true;
}

my_vector::my_vector(size_t num, unsigned val) {
	if (num == 0) {
		is_empty = true;
		return;
	}
	if (num <= size_small) {
		is_empty = false;
		is_small = true;
		small_data_size = num;
		for (size_t i = 0; i < num; i++) {
			small_object[i] = val;
		}
		return;
	}
	is_empty = is_small = false;
	cnt_ref = new int (1);
	data = new std::vector<unsigned>;
	for (size_t i = 0; i < num; i++) {
		(*data).push_back(val);
	}
}

my_vector::my_vector(const my_vector &val) {
	if (val.is_empty) {
		is_empty = true;
		return;
	}
	if (val.is_small) {
		is_empty = false;
		is_small = true;
		small_data_size = val.small_data_size;
		for (size_t i = 0; i < size_small; i++) {
			small_object[i] = val.small_object[i];
		}
		return;
	}
	cnt_ref = val.cnt_ref;
	data = val.data;
	(*cnt_ref)++;
	is_empty = is_small = false;
}
my_vector::~my_vector() {
	if (!is_small && !is_empty) {
		this->clear_vector();
	}
}
size_t my_vector::size() const {
	if (is_empty) {
		return 0;
	}
	if (is_small) {
		return small_data_size;
	}
	return (*data).size();
}
unsigned my_vector::operator[] (size_t index) const {
	if (is_small) {
		return small_object[index];
	}
	return (*data)[index];
}	
void my_vector::push_back(unsigned val) {
	if (is_empty || (is_small && small_data_size < size_small)) {
		small_data_size = is_empty ? 1 : small_data_size + 1;
		is_empty = false;
		is_small = true;
		small_object[small_data_size - 1] = val;
		return;
	}
	if (is_small) {
		this->small_to_big();
		(*data).push_back(val);
		return;
	}
	
	if ((*cnt_ref) != 1) {
		this->create_new_vector();
	}
	(*data).push_back(val);
}
my_vector& my_vector::operator = (const my_vector& val) {
	if (val.is_empty) {
		is_empty = true;
		return (*this);
	}
	if (val.is_small) {
		is_empty = false;
		is_small = true;
		small_data_size = val.small_data_size;
		for (size_t i = 0; i < size_small; i++) {
			small_object[i] = val.small_object[i];
		}
		return (*this);
	}
	cnt_ref = val.cnt_ref;
	data = val.data;
	(*cnt_ref)++;
	is_empty = is_small = false;
	return (*this);
}

void my_vector::pop_back() {
	if (is_small) {
		if (small_data_size == 1) {
			is_empty = true;
		} else {
			small_data_size--;
		}
		return;
	}
	if ((*cnt_ref) != 1) {
		this->create_new_vector();
	}
	if ((*data).size() == size_small + 1) {
		(*data).pop_back();
		this->big_to_small();
	} else {
		(*data).pop_back();
	}
}

void my_vector::create_new_vector() {
	data = new std::vector<unsigned> (*data);
	(*cnt_ref)--;
	cnt_ref = new int (1);
}

void my_vector::clear_vector() {
	if ((*cnt_ref) == 1) {
		(*data).clear();
		delete data;
		delete cnt_ref;
	} else {
		(*cnt_ref)--;
	}
}

void my_vector::small_to_big() {
	is_small = is_empty = false;
	data = new std::vector<unsigned>;
	for (size_t i = 0; i < size_small; i++) {
		(*data).push_back(small_object[i]);
	}
	cnt_ref = new int(1); 
}

void my_vector::big_to_small() {
	is_small = true;
	for (size_t i = 0; i < size_small; i++) {
		small_object[i] = (*data)[i];
	}
	small_data_size = size_small;
	this->clear_vector();
}


unsigned& my_vector::put_to(size_t index) {
	if (is_small) {
		return small_object[index];
	} else {
		if ((*cnt_ref) != 1) {
			data = new std::vector<unsigned> (*data);
			(*cnt_ref)--;
			cnt_ref = new int (1);
		}
		return (*data)[index];
	}
}