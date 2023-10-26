#include "lecture_management_prompts.h"
#include "utils.h"

#include <iostream>

using namespace std;

void lecture_management_prompt() {
  int sel;
  while (true) {
    cout << ">학사팀 메뉴\n"
         << "0) 돌아가기\n"
         << "1) 강의 추가\n"
         << "2) 강의 삭제\n"
         << "------------------------------------------------------------------"
            "--------\n"
         << "B07 Timetable: menu > ";
    
    if((sel = check_num_input(2)) == 1){
      add_lecture_prompt();
    } else if (sel == 2) {
      delete_lecture_prompt();
    }else{
      return;
    }
  }
}