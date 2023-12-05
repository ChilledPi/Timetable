#include "file_integrity.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "types.h"
#include "utils.h"

extern vector<Lecture> all_classes_list;
extern vector<pair<string, string>> professor;
extern vector<string> classrooms;

extern string home_path;

using namespace std;

bool room_is_addable(tp time, string room) {
  for (int i = 0; i < all_classes_list.size(); i++) {
    for (int j = 0; j < all_classes_list.at(i).tp_list.size(); j++) {
      if (all_classes_list.at(i).tp_list.at(j).classroom == room) {
        if (all_classes_list.at(i).tp_list.at(j).day == time.day) {
          return compare_time(all_classes_list.at(i).tp_list.at(j).time,
                              time.time);
        }
      }
    }
  }
  return true;
}
bool is_expendable(vector<tp> ex, Day day, string time) {
  for (int i = 0; i < ex.size(); i++) {
    if (ex.at(i).day == day) {
      return compare_time(ex.at(i).time, time);
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
    string last = "";
    last += classes.back();
    if (classes == "" || last == "\t") {
      is_fuckedup = true;
    }
    string num;
    istringstream ss(classes);
    int a = 0;
    Lecture all_classes;
    while (getline(ss, num, '\t')) {
      if (a == 0) {
        for (int i = 0; i < all_classes_list.size(); i++) {
          if (num == all_classes_list.at(i).num) {
            is_fuckedup = true;
            // cout << "1\n";
            break;
          }
        }
        if (check_num(num) != 0) {
          is_fuckedup = true;
          // cout << "2\n";
          break;
        }
        all_classes.num = num;
      } else if (a == 1) {
        if (check_name(num) != 0) {
          is_fuckedup = true;
          // cout << "3\n";
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
                // cout << "4\n";
                break;
              }
              c = dt.at(0) - '0';
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
                // cout << "5\n";
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
                // cout << "6\n";
                break;
              }
              if (!room_is_addable(thatday, dt)) {
                is_fuckedup = true;
                // cout << "7\n";
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
        vector<string> prof;
        istringstream proflist(num);
        string p;
        while (getline(proflist, p, ' ')) {
          bool exist = false;
          for (int i = 0; i < professor.size(); i++) {
            if (professor[i].first == p) {
              exist = true;
            }
          }
          if (check_num(p) != 0 || exist == false) {
            is_fuckedup = true;
            // cout << "8\n";
            break;
          }
          prof.push_back(p);
        }

        all_classes.professor_id_list = prof;
      } else if (a == 4) {
        if (check_credit(num) == false) {
          is_fuckedup = true;
          // cout << "9\n";
          break;
        }
        int time1 = 0;
        for (int i = 0; i < all_classes.tp_list.size(); i++) {
          int a = stoi(all_classes.tp_list.at(i).time);
          int b = a % 100;
          a /= 100;
          if (a == 19) {
            a = -1;
          }
          if (b == 19) {
            b = -1;
          }
          int c = b - a;
          time1 += c;
        }
        for (int i = 0; i < all_classes_list.size(); i++) {
          if (all_classes.name == all_classes_list.at(i).name) {
            int time2 = 0;
            if (num != all_classes_list.at(i).credit) {
              is_fuckedup = true;
              // cout << "10\n";
            }
            for (int j = 0; j < all_classes_list.at(i).tp_list.size(); j++) {
              int a = stoi(all_classes_list.at(i).tp_list.at(j).time);
              int b = a % 100;
              a /= 100;
              if (a == 19) {
                a = -1;
              }
              if (b == 19) {
                b = -1;
              }
              int c = b - a;
              time2 += c;
            }
            if (time1 != time2) {
              is_fuckedup = true;
              // cout << "11\n";
            }
          }
        }
        all_classes.credit = num;
      }
      a++;
    }
    if (is_fuckedup || a != 5) {
      cout << classes << endl;
      file_is_fuckedup = true;
      // cout << "12\n";
    }
    all_classes_list.push_back(all_classes);
  }

  if (!prof_integrity()) {
    file_is_fuckedup = true;
  }

  if (file_is_fuckedup) {
    // cout << "1";
    abort();
  }
}

// void time_table_integrity() {
//   fstream newfile;
//   string classes;
//   newfile.open("timetables.txt");
//   bool file_is_fuckedup = false;
//   while (getline(newfile, classes)) {
//     string num;
//     istringstream ss(classes);
//     int a = 0;
//     vector<string> time_name;
//     bool is_fuckedup = false
// cout << "1";
//     string last = "";
//     last += classes.back();
//     if (classes == "" || last == "\t") {
//       is_fuckedup = true;
//     }
//     vector<Lecture> temp;
//     while (getline(ss, num, '\t')) {
//       if (a == 0) {
//         for (int i = 0; i < time_name.size(); i++) {
//           if (num == time_name.at(i) || check_name(num) == -1) {
//             is_fuckedup = true;
//             break;
//           }
//         }
//         time_name.push_back(num);
//       } else {
//         bool exist = false;
//         for (int i = 0; i < all_classes_list.size(); i++) {
//           if (all_classes_list.at(i).num == num) {
//             exist = true;
//           }
//         }
//         if (exist == false) {
//           is_fuckedup = true;
//           break;
//         }
//         if (!temp.empty()) {
//           if (is_addable(temp, num)) {
//             Lecture temp2;
//             temp2.num = num;
//             temp.push_back(temp2);
//           } else {
//             is_fuckedup = true;
//           }
//         }
//       }
//       a++;
//     }
//     if (is_fuckedup) {
//       cout << classes << endl;
//       file_is_fuckedup = true;
//     }
//   }
//   if (file_is_fuckedup == true) {
//     abort();
//   }
// }

bool name_dup(vector<Lecture> num, Lecture num2) {
  for (int i = 0; i < all_classes_list.size(); i++) {
    if (num2.num == all_classes_list.at(i).num) {
      for (int j = 0; j < num.size(); j++) {
        for (int k = 0; k < all_classes_list.size(); k++) {
          if (num.at(j).num == all_classes_list.at(k).num) {
            if (all_classes_list.at(i).name == all_classes_list.at(k).name) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

void time_table_integrity() {
  fstream newfile;
  string classes;
  newfile.open("timetables.txt");
  bool file_is_fuckedup = false;
  vector<string> time_name;
  while (getline(newfile, classes)) {
    string num;
    istringstream ss(classes);
    int a = 0;
    int c = 0;
    bool is_fuckedup = false;
    string last = "";
    last += classes.back();
    if (classes == "" || last == "\t") {
      is_fuckedup = true;
    }
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
        int j;
        for (int i = 0; i < all_classes_list.size(); i++) {
          if (all_classes_list.at(i).num == num) {
            exist = true;
            c += stoi(all_classes_list.at(i).credit);
          }
        }
        if (exist == false) {
          is_fuckedup = true;
          break;
        }
        if (!is_addable(temp, num)) {
          is_fuckedup = true;
        }
        Lecture temp2;
        temp2.num = num;
        if (!name_dup(temp, temp2)) {
          is_fuckedup = true;
          break;
        }
        temp.push_back(temp2);
      }
      a++;
    }
    if (is_fuckedup || c > 18) {
      cout << classes << endl;
      file_is_fuckedup = true;
    }
  }
  if (file_is_fuckedup == true) {
    // cout << "2";
    abort();
  }
}

void professor_list_integrity() {
  bool file_is_fuckedup = false;
  fstream newfile;
  string classes;
  set<string> proflist;
  newfile.open("Professor_list.txt");
  if (newfile.peek() == ifstream::traits_type::eof()) abort();
  while (getline(newfile, classes)) {
    string num;
    pair<string, string> temp;
    istringstream ss(classes);
    int a = 0;
    bool is_fuckedup = false;
    string last = "";
    last += classes.back();
    if (classes == "" || last == "\t") {
      // cout << " 11 ";
      is_fuckedup = true;
    }
    while (getline(ss, num, '\t')) {
      if (a == 0) {
        if (check_num(num) == -1) {
          // cout << " 12 ";
          is_fuckedup = true;
        }
        temp.first = num;
        proflist.insert(num);
      } else if (a == 1) {
        if (check_name(num) == -1) {
          // cout << " 13 ";
          is_fuckedup = true;
        }
        temp.second = num;
        professor.push_back(temp);
      } else {
        // cout << " 14 ";
        is_fuckedup = true;
      }
      a++;
    }
    if (is_fuckedup) {
      cout << classes << endl;
      file_is_fuckedup = true;
    }
  }
  if (proflist.size() < professor.size() || file_is_fuckedup == true) {
    // cout << "3";
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
    // cout << "4";
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
    cout << "오류: 홈 경로" << home_path
         << "에 Professor_list 데이터 파일이 없습니다." << endl;
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
    cout << "오류: 홈 경로" << home_path
         << "에 Classroom_list 데이터 파일이 없습니다." << endl;
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
      cout << "경고: 홈 경로" << home_path << "에 데이터 파일이 없습니다."
           << endl;
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

bool prof_integrity() {
  typedef struct Lec {
    string num;
    vector<string> prof[5][20];
  };
  vector<Lec> lecs;
  for (int i = 0; i < all_classes_list.size(); i++) {
    Lec lect;
    vector<string> profs = all_classes_list.at(i).professor_id_list;
    lect.num = all_classes_list.at(i).num;
    for (int j = 0; j < all_classes_list.at(i).tp_list.size(); j++) {
      int a = all_classes_list.at(i).tp_list.at(j).day;
      int b = stoi(all_classes_list.at(i).tp_list.at(j).time);
      int c = b % 100;
      b /= 100;
      if (b == 19) {
        b = -1;
      }
      if (c == 19) {
        c = -1;
      }
      for (int k = b + 1; k <= c + 1; k++) {
        lect.prof[a][k] = profs;
      }
    }
    lecs.push_back(lect);
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 20; j++) {
      vector<vector<string>> pro;
      for (int k = 0; k < lecs.size(); k++) {
        if (lecs.at(k).prof[i][j].size() > 0) {
          pro.push_back(lecs.at(k).prof[i][j]);
        }
      }
      if (brute(pro) == false) {
        return false;
      }
    }
  }
  return true;
}

bool brute(vector<vector<string>> pro) {
  if (pro.size() == 0) return true;
  vector<string> list;
  int i = 0, j = 0;
  while (true) {
    if (find(list.begin(), list.end(), pro.at(i).at(j)) == list.end()) {
      if (i == list.size()) {
        list.push_back(pro.at(i).at(j));
        if (list.size() == pro.size()) {
          return true;
        }
      } else {
        list.erase(list.begin() + list.size() - 1);
        list.push_back(pro.at(i).at(j));
      }
      i = list.size(), j = 0;
    } else {
      if (j < pro.at(i).size() - 1) {
        j++;
      } else {
        if (list.size() > i) {
          list.erase(list.begin() + list.size() - 1);
        }
        i--;
        if (i == -1) {
          return false;
        }
        for (int k = 0; k < pro.at(i).size(); k++) {
          if (list.at(list.size() - 1) == pro.at(i).at(k)) {
            j = k;
          }
        }
      }
    }
  }
  return true;
}