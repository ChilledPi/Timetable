#include "types.h"
#include "utils.h"
#include <iostream>
#include <regex>

extern vector<Lecture> all_classes_list;

void print_lecture_list() { // 어디까지 출력할 지 정하기
  sort(all_classes_list.begin(), all_classes_list.end());
  cout << "0) 돌아가기";
  for (int i = 0; i < all_classes_list.size(); i++) {
    cout << i + 1 << ") " << all_classes_list[i].name << ' '
         << all_classes_list[i].num << '\n';
  }
}

std::string ltrim(std::string const& str)  // 문자열 좌측 공백 제거
{
  return std::regex_replace(str, std::regex("^\\s+"), "");
}
std::string rtrim(std::string const& str)  // 문자열 우측 공백 제거
{
  return std::regex_replace(str, std::regex("\\s+$"), "");
}
std::string trim(std::string const& str)  // 문자열 좌우 공백 제거
{
  return ltrim(rtrim(str));
}

int check_num_input(int num){
  string str;
  regex re("\\d+$");
  int ret;
  bool is_num = true;
  getline(cin, str);
  trim(str);
  if (regex_match(str, re)) {
    ret = stoi(str);
  }else{
    is_num = false;
  }

  cout << "------------------------------------------------------------"
          "--------------\n";
  if (0 <= ret && ret <= num) {
    return ret;
  }else if(is_num){
    cout << "! 잘못 입력했습니다. 범위(0~" << num
         << ") 안에서 다시 선택해주세요\n"
         << "------------------------------------------------------------"
            "--------------\n";
    return -1;
  } else {
    cout << "! " << ret << "번 항목이 존재하지 않습니다.\n"
         << "------------------------------------------------------------"
            "--------------\n";
    return -1;
  }
}

int check_name(string name) {
  regex re("^[A-Z][a-z]{0,19}( [A-Z][a-z]{0,19}){0,2}$");

  if (regex_match(name, re)) {
    return 0;
  } else{
    return -1;
  }
}

string read_name() {
  string str;
  int ret;
  int sel;
  cout << "추가할 > ";
  while (true) {
    getline(cin, str);
    trim(str);
    cout << "------------------------------------------------------------"
            "--------------\n";

    if(check_name(str) == 0){
      return str;
    } else {
      cout << "!\n"  // 오류 메세지
           << "------------------------------------------------------------"
              "--------------\n";
    }
  }
}

int check_num(string num) {
  regex re("\\d{4}$");
  if(num.length() != 4){
    return -1;
  }
  if(regex_match(num, re)){
    return 0;
  }
  return -2;
}

string read_num() {
  string str;
  int ret;
  int sel;
  while (true) {
    getline(cin, str);
    trim(str);
    cout << "------------------------------------------------------------"
            "--------------\n";

    if (check_num(str) == 0) {
      return str;
    } else {
      cout << "!\n"  // 오류 메세지
           << "------------------------------------------------------------"
              "--------------\n";
    }
  }
}

int check_time(string time) {
  regex re("[0-4]((0[1-9])|(1[0-8])){2}$");

  if(regex_match(time, re)){
    string sub1, sub2;
    sub1 = time.substr(1, 2);
    sub2 = time.substr(3, 4);
    if (stoi(sub1) >= stoi(sub2)) return -1;
    else
      return 0;
  }
  return -1;
}

string read_time() {
  string str;
  int ret;
  int sel;
  while (true) {
    getline(cin, str);
    trim(str);
    cout << "------------------------------------------------------------"
            "--------------\n";

    if (check_time(str) == 0) {
      return str;
    } else {
      cout << "!\n"  // 오류 메세지
           << "------------------------------------------------------------"
              "--------------\n";
    }
  }
}