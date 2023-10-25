#include "types.h"
#include "utils.h"
#include <iostream>
#include <algorithm>>

extern vector<Lecture> all_classes_list;

void delete_lecture_prompt() {
  int sel;
  vector<Lecture>::iterator iter;
  while (true) {
    cout << "삭제할 강의가 있는지 확인합니다.\n";
    if (all_classes_list.empty()) {
      cout << "! 삭제할 강의가 존재하지 않습니다.\n"
           << "------------------------------------------------------------"
              "--------------\n";
      return;
    }
    cout << "삭제할 강의가 존재합니다.\n"
         << "------------------------------------------------------------"
            "--------------\n";

    while (true) {
      print_lecture_list();
      cout << "삭제할 번호를 입력해주세요 > ";
      sel = select_num(all_classes_list.size());
      cout << "------------------------------------------------------------"
              "--------------\n";
      if(sel == 0){
        return;
      } else if (sel == -1) {
        cout << "! 잘못 입력했습니다. 범위(0~2) 안에서 다시 선택해주세요\n"
             << "------------------------------------------------------------"
                "--------------\n";
      } else if (sel <= all_classes_list.size()) {
        iter = find(all_classes_list.begin(), all_classes_list.end(),
             all_classes_list[sel - 1]);
        cout << "------------------------------------------------------------"
                "--------------\n";
        break;
      } else {
        cout << "! " << sel << "번 항목이 존재하지 않습니다.\n"
             << "------------------------------------------------------------"
                "--------------\n";
      }
    }

    while(true){
      cout << "1) 예\n"
           << "0) 아니오 \n"
           << "정말 삭제하시겠습니까? > ";

      sel = select_num(1);
      cout << "------------------------------------------------------------"
              "--------------\n";
      if (sel == 0) {
        return;
      } else if (sel == 1) {
        all_classes_list.erase(iter);
        cout << "삭제가 완료되었습니다.\n"
             << "------------------------------------------------------------"
                "--------------\n";
        break;
      } else {
        cout << "! " << sel << "번 항목이 존재하지 않습니다.\n"
             << "------------------------------------------------------------"
                "--------------\n";
      }
    }
  }
}