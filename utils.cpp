#include "types.h"
#include "utils.h"
#include <iostream>

extern vector<Lecture> all_classes_list;

int select_num(int num){

}

void print_lecture_list() { // 어디까지 출력할 지 정하기
  cout << "0) 돌아가기";
  for (int i = 0; i < all_classes_list.size(); i++) {
    cout << i + 1 << ") " << all_classes_list[i].name << ' '
         << all_classes_list[i].num << '\n';
  }
}