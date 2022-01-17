#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Nation
{
	string nation;
	string capital;
public:
	Nation() {}
	Nation(string n, string c) :nation(n), capital(c) {}
	void setNation(string n) {
		nation = n;
	}
	void setCapital(string c) {
		capital = c;
	}
	string getNation() {
		return nation;
	}
	string getCapital() {
		return capital;
	}
	friend ostream& operator<<(ostream& stream, const Nation& n) {	//Nation 객체 출력
		stream << "(" << n.nation << ", " << n.capital << ")";
		return stream;
	}
	friend istream& operator >>(istream& stream, Nation& n) {	//Nation 객체 입력
		cout << "나라이름 입력: ";
		getline(stream, n.nation);
		cout << "수도이름 입력: ";
		getline(stream, n.capital);
		return stream;
	}
};

class QuizManager
{
	vector<Nation> v;
public:
	bool checkInputError();

	void menu();
	//메뉴에서 호출
	void upload();	//소스파일 업로드
	void renew();	//정보 갱신
	void search();	//수도 정보 검색
	void quiz();	//퀴즈

	//정보갱신
	void changeName();
	void addNation();
	void delNation();
	void backUp();

	//수도정보 검색
	int searchByname();	//검색한 나라의 인덱스 반환
	void printAll();	//업로드 해온 나라와 수도 정보 모두 출력
};