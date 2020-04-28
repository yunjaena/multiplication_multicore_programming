#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "Algorithm.h"

class Karatsuba : public Algorithm
{
private:
	vector<int> v1;
	vector<int> v2;

	void set_vector(const string &s1, const string &s2);

	void normalize(vector<int> &num);
	void addTo(vector<int> &a, const vector<int> &b, int k);
	void parallel_addTo(vector<int> &a, const vector<int> &b, int k);
	void subFrom(vector<int> &a, const vector<int> &b);
	void parallel_subFrom(vector<int> &a, const vector<int> &b);
	vector<int> multiply(const vector<int> &a, const vector<int> &b);
	vector<int> parallel_multiply(const vector<int> &a, const vector<int> &b);

	vector<int> serial_karatsuba(const vector<int> &a, const vector<int> &b);
	string seial_get_result_from_vector(const vector<int> &vec);

	vector<int> parallel_karatsuba(const vector<int> &a, const vector<int> &b);
	string parallel_get_result_from_vector(const vector<int> &vec);

	vector<int> string_to_vi(const string &s) {
		int n = s.size();
		vector<int> ret(n);
		for (int i = 0; i < n; i++)
			ret[i] = s[i] - '0';
		return ret;
	}

public:
	virtual string get_parallel_result(const string&, const string&);
	virtual string get_serial_result(const string&, const string&);
};

