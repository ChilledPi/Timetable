#ifndef UTILS_T
#define UTILS_T
#include "types.h"
#include <string>

using namespace std;

void print_lecture_list();  // 강의 목록 출력

std::string ltrim(std::string const& str);  //문자열 좌측 공백 제거
std::string rtrim(std::string const& str);  // 문자열 우측 공백 제거
std::string trim(std::string const& str);   // 문자열 좌우 공백 제거

int check_num_input(int num);

int check_name(string name);
string read_name();
int check_num(string num);
string read_num();
int check_time(string time);
string read_time();

void update_all_classes_file();

bool is_addable(vector<Lecture> set, string idx);
#endif