#include "Karatsuba.h"
#include <omp.h>


string Karatsuba::get_serial_result(const string &s1, const string &s2) {
	set_vector(s1, s2);
	vector<int> result = serial_karatsuba(v1, v2);
	return seial_get_result_from_vector(result);
}

string Karatsuba::seial_get_result_from_vector(const vector<int> &vec) {
	string ret;
	for (int i : vec) ret += i + '0';
	reverse(ret.begin(), ret.end());

	return ret;
}

string Karatsuba::get_parallel_result(const string& s1, const string& s2) {
	set_vector(s1, s2);
	vector<int> result = parallel_karatsuba(v1, v2);
	return parallel_get_result_from_vector(result);
}

string Karatsuba::parallel_get_result_from_vector(const vector<int> &vec) {
	int n = vec.size();
	string ret(n, 0);
	#pragma	omp parallel for
	for (int i = 0; i < n; ++i) {
		ret[i] = vec[i] + '0';
	}
	reverse(ret.begin(), ret.end());

	return ret;
}

void Karatsuba::set_vector(const string &s1, const string &s2) {
	v1 = string_to_vi(s1);
	v2 = string_to_vi(s2);
	reverse(v1.begin(), v1.end());
	reverse(v2.begin(), v2.end());
}

void Karatsuba::normalize(vector<int> &num) {
	num.push_back(0);
	int n = num.size();

	for (int i = 0; i < n; ++i) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while (num.size() > 1 && num.back() == 0) num.pop_back();
}

void Karatsuba::addTo(vector<int> &a, const vector<int> &b, int k) {
	int bn = b.size();
	a.resize(max<int>(a.size(), bn + k) + 1);
	for (int i = 0; i < bn; ++i)
		a[i + k] += b[i];
	normalize(a);
}

void Karatsuba::parallel_addTo(vector<int> &a, const vector<int> &b, int k) {
	int bn = b.size();
	a.resize(max<int>(a.size(), bn + k) + 1);
	#pragma omp parallel for
	for (int i = 0; i < bn; ++i)
		a[i + k] += b[i];
	normalize(a);
}

void Karatsuba::subFrom(vector<int> &a, const vector<int> &b) {
	int bn = b.size();
	for (int i = 0; i < bn; ++i)
		a[i] -= b[i];
	normalize(a);
}

void Karatsuba::parallel_subFrom(vector<int> &a, const vector<int> &b) {
	int bn = b.size();
	#pragma omp parallel for
	for (int i = 0; i < bn; ++i)
		a[i] -= b[i];
	normalize(a);
}

vector<int> Karatsuba::multiply(const vector<int> &a, const vector<int> &b) {
	int an = a.size(), bn = b.size();
	vector<int> ret(an + bn + 1, 0);
	for (int i = 0; i < an; ++i)
		for (int j = 0; j < bn; ++j)
			ret[i + j] += a[i] * b[j];

	normalize(ret);
	return ret;
}

vector<int> Karatsuba::parallel_multiply(const vector<int> &a, const vector<int> &b) {
	int an = a.size(), bn = b.size();
	vector<int> ret(an + bn + 1, 0);
	#pragma omp parallel for schedule(static, 1)
	for (int i = 0; i < an + bn - 1; ++i)
		for (int j = 0; j <= i; ++j)
			ret[i] += a[i - j] * b[j];

	normalize(ret);
	return ret;
}

vector<int> Karatsuba::serial_karatsuba(const vector<int> &a, const vector<int> &b) {
	int an = a.size(), bn = b.size();
	if (an < bn) return serial_karatsuba(b, a);
	if (an == 0 || bn == 0) return {};
	if (an <= 50) return multiply(a, b);

	int half = an >> 1;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = serial_karatsuba(a1, b1);
	vector<int> z0 = serial_karatsuba(a0, b0);
	
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);

	vector<int> z1 = serial_karatsuba(a0, b0);
	
	subFrom(z1, z0);
	subFrom(z1, z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half << 1);

	return ret;
}

vector<int> Karatsuba::parallel_karatsuba(const vector<int> &a, const vector<int> &b) {
	int an = a.size(), bn = b.size();
	if (an < bn) return parallel_karatsuba(b, a);
	if (an == 0 || bn == 0) return {};
	if (an <= 50) return parallel_multiply(a, b);

	int half = an >> 1;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = parallel_karatsuba(a1, b1);
	vector<int> z0 = parallel_karatsuba(a0, b0);

	parallel_addTo(a0, a1, 0);
	parallel_addTo(b0, b1, 0);

	vector<int> z1 = parallel_karatsuba(a0, b0);

	parallel_subFrom(z1, z0);
	parallel_subFrom(z1, z2);

	vector<int> ret;
	parallel_addTo(ret, z0, 0);
	parallel_addTo(ret, z1, half);
	parallel_addTo(ret, z2, half << 1);

	return ret;
}