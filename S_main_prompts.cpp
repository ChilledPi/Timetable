#include <iostream>

#include "S_main_prompts.h"
#include "utils.h"

extern vector<Lecture >all_classes_list;

void S_main_prompt() {
    if(all_classes_list.empty()){
      cout << "----------------------------------------------------------------"
              "----------\n"
           << "! 시간표에 추가할 강의가 없습니다!\n"
           << "----------------------------------------------------------------"
              "----------\n";
      return;
    }
    
  int sel;
  while (true) {
      cout << "> 학생 메뉴\n\n";
      print_selected_timetable(1);
      cout << "0) 돌아가기\n\n"
           << "1) 강의 추가/삭제\n\n"
           << "2) 시간표 추가/삭제\n\n"
           << "3) 대표 시간표 변경\n"
           << "----------------------------------------------------------------"
              "--"
              "--------\n"
           << "B07 Timetable: menu > ";
      sel = check_num_input(3);
      if (sel == 1) {
        S_lecture_management_prompt();
    } else if (sel == 2) {
      S_timetable_management_prompt();
    } else if (sel == 3) {
      S_select_main_timetable_prompt();
    } else if (sel == 0)
      return;
  }
}