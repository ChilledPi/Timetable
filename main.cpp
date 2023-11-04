#include "main.h"
#include "file_integrity.h"
#include "types.h"
#include "utils.h"

vector<Lecture> all_classes_list;
vector<pair<string, string>> professor;
vector<string> classrooms;

string home_path;

int main(int argc, char* argv[]) {
  home_path = argv[0];
  check_file();

  // all_classes_list.push_back(
  //     Lecture(string("1000"), string("System Programming"), string("1234")));
  // all_classes_list.push_back(
  //     Lecture(string("1004"), string("System Programming"), string("1234")));
  // all_classes_list.push_back(
  //     Lecture(string("1002"), string("System Programming"), string("1234")));
  // all_classes_list.push_back(
  //     Lecture(string("1003"), string("System Programming"), string("1234")));
  // all_classes_list.push_back(
  //     Lecture(string("1001"), string("System Programming"), string("1234")));

  menu_prompt();
  // find(all_classes_list.begin(), all_classes_list.end(), str);
  update_all_classes_file();
}
