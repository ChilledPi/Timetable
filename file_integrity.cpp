#include "file_integrity.h"
#include "utils.h"
#include "types.h"

extern vector<Lecture> all_classes_list;

using namespace std;

void all_class_integrity() {
  fstream newfile;
  string classes;
  newfile.open("classes.txt");
  while (getline(newfile, classes)) {
    string num;
    istringstream ss(classes);
    int a = 0;
    Lecture test;
    while (getline(ss, num, '\t')) {
      if (a == 0) {
        if (check_num(num) != 0){
          cout << classes;
          // abort();
        }
        test.num = num;
      } else if (a == 1) {
        if (check_name(num) == -1){
          cout << classes;
          // abort();
        }
        test.name = num;
      } else if (a == 2) {
        string dt;
        istringstream daytime(num);
        int b = 0;
        vector<tp> dtl;
        tp thatday;
        while (getline(daytime, dt, ' ')) {
          int c;
          switch (b % 2) {
            case 0:
              c = dt.at(0) - '1';
              switch (c) {
                case 0:
                  thatday.day = MON;
                  break;
                case 1:
                  thatday.day = TUE;
                  break;
                case 2:
                  thatday.day = WED;
                  break;
                case 3:
                  thatday.day = THU;
                  break;
                case 4:
                  thatday.day = FRI;
                  break;
              }
              dt.erase(0, 1);
              thatday.time = dt;
              break;
            case 1:
              thatday.classroom = dt;
              dtl.push_back(thatday);
              break;
          }
          b++;
        }
        test.tp_list = dtl;
      } else if (a == 3) {
        test.professor_id = num;
      }
      a++;
    }
    all_classes_list.push_back(test);
  }
}

void time_table_integrity() {
  fstream newfile;
  string classes;
  newfile.open("classes.txt");
  while (getline(newfile, classes)) {
    string num;
    istringstream ss(classes);
    while (getline(ss, num, '\t')) {
    }
  }
}
void professor_list_integrity() {
  fstream newfile;
  string classes;
  newfile.open("professor.txt");
  while (getline(newfile, classes)) {
    string num;
    istringstream ss(classes);
    while (getline(ss, num, '\t')) {
    }
  }
}
void classroom_list_integrity() {
  fstream newfile;
  string classes;
  newfile.open("classroom.txt");
  while (getline(newfile, classes)) {
    string num;
    istringstream ss(classes);
  }
}
void check_file() {
  ifstream lect("classes.txt");
  ifstream lect2("time.txt");
  ifstream lect3("professor.txt");
  ifstream lect4("classroom.txt");
  if (!lect) {
    cout << "classes.txt doesn't exist. Creating" << endl;
    ofstream class_file("classes.txt");
  } else {
    all_class_integrity();
  }
  if (!lect2) {
    cout << "time.txt doesn't exist. Creating" << endl;
    ofstream class_file("time.txt");
  } else {
    time_table_integrity();
  }
  if (!lect3) {
    cout << "professor.txt doesn't exist. Creating" << endl;
    ofstream class_file("professor.txt");
  } else {
    professor_list_integrity();
  }
  if (!lect4) {
    cout << "classroom.txt doesn't exist. Creating" << endl;
    ofstream class_file("classroom.txt");
  } else {
    classroom_list_integrity();
  }
}