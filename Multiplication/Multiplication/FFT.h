#pragma once
#define _USE_MATH_DEFINES
#define ll long long
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h> 
#include <stack>
#include <queue>
#include <omp.h>
#include <vector>
#include <complex>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "Algorithm.h"

using namespace std;

class FFT : public Algorithm
{
private:
	vector<int> v1;
	vector<int> v2;
	typedef complex<double> base;

	void set_vector(std::string s1, std::string s2);

	void serial_fft(vector<base>& a, bool inv);
	vector<int> serial_multiply(vector<int>& A, vector<int>& B);
	string seial_get_result_from_vector(vector<int> &ret);

	void parallel_fft(vector<base>& a, bool inv);
	vector<int> parallel_multiply(vector<int>& A, vector<int>& B);
	string parallel_get_result_from_vector(vector<int>& ret);

	
	template <typename T>
	T bit_reverse(T n) {
		T ret = 0;
		while (n) {
			ret <<= 1;
			ret |= n & 1;
			n >>= 1;
		}
		return ret;
	}

	template <typename T>
	T power_of_2_ge_than(T n) {
		T ret = 1;
		while (n > ret) ret <<= 1;
		return ret;
	}

	vector<int> string_to_vi(string& s) {
		vector<int> ret(s.size());
		for (int i = 0; i < s.size(); i++)
			ret[i] = s[i] - '0';
		return ret;
	}

public:
	virtual std::string get_parallel_result(std::string, std::string);
	virtual std::string get_serial_result(std::string, std::string);
};

