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

  // tp(Day day_, string classroom_, string time_) : day(day_), classroom(classroom_), time(time_) {}
} tp;

class Lecture{
    public:
     string num;
     string name;
     vector<string> professor_id_list;
     vector<tp> tp_list;
     string credit;

     Lecture(){};
     Lecture(string num_): num(num_){}
     Lecture(string num_, string name_) : num(num_), name(name_){}

     bool operator<(const Lecture& rhs) const { return num < rhs.num; }
     bool operator==(const Lecture& rhs) const { return num == rhs.num; }
     Lecture& operator=(const Lecture& rhs);
};



#endif
