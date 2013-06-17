#ifndef TREESET_H
#define	TREESET_H
#include <iterator>

template<typename T>
struct tree_set;

template <typename T>
struct set_iterator;

template <typename T>
struct const_set_iterator;


template <typename T>
struct node {
	T value;
	node *left, *right, *parent;

	node() {}

	node(T value, node *left, node *right, node *parent) : value(value), left(left), right(right), parent(parent) {}
};

struct base
{
	virtual char const* msg()
	{
		return "base";
	}
};

struct derived : base
{
	char const* msg()
	{
		return "derived";
	}
};

template <typename T>
struct set_iterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t, T*, T&> {
private:
	node<T> *data;
public:
	set_iterator() {}

	set_iterator(set_iterator<T> const& rhs) : data(rhs.data) {}

	set_iterator<T>& operator = (set_iterator<T> const& rhs) {
		data = rhs.data;
		return *this;
	}

	set_iterator<T> operator ++ (int) {
		if (data->parent == nullptr) {
			throw derived();

		}
		set_iterator<T> ans = *this;
		if (data->right != nullptr) {
			data = data->right;
			while (data->left != nullptr) {
				data = data->left;
			}
			return ans;
		}
		while (data == data->parent->right) {
			data = data->parent;
		}
		data = data->parent;
		return ans;
	}

	set_iterator<T>& operator ++ () {
		if (data->parent == nullptr) {
			throw new std::exception();
		}

		if (data->right != nullptr) {
			data = data->right;
			while (data->left != nullptr) {
				data = data->left;
			}
			return *this;
		}
		while (data == data->parent->right) {
			data = data->parent;
		}
		data = data->parent;
		return *this;
	}

	set_iterator<T> operator -- (int) {


		set_iterator<T> ans = *this;
		if (data->left != nullptr) {
			data = data->left;
			while (data->right != nullptr) {
				data = data->right;
			}
			return ans;
		}
		while (data == data->parent->left) {
			data = data->parent;
			if (data == nullptr) {
				throw new std::exception();
			}
		}
		data = data->parent;
		if (data = )
		return ans;
	}

	set_iterator<T>& operator -- () {
		if (data->left != nullptr) {
			data = data->left;
			while (data->right != nullptr) {
				data = data->right;
			}
			return *this;
		}
		while (data == data->parent->left) {
			data = data->parent;
			if (data == nullptr) {
				throw new std::exception();
			}
		}
		data = data->parent;
		return *this;
	}

	T* operator -> () const {
		return &(data->value);
	}

	T& operator * () const {
		return data->value;
	}

	
	template<typename U>
	bool operator == (set_iterator<U> const& rhs) const {
		return data == rhs.data;
	}

	template<typename U>
	bool operator != (set_iterator<U> const& rhs) const {
		return data != rhs.data;
	}

	set_iterator(node<T> * data) : data(data) {

	}
	friend struct tree_set<T>;
};

template <class T>
struct const_set_iterator : public std::iterator<std::bidirectional_iterator_tag, const T, ptrdiff_t, const T*, const T&> {
private:
	node<T> *data;
public:
	const_set_iterator() {}

	const_set_iterator(const_set_iterator<T> const& rhs) : data(rhs.data) {}

	const_set_iterator<T>& operator = (const_set_iterator<T> const& rhs) {
		data = rhs.data;
		return *this;
	}

	const_set_iterator<T> operator ++ (int) {
		if (data->parent == nullptr) {
			throw new std::exception();
		}
		const_set_iterator<T> ans = *this;
		if (data->right != nullptr) {
			data = data->right;
			while (data->left != nullptr) {
				data = data->left;
			}
			return ans;
		}
		while (data == data->parent->right) {
			data = data->parent;
		}
		data = data->parent;
		return ans;
	}

	const_set_iterator<T>& operator ++ () {
		if (data->parent == nullptr) {
			throw new std::exception();
		}
		if (data->right != nullptr) {
			data = data->right;
			while (data->left != nullptr) {
				data = data->left;
			}
			return *this;
		}
		while (data == data->parent->right) {
			data = data->parent;
		}
		data = data->parent;
		return *this;
	}

	const_set_iterator<T> operator -- (int) {
		const_set_iterator<T> ans = *this;
		if (data->left != nullptr) {
			data = data->left;
			while (data->right != nullptr) {
				data = data->right;
			}
			return ans;
		}
		while (data == data->parent->left) {
			data = data->parent;
			if (data == nullptr) {
				throw new std::exception();
			}
		}
		data = data->parent;
		return ans;
	}

	const_set_iterator<T>& operator -- () {
		if (data->left != nullptr) {
			data = data->left;
			while (data->right != nullptr) {
				data = data->right;
			}
			return *this;
		}
		while (data == data->parent->left) {
			data = data->parent;
			if (data == nullptr) {
				throw new std::exception();
			}
		}
		data = data->parent;
		return *this;
	}

	const T* operator -> () const {
		return &(data->value);
	}

	const T& operator * () const {
		return data->value;
	}

	
	template<typename U>
	bool operator == (const_set_iterator<U> const& rhs) const {
		return data == rhs.data;
	}

	template<typename U>
	bool operator!=(const_set_iterator<U> const& rhs) const {
		return data != rhs.data;
	}

	const_set_iterator(node<T> * data) : data(data) {

	}
};

template<typename T>
struct tree_set {
private:
	node<T> *fake_max;
	size_t tree_size;

public:
	typedef set_iterator<T> iterator;
	typedef const_set_iterator<T> const_iterator;
	typedef std::reverse_iterator< set_iterator<T> > reverse_iterator;
	typedef std::reverse_iterator< const_set_iterator<T> > const_reverse_iterator;

	tree_set() : tree_size(0), fake_max(new node<T> ()) {
		fake_max->left = fake_max->right = fake_max->parent= nullptr;
	}

	tree_set(tree_set<T> const& rhs) : tree_size(0), fake_max(new node<T> ()) {
		fake_max->left = fake_max->right = fake_max->parent= nullptr;

		insert(rhs.begin(), rhs.end());
	}

	template<class InputIterator >
	tree_set(InputIterator first, InputIterator last) : tree_size(0), fake_max(new node<T> ()) {
		fake_max->left = fake_max->right = fake_max->parent= nullptr;

		insert(first, last);
	}

	iterator begin() {
		node<T> *cur = fake_max;
		while (cur->left != nullptr) {
			cur = cur->left;
		}
		return iterator(cur);
	}

	const_iterator begin() const {
		node<T> *cur = fake_max;
		while (cur->left != nullptr) {
			cur = cur->left;
		}
		return const_iterator(cur);
	}

	iterator end() {
		return iterator(fake_max);
	}

	const_iterator end() const {
		return const_iterator(fake_max);
	}

	reverse_iterator rend() {
		node<T> *cur = fake_max;
		while (cur->left != nullptr) {
			cur = cur->left;
		}
		return reverse_iterator(cur);
	}

	const_reverse_iterator rend() const {
		node<T> *cur = fake_max;
		while (cur->left != nullptr) {
			cur = cur->left;
		}
		return const_reverse_iterator(cur);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(fake_max);
	}

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(fake_max);
	}

	size_t size() const {
		return tree_size;
	}

	bool empty() const {
		return size() == 0;
	}

	iterator find ( const T& val) {
		node<T> *cur = fake_max->left;
		while (cur != nullptr) {
			if (cur->value == val) {
				iterator ans(cur);
				return ans;
			}
			if (cur->value > val) {
				cur = cur->left;
			} else {
				cur = cur->right;
			}
		}
		
		return end();
	}

	iterator insert(T value) {
		if (find(value) != end()) {
			return find(value);
		}
		
		if (empty()) {
			tree_size++;
			node<T> *newNode = new node<T> (value, nullptr, nullptr, fake_max);
			fake_max->left = newNode;
			return iterator(newNode);
		}

		tree_size++;
		node<T> *cur = fake_max->left;
		while (true) {
			if (cur->value > value) {
				if (cur->left == nullptr) {
					node<T> *newNode = new node<T> (value, nullptr, nullptr, cur);
					cur->left = newNode;
					return iterator(newNode);
				}
				cur = cur->left;
			} else {
				if (cur->right == nullptr) {
					node<T> *newNode = new node<T> (value, nullptr, nullptr, cur);
					cur->right = newNode;
					return iterator(newNode);
				}
				cur = cur->right;
			}
		}
	}
	
	template<class InputIterator >
	void insert(InputIterator first, InputIterator last) {
		iterator result;
		for (InputIterator it = first; it != last; it++) {
			insert((*it));
		}
	}

	void erase ( iterator pos ) {
		if (pos.data == fake_max) {
			throw new std::exception();
		}
		tree_size--;
		node<T> *cur = pos.data;
		node<T> *initial = pos.data;

		if (cur->left == nullptr) {
			if (cur->parent->left == cur) {
				if (cur->right == nullptr) {
					cur->parent->left = nullptr;
					delete cur;
					return;
				}
				cur->parent->left = cur->right;
				cur->right->parent = cur->parent;
				delete cur;
				return;
			} else {
				if (cur->right == nullptr) {
					cur->parent->right = nullptr;
					delete cur;
					return;
				}
				cur->parent->right = cur->right;
				cur->right->parent = cur->parent;
				delete cur;
				return;
			}
		}
		
		cur = cur->left;
		while (cur->right != nullptr) {
			cur = cur->right;
		}
		if (cur->left == nullptr) {
			cur->parent = nullptr;
			initial->value = cur->value;
			delete cur;
		} else {
			cur->parent->right = cur->left;
			cur->left->parent = cur->parent;
			initial->value = cur->value;
			delete cur;
		}
	}
	
	void erase ( const T& value ) {
		if (find(value) == end()) {
			return;
		}
		erase(find(value));
	}

	void erase ( iterator first, iterator last ) {
		for (iterator it = first; it != last; it++) {
			erase(it);
		}
	}

	iterator lower_bound ( const T& value ) {
		if (empty()) {
			return end();
		}
		
		node<T> *cur = fake_max->left;
		while (cur->right != nullptr) {
			cur = cur->right;
		}
		if (cur->value < value) {
			return end();
		}

		T min_val = cur->value;
		cur = fake_max->left;
		while (cur != nullptr) {
			if (cur->value >= value) {
				min_val = min(min_val, cur->value);
			}
			if (cur ->value == value) {
				break;
			}
			if (cur->value > value) {
				cur = cur->left;
			} else {
				cur = cur->right;
			}
		}

		return find(min_val);
	}

	iterator upper_bound ( const T& value ) {
		if (empty()) {
			return end();
		}
		
		node<T> *cur = fake_max->left;
		while (cur->right != nullptr) {
			cur = cur->right;
		}
		if (cur->value <= value) {
			return end();
		}

		T min_val = cur->value;
		cur = fake_max->left;
		while (cur != nullptr) {
			if (cur->value > value) {
				min_val = min(min_val, cur->value);
			}
			if (cur->value > value) {
				cur = cur->left;
			} else {
				cur = cur->right;
			}
		}

		return find(min_val);
	}

	~tree_set() {
		iterator it = begin();
		while (it != end()) {
			iterator tmp = it;
			tmp++;
			erase(it);
			it = tmp;
		}
        delete fake_max;
    }

};
#endif