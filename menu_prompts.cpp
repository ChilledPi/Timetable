#include <iostream>
#include "utils.h"
#include "menu_prompts.h"

void menu_prompt(){
  int sel;
  while (true) {
    cout << "> B07 Timetable Menu\n\n"
         << "1) 학사팀 메뉴\n\n"
         << "2) 학생팀 메뉴\n\n"
         << "0) 종료\n";
    cout << "------------------------------------------------------------------"
            "--------\n";
    cout << "B07 Timetable : menu > ";
    sel = check_num_input(2);
    if (sel == 1) {
      A_lecture_management_prompt();
    } else if (sel == 2) {
    //   student_lecture_management_prompt();
    } else if(sel == 0){
      return;
    }
  }
}