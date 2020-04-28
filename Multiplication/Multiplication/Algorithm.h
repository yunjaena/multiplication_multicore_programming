#pragma once
#include<string>
using namespace std;

class Algorithm
{
private:
	bool isSerial;
public:
	virtual string get_parallel_result(const string&, const string&) = 0;
	virtual string get_serial_result(const string&, const string&) = 0;
	void set_serial(bool is_serial);
	bool is_serial();
};

