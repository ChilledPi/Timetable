#ifndef FILE_INTEGRITY_H
#define FILE_INTEGRITY_H
#include <string>
#include <vector>
#include "types.h"

void all_class_integrity();
void time_table_integrity();
void professor_list_integrity();
void classroom_list_integrity();
void check_file();
bool prof_is_addable(string prof, vector<tp> his_time);
bool room_is_addable(tp time, string room);
bool is_expendable(vector<tp> ex, Day day, string time);

#endif