#include "utils.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
// #include <algorithm>

#include "types.h"

extern vector<Lecture> all_classes_list;

void print_lecture_list() { // 어디까지 출력할 지 정하기
  sort(all_classes_list.begin(), all_classes_list.end());
  for (int i = 0; i < all_classes_list.size(); i++) {
    vector<int> count(all_classes_list.size());
    for(int j = i; j < all_classes_list.size(); j++){
      if (all_classes_list[i].name == all_classes_list[j].name){
        if(count[i] == 0){
          count[i] = 1;
        }
        count[j] = count[i] + 1;
        break;
      }
    }
    cout << i + 1 << ") " << all_classes_list[i].name << ' ';
    if (count[i]) cout << count[i] << ' ';
    cout << all_classes_list[i].num << ' ';
    for (tp j : all_classes_list[i].tp_list) {
      cout << j.day << j.time << ' ';
         }
         cout << '\n';
  }
}

std::string ltrim(std::string const & str)  // 문자열 좌측 공백 제거
{
  return std::regex_replace(str, std::regex("^\\s+"), "");
}
std::string rtrim(std::string const & str)  // 문자열 우측 공백 제거
{
  return std::regex_replace(str, std::regex("\\s+$"), "");
}
std::string trim(std::string const & str)  // 문자열 좌우 공백 제거
{
  return ltrim(rtrim(str));
}

int check_num_input(int num){
  string str;
  regex zero("^0[0-9]+$");
  regex re("^\\d+$");
  int ret = 0;
  bool is_num = true;
  getline(cin, str);
  str = trim(str);
  if (regex_match(str, re)) {
    if (regex_match(str, zero)) {
      is_num = false;
    } else {
      ret = stoi(str);
    }
  }else{
    is_num = false;
  }

  cout << "------------------------------------------------------------"
          "--------------\n";
  if (is_num) {
    if (0 <= ret && ret <= num) {
      return ret;
    }
    cout << "! " << ret << "번 항목이 존재하지 않습니다.\n"
         << "------------------------------------------------------------"
            "--------------\n";
    return -1;
  } else {
    cout << "! 잘못 입력했습니다. 범위(0~" << num
         << ") 안에서 다시 선택해주세요\n"
         << "------------------------------------------------------------"
            "--------------\n";
    return -1;
  }
}

int check_name(string name) {
  regex re("^[A-Z][a-z]{0,19}( [A-Z][a-z]{0,19}){0,2}$");
  if (regex_match(name, re)) {
    return 0;
  } else{
    return -1;
  }
}

string read_name() {
  string ret;
  int sel;
  getline(cin, ret);
  ret = trim(ret);
  cout << "------------------------------------------------------------"
          "--------------\n";

  if (check_name(ret) == 0) {
    return ret;
  } else {
    cout << "! 이름은 최대 단어 3개로 구성되며, 각 단어는 빈 칸으로 구분되고, 단어는 대문자로 시작합니다.\n"  // 오류 메세지
         << "------------------------------------------------------------"
            "--------------\n";
    return "";
  }
}

int check_num(string num) {
  regex re("^\\d{4}$");
  // if(num.length() != 4){
  //   return -1;
  // }
  if(regex_match(num, re)){
    return 0;
  }
  return -1;
}

string read_num() {
  string ret;
  getline(cin, ret);
  ret = trim(ret);
  cout << "------------------------------------------------------------"
          "--------------\n";

  if (check_num(ret) == 0) {
    return ret;
  } else {
    cout << "! 번호는 0으로 시작하지 않는 4자리 수입니다.\n"  // 오류 메세지
         << "------------------------------------------------------------"
            "--------------\n";
    return "";
  }
}

int check_time(string time) {
  regex re("^[0-4]((0[1-9])|(1[0-8])){2}$");

  if(regex_match(time, re)){
    string sub1, sub2;
    sub1 = time.substr(1, 2);
    sub2 = time.substr(3, 4);
    if (stoi(sub1) >= stoi(sub2)) return -2;
    else
      return 0;
  }
  return -1;
}

string read_time() {
  string ret;
  int sel;
  getline(cin, ret);
  ret = trim(ret);
  cout << "------------------------------------------------------------"
          "--------------\n";
  sel = check_time(ret);
  if (sel == 0) {
    return ret;
  } else if(sel == -1) {
    cout << "! 강의 시간은 요일(0~4) + 시작 교시(00~19) + 끝 교시로(00~19) "
            "구성됩니다.\n"  // 오류 메세지
         << "------------------------------------------------------------"
            "--------------\n";
    return "";
  } else{
    cout << "! 시작시간이 종료시각보다 빨라야 합니다.\n"  // 오류 메세지
         << "------------------------------------------------------------"
            "--------------\n";
    return "";
  }
}

int check_credit(string credit) {
  regex re("^[1-3]$");
  if (regex_match(credit, re)) {
    return 0;
  }
  return -1;
}

void update_all_classes_file() {
  ofstream ofs("allclasses.txt", ios::trunc);
  sort(all_classes_list.begin(), all_classes_list.end());
  for (int i = 0; i < all_classes_list.size(); i++){
    ofs << all_classes_list[i].num << '\t' << all_classes_list[i].name << '\t';
    for (int j = 0; j < all_classes_list[i].tp_list.size(); j++) {
      ofs << all_classes_list[i].tp_list[j].day
          << all_classes_list[i].tp_list[j].time << ' '
          << all_classes_list[i].tp_list[j].classroom;
      if (j == (all_classes_list[i].tp_list.size() - 1)) ofs << '\t';
      else ofs << ' ';
    }
    for (int j = 0; j < all_classes_list[i].professor_id_list.size(); j++) {
      ofs << all_classes_list[i].professor_id_list[j];
      if (j == (all_classes_list[i].professor_id_list.size() - 1))
        ofs << '\t';
      else
        ofs << ' ';
    }
    ofs << all_classes_list[i].credit << '\n';
  }
}

bool is_addable(vector<Lecture> temp, string selectedLectureIndex) {
  if (temp.empty()) {
    return true;
  }
  Lecture temp2;
  for (int i = 0; i < all_classes_list.size(); i++) {
    if (all_classes_list.at(i).num == selectedLectureIndex) {
      temp2 = all_classes_list.at(i);
    }
  }

  for (int i = 0; i < temp.size(); i++) {
    Lecture temp3;
    for (int j = 0; j < all_classes_list.size(); j++) {
      if (all_classes_list.at(j).num == temp.at(i).num) {
        temp3 = all_classes_list.at(j);
      }
    }
    for (int j = 0; j < temp2.tp_list.size(); j++) {
      for (int k = 0; k < temp3.tp_list.size(); k++) {
        if (temp2.tp_list.at(j).day == temp3.tp_list.at(k).day) {
          int t2 = stoi(temp2.tp_list.at(j).time);
          int t3 = stoi(temp3.tp_list.at(k).time);
          int t22 = t2 / 100;
          t2 %= 100;
          int t33 = t3 / 100;
          t3 %= 100;
          if ((t33 >= t22 && t33 <= t2) || (t22 >= t33 && t22 <= t3)) {
            return false;
          }
        }
      }
    }
    if (temp2.name == temp3.name) {
      return false;
    }
  }

  return true;
}

  Lecture& Lecture::operator=(const Lecture& rhs) {
    num = rhs.num;
    name = rhs.name;
    professor_id_list = rhs.professor_id_list;
    tp_list = rhs.tp_list;
    return *this;
  }

  int print_timetable_list() {
  ifstream file("timetables.txt");
  if (file.is_open()) {
    int lineNumber = 0;
    string line;
    while (getline(file, line)) {
      if (!line.empty()) {
        cout << lineNumber + 1 << ") " << line.substr(0, line.find('\t'))
             << endl;
        lineNumber++;
      }
    }
    return lineNumber;
  } else {
    cout << "Unable to open file";
    return -1;
  }
  }

  void print_selected_timetable(int selected_line){
  ifstream file("timetables.txt");
  if (file.is_open()) {
    int lineNumber = 1;
    string line;
    while (getline(file, line)) {
      if (lineNumber == selected_line) {
        replace(line.begin(), line.end(), '\t', '/');
        cout << line << endl;
      }
      lineNumber++;
    }
    return;
  } else {
    cout << "Unable to open file";
    return;
  }
  }

  bool name_duplication(string name) {
  vector<string> lines;
  vector<string> dup;
  string line;

  ifstream file("timetables.txt");
  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
  }
  file.close();

  for (const string& name : lines) {
    stringstream ss(name);
    string token;
    getline(ss, token, '\t');
    dup.push_back(token);
  }

  for (int i = 0; i < dup.size(); i++) {
    if (name == dup[i]) {
      cout << "중복된 이름입니다." << endl;
      cout << "------------------------------------------------------------"
              "--------------\n";
      // S_add_timetable_prompt();
      return false;
    }
  }
  return true;
  }

  void add_tables(string name) {
  string filename = "timetables.txt";
  string timetable_name = name;
  ifstream ifile;
  ofstream ofile;
  char last;

  ifile.seekg(-1, ios_base::end);
  ifile.get(last);
  ifile.close();

  ofile.open(filename, ios::app);

  if (!ofile.is_open()) {
    cerr << "File Load Fail." << endl;
    // S_main_prompt();
  }

  if (last == '\n') {
    ofile << timetable_name << "\n";
  } else {
    ofile << timetable_name << "\n";
  }
  cout << "추가되었습니다!\n"
       << "----------------------------------------------------------------"
          "--"
          "--------\n";
  ofile.close();
  // cout << "현재 시간표 목록" << endl;
  // print_timetable_list();
  }

  bool S_check_file() {
  ifstream file("timetables.txt");
  return file.peek() == ifstream::traits_type::eof();
  }

  void S_update_main_timetable(vector<string> lines, int select_number) {
  string selectedLine = lines[select_number - 1];
  lines.erase(lines.begin() + select_number - 1);
  lines.insert(lines.begin(), selectedLine);
  ofstream outFile("timetables.txt");
  if (outFile.is_open()) {
    for (const string& updatedLine : lines) {
      outFile << updatedLine << endl;
    }
    outFile.close();
    cout << "변경되었습니다!" << endl;
    } else if (!outFile.is_open()) {
      cout << "Unable to open file" << endl;
    }
    cout << "----------------------------------------------------------------"
            "--"
            "--------"
         << endl;
  }

  vector<vector<string>> get_all_timetables(){
    vector<vector<string>> all_timetables;
    string str;
    string token;
    ifstream file("timetables.txt");

    while (getline(file, str)) {
      istringstream iss(str);
      vector<string> temp;
      while (getline(iss, token, '\t')) {
      temp.push_back(token);
      }
      all_timetables.push_back(temp);
    }
    return all_timetables;
  }

  void remove_lecture_in_timetable(string num) {
    vector<vector<string>> all_timetables = get_all_timetables();
    ofstream file("timetables.txt");

    for (int i = 0; i < all_timetables.size(); i++) {
      for (int j = 0; j < all_timetables[i].size(); j++) {
      if (all_timetables[i][j] == num) {
        all_timetables[i].erase(all_timetables[i].begin() + j);
      }
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
  }