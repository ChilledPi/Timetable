#include "S_timetable_management_prompts.h"
#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"

using namespace std;

void S_timetable_management_prompt(){
  while(true){
    string input;
    int _btn;
    cout << "0) 뒤로가기" << endl << endl;
    cout << "1) 시간표 추가" << endl << endl;
    cout << "2) 시간표 삭제" << endl;
    cout << "------------------------------------------------------------------"
            "--------"
         << endl;
    cout << "B07 Timetable:menu > ";
    _btn = check_num_input(2);

    if(_btn == 1){
      S_add_timetable_prompt();
    }else if(_btn == 2){
      S_delete_timetable_prompt();
    }else if(_btn == 0){
      return;
    }

  }
}
