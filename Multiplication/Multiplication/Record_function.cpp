#include "Record_function.h"

void Record_function::record_fucntion(string vector_A, string vector_B, string output) {
	int mode = 1;
	int nf_mode = 0;
	int f_mode = 0;
	bool next = false;
	string file_name;
	string file_contents;
	
	/*
	while (next) {
		printf("출력 = 0 | 계산결과 추가 = 1 | 자유 메모 작성 = 2 : ");
		scanf_s("%d", &mode);
		if (mode > 2) {
			printf("잘못된 입력\n");
			next = true;
		}
		else if (mode == 2) {
			f_mode = 1;
			next = false;
		}
		else next = false;
	}
	*/


	while (!next) {
		printf("파일 이름 입력 :  ");
		cin >> file_name;
		file_name += ".txt";

		ifstream filecheck;
		filecheck.open(file_name);

		if (!filecheck) {
				cout << "'" + file_name + "'" + "과 같은 이름의 파일은 존재하지 않습니다! \n";
				cout << "새로운 파일을 생성하시겠습니까? (1 - Yes, others - No) : ";
				scanf_s("%d", &nf_mode);
				if (nf_mode == 1) next = true;
				else next = false;
		}
		else next = true;
	}

	file_contents = read_file(file_name);

	int m_mode = 0;
	printf("추가적인 메모를 입력하시겠습니까? (1 - Yes, others - No) : ");
	scanf_s("%d", &m_mode);
	file_contents = write_file(file_name, file_contents, vector_A, vector_B, output);

	if (m_mode == 1) {
		write_memo(file_name, file_contents, f_mode);
	}
}

void Record_function::print_file() {
	bool next = false;
	string file_name;

	while (!next) {
		printf("파일 이름 입력 :  ");
		cin >> file_name;
		file_name += ".txt";

		ifstream filecheck;
		filecheck.open(file_name);

		if (!filecheck) {
				cout << "'" + file_name + "'" + "과 같은 이름의 파일은 존재하지 않습니다! \n";
				next = false;
		}
		else next = true;
	}
	string file_contents = read_file(file_name);

	cout << file_contents + "\n";
}

void Record_function::write_free_memo() {
	bool next = false;
	int nf_mode = 0;
	string file_name;
	string file_contents;

	while (!next) {
		printf("파일 이름 입력 :  ");
		cin >> file_name;
		file_name += ".txt";

		ifstream filecheck;
		filecheck.open(file_name);

		if (!filecheck) {
			cout << "'" + file_name + "'" + "과 같은 이름의 파일은 존재하지 않습니다! \n";
			cout << "새로운 파일을 생성하시겠습니까? (1 - Yes, others - No) : ";
			scanf_s("%d", &nf_mode);
			if (nf_mode == 1) next = true;
			else next = false;
		}
		else next = true;
	}

	file_contents = read_file(file_name);

		write_memo(file_name, file_contents, 1);


}




string Record_function::read_file(string fname) {

	string f_contents;
	string get_contents;

	readFile.open(fname);
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			getline(readFile, get_contents);
			f_contents = f_contents + get_contents + "\n";
		}
		readFile.close();
	}
	return f_contents;
}

string Record_function::write_file(string fname, string f_contents, string A, string B, string op) {
	string time = get_current_time();

	writeFile.open(fname);
	string str = f_contents + time + "   "
		+ A + " * " + B + " = " + op;
	writeFile.write(str.c_str(), str.size());
	writeFile.close();
	return str;
}

string Record_function::get_current_time() {
	time_t curr_time = time(NULL);
	struct tm curr_tm;

	localtime_s(&curr_tm, &curr_time);

	string time = to_string(curr_tm.tm_year + 1900) + "-"
		+ to_string(curr_tm.tm_mon + 1) + "-"
		+ to_string(curr_tm.tm_mday) + " "
		+ to_string(curr_tm.tm_hour) + ":"
		+ to_string(curr_tm.tm_min) + ":"
		+ to_string(curr_tm.tm_sec);
	return time;
}

void Record_function::write_memo(string fname, string f_contents, bool free) {
	string time = get_current_time();
	string memo;

	cout << "입력 : ";
	cin.ignore();
	getline(cin, memo);
	writeFile.open(fname);
	string str;
	if (free) str = f_contents + time + "\n" + memo;
	else str = f_contents + "\n-> " + memo;

	writeFile.write(str.c_str(), str.size());
	writeFile.close();
}














