#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main(){

    string inputName;
    regex re("^[A-Z][a-z]+( [A-Z][a-z]+){0,2}$");

    do {
        cout << "강의명 or 시간표의 제목을 입력해주세요." << endl;
        cout << "( 이름은 1 ~ 3개 단어, 단어의 처음 대문자 이외 소문자, 공백으로 단어 분할 )" << endl;
        cout << "( 잘못 입력 시 자동으로 현재 작업 재실행 )" << endl << endl;

        getline(cin, inputName);
    } while (!regex_match(inputName, re));

    cout << inputName << endl;
    cout << "입력 성공^^" << endl;

}