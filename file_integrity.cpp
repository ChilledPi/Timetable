#include "file_integrity.h"
#include "utils.h"
#include "types.h"

extern vector<Lecture> all_classes_list;
extern vector<string> professor;
extern vector<string> classrooms;

extern string home_path;

using namespace std;

bool prof_is_addable(string prof, vector<tp> his_time) {
  vector<Lecture> lects;
  for (int i = 0; i < all_classes_list.size(); i++) {
    if (prof == all_classes_list.at(i).professor_id) {
      Lecture temp = all_classes_list.at(i);
      lects.push_back(temp);
    }
  }
  for (int i = 0; i < lects.size(); i++) {
    for (int j = 0; j < his_time.size(); j++) {
      for (int k = 0; k < lects.at(i).tp_list.size(); k++) {
        if (his_time.at(j).day == lects.at(i).tp_list.at(k).day) {
          int t2 = stoi(his_time.at(j).time);
          int t3 = stoi(lects.at(i).tp_list.at(k).time);
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
  }
  return true;
}
bool room_is_addable(tp time, string room) {
  for (int i = 0; i < all_classes_list.size(); i++) {
    for (int j = 0; j < all_classes_list.at(i).tp_list.size(); j++) {
      if (all_classes_list.at(i).tp_list.at(j).classroom == room) {
        if (all_classes_list.at(i).tp_list.at(j).day == time.day) {
          int t2 = stoi(all_classes_list.at(i).tp_list.at(j).time);
          int t3 = stoi(time.time);
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
  }
  return true;
}
bool is_expendable(vector<tp> ex, Day day, string time) {
  for (int i = 0; i < ex.size(); i++) {
    if (ex.at(i).day == day) {
      int t2 = stoi(ex.at(i).time);
      int t3 = stoi(time);
      int t22 = t2 / 100;
      t2 %= 100;
      int t33 = t3 / 100;
      t3 %= 100;
      if ((t33 >= t22 && t33 <= t2) || (t22 >= t33 && t22 <= t3)) {
        return false;
      }
    }
  }
  return true;
}

void all_class_integrity() {
  bool file_is_fuckedup = false;
  fstream newfile;
  string classes;
  newfile.open("allclasses.txt");
  while (getline(newfile, classes)) {
    bool is_fuckedup = false;
    string num;
    istringstream ss(classes);
    int a = 0;
    Lecture all_classes;
    while (getline(ss, num, '\t')) {
      if (a == 0) {
        for (int i = 0; i < all_classes_list.size(); i++) {
          if (num == all_classes_list.at(i).num) {
            is_fuckedup = true;
            break;
          }
        }
        if (check_num(num) != 0) {
          is_fuckedup = true;
          break;
        }
        all_classes.num = num;
      } else if (a == 1) {
        if (check_name(num) != 0) {
          is_fuckedup = true;
          break;
        }
        all_classes.name = num;
      } else if (a == 2) {
        string dt;
        istringstream daytime(num);
        int b = 0;
        vector<tp> dtl;
        tp thatday;
        while (getline(daytime, dt, ' ')) {
          bool exists = false;
          int c;
          switch (b % 2) {
            case 0:
              if (check_time(dt) != 0) {
                is_fuckedup = true;
                break;
              }
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
              if (!is_expendable(dtl, thatday.day, thatday.time)) {
                is_fuckedup = true;
                break;
              }
              break;
            case 1:
              for (int i = 0; i < classrooms.size(); i++) {
                if (classrooms.at(i) == dt) {
                  exists = true;
                }
              }
              if (check_num(dt) != 0 || exists == false) {
                is_fuckedup = true;
                break;
              }
              if (!room_is_addable(thatday, dt)) {
                is_fuckedup = true;
                break;
              }
              thatday.classroom = dt;
              dtl.push_back(thatday);
              break;
          }
          b++;
        }
        all_classes.tp_list = dtl;
      } else if (a == 3) {
        bool exist = false;
        for (int i = 0; i < professor.size(); i++) {
          if (professor.at(i) == num) {
            exist = true;
          }
        }
        if (check_num(num) != 0 || exist == false) {
          is_fuckedup = true;
          break;
        }
        if (!prof_is_addable(num, all_classes.tp_list)) {
          is_fuckedup = true;
          break;
        }
        all_classes.professor_id = num;
      }
      a++;
    }
    if (is_fuckedup || a != 4) {
      cout << classes << endl;
      file_is_fuckedup = true;
    }
    all_classes_list.push_back(all_classes);
  }
  if (file_is_fuckedup) {
    abort();
  }
}
void time_table_integrity() {
  fstream newfile;
  string classes;
  newfile.open("timetables.txt");
  bool file_is_fuckedup = false;
  while (getline(newfile, classes)) {
    string num;
    istringstream ss(classes);
    int a = 0;
    vector<string> time_name;
    bool is_fuckedup = false;
    vector<Lecture> temp;
    while (getline(ss, num, '\t')) {
      if (a == 0) {
        for (int i = 0; i < time_name.size(); i++) {
          if (num == time_name.at(i) || check_name(num) == -1) {
            is_fuckedup = true;
            break;
          }
        }
        time_name.push_back(num);
      } else {
        bool exist = false;
        for (int i = 0; i < all_classes_list.size(); i++) {
          if (all_classes_list.at(i).num == num) {
            exist = true;
          }
        }
        if (exist == false) {
          is_fuckedup = true;
          break;
        }
        if (!temp.empty()) {
          if (is_addable(temp, num)) {
            Lecture temp2;
            temp2.num = num;
            temp.push_back(temp2);
          } else {
            is_fuckedup = true;
          }
        }
      }
      a++;
    }
    if (is_fuckedup) {
      cout << classes << endl;
      file_is_fuckedup = true;
    }
  }
  if (file_is_fuckedup == true) {
    abort();
  }
}
void professor_list_integrity() {
  bool file_is_fuckedup = false;
  fstream newfile;
  string classes;
  newfile.open("Professor_list.txt");
  if (newfile.peek() == ifstream::traits_type::eof()) abort();
  while (getline(newfile, classes)) {
    bool is_fuckedup = false;
    string num;
    istringstream ss(classes);
    int a = 0;
    if (classes == "") {
      file_is_fuckedup = true;
    }
    while (getline(ss, num, '\t')) {
      if (a == 0) {
        if (check_num(num) != 0) {
          is_fuckedup = true;
        }
        professor.push_back(num);
      } else if (a == 1) {
        if (check_name(num) == -1) {
          is_fuckedup = true;
        }
      } else {
        is_fuckedup = true;
      }
      a++;
    }
    if (is_fuckedup) {
      cout << classes << endl;
      file_is_fuckedup = true;
    }
  }
  set<string> proflist(professor.begin(), professor.end());
  if (proflist.size() < professor.size() || file_is_fuckedup == true) {
    abort();
  }
}
void classroom_list_integrity() {
  fstream newfile;
  string classes;
  bool is_fuckedup = false;
  newfile.open("Classroom_list.txt");
  if (newfile.peek() == ifstream::traits_type::eof()) abort();
  while (getline(newfile, classes)) {
    if (classes == "") {
      is_fuckedup = true;
    }
    if (check_num(classes) != 0) {
      cout << classes << endl;
      is_fuckedup = true;
    }
    classrooms.push_back(classes);
  }
  set<string> roomlist(classrooms.begin(), classrooms.end());
  if (roomlist.size() < classrooms.size() || is_fuckedup == true) {
    abort();
  }
}


void check_file() {

  ifstream lect("Professor_list.txt");
  ifstream lect2("Classroom_list.txt");
  ifstream lect3("allclasses.txt");
  ifstream lect4("timetables.txt");
  bool exist = true;
  if (!lect) {
    cout << "경고: 홈 경로" << home_path << "에 Professor_list 데이터 파일이 없습니다." << endl;
    abort();
    // cout << "홈 경로에 빈 데이터 파일을 새로 생성했습니다:" << endl;
    // cout << home_path << "\\Professor_list.txt" << endl;
    // exist = false;
    // ofstream class_file("Professor_list.txt");
    // if (stat("C:\\Timetable\\Professor_list.txt", &sb) != 0) {
    //   abort();
    // }
  } else {
    professor_list_integrity();
  }

  if (!lect2) {
    cout << "경고: 홈 경로" << home_path << "에 Classroom_list 데이터 파일이 없습니다." << endl;
    abort();
      // cout << "홈 경로에 빈 데이터 파일을 새로 생성했습니다:" << endl;
      // exist = false;
    // cout << home_path << "\\Classroom_list.txt " << endl;
    // ofstream class_file("Classroom_list.txt");
    // if (stat("C:\\Timetable\\Classroom_list.txt", &sb) != 0) {
    //   abort();
    // }
  } else {
    classroom_list_integrity();
  }

  if (!lect3) {
    if (!exist) {
      cout << "경고: 홈 경로" << home_path << "에 데이터 파일이 없습니다." << endl;
      cout << "홈 경로에 빈 데이터 파일을 새로 생성했습니다:" << endl;
      exist = false;
    }
    cout << home_path << "\\allclasses.txt" << endl;
    ofstream class_file("allclasses.txt");
    // if (stat("C:\\Timetable\\allclasses.txt", &sb) != 0) {
    //   abort();
    // }
  } else {
    all_class_integrity();
  }
  if (!lect4) {
    if (!exist) {
      cout << "경고: 홈 경로" << home_path << "데이터 파일이 없습니다." << endl;
      cout << "홈 경로에 빈 데이터 파일을 새로 생성했습니다:" << endl;
      exist = false;
    }
    cout << home_path << "\\timetables.txt" << endl;
    ofstream class_file("timetables.txt");
    // if (stat("C:\\Timetable\\timetables.txt", &sb) != 0) {
    //   abort();
    // }
  } else {
    time_table_integrity();
  }
}