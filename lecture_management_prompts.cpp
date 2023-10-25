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
    sel = select_num(2);
    cout << "------------------------------------------------------------------"
            "--------\n";

    if (sel == 0) {
      return;
    } else if (sel == 1) {
      add_lecture_prompt();
    } else if (sel == 2) {
      delete_lecture_prompt();
    } else if(sel == -1){
      cout << "! 잘못 입력했습니다. 범위(0~2) 안에서 다시 선택해주세요\n"
           << "------------------------------------------------------------"
              "--------------\n";
    }else{
      cout << "! " << sel << "번 항목이 존재하지 않습니다.\n"
           << "------------------------------------------------------------"
              "--------------\n";
    }
  }
}