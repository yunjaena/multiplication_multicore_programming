#include "Naive.h"

string Naive::get_serial_result(const string& s1, const string& s2) {
    Naive::set_vector(s1, s2);
    vector<int> result = serial_multiply(v1, v2);
    return result_from_vector(result);
}


string Naive::get_parallel_result(const string& s1, const string& s2) {
    Naive::set_vector(s1, s2);
    vector<int> result = parallel_multiply(v1, v2);
    return result_from_vector(result);
}

void Naive::set_vector(string s1, string s2) {
    v1 = string_to_vi(s1);
    v2 = string_to_vi(s2);
    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());
}


vector<int> Naive::serial_multiply(vector<int>& A, vector<int>& B) {
    vector<int> res(A.size() + B.size());

    if (A.size() > B.size()) {
        for (int i = 0; i < B.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                res[j + i] += B[i] * A[j];
            }
        }
    }
    else {
        for (int i = 0; i < A.size(); i++) {
            bool upper = false;
            for (int j = 0; j < B.size(); j++) {
                res[j + i] += A[i] * B[j];
            }
        }
    }


    for (int i = 0; i < res.size(); i++) {
        if (res[i] >= 10) {
            int upper = res[i] / 10;
            res[i] = res[i] % 10;
            res[i + 1] += upper;
        }
    }

    reverse(res.begin(), res.end());
    return res;
    /*
    vector<vector<int>> res(threads, vector<int>(A.size() + B.size(), 0));
    vector<int> res_2(A.size() + B.size());


    if (A.size() > B.size()) {
        for (int i = 0; i < B.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                res[0][j + i] += B[i] * A[j];
            }
        }
    }
    else {
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < B.size(); j++) {
                res[0][j + i] += A[i] * B[j];
            }
        }
    }

    for (int i = 0; i < threads;i++) {
        for (int j = 0; j < A.size() + B.size();j++) {
            res_2[j] += res[i][j];
        }
    }

    for (int i = 0; i < res_2.size(); i++) {
        if (res_2[i] >= 10) {
            int upper = res_2[i] / 10;
            res_2[i] = res_2[i] % 10;
            res_2[i + 1] += upper;
        }
    }

    reverse(res_2.begin(), res_2.end());
    return res_2;
    */
}

vector<int> Naive::parallel_multiply(vector<int>& A, vector<int>& B) {
    vector<vector<int>> res(threads, vector<int>(A.size() + B.size(), 0));
    vector<int> res_2(A.size() + B.size());


    if (A.size() > B.size()) {
#pragma omp parallel for num_threads(threads) 
        for (int i = 0; i < B.size(); i++) {
            int tid = omp_get_thread_num();
            for (int j = 0; j < A.size(); j++) {
                res[tid][j + i] += B[i] * A[j];
            }
        }
    }
    else {
#pragma omp parallel for num_threads(threads) 
        for (int i = 0; i < A.size(); i++) {
            int tid = omp_get_thread_num();
            for (int j = 0; j < B.size(); j++) {
                res[tid][j + i] += A[i] * B[j];
            }
        }
    }

    for (int i = 0; i < threads;i++) {
        for (int j = 0; j < A.size() + B.size();j++) {
            res_2[j] += res[i][j];
        }
    }

    for (int i = 0; i < res_2.size(); i++) {
        if (res_2[i] >= 10) {
            int upper = res_2[i] / 10;
            res_2[i] = res_2[i] % 10;
            res_2[i + 1] += upper;
        }
    }

    reverse(res_2.begin(), res_2.end());
    return res_2;
}


string Naive::result_from_vector(vector<int>& ret) {
    int i = 0;
    string s = "";
    bool start = false;
    for (auto elem : ret) {
        if (elem) start = true;
        if (start) s += to_string(elem);
    }
    if (!start) s += "0";

    return s;
}