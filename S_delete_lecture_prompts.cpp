#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "S_delete_lecture_prompts.h"
#include "types.h"
#include "utils.h"

extern vector<Lecture> all_classes_list;

void S_delete_lecture_prompt(int selected_line){
  ifstream file("timetables.txt");
  int sel, lines;
  string str;
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
      vector<int> count(all_classes_list.size());
      int s = find(all_classes_list.begin(), all_classes_list.end(),
                   Lecture(selected_timetable[i])) -
              all_classes_list.begin();
      for (int j = s; j < all_classes_list.size(); j++) {
        if (all_classes_list[i].name == all_classes_list[j].name) {
          if (count[i] == 0) {
            count[i] = 1;
          }
          count[j] = count[i] + 1;
          break;
        }
      }
      cout << i + 1 << ") " << selected_timetable[i].name << ' ';
      if (count[s]) cout << count[s] << ' ';
      cout << selected_timetable[i].num << ' ';
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
      vector<vector<string>> all_timetables = get_all_timetables();
      for(auto i : all_timetables){
        for (auto j : i){
          cout << j;
        }
        cout << '\n';
      }
      ofstream file("timetables.txt");
      for (int i = 0; i < all_timetables.size(); i++) {
        if (i + 1 == selected_line){
            all_timetables[i].erase(find(all_timetables[i].begin(), all_timetables[i].end(), selected_timetable[sel-1].num));
        }
      }

      selected_timetable.erase(find(selected_timetable.begin(),
                                    selected_timetable.end(),
                                    Lecture(selected_timetable[sel - 1].num)));

      for (int i = 0; i < all_timetables.size(); i++) {
        for (int j = 0; j < all_timetables[i].size(); j++) {
          file << all_timetables[i][j];
          if (j == all_timetables[i].size() - 1) {
            file << '\n';
          } else {
            file << '\t';
          }
        }
      }
    } else if (sel == 0) {
      return;
    }
  }
}