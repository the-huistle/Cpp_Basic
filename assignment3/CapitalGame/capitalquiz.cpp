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
		cout << "�߸��� ���� �Է��Դϴ�.\n" << "�ٽ� �Է����ּ���." << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return true;
	}
	else
		return false;
}
void QuizManager::upload()
{
	ifstream fin("C:\\Users\\����\\source\\repos\\CapitalGame\\CapitalGame\\nation.txt", ios::in);
	if (!fin)
	{
		cout << "nation.txt ���� ����" << endl;
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
		if (check == 0)	//���� �̸�
		{
			if (ch == ';')
			{
				nat.setNation(n);
				n.clear();
				check = 1;
			}
			else
			{
				n.push_back(ch);	// ; ���������� ���� n�� ����
			}
		}
		else if (check == 1)	//���� �̸�
		{
			if (ch == '\n')
			{
				nat.setCapital(c);
				c.clear();

				//�ߺ� ���� üũ
				for (auto& i : v) {
					if (i.getNation() == nat.getNation()) {
						cout << "���� �̸� �ߺ� ����!! nation.txt�� �ٽ� �ۼ��Ͻÿ�." << endl;
						return;
					}
					if (i.getCapital() == nat.getCapital()) {
						cout << "���� �̸� �ߺ� ����!! nation.txt�� �ٽ� �ۼ��Ͻÿ�." << endl;
						return;
					}
				}
				//���Ϳ� ��� �߰�
				v.push_back(nat);
				check = 0;
			}
			else
			{
				c.push_back(ch);	//'\n'������ ���ڵ��� c�� ����
			}
		}
	}
	fin.close();
	cout << "���ε� �Ϸ�\n" << endl;
}
void QuizManager::renew()
{
	int menu;
	while (1)
	{
		cout << "[---------���� ����---------]" << endl;
		cout << "(1) �����̸� ����  (2) ���ο� ���� �߰�  (3) ���� ����  (4) �ҽ����� ���\n�Է�: ";
		cin >> menu;
		if (checkInputError())
			continue;
		else if (menu != 1 && menu != 2 && menu != 3 && menu != 4)
		{
			cout << "�߸��� ���� �Է��Դϴ�." << endl;
			continue;
		}
		else
			break;
	}

	switch (menu)
	{
	case 1: //�����̸� ����
		changeName();
		break;
	case 2: //���ο� ���� �߰�
		addNation();
		break;
	case 3: //���� ����
		delNation();
		break;
	case 4: //�ҽ����� ���
		backUp();
		break;
	}
}
void QuizManager::search()
{
	int menu;
	while (1)
	{
		cout << "[---------���� ���� �˻�---------]" << endl;
		cout << "(1) �����̸����� ���� �˻�  (2) �������� ��ü ���\n�Է�: ";
		cin >> menu;
		if (checkInputError())
			continue;
		else if (menu != 1 && menu != 2)
		{
			cout << "�߸��� ���� �Է��Դϴ�." << endl;
			continue;
		}
		else
			cout << endl;
			break;
	}

	if (menu == 1)	//�����̸����� �˻�
	{
		searchByname();
		cout << endl;
	}

	else //�������� ��ü ���
	{
		printAll();
		cout << endl;
	}
}
void QuizManager::quiz()
{
	if (v.empty())
	{
		cout << "��� ������ ������ �����ϴ�! ���ε� ���ּ���.\n" << endl;
		return;
	}
	srand((unsigned int)time(0));
	int idx;
	vector<int>::iterator it;
	vector <int> ex;	//���� ����
	vector <int> pro;	//���� ����
	Nation ans;	//������ ��ü
	int ansIdx;	//������ ����
	int choice;	//������� ����
	double count = 1, correct = 0;	//����� ��� ���� �ʿ�

	while (1)
	{
		//���� ���� ����
		while (1)	//���� �ߺ� ���� ����
		{
			ansIdx = rand() % v.size();
			it = find(pro.begin(), pro.end(), ansIdx);
			if (it == pro.end())
				break;
		}
		pro.push_back(ansIdx);	//������ ���� �ε��� ����
		ans = v[ansIdx];
		cout << "[" << count << "��° ����" << "]" << endl;
		cout << "���� �̸�: " << ans.getNation() << endl;
		
		//���� ���� ������ ���� 4�� ����
		cout << "[����]" << endl;
		for (int i = 0; i < 4; i++)
		{
			while (1)	// ���� �ߺ� üũ
			{
				idx = rand() % v.size();	// ���Ϳ��� ��������
				it = find(ex.begin(), ex.end(), idx);
				if (it == ex.end())	//���� �߿� �ߺ��Ǵ� ������ ������ ���� ���
				{
					break;
				}
			}
			ex.push_back(idx);	//���� ���Ϳ� �ε��� �߰�
		}

		it = find(ex.begin(), ex.end(), ansIdx);
		if (it == ex.end())	//���� �߿� ������ ���� ���
		{
			idx = rand() % 4;	//4�� ���� �� ��������  �������� ��ü��Ŵ
			ex[idx] = ansIdx;	//������ ������ �ε���
		}
		cout << "�� ������ ���� �̸���?    (9 �Է½� ���� ����)" << endl;
		//���� ���
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 << "��: " << v[ex[i]].getCapital() << endl;
		}
		cout << endl;
		cout << "���� )";
		while (1)			// �������� �߸��� �Է� ó��
		{
			cin >> choice;
			if (checkInputError())
				continue;
			else if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 9)
			{
				cout << "������ ��� �Է��Դϴ�!" << endl;
				continue;
			}
			else
				break;
		}
		if (choice == 9 || pro.size() == v.size())
		{
			cout << "��� �����մϴ�." << endl;
			break;
		}
		if (ex[choice - 1] == ansIdx)
		{
			cout << "*********�����Դϴ�!!*********\n" << endl;
			correct++;
		}
		else
		{
			cout << "*********�����Դϴ٤�.�� ������ " << ans.getCapital() << "�Դϴ�*********\n" << endl;
		}
		count++;
		ex.clear();
	}
	cout << "����� ������� " << (correct / count) * 100 << "%�Դϴ�!\n" << endl;
}

//��������
void QuizManager::changeName()
{
	int idx = searchByname();
	if (idx == -1) {
		cout << "�������� �ʴ� �����̸� �Դϴ�!\n" << endl;
		return;
	}

	string c;
	cout << "���� �� �����̸� �Է�: ";
	getline(cin, c);

	Nation& n = v[idx];
	n.setCapital(c);
	cout << "�����̸� ���� �Ϸ�\n" << endl;
}
void QuizManager::addNation()
{
	Nation nat;
	cin.ignore(100, '\n');

	cout << "�����̸��� no �Է� ��, ���ο� ���� �߰��� �����մϴ�." << endl;
	while (1)
	{
		cin >> nat;

		if (nat.getNation() == "no") {
			cout << "���ο� ���� �߰��� �����մϴ�." << endl;
			return;
		}

		//�����̸� �ߺ� üũ
		for (auto &i : v) {
			if (i.getNation() == nat.getNation()) {
				cout << "�����ϴ� �����̸��Դϴ�!\n" << endl;
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
		cout << "�������� �ʴ� �����̸� �Դϴ�!\n" << endl;
		return;
	}

	vector<Nation>::iterator it;
	it = v.begin();
	it = v.erase(it + idx);

	cout << "���� ���� �Ϸ�\n" << endl;
}
void QuizManager::backUp()
{
	ofstream fout("C:\\Users\\����\\source\\repos\\CapitalGame\\CapitalGame\\nation.txt", ios::out);
	if (!fout)
	{
		cout << "nation.txt ���� ����" << endl;
		return;
	}

	if (v.empty()) {
		cout << "����� ���Ͱ� ����ֽ��ϴ�!\n" << endl;
		return;
	}

	string n, c;
	for (auto& i : v) {
		fout << i.getNation() << ";" << i.getCapital() << "\n";
	}
	cout << "�ҽ����� ��� �Ϸ�\n" << endl;
	fout.close();
}

//�������� �˻�
int QuizManager::searchByname()
{
	//�˻��ϰ��� �ϴ� ���� �̸�
	string n;
	cout << "�����̸��� �Է����ּ���. >>";
	cin.ignore(100, '\n');
	getline(cin, n);
	int idx = 0;
	for (auto& i:v){
		if (i.getNation() == n) {
			cout << i << endl;	//cout<<i�� �ٲ������
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
		cout << "����� ���� �����ϴ�!" << endl;
		return;
	}
	int idx = 1;
	for (auto& i : v)
	{
		cout << idx << ": " << i << endl;	//cout<<i�� �ٲ������
		idx++;
	}
}

//�޴� ���
void QuizManager::menu()
{
	int menu;

	while (1)
	{
		while (1)
		{
			cout << "[---------�� ��---------]" << endl;
			cout << "(1) �ҽ����� ���ε�  (2) ���� ����  (3) �������� �˻�\n(4) ���� ����  (5) ����\n�Է�: ";
			cin >> menu;
			if (checkInputError())
				continue;
			else if (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5)
			{
				cout << "�߸��� ���� �Է��Դϴ�.\n" << endl;
				continue;
			}
			else
				cout << endl;
				break;
		}

		switch (menu)
		{
		case 1:	//�ҽ����� ���ε�
			upload();
			break;
		case 2: //���� ����
			renew();
			break;
		case 3: //�������� �˻�
			search();
			break;
		case 4: //���� ����
			quiz();
			break;
		case 5: //����
			//��ü ���� ���� ���� ���� ����� ���
			return;
		}
	}
}