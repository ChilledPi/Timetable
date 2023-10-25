#ifndef TYPES_H
#define TYPES_H

#include<string>
#include<vector>

using namespace std;

enum Day { MON, TUE, WED, THU, FRI };

typedef struct TimePlace{
  Day day;
  string classroom;
  string time;
} tp;

class Lecture{
    public:
     string name;
     string num;
     string professor_id;
     vector<tp> tp_list;

     bool operator<(Lecture rhs) { return num < rhs.num; }
     bool operator==(Lecture rhs) { return num == rhs.num; }
};

#endif TYPES_H
