#include "types.h"
#include "utils.h"
#include "delete_lecture_prompts.h"
#include <iostream>
#include <algorithm>

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
      if((sel = check_num_input(all_classes_list.size())) > 0){
        iter = find(all_classes_list.begin(), all_classes_list.end(),
                    all_classes_list[sel - 1]);
      }else{
        return;
      }
    }

    while(true){
      cout << "1) 예\n"
           << "0) 아니오 \n"
           << "정말 삭제하시겠습니까? > ";
      if((sel = check_num_input(1)) == 1){
        all_classes_list.erase(iter);
        cout << "삭제가 완료되었습니다.\n"
             << "------------------------------------------------------------"
                "--------------\n";
        break;
      }else{
        return;
      }
    }
  }
}