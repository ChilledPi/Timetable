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

// 학사팀(A) 강의 추가 프롬프트
// 강의 정보들을 입력받고, 규칙 및 중복 검사
// 이후 강의번호의 존재 여부에 따라 수정 혹은 추가
void A_add_lecture_prompt() {
  Lecture new_lecture;
  int prof_id_index;
  vector<tp> timeplace;
  std::string weekday;
  std::string lecture_time;
  int room_id_index;
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

  while(true){
    for (int i = 0; i < professor.size(); i++){
      cout << i + 1 << ") " << professor[i].second << '\n';
    }
    std::cout << "추가할 교강사의 번호(교번 X)를 입력해주세요 > ";
    prof_id_index = check_num_input(professor.size());
    if(prof_id_index > 0){
      // new_lecture.professor_id = professor[prof_id_index - 1].first; 프로페서did
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
//   check = 0;
  while (true) {
    tp new_tp;
    // 요일 입력
    while (true) {
      string temp;
      std::cout << "추가할 강의의 요일과 강의시간을 입력해주세요 > ";
      if((temp = read_time()) != ""){
        new_tp.day = Day((temp[0]) - '0'); // !!!!!!!!!!!
        new_tp.time = temp.substr(1, 4);
        break;
      }
    }

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

    if(is_expendable(timeplace, new_tp.day, new_tp.time)){
      timeplace.push_back(new_tp);
    }else{
      std::cout << "! 요일/시간이 겹칩니다."
                << std::endl;
      std::cout
          << "------------------------------------------------------------"
             "--------------\n";
      continue;
    }

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


void modify_lecture(const Lecture& new_lecture) {
  // 1. lecture_id와 find로 인덱스 접근
  // 2. 자료마다 하나하나 대입
  // 3. tp는 반복문돌면서 대입
  // 4. 학생이 넣은 강의는 삭제

  vector<Lecture>::iterator iter =
      find(all_classes_list.begin(), all_classes_list.end(),
           Lecture(new_lecture.num));
  *iter = new_lecture;
  remove_lecture_in_timetable(new_lecture.num);
}