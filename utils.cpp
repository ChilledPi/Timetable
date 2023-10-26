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

int check_num_input(int num){
  string str;
  regex re("\d+");
  int ret;
  getline(cin, str);
  if (regex_match(str, re)) {
    ret = stoi(str);
  } else {
    ret = -1;
  }
  while(true){
    //입력 받고 입력이 수면 수로, 문자열이면 -1로 ret 초기화
    cout << "------------------------------------------------------------"
            "--------------\n";
    if (ret == 0) {
      return -1;
    } else if (ret == -1) {
      cout << "! 잘못 입력했습니다. 범위(0~" << num
           << ") 안에서 다시 선택해주세요\n"
           << "------------------------------------------------------------"
              "--------------\n";
    } else if (ret <= num) {
      cout << "------------------------------------------------------------"
              "--------------\n";
      return ret;
    } else {
      cout << "! " << ret << "번 항목이 존재하지 않습니다.\n"
           << "------------------------------------------------------------"
              "--------------\n";
    }
  }
}

int check_name(string name){

}
