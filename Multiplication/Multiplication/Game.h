#include "FFT.h"
#include "Karatsuba.h"
#include "Naive.h"
#include "Algorithm.h"
#include "DS_definitions.h"
#include "DS_timer.h"
#include <ctime>

#pragma once
class Game
{
private:
	vector <pair<string, Algorithm*>> algorithm_vector;
	int min;
public:
	~Game();
	void insert_algorithm(string name, Algorithm* algorithm, bool is_serial);
	void remove_algorithm(int index);
	void print_algorithm_list();
	void show_menu();
	void show_insert_menu();
	void show_remove_menu();
	void play_game(int limit_second);
	string get_number(int length);

};

