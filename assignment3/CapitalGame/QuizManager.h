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
	friend ostream& operator<<(ostream& stream, const Nation& n) {	//Nation ��ü ���
		stream << "(" << n.nation << ", " << n.capital << ")";
		return stream;
	}
	friend istream& operator >>(istream& stream, Nation& n) {	//Nation ��ü �Է�
		cout << "�����̸� �Է�: ";
		getline(stream, n.nation);
		cout << "�����̸� �Է�: ";
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
	//�޴����� ȣ��
	void upload();	//�ҽ����� ���ε�
	void renew();	//���� ����
	void search();	//���� ���� �˻�
	void quiz();	//����

	//��������
	void changeName();
	void addNation();
	void delNation();
	void backUp();

	//�������� �˻�
	int searchByname();	//�˻��� ������ �ε��� ��ȯ
	void printAll();	//���ε� �ؿ� ����� ���� ���� ��� ���
};