#include "utils.h"
#include <string>
#include <iostream>

void S_add_timetable_prompt() {
    string name;
    while (true) {
      cout << "추가할 시간표의 이름을 입력해주세요 > ";
      if ((name = read_name()) != "") break;
        cout <<
        "----------------------------------------------------------------"
                "--"
                "--------"
             << endl;
    }
    if (!name_duplication(name)) return;
    add_tables(name);
}