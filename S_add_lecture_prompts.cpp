#include "S_add_lecture_prompts.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "types.h"
#include "utils.h"

extern vector<Lecture> all_classes_list;

void S_add_lecture_prompt(int selected_line) {
  ifstream file("timetables.txt");
  vector<Lecture> copy_list(all_classes_list.begin(), all_classes_list.end());
  vector<Lecture> selected_timetable;
  int sel, lines;
  string str;

  lines = 1;
  while (getline(file, str)) {
    if (lines == selected_line) {
      istringstream iss(str);
      string temp;
      while (getline(iss, temp, '\t')) {
        if (check_num(temp) == 0) {
          selected_timetable.push_back(*find(
              all_classes_list.begin(), all_classes_list.end(), Lecture(temp)));
          copy_list.erase(
              find(copy_list.begin(), copy_list.end(), Lecture(temp)));
        }
      }
      break;
    }
    lines++;
  }

  while (true) {
    print_selected_timetable(selected_line);
    cout << "0) 삽입 중단\n";

    vector<int> count(all_classes_list.size());
    for (int i = 0; i < all_classes_list.size(); i++){
      for (int j = i + 1; j < all_classes_list.size(); j++) {
        if (all_classes_list[i].name == all_classes_list[j].name) {
          if (count[i] == 0) {
            count[i] = 1;
          }
          count[j] = count[i] + 1;
          break;
        }
      }
    }
      sort(copy_list.begin(), copy_list.end());
    for (int i = 0; i < copy_list.size(); i++) {
      int s = find(all_classes_list.begin(), all_classes_list.end(),
           Lecture(copy_list[i])) - all_classes_list.begin();
      cout << i + 1 << ") " << copy_list[i].name << ' ';
      if (count[s]) cout << count[s] << ' ';
      cout << copy_list[i].num << ' ';
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
      if (getTotalCreditsForTimetable(selected_line) +
              stoi(copy_list[sel - 1].credit) >
          18) {
        cout << "! 학점 상한을 초과하였습니다!\n";
      } else if (is_addable(selected_timetable,
                            find(all_classes_list.begin(),
                                 all_classes_list.end(), copy_list[sel - 1])
                                ->num) &&
                 name_dup(selected_timetable, copy_list[sel - 1])) {
        vector<vector<string>> all_timetables = get_all_timetables();
        ofstream file("timetables.txt");
        for (int i = 0; i < all_timetables.size(); i++) {
          if (i + 1 == selected_line) {
            all_timetables[i].push_back(copy_list[sel - 1].num);
            sort(all_timetables[i].begin() + 1, all_timetables[i].end());
            break;
          }
        }

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