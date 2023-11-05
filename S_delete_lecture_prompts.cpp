#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "S_delete_lecture_prompts.h"
#include "types.h"
#include "utils.h"

extern vector<Lecture> all_classes_list;

void S_delete_lecture_prompt(int selected_line){

  int sel, lines;
  string str;
  ifstream file("timetables.txt");
  vector<Lecture> selected_timetable;

  lines = 1;
  while (getline(file, str)) {
    if (lines == selected_line) {
      istringstream iss(str);
      string temp;
      while (getline(iss, temp, '\t')) {
        if (check_num(temp) == 0) {
          selected_timetable.push_back(*find(
              all_classes_list.begin(), all_classes_list.end(), Lecture(temp)));
        }
      }
      break;
    }
    lines++;
  }
  while (true) {
    if (selected_timetable.empty()) {
      cout << "! 삭제할 강의가 존재하지 않습니다.\n"
           << "------------------------------------------------------------"
              "--------------\n";
      return;
    }

    cout << "0) 삭제 중단\n";
    sort(selected_timetable.begin(), selected_timetable.end());
    for (int i = 0; i < selected_timetable.size(); i++) {
      cout << i + 1 << ") " << selected_timetable[i].name << ' ' << selected_timetable[i].num
           << ' ';
      for (tp j : selected_timetable[i].tp_list) {
        cout << j.day << j.time << ' ';
      }
      cout << '\n';
    }
    cout << "------------------------------------------------------------"
            "------"
            "--------\n"
         << "삭제할 번호를 입력해주세요 > ";
    sel = check_num_input(selected_timetable.size());

    if(sel > 0){
      selected_timetable.erase(find(selected_timetable.begin(),
                                    selected_timetable.end(),
                                    Lecture(selected_timetable[sel - 1].num)));
    } else if (sel == 0) {
      // 파일에 쓰고
      return;
    }
  }
}