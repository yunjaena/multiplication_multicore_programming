#pragma once
#include<string>
using namespace std;

class Algorithm
{
public:
	virtual string get_parallel_result(const string&, const string&) = 0;
	virtual string get_serial_result(const string&, const string&) = 0;
};

