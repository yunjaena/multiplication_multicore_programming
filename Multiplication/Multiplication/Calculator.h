#pragma once
#include "Algorithm.h"
#include "Naive.h"
#include "Karatsuba.h"
#include "FFT.h"
#include "DS_definitions.h"
#include "DS_timer.h"
using namespace std;

class Calculator
{
public:
	Calculator();
	~Calculator();
	void set_number(const string& s1, const string& s2);
	void print_algorithm_list();
	void on_algorithm(int index);
	void off_algorithm(int index);
	void execute();

	
	void show_menu();
	void show_remove_menu();
	void show_insert_menu();

	void insert_data();
	void use_calculator();
	void print_results(int k);

private:
	int umask;
	string num1, num2;
	vector<string> algo_list;
	vector<Algorithm*> algorithm;
};