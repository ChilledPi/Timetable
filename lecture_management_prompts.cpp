#include "lecture_management_prompts.h"
#include "utils.h"

#include <iostream>

using namespace std;

void lecture_management_prompt() {
  int sel;
  while (true) {
    cout << "> 학사팀 메뉴\n\n"
         << "0) 돌아가기\n\n"
         << "1) 강의 추가\n\n"
         << "2) 강의 삭제\n"
         << "------------------------------------------------------------------"
            "--------\n"
         << "B07 Timetable: menu > ";
    sel = check_num_input(2);
    if (sel == 1) {
      // add_lecture_prompt();
    } else if (sel == 2) {
      delete_lecture_prompt();
    } else if(sel == 0){
      return;
    }
  }
}