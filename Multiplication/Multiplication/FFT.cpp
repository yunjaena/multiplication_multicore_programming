#include "FFT.h"


string FFT::get_serial_result(const string& s1, const string& s2) {
	FFT::set_vector(s1, s2);
	vector<int> result = serial_multiply(v1, v2);
	return seial_get_result_from_vector(result);
}


string FFT::get_parallel_result(const string& s1, const string& s2) {
	FFT::set_vector(s1, s2);
	vector<int> result = parallel_multiply(v1, v2);
	return parallel_get_result_from_vector(result);
}

void FFT::set_vector(string s1, string s2) {
	v1 = string_to_vi(s1);
	v2 = string_to_vi(s2);
	reverse(v1.begin(), v1.end());
	reverse(v2.begin(), v2.end());
}



void FFT::serial_fft(vector<base>& a, bool inv) {
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		while (!((j ^= bit) & bit)) bit >>= 1;
		if (i < j) swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		double x = (inv ? 1 : -1) * M_PI / i;
		base w = { cos(x), sin(x) };
		for (int j = 0; j < n; j += i << 1) {
			base th(1);
			for (int k = 0; k < i; k++) {
				base tmp = a[i + j + k] * th;
				a[i + j + k] = a[j + k] - tmp;
				a[j + k] += tmp;
				th *= w;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; i++) a[i] /= n;
	}
}
vector<int> FFT::serial_multiply(vector<int>& A, vector<int>& B) {
	vector<base> a(A.begin(), A.end());
	vector<base> b(B.begin(), B.end());
	int n = power_of_2_ge_than(max(a.size(), b.size())) * 2;

	a.resize(n);	b.resize(n);
	serial_fft(a, false);	serial_fft(b, false);

	for (int i = 0; i < n; i++)
		a[i] *= b[i];
	serial_fft(a, true);

	vector<int> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = (int)round(a[i].real());
	return ret;
}

void FFT::parallel_fft(vector<base>& a, bool inv) {
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		while (!((j ^= bit) & bit)) bit >>= 1;
		if (i < j) swap(a[i], a[j]);
	}

	for (int i = 1; i < n; i <<= 1) {
		double x = (inv ? 1 : -1) * M_PI / i;
		base w = { cos(x), sin(x) };
		for (int j = 0; j < n; j += i << 1) {
			base th(1);
			for (int k = 0; k < i; k++) {
				base tmp = a[i + j + k] * th;
				a[i + j + k] = a[j + k] - tmp;
				a[j + k] += tmp;
				th *= w;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; i++) a[i] /= n;
	}
}
vector<int> FFT::parallel_multiply(vector<int>& A, vector<int>& B) {
	vector<base> a(A.begin(), A.end());
	vector<base> b(B.begin(), B.end());
	int n = power_of_2_ge_than(max(a.size(), b.size())) * 2;

	a.resize(n);	b.resize(n);
	parallel_fft(a, false);	parallel_fft(b, false);
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		a[i] *= b[i];
	}
	parallel_fft(a, true);

	vector<int> ret(n);
#pragma omp parallel for
	for (int i = 0; i < n; i++)
		ret[i] = (int)round(a[i].real());
	return ret;
}

string FFT::seial_get_result_from_vector(vector<int>& ret) {
	int i = 0;
	string s = "";
	while (i < ret.size()) {
		if (ret[i] >= 10) {
			if (i == ret.size() - 1)
				ret.push_back(ret[i] / 10);
			else
				ret[i + 1] += ret[i] / 10;
			ret[i] %= 10;
		}
		++i;
	}

	reverse(ret.begin(), ret.end());

	bool start = false;
	for (auto elem : ret) {
		if (elem)start = true;
		if (start)s += to_string(elem);
	}
	if (!start)s += "0";

	return s;
}

string FFT::parallel_get_result_from_vector(vector<int>& ret) {
	int i = 0;
	string s = "";
	while (i < ret.size()) {
		if (ret[i] >= 10) {
			if (i == ret.size() - 1)
				ret.push_back(ret[i] / 10);
			else
				ret[i + 1] += ret[i] / 10;
			ret[i] %= 10;
		}
		++i;
	}

	reverse(ret.begin(), ret.end());

	bool start = false;
	for (auto elem : ret) {
		if (elem)start = true;
		if (start)s += to_string(elem);
	}
	if (!start)s += "0";

	return s;
}
