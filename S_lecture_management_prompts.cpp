#include <iostream>
#include <fstream>
#include "S_lecture_management_prompts.h"
#include "utils.h"

void S_lecture_management_prompt(){
  fstream file("timetables.txt");
  int sel, lines, selected_line;
  cout << "----------------------------------------------------------------"
          "----------\n"
       << "시간표 존재 여부를 확인합니다.\n";
  if (file.peek() == ifstream::traits_type::eof()) {
    cout << "! 시간표가 존재하지 않습니다!\n"
         << "----------------------------------------------------------------"
            "----------\n";
    return;
  }

  cout << "시간표가 존재합니다!\n"
       << "----------------------------------------------------------------"
          "----------\n";
  while(true){
    lines = print_timetable_list();
    cout << "------------------------------------------------------------------"
            "--------\n"
         << "강의를 추가/삭제할 시간표를 선택해주세요 > ";
    selected_line = check_num_input(lines);
    if (selected_line > 0) {
      break;
    }
    if (selected_line == 0) {
      std::cout
          << "! 0번 항목이 존재하지 않습니다." << std::endl
          << "------------------------------------------------------------"
             "--------------"
          << std::endl;
    }
  }

  while (true) {
    cout << "> 학생 메뉴\n";
    print_selected_timetable(selected_line);
    cout << "0) 돌아가기\n\n"
         << "1) 강의 추가\n\n"
         << "2) 강의 삭제\n"
         << "------------------------------------------------------------------"
            "--------\n"
         << "B07 Timetable: menu > ";
    sel = check_num_input(2);
    if (sel == 1) {
      S_add_lecture_prompt(selected_line);
    } else if (sel == 2) {
      S_delete_lecture_prompt(selected_line);
    } else if (sel == 0)
      return;
  }
}