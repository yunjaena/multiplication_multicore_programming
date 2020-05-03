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

		//timer.onTimer(i);
		if (i & 1) {
			timer.onTimer(i);
			algorithm[i]->get_parallel_result(num1, num2);
			timer.offTimer(i);
			print_results(i);
		}
		else {
			timer.onTimer(i);
			algorithm[i]->get_serial_result(num1, num2);
			timer.offTimer(i);
			print_results(i);
		}
		//timer.offTimer(i);
	}

	timer.printTimer();
}

void Calculator::show_menu() {
	int n = -1;
	while (true) {
		cout << "1. insert algorithm 2. remove algorithm 3. algorithm list 4. Use Calculator 5. Add Free text 6. exit" << endl;
		cin >> n;
		switch (n) {
		case 1:
			show_insert_menu();
			break;
		case 2:
			show_remove_menu();
			break;
		case 3:
			print_algorithm_list();
			break;
		case 4:
			use_calculator();
			break;
		case 5:
			
			break;
		case 6:
			return;
			break;
		}
	}
}

void Calculator::show_insert_menu() {
	int algorithm = -1;
	cout << "inserted algorithm" << endl;
	print_algorithm_list();
	cout << "choose algorithm" << endl;
	cout << "1. naive(serial) 2. naive(parallel) 3. karatsuba(serial) 4. karatsuba(parallel) 5. FFT(serial) 6. FFT(parallel) 7. All" << endl;
	cin >> algorithm;
	switch (algorithm) {
	case 1:
		on_algorithm(0);
		break;
	case 2:
		on_algorithm(1);
		break;
	case 3:
		on_algorithm(2);
		break;
	case 4:
		on_algorithm(3);
		break;
	case 5:
		on_algorithm(4);
		break;
	case 6:
		on_algorithm(5);
		break;
	case 7:
		for (int i = 1; i < 7; i++) on_algorithm(i - 1);;
		break;
	}
}

void Calculator::show_remove_menu() {
	print_algorithm_list();
	cout << "choose algorithm" << endl;
	cout << "1. naive(serial) 2. naive(parallel) 3. karatsuba(serial) 4. karatsuba(parallel) 5. FFT(serial) 6. FFT(parallel) 7. All" << endl;

	int n = -1;
	cin >> n;
	if (n == 7) {
		for (int i = 1; i < 7; i++) off_algorithm(i - 1);;
	}
	else off_algorithm(n-1);

}

void Calculator::use_calculator() {
	insert_data();
	cout << num1 << " * " << num2 << endl;
	execute();
	

}

void Calculator::insert_data() {
	cout << "s1 값을 입력하세요 : ";
	cin >> num1;
	cout << "s2 값을 입력하세요 : ";
	cin >> num2;
}

void Calculator::print_results(int k) {
	cout << algo_list[k] << " = ";
	if (k & 1) cout << algorithm[k]->get_parallel_result(num1, num2) << endl;
	else cout << algorithm[k]->get_serial_result(num1, num2) << endl;
}