#include "S_add_lecture_prompts.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "types.h"
#include "utils.h"

extern vector<Lecture> all_classes_list;

void S_add_lecture_prompt(int selected_line){
  vector<Lecture> copy_list(all_classes_list.begin(), all_classes_list.end());
  vector<Lecture> selected_timetable;
  int sel, lines;
  string str;
  ifstream file("timetables.txt");

  lines = 1;
  while (getline(file, str)) {
    if(lines == selected_line){
      istringstream iss(str);
      string temp;
      while (getline(iss, temp, '\t')){
        if(check_num(temp) == 0){
          selected_timetable.push_back(*find(all_classes_list.begin(), all_classes_list.end(), Lecture(temp)));
          copy_list.erase(
              find(copy_list.begin(), copy_list.end(), Lecture(temp)));
        }
      }
      break;
    }
    lines++;
  }

  while (true) {
    cout << "0) 삽입 중단\n";
    sort(copy_list.begin(), copy_list.end());
    for (int i = 0; i < copy_list.size(); i++) {
      cout << i + 1 << ") " << copy_list[i].name << ' '
           << copy_list[i].num << ' ';
      for (tp j : copy_list[i].tp_list) {
        cout << j.day << j.time << ' ';
      }
      cout << '\n';
    }
    cout << "------------------------------------------------------------"
            "------"
            "--------\n"
         << "시간표에 추가할 강의를 선택해주세요 > ";
    sel = check_num_input(copy_list.size());
    if (sel > 0) {
      if (is_addable(
              selected_timetable, find(all_classes_list.begin(), all_classes_list.end(),
                             copy_list[sel - 1])->num)) {
        // 파일에 쓰고
        copy_list.erase(
            find(copy_list.begin(), copy_list.end(), copy_list[sel - 1]));
        cout << "추가되었습니다!\n";
        } else {
        cout << "! 강의를 추가할 수 없습니다!\n";
        }
        cout << "------------------------------------------------------------"
                "------"
                "--------\n";
    } else if (sel == 0) {
        return;
    }
  }
}