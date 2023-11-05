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
  menu_prompt();
  update_all_classes_file();
}
