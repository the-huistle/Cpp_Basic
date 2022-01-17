#include "QuizManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

bool QuizManager::checkInputError()
{
	if (cin.fail())
	{
		cout << "잘못된 숫자 입력입니다.\n" << "다시 입력해주세요." << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return true;
	}
	else
		return false;
}
void QuizManager::upload()
{
	ifstream fin("C:\\Users\\세휘\\source\\repos\\CapitalGame\\CapitalGame\\nation.txt", ios::in);
	if (!fin)
	{
		cout << "nation.txt 열기 오류" << endl;
		return;
	}

	if (!v.empty())
	{
		v.clear();
	}

	int ch, check = 0;
	Nation nat;
	string n = "";
	string c = "";

	while ((ch=fin.get())!=EOF)
	{
		if (check == 0)	//나라 이름
		{
			if (ch == ';')
			{
				nat.setNation(n);
				n.clear();
				check = 1;
			}
			else
			{
				n.push_back(ch);	// ; 이전까지의 문자 n에 저장
			}
		}
		else if (check == 1)	//수도 이름
		{
			if (ch == '\n')
			{
				nat.setCapital(c);
				c.clear();

				//중복 여부 체크
				for (auto& i : v) {
					if (i.getNation() == nat.getNation()) {
						cout << "나라 이름 중복 오류!! nation.txt를 다시 작성하시오." << endl;
						return;
					}
					if (i.getCapital() == nat.getCapital()) {
						cout << "수도 이름 중복 오류!! nation.txt를 다시 작성하시오." << endl;
						return;
					}
				}
				//벡터에 요소 추가
				v.push_back(nat);
				check = 0;
			}
			else
			{
				c.push_back(ch);	//'\n'이전의 문자들을 c에 저장
			}
		}
	}
	fin.close();
	cout << "업로드 완료\n" << endl;
}
void QuizManager::renew()
{
	int menu;
	while (1)
	{
		cout << "[---------정보 갱신---------]" << endl;
		cout << "(1) 수도이름 수정  (2) 새로운 나라 추가  (3) 나라 삭제  (4) 소스파일 백업\n입력: ";
		cin >> menu;
		if (checkInputError())
			continue;
		else if (menu != 1 && menu != 2 && menu != 3 && menu != 4)
		{
			cout << "잘못된 숫자 입력입니다." << endl;
			continue;
		}
		else
			break;
	}

	switch (menu)
	{
	case 1: //수도이름 수정
		changeName();
		break;
	case 2: //새로운 나라 추가
		addNation();
		break;
	case 3: //나라 삭제
		delNation();
		break;
	case 4: //소스파일 백업
		backUp();
		break;
	}
}
void QuizManager::search()
{
	int menu;
	while (1)
	{
		cout << "[---------수도 정보 검색---------]" << endl;
		cout << "(1) 나라이름으로 개별 검색  (2) 나라정보 전체 출력\n입력: ";
		cin >> menu;
		if (checkInputError())
			continue;
		else if (menu != 1 && menu != 2)
		{
			cout << "잘못된 숫자 입력입니다." << endl;
			continue;
		}
		else
			cout << endl;
			break;
	}

	if (menu == 1)	//나라이름으로 검색
	{
		searchByname();
		cout << endl;
	}

	else //나라정보 전체 출력
	{
		printAll();
		cout << endl;
	}
}
void QuizManager::quiz()
{
	if (v.empty())
	{
		cout << "퀴즈를 진행할 내용이 없습니다! 업로드 해주세요.\n" << endl;
		return;
	}
	srand((unsigned int)time(0));
	int idx;
	vector<int>::iterator it;
	vector <int> ex;	//보기 벡터
	vector <int> pro;	//문제 벡터
	Nation ans;	//정답인 객체
	int ansIdx;	//문제의 정답
	int choice;	//사용자의 정답
	double count = 1, correct = 0;	//정답률 계산 위해 필요

	while (1)
	{
		//문제 랜덤 출제
		while (1)	//문제 중복 출제 방지
		{
			ansIdx = rand() % v.size();
			it = find(pro.begin(), pro.end(), ansIdx);
			if (it == pro.end())
				break;
		}
		pro.push_back(ansIdx);	//출제된 문제 인덱스 저장
		ans = v[ansIdx];
		cout << "[" << count << "번째 퀴즈" << "]" << endl;
		cout << "나라 이름: " << ans.getNation() << endl;
		
		//정답 포함 객관식 보기 4개 생성
		cout << "[보기]" << endl;
		for (int i = 0; i < 4; i++)
		{
			while (1)	// 보기 중복 체크
			{
				idx = rand() % v.size();	// 벡터에서 랜덤으로
				it = find(ex.begin(), ex.end(), idx);
				if (it == ex.end())	//보기 중에 중복되는 나라의 수도가 없을 경우
				{
					break;
				}
			}
			ex.push_back(idx);	//보기 벡터에 인덱스 추가
		}

		it = find(ex.begin(), ex.end(), ansIdx);
		if (it == ex.end())	//보기 중에 정답이 없을 경우
		{
			idx = rand() % 4;	//4개 보기 중 랜덤으로  정답으로 대체시킴
			ex[idx] = ansIdx;	//출제된 문제의 인덱스
		}
		cout << "위 나라의 수도 이름은?    (9 입력시 퀴즈 종료)" << endl;
		//보기 출력
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 << "번: " << v[ex[i]].getCapital() << endl;
		}
		cout << endl;
		cout << "정답 )";
		while (1)			// 정답으로 잘못된 입력 처리
		{
			cin >> choice;
			if (checkInputError())
				continue;
			else if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 9)
			{
				cout << "범위를 벗어난 입력입니다!" << endl;
				continue;
			}
			else
				break;
		}
		if (choice == 9 || pro.size() == v.size())
		{
			cout << "퀴즈를 종료합니다." << endl;
			break;
		}
		if (ex[choice - 1] == ansIdx)
		{
			cout << "*********정답입니다!!*********\n" << endl;
			correct++;
		}
		else
		{
			cout << "*********오답입니다ㅜ.ㅜ 정답은 " << ans.getCapital() << "입니다*********\n" << endl;
		}
		count++;
		ex.clear();
	}
	cout << "당신의 정답률은 " << (correct / count) * 100 << "%입니다!\n" << endl;
}

//정보갱신
void QuizManager::changeName()
{
	int idx = searchByname();
	if (idx == -1) {
		cout << "존재하지 않는 나라이름 입니다!\n" << endl;
		return;
	}

	string c;
	cout << "수정 후 수도이름 입력: ";
	getline(cin, c);

	Nation& n = v[idx];
	n.setCapital(c);
	cout << "수도이름 수정 완료\n" << endl;
}
void QuizManager::addNation()
{
	Nation nat;
	cin.ignore(100, '\n');

	cout << "나라이름에 no 입력 시, 새로운 나라 추가를 종료합니다." << endl;
	while (1)
	{
		cin >> nat;

		if (nat.getNation() == "no") {
			cout << "새로운 나라 추가를 종료합니다." << endl;
			return;
		}

		//나라이름 중복 체크
		for (auto &i : v) {
			if (i.getNation() == nat.getNation()) {
				cout << "존재하는 나라이름입니다!\n" << endl;
				return;
			}
		}

		v.push_back(nat);
	}
}
void QuizManager::delNation()
{
	int idx = searchByname();
	if (idx == -1) {
		cout << "존재하지 않는 나라이름 입니다!\n" << endl;
		return;
	}

	vector<Nation>::iterator it;
	it = v.begin();
	it = v.erase(it + idx);

	cout << "나라 삭제 완료\n" << endl;
}
void QuizManager::backUp()
{
	ofstream fout("C:\\Users\\세휘\\source\\repos\\CapitalGame\\CapitalGame\\nation.txt", ios::out);
	if (!fout)
	{
		cout << "nation.txt 열기 오류" << endl;
		return;
	}

	if (v.empty()) {
		cout << "백업할 벡터가 비어있습니다!\n" << endl;
		return;
	}

	string n, c;
	for (auto& i : v) {
		fout << i.getNation() << ";" << i.getCapital() << "\n";
	}
	cout << "소스파일 백업 완료\n" << endl;
	fout.close();
}

//수도정보 검색
int QuizManager::searchByname()
{
	//검색하고자 하는 나라 이름
	string n;
	cout << "나라이름을 입력해주세요. >>";
	cin.ignore(100, '\n');
	getline(cin, n);
	int idx = 0;
	for (auto& i:v){
		if (i.getNation() == n) {
			cout << i << endl;	//cout<<i로 바꿔줘야함
			return idx;
		}
		idx++;
	}
	return -1;
}
void QuizManager::printAll()
{
	if (v.empty())
	{
		cout << "출력할 나라가 없습니다!" << endl;
		return;
	}
	int idx = 1;
	for (auto& i : v)
	{
		cout << idx << ": " << i << endl;	//cout<<i로 바꿔줘야함
		idx++;
	}
}

//메뉴 출력
void QuizManager::menu()
{
	int menu;

	while (1)
	{
		while (1)
		{
			cout << "[---------메 뉴---------]" << endl;
			cout << "(1) 소스파일 업로드  (2) 정보 갱신  (3) 수도정보 검색\n(4) 퀴즈 시작  (5) 종료\n입력: ";
			cin >> menu;
			if (checkInputError())
				continue;
			else if (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5)
			{
				cout << "잘못된 숫자 입력입니다.\n" << endl;
				continue;
			}
			else
				cout << endl;
				break;
		}

		switch (menu)
		{
		case 1:	//소스파일 업로드
			upload();
			break;
		case 2: //정보 갱신
			renew();
			break;
		case 3: //수도정보 검색
			search();
			break;
		case 4: //퀴즈 시작
			quiz();
			break;
		case 5: //종료
			//전체 퀴즈 문제 수에 대한 정답률 출력
			return;
		}
	}
}