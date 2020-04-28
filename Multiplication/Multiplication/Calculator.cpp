#include "Calculator.h"

Calculator::Calculator() {
	algo_list.push_back("0. naive (serial)");
	algo_list.push_back("1. naive (parallel)");
	algo_list.push_back("2. karatsuba (serial)");
	algo_list.push_back("3. karatsuba (parallel)");
	algo_list.push_back("4. FFT (serial)");
	algo_list.push_back("5. FFT (parallel)");

	algorithm.push_back(new Naive());
	algorithm.push_back(new Naive());
	algorithm.push_back(new Karatsuba());
	algorithm.push_back(new Karatsuba());
	algorithm.push_back(new FFT());
	algorithm.push_back(new FFT());

	umask = 0;
}

Calculator::~Calculator() {
	for (auto& it : algorithm) delete it;
}

void Calculator::set_number(const string& s1, const string& s2) {
	num1 = s1;
	num2 = s2;
}

void Calculator::print_algorithm_list() {
	for (int i = 0; i < algo_list.size(); ++i) {
		cout << algo_list[i];
		if (1 << i & umask) cout << " OFF\n";
		else cout << " ON\n";
	}
}

void Calculator::on_algorithm(int index) {
	if (0 <= index && index < 6) {
		umask &= ~(1 << index);
	}
}

void Calculator::off_algorithm(int index) {
	if (0 <= index && index < 6) {
		umask |= 1 << index;
	}
}

void Calculator::execute() {
	DS_timer timer(6);
	for (int i = 0, j = 0; i < 6; ++i) {
		if (umask & 1 << i) continue;
		timer.setTimerName(i, (char*)algo_list[i].c_str());

		timer.onTimer(i);
		if (i & 1) algorithm[i]->get_parallel_result(num1, num2);
		else algorithm[i]->get_serial_result(num1, num2);
		timer.offTimer(i);
	}

	timer.printTimer();
}