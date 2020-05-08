#include "Game.h"
#include <stdlib.h>
#include <Windows.h>
#include <stack>

void Game::insert_algorithm(string name, Algorithm* algorithm, bool is_serial) {
	algorithm->set_serial(is_serial);
	algorithm_vector.push_back(pair<string, Algorithm*>(name, algorithm));
}

void Game::show_insert_menu() {
	int algorithm = -1;
	cout << "inserted algorithm" << endl;
	print_algorithm_list();
	cout << "choose algorithm" << endl;
	cout << "1. naive(serial) 2. karatsuba(serial) 3. FFT(serial) 4. naive(parallel) 5. karatsuba(parallel) 6. FFT(parallel) 7. All" << endl;
	cin >> algorithm;
	switch (algorithm) {
	case 1:
		insert_algorithm("naive(serial)", new Naive(), true);
		break;
	case 2:
		insert_algorithm("karatsuba(serial)", new Karatsuba(), true);
		break;
	case 3:
		insert_algorithm("FFT(serial)", new FFT(), true);
		break;
	case 4:
		insert_algorithm("naive(parallel)", new Naive(), false);
		break;
	case 5:
		insert_algorithm("karatsuba(parallel)", new Karatsuba(), false);
		break;
	case 6:
		insert_algorithm("FFT(parallel)", new FFT(), false);
		break;
	case 7:
		insert_algorithm("naive(serial)", new Naive(), true);
		insert_algorithm("karatsuba(serial)", new Karatsuba(), true);
		insert_algorithm("FFT(serial)", new FFT(), true);
		insert_algorithm("naive(parallel)", new Naive(), false);
		insert_algorithm("karatsuba(parallel)", new Karatsuba(), false);
		insert_algorithm("FFT(parallel)", new FFT(), false);
		break;
	}
}

void Game::show_remove_menu() {
	print_algorithm_list();
	cout << "select remove algorithm : " << endl;
	int n = -1;
	cin >> n;
	remove_algorithm(n);
}

void Game::show_menu() {
	int n = -1;
	int time = 5;
	while (true) {
		cout << "1. insert algorithm 2. remove algorithm 3. algorithm list 4. play game 5. exit" << endl;
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
			time = 5;
			cout << "input limit second : ";
			cin >> time;
			play_game(time);
			return;
			break;
		case 5:
			return;
			break;
		}
	}
}
void Game::play_game(int limit_second = 5){
	if (min < 0) {
		cout << "wrong_time_input"<< endl;
		return;
	}
	Game::min = limit_second;
	int number_length = 100;
	bool isConsoleOuputMode = false;
	int n;
	stack<int> gameover_index;
	stack<pair<string, float>> record;
	

	cout << endl << "Console Mode On : 0 Off : 1" << endl;
	cin >> n;
	isConsoleOuputMode = (n == 0) ? true : false;
	clock_t start;

	if(isConsoleOuputMode)
	secondConsole.Create("Output");

	while (algorithm_vector.size() >= 2) {
		string a = get_number(number_length);
		string b = get_number(number_length);

		cout << "current length " << number_length << endl;
		string answer = "";

		if (isConsoleOuputMode)
		for (int i = 0; i < a.length() ; i++) {
			secondConsole.printf("%c", a[i]);
		}

		if (isConsoleOuputMode)
		secondConsole.printf(" X ");

		if (isConsoleOuputMode)
		for (int i = 0; i < b.length() ; i++) {
			secondConsole.printf("%c", b[i]);
		}


		for (int i = 0; i < algorithm_vector.size(); i++) {
			start = (int)clock();
			if(algorithm_vector[i].second->is_serial())
				answer = algorithm_vector[i].second->get_serial_result(a, b);
			else
				answer = algorithm_vector[i].second->get_parallel_result(a, b);

			float end = (float)(clock() - start) / CLOCKS_PER_SEC;
			if (isConsoleOuputMode) {
				secondConsole.printf("\n-----------------------------\n");
				secondConsole.printf("answer => ");

				for (int i = 0; i < answer.length(); i++) {
					secondConsole.printf("%c", answer[i]);
				}

				secondConsole.printf("\n-----------------------------\n");
			}
			cout << "[" << algorithm_vector[i].first << "] "<<" => time" << end <<" s" << endl;
		
			if (end > limit_second) {
				cout << "time out!!!" << endl;
				record.push(pair<string, float>(algorithm_vector[i].first, end));
				gameover_index.push(i);
				
			}

			Sleep(1000);
		}
	
		while (!gameover_index.empty()) {
			remove_algorithm(gameover_index.top());
			gameover_index.pop();
		}

		number_length += 100000;

		

		system("cls");
	}

	if (algorithm_vector.size() == 1) {
		cout << "winner : " << algorithm_vector[0].first << endl;
	}

		while (!record.empty()) {
			cout << record.top().first << " : " << record.top().second<<" s " << endl;
			record.pop();
		}
		cout << endl;
		getchar();
		getchar();
		if (isConsoleOuputMode) secondConsole.Close();
	
}


void Game::remove_algorithm(int index) {
	if (algorithm_vector.size() > index && index >= 0) {
		vector <pair<string, Algorithm*>>::iterator iter = algorithm_vector.begin();
		iter += (index);
		algorithm_vector.erase(iter);
		cout << "deleted" << endl;
	}
	else {
		cout << "wrong index" << endl;
		print_algorithm_list();
	}
	system("cls");
}

void Game::print_algorithm_list() {
	cout << "\n\n---- algorithm list ----" << endl;
	for (int i = 0; i < algorithm_vector.size(); i++){
		cout<< i << " : " << algorithm_vector[i].first << endl << endl;
	}
}


string Game::get_number(int length) {
	string ret;
	ret += rand() % 9 + 49;
	for (int i = 1; i < length; ++i) ret += rand() % 10 + 48;
	return ret;
}

Game::~Game() {
	for (auto& a : algorithm_vector) {
		delete a.second;
	}
}
