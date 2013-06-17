#include "big_integer.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
unsigned  PLUS_BASE = 0, MINUS_BASE = ~0, MAX_BASE = ~0;

int BASE_DEG = 32;

unsigned long long BASE = (unsigned long long)MAX_BASE + 1L;

sign get_sign(const big_integer& val) {
	return val.data[val.data.size() - 1] == 0 ? PLUS : MINUS;
}

big_integer::big_integer() {
	data.push_back(0);
}

void normalize_size(my_vector &data, int size_code, sign cur_sign) {
	for (size_t i = data.size(); i < size_code; i++) {
		data.push_back(cur_sign == PLUS ? PLUS_BASE : MINUS_BASE);
	}
}

void fix_size(my_vector &data) {
	unsigned last = data[data.size() - 1];
	int num = 0;
	for (size_t i = data.size() - 1; i >= 0; i--) {
		if (data[i] != last) {
			num = i + 1;
			break;
		}
		if (i == 0) {
			break;
		}
	}
	int num_it = data.size();
	for (size_t i = num + 1; i < num_it; i++) {
		data.pop_back();
	}
}

big_integer::big_integer(int int_val) {
	data.push_back(int_val);
	if (int_val >= 0) {
		data.push_back(PLUS_BASE);
		return;
	}
	data.push_back(MINUS_BASE);
}

big_integer::big_integer(const big_integer& copy) 
	:data(copy.data)
{}

big_integer::big_integer(const string& st) {
	bool ch_sign = false;
	string tmp = st;
	if (st[0] == '-') {
		tmp = st.substr(1, st.size() - 1);	
		ch_sign = true;
	}
	vector<int> number(tmp.size());
	for (size_t i = 0; i < tmp.size(); i++) {
		number[tmp.size() - i - 1] = (int) (tmp[i] - '0');
	}
	while (true) {
		data.push_back(number[0] % 2 == 0 ? 0 : 1);
		if (number.size() == 1 && number[0] == 0) {
			break;
		}
		number[0] -= (number[0] % 2) == 1 ? 1 : 0;
		int shift = 0;
		for (size_t i = number.size() - 1; i >= 0; i--) {
			int cur = number[i] + shift * 10;
			number[i] = cur / 2;
			shift = cur % 2;
			if (i == 0) {
				break;
			}
		}
		while (number.size() > 1 && number.back() == 0) {
			number.pop_back();
		}
	}
	my_vector data_new;
	for (size_t i = 0; i < data.size(); i += BASE_DEG) {
		unsigned cur = 0, cur_deg = 1;
		for (size_t j = i; j < min(i + BASE_DEG, data.size()); j++) {
			cur += cur_deg * data[j];
			cur_deg *= 2;
		}
		data_new.push_back(cur);
	}
	while (data.size() > 0) {
		data.pop_back();
	}
	for (size_t i = 0; i < data_new.size(); i++) {
		data.push_back(data_new[i]);
	}
	data.push_back(PLUS_BASE);
	if (ch_sign) {
		(*this) = - (*this);
	}
}

big_integer& big_integer::operator = (const big_integer& val) {
	data = val.data;
	return *this;
}

//comparisons
bool operator == (const big_integer& a, const big_integer& b) {
	int size_code = max(a.data.size(), b.data.size());
	normalize_size(a.data, size_code, get_sign(a));
	normalize_size(b.data, size_code, get_sign(b));
	if (a.data.size() != b.data.size()) {
		return false;
	}
	for (size_t i = 0; i < a.data.size(); i++) {
		if (a.data[i] != b.data[i]) {
			return false;
		}
	}
	fix_size(a.data);
	fix_size(b.data);
	return true;
}	

bool operator < (const big_integer& a, const big_integer& b) {
	int size_code = max(a.data.size(), b.data.size());
	normalize_size(a.data, size_code, get_sign(a));
	normalize_size(b.data, size_code, get_sign(b));
	if (get_sign(a) != get_sign(b)) {
		if (get_sign(a) == MINUS) {
			return true;
		} else {
			return false;
		}
	}
	for (size_t i = a.data.size() - 2; i >= 0; i--) {
		if (a.data[i] < b.data[i]) {
			return true;
		}
		if (a.data[i] > b.data.put_to(i) == 0) {
			return false;
		}
		if (i == 0) {
			break;
		}
	}
	return false;
}

bool operator > (const big_integer& a, const big_integer& b) {
	return (!(a < b) && !(a == b)); 
}

bool operator >= (const big_integer& a, const big_integer& b) {
	return ((a > b) || (a == b));
}

bool operator <= (const big_integer& a, const big_integer& b) {
	return ((a < b) || (a == b));
}

bool operator != (const big_integer& a, const big_integer& b) {
	return !(a == b);
}

//arifm
big_integer big_integer::operator - () {
	big_integer res(*this);
	res = ~res;
	for (size_t i = 0; i < res.data.size(); i++)
		if (res.data.put_to(i) == MAX_BASE) {
			res.data.put_to(i) = 0;
		} else {
			res.data.put_to(i)++;
			break;
		}
	return res;
}

big_integer big_integer::operator + () {
	return *this;
}

big_integer operator + (const big_integer& a, const big_integer& b) {
	int size_code = max(a.data.size(), b.data.size()) + 2;
	normalize_size(a.data, size_code, get_sign(a));
	normalize_size(b.data, size_code, get_sign(b));
	unsigned long long shift = 0;
	big_integer c;
	normalize_size(c.data, size_code, get_sign(c));
	for (size_t i = 0; i < a.data.size(); i++) {
		c.data.put_to(i) = (((unsigned long long)a.data[i] + b.data[i] + shift) % BASE);
		shift = ((unsigned long long)a.data[i] + b.data[i] + shift) / BASE;
	}

	fix_size(a.data);
	fix_size(b.data);
	fix_size(c.data);
	return c;
}

big_integer& big_integer::operator += (const big_integer& val) {
	*this = *this + val;
	return *this;
}

big_integer operator - (const big_integer& a, const big_integer& b) {
	big_integer c, d = b;
	d = -d;
	c = a + d;
	return c;
}

big_integer& big_integer::operator -= (const big_integer& val) {
	*this = *this - val;
	return *this;
}

big_integer operator % (const big_integer& a, const big_integer& b) {
	big_integer tmp_a = a, tmp_b = b;
	if (get_sign(tmp_a) == MINUS) {
		tmp_a = -tmp_a;
	}
	if (get_sign(tmp_b) == MINUS) {
		tmp_b = -tmp_b;
	}
	big_integer ans = tmp_a - tmp_b * (tmp_a / tmp_b);
	if (get_sign(a) == MINUS) {
		ans = -ans;
	}
	return ans;
}

big_integer& big_integer::operator %= (const big_integer& val) {
	*this = *this % val;
	return *this;
}

big_integer operator * (const big_integer& a, const big_integer& b) {
	big_integer help_a = a, help_b = b;
	bool ch_sign = false;
	if ((help_a < 0 && help_b > 0) || (help_a > 0 && help_b < 0)) {
		ch_sign = true;
	}
	if (help_a < 0) {
		help_a = -help_a;
	}
	if (help_b < 0) {
		help_b = -help_b;
	}

	my_vector res(help_a.data.size() + help_b.data.size() + 3, 0);

	for (size_t i = 0; i < help_a.data.size(); i++)
		for (size_t j = 0, shift = 0; j < help_b.data.size() || shift; j++) {
			unsigned long long cur = (unsigned long long)res[i + j] + help_a.data[i] * 1ll * (j < (int)help_b.data.size() ? help_b.data[j] : 0) + (unsigned long long)shift;
			res.put_to(i + j) = unsigned (cur % BASE);
			shift = unsigned (cur / BASE);
	}
	
	res.push_back(PLUS_BASE);
	fix_size(res);
	big_integer ans;
	ans.data = res;
	if (ch_sign) {
		ans = -ans;
	}
	fix_size(ans.data);
	return ans;
}

big_integer& big_integer::operator *= (const big_integer& val) {
	*this = *this * val;
	return *this;
}

big_integer operator / (const big_integer& a, const big_integer& b) {
	fix_size(a.data);
	fix_size(b.data);
	big_integer help_a = a, help_b = b;

	bool ch_sign = false;
	if ((help_a < 0 && help_b > 0) || (help_a > 0 && help_b < 0)) {
		ch_sign = true;
	}
	if (help_a < 0) {
		help_a = -help_a;
	}
	if (help_b < 0) {
		help_b = -help_b;
	}
	fix_size(help_a.data);
	fix_size(help_b.data);

	my_vector to_binary_a, to_binary_b;
	for (size_t i = 0; i < help_a.data.size(); i++) {
		for (size_t j = 0; j < BASE_DEG; j++) {
			if (help_a.data[i] % 2 == 0) {
				to_binary_a.push_back(0);
			} else {
				to_binary_a.push_back(1);
			}
			help_a.data.put_to(i) /= 2;
		}
	}
	for (size_t i = 0; i < help_b.data.size(); i++) {
		for (size_t j = 0; j < BASE_DEG; j++) {
			if (help_b.data[i] % 2 == 0) {
				to_binary_b.push_back(0);
			} else {
				to_binary_b.push_back(1);
			}
			help_b.data.put_to(i) /= 2;
		}
	}

	help_a.data = to_binary_a;
	help_b.data = to_binary_b;
	fix_size(help_a.data);
	fix_size(help_b.data);
	//reverse numbers
	my_vector x;
	my_vector y;
	
	for (size_t i = help_a.data.size() - 2; i >= 0; i--) {
		x.push_back(help_a.data[i]);
		if (i == 0) {
			break;
		}
	}
	for (size_t i = help_b.data.size() - 2; i >= 0; i--) {
		y.push_back(help_b.data[i]);
		if (i == 0) {
			break;
		}
	}
	my_vector ans(x.size(), 0);
	int left = 0;
	while (true) {
		int right = left + y.size() - 1;
		if (right >= x.size()) {
			break;
		}
		bool less = false;
		for (size_t i = 0; i < y.size(); i++) {
			if (x[left + i] > y[i]) {
				break;
			}
			if (x[left + i] < y[i]) {
				less = true;
				break;
			}
		}
		if (less) {
			right++;
		}
		if (right >= x.size()) {
			break;
		}
		ans.put_to(right) = 1;

		for (size_t i = y.size() - 1; i >= 0; i--) {
			int cur_right = right - (y.size() - 1 - i);
			if (y[i] <= x[cur_right]) {
				x.put_to(cur_right) -= y[i];
			} else {
				x.put_to(cur_right) = 1;
				int cur = cur_right - 1;
				while (x[cur] == 0) {
					x.put_to(cur) = 1;
					cur--;
				}
				x.put_to(cur)--;
			}
			if (i == 0) {
				break;
			}
		}
		while (left < x.size() && x[left] == 0) {
			left++;
		}
	}

	big_integer res;
	res.data.pop_back();
	for (size_t i = ans.size() - 1; i >= 0; i--) {
		res.data.push_back(ans[i]);
		if (i == 0) {
			break;
		}
	}
	res.data.push_back(0);
	my_vector data_new;
	for (size_t i = 0; i < res.data.size(); i += BASE_DEG) {
		unsigned cur = 0, cur_deg = 1;
		for (size_t j = i; j < min(i + BASE_DEG, res.data.size()); j++) {
			cur += cur_deg * res.data[j];
			cur_deg *= 2;
		}
		data_new.push_back(cur);
	}
	data_new.push_back(PLUS_BASE);
	res.data = data_new;
	fix_size(res.data);
	if (ch_sign) {
		res = -res;
	}
	fix_size(res.data);
	return res;
}

big_integer& big_integer::operator /= (const big_integer& val) {
	*this = *this / val;
	return *this;
}

big_integer& big_integer::operator ++ () {
	*this += 1;
	return *this;
}

big_integer& big_integer::operator -- () {
	*this -= 1;
	return *this;
}

big_integer big_integer::operator ++ (int) {
	big_integer tmp(*this);
	++(*this);
	return tmp;
}

big_integer big_integer::operator -- (int) {
	big_integer tmp(*this);
	--(*this);
	return tmp;
}

//logical 
big_integer operator & (const big_integer& a, const big_integer& b) {
	int size_code = max(a.data.size(), b.data.size());
	normalize_size(a.data, size_code, get_sign(a));
	normalize_size(b.data, size_code, get_sign(b));

	big_integer res;
	normalize_size(res.data, size_code, get_sign(res));
	for (size_t i = 0; i < a.data.size(); i++) {
		res.data.put_to(i) = a.data[i] & b.data[i];
	}
	fix_size(res.data);
	return res;
}

big_integer& big_integer::operator &= (const big_integer& val) {
	*this = *this & val;
	return *this;
}

big_integer operator | (const big_integer& a, const big_integer& b) {
	int size_code = max(a.data.size(), b.data.size());
	normalize_size(a.data, size_code, get_sign(a));
	normalize_size(b.data, size_code, get_sign(b));

	big_integer res;
	normalize_size(res.data, size_code, get_sign(res));
	for (size_t i = 0; i < a.data.size(); i++) {
		res.data.put_to(i) = a.data[i] | b.data[i];
	}
	fix_size(res.data);
	return res;
}

big_integer& big_integer::operator |= (const big_integer& val) {
	*this = *this | val;
	return *this;
}

big_integer operator ^ (const big_integer& a, const big_integer& b) {
	int size_code = max(a.data.size(), b.data.size());
	normalize_size(a.data, size_code, get_sign(a));
	normalize_size(b.data, size_code, get_sign(b));

	big_integer res;
	normalize_size(res.data, size_code, get_sign(res));
	for (size_t i = 0; i < a.data.size(); i++) {
		res.data.put_to(i) = a.data[i] ^ b.data[i];
	}
	fix_size(res.data);
	return res;
}

big_integer& big_integer::operator ^= (const big_integer& val) {
	*this = *this ^ val;
	return *this;
}

big_integer big_integer::operator ~ () {
	big_integer res;
	normalize_size(res.data, data.size(), get_sign(res));
	for (size_t i = 0; i < res.data.size(); i++) {
		res.data.put_to(i) = ~data[i];
	}
	return res;
}

int set_bit(unsigned data, size_t i, int val) {
	
	int res = data & (~(1 << i));
	if (val != 0) {
		res += (1 << i);
	}
	return res;
}

int get_bit(const my_vector &data, size_t i) {
	return (data[i / BASE_DEG] >> (i % BASE_DEG)) & 1;
}

big_integer operator >> (const big_integer& val, int num) {
	big_integer res(val);
	int cur_int_sign = get_sign(val) == PLUS ? 0 : 1;
	for (size_t i = val.data.size() * BASE_DEG - num; i < val.data.size() * BASE_DEG ; i++) {
		int cur_block = i / BASE_DEG;
		res.data.put_to(cur_block) = set_bit(res.data[cur_block], i - cur_block * BASE_DEG, cur_int_sign);	
	}
	for (size_t i = 0; i < val.data.size() * BASE_DEG - num; i++) {
		int cur_block = i / BASE_DEG, cur_bit = get_bit(val.data, i + num);
		res.data.put_to(cur_block) = set_bit(res.data[cur_block], i - cur_block * BASE_DEG, cur_bit);	
	}
	return res;
}

big_integer& big_integer::operator >>= (int num) {
	*this = *this >> num;
	return *this;
}

big_integer operator << (const big_integer& val, int num) {
	big_integer res;
	int i = BASE_DEG * val.data.size() + num - 1;
	normalize_size(res.data, val.data.size() + num / BASE_DEG + 1, get_sign(res));
	for (i == BASE_DEG * val.data.size() + num - 1; i >= num; i--) {
		if (get_bit(val.data, i - num) != 0) {
			res.data.put_to(i / BASE_DEG) += (1 << (i % BASE_DEG));
		}
	}
	fix_size(res.data);
	return res;
}

big_integer& big_integer::operator <<= (int num) {
	*this = *this << num;
	return *this;
}

my_vector add_dec(const my_vector& a, const my_vector& b) {
	my_vector c(a.size(), 0);
	c = a;
	int shift = 0;
	for (size_t i = 0; i < max(c.size(),b.size()) || shift; ++i) {
		if (i == a.size()) {
			c.push_back (0);
		}
		c.put_to(i) += shift + (i < b.size() ? b[i] : 0);
		shift = c[i] >= 10;
		if (shift)  c.put_to(i) -= 10;
	}
	return c;
}

my_vector power_two_dec(int deg) {
	my_vector res(1, 1);

	for (size_t i = 0; i < deg; i++) {
		int shift = 0;
		for (size_t j = 0; j < res.size(); j++) {
			res.put_to(j) = res[j] * 2 + shift;
			if (res[j] > 9) {
				shift = 1;
				res.put_to(j) -= 10;
			} else {
				shift = 0;
			}
		}
		if (shift != 0) {
			res.push_back(shift);
		}
	}
	return res;
}

string to_string(const big_integer& val) {
	fix_size(val.data);

	big_integer tmp = val;
	string res = "";
	my_vector ans(val.data.size(), 0);
	if (get_sign(val) == MINUS) {
		res += "-";
		tmp = -tmp;
	}
	for (size_t i = 0; i < val.data.size(); i++) {
		for (size_t j = 0; j < BASE_DEG; j++) {
			if (get_bit(val.data, i * BASE_DEG + j) == 1) {
				ans = add_dec(ans, power_two_dec(i * BASE_DEG + j));
			}			
		}
	}
	for (size_t i = ans.size() - 1; i >= 0; i--) {
		if (ans[i] != 0) {
			for (size_t j = i; j >= 0; j--) {
				res += ('0' + ans[j]);
				if (j == 0) {
					break;
				}
			}
			return res;
		}
		if (i == 0) {
			break;
		}
	}
	return "0";
}
	