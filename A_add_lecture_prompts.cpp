#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "A_add_lecture_prompts.h"
#include "file_integrity.h"
#include "types.h"
#include "utils.h"

#define ID_NUM 4

extern vector<Lecture> all_classes_list;
extern vector<pair<string, string>> professor;
extern vector<string> classrooms;

bool is_digit(
    std::string str) {  // 문자열이 숫자인지 확인, 숫자거나 0000이면 참
  return (atoi(str.c_str()) || !str.compare("0000"));
}

// 학사팀(A) 강의 추가 프롬프트
// 강의 정보들을 입력받고, 규칙 및 중복 검사
// 이후 강의번호의 존재 여부에 따라 수정 혹은 추가
void A_add_lecture_prompt() {
  Lecture new_lecture;
//   std::string lecture_id;
//   std::string lecture_name;
  std::string prof_id;
  int prof_id_index;
  int count_prof;

  vector<tp> timeplace;
  std::string weekday;
  std::string lecture_time;
  std::string room_id;
  int room_id_index;
  int count_room;

  std::string read_file_line;
  int iter;
  int check;

  // 강의번호 입력
  while (true) {
    std::cout << "추가할 강의번호를 입력해주세요 > ";
    if((new_lecture.num = read_num()) != ""){
      break;
    }
  }
  
  // 강의명 입력
  while (true) {
    std::cout << "추가할 강의명을 입력해주세요 > ";
    if((new_lecture.name = read_name()) != ""){
      break;
    }
  }

//   // 교강사 파일에서 목록 출력
//   std::ifstream file("Professor_list.txt");
//   if (file.is_open()) {  // 파일 열기 성공
//     count_prof = 0;
//     while (std::getline(file, read_file_line)) {  // 교강사 목록 출력
//       cout << count_prof + 1 << ") " << read_file_line << std::endl;
//       if (!trim(read_file_line).empty()) {
//         count_prof++;
//       }  // 비어있거나 공백만 있는 행은(무결성에 의해 없겠지만) 줄 수에 포함하지
//          // 않음
//     }
//   } else {  // 파일 열기 실패
//     std::cout << "! Unable to open file." << std::endl;
//     return;
//   }
//   if (count_prof == 0) {
//     std::cout << "! Professor does not exist." << std::endl;
//     return;
//   }  // Professor_list.txt가 비어있거나 공백, 개행만 있는 경우

  // 교강사 입력
//   iter = 0;
//   while (true) {
//     std::cout << "추가할 교강사의 번호(교번 X)를 입력해주세요 > ";
//     prof_id_index = check_num_input(count_prof);
//     if (prof_id_index == 0) {
//       std::cout
//           << "! 0번 항목이 존재하지 않습니다." << std::endl
//           << "------------------------------------------------------------"
//              "--------------"
//           << std::endl;
//       continue;
//     }
//     if (file.is_open()) {  // 파일이 열려있으면
//       file.clear();
//       file.seekg(0, std::ios::beg);  // 파일 포인터 처음으로 이동
//       while (std::getline(file, read_file_line)) {
//         iter++;
//         if (iter == prof_id_index) {
//           std::istringstream parse_line(read_file_line);
//           parse_line >> prof_id;
//           break;
//         }
//       }
//     } else {  // 파일 열려있지 않음
//       std::cerr << "! Unable to open file." << std::endl;
//       return;
//     }
//   }
//   file.close();

  while(true){
    for (int i = 0; i < professor.size(); i++){
      cout << i + 1 << ") " << professor[i].second << '\n';
    }
    std::cout << "추가할 교강사의 번호(교번 X)를 입력해주세요 > ";
    prof_id_index = check_num_input(professor.size());
    if(prof_id_index > 0){
      new_lecture.professor_id = professor[prof_id_index - 1].first;
      break;
    }
    if (prof_id_index == 0) {
      std::cout
          << "! 0번 항목이 존재하지 않습니다." << std::endl
          << "------------------------------------------------------------"
             "--------------"
          << std::endl;
    }
  }

  // 요일, 강의시간(교시), 강의실 입력
  check = 0;
  while (true) {
    tp new_tp;
    // 요일 입력
    while (true) {
    //   std::cout << "추가할 강의의 요일과 강의시간을 입력해주세요 > ";
    //   std::getline(std::cin, weekday);
    //   weekday = trim(weekday);  // 좌우 공백 제거
    //   if (A_check_weekday(weekday)) {
    //     timeplace[check].day = Day(stoi(weekday) - 1);  // enum Day를 대입
    //     break;
    //   }

    //   std::cout << "추가할 강의의 요일을 입력해주세요 > ";
    //   weekday()
      string temp;
      std::cout << "추가할 강의의 요일과 강의시간을 입력해주세요 > ";
      if((temp = read_time()) != ""){
        new_tp.day = Day((temp[0]) - '0'); // !!!!!!!!!!!
        new_tp.time = temp.substr(1, 4);
        break;
      }
    }

    // 강의시간(교시) 입력
    // while (true) {
    //   std::cout << "추가할 강의시간(교시)을 입력해주세요 > ";
    //   std::getline(std::cin, lecture_time);
    //   lecture_time = trim(lecture_time);  // 좌우 공백 제거
    //   if (A_check_time(lecture_time)) {
    //     timeplace[check].time.assign(lecture_time);
    //     break;
    //   }
    // }

    // 강의실 파일에서 목록 출력
    // file.open("Classroom_list.txt");
    // if (file.is_open()) {  // 파일 열기 성공
    //   count_room = 0;
    //   while (std::getline(file, read_file_line)) {  // 강의실 목록 출력
    //     cout << count_room + 1 << ") " << read_file_line << std::endl;
    //     if (!trim(read_file_line).empty()) {
    //       count_room++;
    //     }  // 파일에서 비어있거나 공백인 행은 줄 수에 포함하지 않기 (무결성 오류
    //        // 방어)
    //   }
    // } else {  // 파일 열기 실패
    //   std::cout << "! Unable to open file." << std::endl;
    //   return;
    // }
    // if (count_room == 0) {
    //   std::cout << "! Classroom does not exist." << std::endl;
    //   return;
    // }  // Classroom_list.txt가 비어있는 경우

    // // 강의실 입력
    // iter = 0;
    // while (true) {
    //   std::cout << "추가할 강의의 강의실을 입력해주세요 > ";
    //   room_id_index = check_num_input(count_room);
    //   if (room_id_index == 0) {
    //     std::cout
    //         << "! 0번 항목이 존재하지 않습니다." << std::endl
    //         << "------------------------------------------------------------"
    //            "--------------"
    //         << std::endl;
    //     continue;
    //   }
    //   if (file.is_open()) {  // 파일이 열려있으면
    //     file.clear();
    //     file.seekg(0, std::ios::beg);  // 파일 포인터 처음으로 이동
    //     while (std::getline(file, read_file_line)) {
    //       iter++;
    //       if (iter == room_id_index) {
    //         std::istringstream parse_line(read_file_line);
    //         parse_line >> room_id;
    //         timeplace[check].classroom.assign(room_id);
    //         break;
    //       }
    //     }
    //   } else {  // 파일 열려있지 않음
    //     std::cerr << "! Unable to open file." << std::endl;
    //     return;
    //   }
    // }
    // file.close();

    while (true) {
      for (int i = 0; i < classrooms.size(); i++) {
        cout << i + 1 << ") " << classrooms[i] << '\n';
      }
      std::cout << "추가할 강의의 강의실을 입력해주세요 > ";
      room_id_index = check_num_input(classrooms.size());
      if (room_id_index > 0) {
        new_tp.classroom = classrooms[room_id_index - 1];
        break;
      }
      if (room_id_index == 0) {
        std::cout
            << "! 0번 항목이 존재하지 않습니다." << std::endl
            << "------------------------------------------------------------"
               "--------------"
            << std::endl;
      }
    }

    // tp temp;
    // temp.day = Day(stoi(weekday) - 1);
    // temp.time = lecture_time;
    // temp.classroom = classrooms[room_id_index - 1];

    timeplace.push_back(new_tp);

    // if (!A_check_crosscheck()) {
    //   std::cout << "1) 예" << std::endl
    //             << "0) 아니오" << std::endl
    //             << "강의 일시를 더 추가하시겠습니까? > ";
    //   if (check_num_input(1) == 0) {
    //     break;
    //   }
    //   check++;
    //   continue;
    // } else {
    //   std::cout << "! 해당 요일/시간에 강의실이 이미 사용중입니다."
    //             << std::endl;
    //   continue;
    // }

    if (!room_is_addable(new_tp, classrooms[room_id_index - 1]) &&
        find(all_classes_list.begin(), all_classes_list.end(),
             Lecture(new_lecture.num)) ==
            all_classes_list.end()) {  // 강의실 꽉차면 나갈 방법이 없음
      std::cout << "! 해당 요일/시간에 강의실이 이미 사용중입니다."
                << std::endl;
      std::cout
          << "------------------------------------------------------------"
             "--------------\n";
      continue;
    }

    if (!prof_is_addable(professor[prof_id_index - 1].first, timeplace) &&
        find(all_classes_list.begin(), all_classes_list.end(),
             Lecture(new_lecture.num)) ==
            all_classes_list.end()) {  // 교강사 역시 마찬가지
      std::cout << "! 해당 요일/시간에 해당 교강사가 이미 강의중입니다."
                << std::endl;
      std::cout
          << "------------------------------------------------------------"
             "--------------\n";
      continue;
    }

    int sel;
    while (true) {
      std::cout << "1) 예" << std::endl
                << "0) 아니오" << std::endl
                << "강의 일시를 더 추가하시겠습니까? > ";
      if ((sel = check_num_input(1)) >= 0) {
        new_lecture.tp_list.push_back(new_tp);
        break;
      }
    }
    if (sel == 0) break;
  }

  // 강의번호 이미 존재하는지 검사
  std::cout << "동일한 강의번호의 존재유무를 확인합니다." << std::endl;

  // 중복 강의번호 있음
  if (find(all_classes_list.begin(), all_classes_list.end(),
           Lecture(new_lecture.num)) != all_classes_list.end()) {
    std::cout << "중복되는 강의 번호가 존재합니다!" << std::endl
              << "------------------------------------------------------------"
                 "--------------"
              << std::endl;

    while (true) {
      std::cout << "1) 예" << std::endl
                << "0) 아니오" << std::endl
                << "정말 갱신하시겠습니까? > ";
      check = check_num_input(1);
      if (check == 1) {
            modify_lecture(new_lecture); // 자료구조 수정, 학생이 넣은 강의는 삭제해야함
            std::cout << "강의 정보를 갱신합니다." << std::endl
                      << "-----------------------------------------------------"
                         "-------"
                         "--------------"
                      << std::endl;
            return;
      } else if (check == 0) {
            std::cout << "강의 정보를 갱신하지 않았습니다." << std::endl
                      << "-----------------------------------------------------"
                         "-------"
                         "--------------"
                      << std::endl;
            return;
      } else {
            continue;
      }
    }
  }

  // 중복 강의번호 없음
  std::cout << "중복되는 강의 번호가 없습니다!" << std::endl
            << "------------------------------------------------------------"
               "--------------"
            << std::endl
            << "1) 예" << std::endl
            << "0) 아니오" << std::endl
            << "해당 강의를 추가하시겠습니까? > ";
  check = check_num_input(1);
  if (check == 1) {
    // 1. all_classes_list 맨 끝 + 1 인덱스 접근
    // 2. 자료마다 하나하나 대입
    // 3. tp는 반복문돌면서 대입
    all_classes_list.push_back(new_lecture);
    std::cout << "강의를 추가하였습니다." << std::endl
              << "------------------------------------------------------------"
                 "--------------"
              << std::endl;
    return;
  } else if (check == 0) {
    std::cout << "강의를 추가하지 않았습니다." << std::endl
              << "------------------------------------------------------------"
                 "--------------"
              << std::endl;
    return;
  }
}

// bool A_check_id(std::string lecture_id) {
//   if (lecture_id.length() != 4) {
//     std::cout << "! 4자리가 아닙니다" << std::endl;
//     return false;
//   }

//   if (!is_digit(lecture_id) || lecture_id.find("+") < ID_NUM ||
//       lecture_id.find("-") < ID_NUM || lecture_id.find(" ") < ID_NUM) {
//     // 1) 4자리의 문자열이 (양/음 기호, 내부 공백을 포함한)숫자가 아니거나
//     // 2) 4자리 내에 +, - , 공백이 포함된 경우
//     // false 반환
//     std::cout << "! 4자리의 숫자로만 구성되어 있습니다." << std::endl;
//     return false;
//   }
//   return true;
// }

// bool A_check_weekday(std::string weekday) {
//   regex r("[0-4]$");
//   return regex_match(weekday, r);
// }

// bool A_check_time(std::string time) {
//   regex re("((0[1-9])|(1[0-8])){2}$");

//   if (regex_match(time, re)) {
//     string sub1, sub2;
//     sub1 = time.substr(1, 2);
//     sub2 = time.substr(3, 4);
//     if (sub1 >= sub2)
//       return false;
//     else
//       return true;
//   }
//   return false;
// }

// bool A_check_crosscheck(std::string weekday, std::string time,
//                         std::string prof_id, std::string room_id) {
//   // 1. all_classes_list find로 돌면서 입력한 요일+시간 같을 때 겹치는
//   // 강사/강의실 있는지 확인
// }

void modify_lecture(const Lecture& new_lecture) {
  // 1. lecture_id와 find로 인덱스 접근
  // 2. 자료마다 하나하나 대입
  // 3. tp는 반복문돌면서 대입
  // 4. 학생이 넣은 강의는 삭제
  vector<Lecture>::iterator iter =
      find(all_classes_list.begin(), all_classes_list.end(),
           Lecture(new_lecture.num));
  *iter = new_lecture;
  //시간표 수정
}