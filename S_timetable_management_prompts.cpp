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
    // getline(cin, input);
    // cout << endl;

    // if (input.empty() || input.find_first_not_of(" \t\n")) {
    //   cout << "개행문자는 입력으로 받을 수 없습니다." << endl << endl;
    //   S_timetable_management_prompt();
    // }

    if(_btn == 1){
      S_add_timetable_prompt();
    }else if(_btn == 2){
      S_delete_timetable_prompt();
    }else if(_btn == 0){
      return;
    }

    // if (isdigit(input[0])) {
    //   _btn = stoi(input);
    //   switch (_btn) {
    //     case 1:
    //       S_add_timetable_prompt();
    //       break;
    //     case 2:
    //       S_delete_timetable_prompt();
    //       break;
    //     case 0:
    //       S_main_prompt();
    //       break;
    //     default:
    //       cout << "올바른 번호를 입력해주세요." << endl;
    //       S_timetable_management_prompt();
    //   }
    // } else {
    //   cout << "잘못된 입력입니다." << endl << endl;
    //   S_timetable_management_prompt();
    // }
  }
}

// #include <fstream>
// #include <iostream>
// #include <regex>
// #include <sstream>
// #include <string>
// #include <vector>
// using namespace std;

// void S_main_prompt();
// void S_timetable_management_prompt();
// void S_add_timetable_prompt();
// void S_delete_timetable_prompt();
// void S_select_main_timetable_prompt();
// void print_timetable_list();
// void S_add_tables(string name);
// void S_delete_tables();
// int check_name(string name);
// void S_update_main_timetable(vector<string> lines, int select_number);
// bool S_check_file();
// void S_name_duplication(string name);

// int main() { S_main_prompt(); }

// void S_main_prompt() {
//   ifstream file("timetables.txt");
//   string firstLine;
//   string input;
//   int main_btn;
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   cout << "학생메뉴" << endl << endl;
//   if (!S_check_file()) {
//     cout << "대표 시간표: 없음" << endl << endl;
//   } else {
//     if (file.is_open() && getline(file, firstLine)) {
//       cout << "대표 시간표: " << firstLine << endl << endl;
//     }
//     file.close();
//   }
//   cout << "1) no.. " << endl;
//   cout << "2) 시간표 추가/삭제" << endl;
//   cout << "3) 대표시간표 변경" << endl << endl;
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   cout << "메뉴를 선택해주세요 > ";
//   getline(cin, input);
//   cout << endl;

//   if (input.empty() || input.find_first_not_of(" \t\n")) {
//     cout << "개행문자는 입력으로 받을 수 없습니다." << endl << endl;
//     S_main_prompt();
//   }
//   if (isdigit(input[0])) {
//     main_btn = stoi(input);
//     switch (main_btn) {
//       case 1:
//         break;
//       case 2:
//         S_timetable_management_prompt();
//         break;
//       case 3:
//         S_select_main_timetable_prompt();
//         break;
//       default:
//         cout << "올바른 번호를 입력해주세요." << endl << endl;
//         S_main_prompt();
//     }
//   } else {
//     cout << "잘못된 입력입니다." << endl << endl;
//     S_main_prompt();
//   }
// }

// void S_timetable_management_prompt() {
//   string input;
//   int _btn;
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   cout << "1 ) 시간표 추가" << endl;
//   cout << "2 ) 시간표 삭제" << endl;
//   cout << "0 ) 뒤로가기" << endl << endl;
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   cout << "메뉴를 선택해주세요 > ";
//   getline(cin, input);
//   cout << endl;

//   if (input.empty() || input.find_first_not_of(" \t\n")) {
//     cout << "개행문자는 입력으로 받을 수 없습니다." << endl << endl;
//     S_timetable_management_prompt();
//   }

//   if (isdigit(input[0])) {
//     _btn = stoi(input);
//     switch (_btn) {
//       case 1:
//         S_add_timetable_prompt();
//         break;
//       case 2:
//         S_delete_timetable_prompt();
//         break;
//       case 0:
//         S_main_prompt();
//         break;
//       default:
//         cout << "올바른 번호를 입력해주세요." << endl;
//         S_timetable_management_prompt();
//     }
//   } else {
//     cout << "잘못된 입력입니다." << endl << endl;
//     S_timetable_management_prompt();
//   }
// }

// void S_add_timetable_prompt() {
//   string name;
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   print_timetable_list();
//   cout << "0) 뒤로가기" << endl << endl;
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   cout << "새로운 시간표의 이름을 입력해주세요 > ";
//   getline(cin, name);
//   cout << endl;
//   if (name == "0") {
//     S_timetable_management_prompt();
//   }

//   S_name_duplication(name);

//   if (check_name(name) == 0) {
//     cout << "시간표가 추가되었습니다." << endl << endl;
//     S_add_tables(name);

//     S_timetable_management_prompt();
//   } else if (check_name(name) == -1) {
//     cout << "잘못된 입력입니다." << endl;
//     cout << "올바른 입력: 단어 별 공백 및 처음 단어는 대문자." << endl;
//     cout << "ex ) System Programming." << endl << endl;

//     S_add_timetable_prompt();
//   } else {
//     cerr << "System error" << endl;
//   }
// }

// void S_name_duplication(string name) {
//   vector<string> lines;
//   vector<string> dup;
//   string line;

//   ifstream file("timetables.txt");
//   if (file.is_open()) {
//     while (getline(file, line)) {
//       lines.push_back(line);
//     }
//   }
//   file.close();

//   for (const string& name : lines) {
//     stringstream ss(name);
//     string token;
//     getline(ss, token, '\t');
//     dup.push_back(token);
//   }

//   for (int i = 0; i < dup.size(); i++) {
//     if (name == dup[i]) {
//       cout << "중복된 이름입니다." << endl << endl;
//       S_add_timetable_prompt();
//     }
//   }
// }

// void S_delete_timetable_prompt() {
//   if (!S_check_file()) {
//     cerr << "No File" << endl;
//     S_timetable_management_prompt();
//   } else {
//     S_delete_tables();
//   }
// }

// void S_select_main_timetable_prompt() {
//   int selectedLineNumber;
//   vector<string> lines;
//   string line;
//   string input;
//   if (!S_check_file()) {
//     cout << "No File" << endl;
//     S_timetable_management_prompt();
//   } else {
//     cout << "--------------------------------------------------------" << endl
//          << endl;
//     print_timetable_list();
//     cout << "0) 뒤로가기" << endl << endl;
//     cout << "--------------------------------------------------------" << endl
//          << endl;
//   }

//   ifstream file("timetables.txt");
//   if (file.is_open()) {
//     while (getline(file, line)) {
//       lines.push_back(line);
//     }
//   }
//   file.close();

//   cout << "대표시간표로 설정할 시간표의 번호를 입력해주세요 > ";
//   getline(cin, input);
//   cout << endl;

//   if (input.empty() || input.find_first_not_of(" \t\n")) {
//     cout << "개행문자는 입력으로 받을 수 없습니다." << endl << endl;
//     S_select_main_timetable_prompt();
//   }
//   if (isdigit(input[0])) {
//     selectedLineNumber = stoi(input);
//     if (selectedLineNumber == 0) {
//       S_main_prompt();
//     } else {
//       S_update_main_timetable(lines, selectedLineNumber);
//     }
//   } else {
//     cout << "잘못된 입력입니다." << endl << endl;
//     S_select_main_timetable_prompt();
//   }
// }

// void S_update_main_timetable(vector<string> lines, int select_number) {
//   if (select_number >= 1 && select_number <= lines.size()) {
//     string selectedLine = lines[select_number - 1];
//     lines.erase(lines.begin() + select_number - 1);
//     lines.insert(lines.begin(), selectedLine);
//   } else if (select_number < 1 || select_number > lines.size()) {
//     cout << "올바른 번호가 아닙니다." << endl << endl;
//     S_select_main_timetable_prompt();
//   } else {
//     cout << "잘못된 입력입니다." << endl;
//     S_select_main_timetable_prompt();
//   }

//   ofstream outFile("timetables.txt");
//   if (outFile.is_open()) {
//     for (const string& updatedLine : lines) {
//       outFile << updatedLine << endl;
//     }
//     outFile.close();
//     cout << "대표시간표가 변경되었습니다." << endl << endl;
//   } else if (!outFile.is_open()) {
//     cout << "Unable to open file" << endl;
//   }
//   cout << "현재 시간표 목록" << endl;
//   print_timetable_list();
//   S_main_prompt();
// }

// void print_timetable_list() {
//   ifstream file("timetables.txt");
//   if (file.is_open()) {
//     int lineNumber = 1;
//     string line;
//     while (getline(file, line)) {
//       if (!line.empty()) {
//         cout << lineNumber << ". " << line << endl;
//         lineNumber++;
//       }
//     }
//     cout << endl;
//     file.close();
//   } else {
//     cout << "Unable to open file";
//   }
// }

// void S_add_tables(string name) {
//   string filename = "timetables.txt";
//   string timetable_name = name;
//   ofstream file;

//   file.open(filename, ios::app);

//   if (!file.is_open()) {
//     cerr << "File Load Fail." << endl;
//     S_main_prompt();
//   }

//   file << timetable_name << "\n";

//   file.close();
//   cout << "현재 시간표 목록" << endl;
//   print_timetable_list();
// }

// void S_delete_tables() {
//   cout << "--------------------------------------------------------" << endl
//        << endl;
//   print_timetable_list();
//   cout << "0) 뒤로가기" << endl << endl;
//   cout << "--------------------------------------------------------" << endl
//        << endl;

//   string input;
//   string line;
//   vector<string> lines;
//   int select_num;

//   ifstream ifile("timetables.txt");
//   if (!ifile.is_open()) {
//     cerr << "File load fail." << endl;
//     S_timetable_management_prompt();
//   }

//   while (getline(ifile, line)) {
//     lines.push_back(line);
//   }

//   ifile.close();

//   cout << "삭제할 시간표의 번호를 입력해주세요 > ";
//   getline(cin, input);
//   cout << endl;

//   if (input.empty() || input.find_first_not_of(" \t\n")) {
//     cout << "개행문자는 입력으로 받을 수 없습니다." << endl << endl;
//     S_delete_timetable_prompt();
//   }

//   if (isdigit(input[0])) {
//     select_num = stoi(input);
//     if (select_num == 0) {
//       S_timetable_management_prompt();
//     }

//     if (select_num < 0 || select_num > lines.size()) {
//       cout << "리스트 내의 번호가 아닙니다. 다시 입력해주세요." << endl << endl;

//       S_delete_timetable_prompt();

//     }

//     else {
//       lines.erase(lines.begin() + select_num - 1);

//       ofstream ofile("timetables.txt");
//       if (!ofile.is_open()) {
//         cerr << "File load fail." << endl;
//         S_timetable_management_prompt();
//       }

//       for (string& updated_line : lines) {
//         ofile << updated_line << '\n';
//       }

//       ofile.close();

//       cout << "삭제되었습니다." << endl << endl;
//       cout << "현재 시간표 목록" << endl;
//       print_timetable_list();

//       S_main_prompt();
//     }
//   } else {
//     cout << "잘못된 입력입니다." << endl << endl;
//     S_delete_timetable_prompt();
//   }
// }

// int check_name(string name) {
//   regex re("^[A-Z][a-z]{0,19}( [A-Z][a-z]+){0,2}$");

//   if (regex_match(name, re)) {
//     return 0;
//   } else {
//     return -1;
//   }
// }

// bool S_check_file() {
//   ifstream file("timetables.txt");
//   return file.peek() != ifstream::traits_type::eof();
// }