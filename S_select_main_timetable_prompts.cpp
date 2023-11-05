#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "S_select_main_timetable_prompts.h"

void S_select_main_timetable_prompt() {
  int selectedLineNumber;
  vector<string> lines;
  string line;
  string input;
  if (S_check_file()) {
    cout << "! 시간표가 존재하지 않습니다!\n"
         << "--------------------------------------------------------------"
            "----"
            "--------\n";
    return;
  }
  ifstream file("timetables.txt");
  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
  }
  file.close();
  while (true) {
    cout << "대표 시간표 선택" << endl;
    print_timetable_list();
    cout << "--------------------------------------------------------------"
            "----"
            "--------"
         << endl;
    selectedLineNumber = check_num_input(lines.size());
    if(selectedLineNumber > 0){
      S_update_main_timetable(lines, selectedLineNumber);
      return;
    }
  }
}