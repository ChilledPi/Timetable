#include <fstream>
#include <iostream>

#include "utils.h"

void S_delete_timetable_prompt() {
  string input;
  string line;
  int select_num;

  while (true) {
    if (S_check_file()) {
      cout << "! 삭제할 시간표가 존재하지 않습니다!\n"
           << "--------------------------------------------------------------"
              "----"
              "--------\n";
      return;
    }

    while (true) {
      cout << "삭제할 시간표 선택" << endl;
      cout << "0) 뒤로가기" << endl;
      print_timetable_list();
      cout << "--------------------------------------------------------------"
              "----"
              "--------"
           << endl;

      ifstream ifile("timetables.txt");
      if (!ifile.is_open()) {
        cerr << "File load fail." << endl;
        // S_timetable_management_prompt();
      }

      vector<string> lines;
      while (getline(ifile, line)) {
        lines.push_back(line);
      }

      ifile.close();

      cout << "삭제할 시간표의 번호를 입력해주세요 > ";
      select_num = check_num_input(lines.size());
      if (select_num > 0) {
        lines.erase(lines.begin() + select_num - 1);

        ofstream ofile("timetables.txt");
        if (!ofile.is_open()) {
          cerr << "File load fail." << endl;
          //   S_timetable_management_prompt();
        }

        for (string& updated_line : lines) {
          ofile << updated_line << '\n';
        }

        ofile.close();
        // delete_tables();
        cout << "삭제되었습니다!" << endl;
        // cout << "현재 시간표 목록" << endl;
        // print_timetable_list();

        // S_main_prompt();
        break;
      } else if (select_num == 0) {
        return;
      }
    }

    // delete_tables();
  }
}
