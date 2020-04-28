#pragma once
#include<string>
class Algorithm
{
public:
	virtual std::string get_parallel_result(std::string, std::string) = 0;
	virtual std::string get_serial_result(std::string, std::string) = 0;
};

