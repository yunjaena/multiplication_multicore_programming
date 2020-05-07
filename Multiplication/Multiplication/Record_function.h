#pragma once
#define _USE_MATH_DEFINES
#define ll long long
#include <cstdio>
#include <cmath>
#include <math.h> 
#include <omp.h>
#include <vector>
#include <complex>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <io.h>

#include "Algorithm.h"

using namespace std;

class Record_function
{
private:
	ifstream readFile;
	ofstream writeFile;
	string get_current_time();
	string read_file(string fname);
	string write_file(string fname, string f_contents, string A, string B, string op);
	
	void write_memo(string fname, string f_contents, bool free);


public:
	void record_function(string vector_A, string vector_B, string output);
	void print_file();
	void write_free_memo();
};