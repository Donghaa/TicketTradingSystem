#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "SignUpMembershipUI.h"


using namespace std;


int main(int argc, char* argv[]) {
	ifstream in("input.txt");
#ifndef _DEBUG
	freopen("output.txt", "w", stdout);	//cout -> output.txt�� ���𷺼�
#endif
	while (in) {
		int first, second;
		string input;
		in >> first >> second;
		switch (first)
		{
		case 1:
			if (second == 1) { //ȸ������
				string id, pw, name, ssn, userType;
				in >> id >> pw >> name >> ssn >> userType;
				SignUpMembershipUI::get().requestSignUP(Info(id, pw, name, ssn, userType));
			}
			else {
				//ȸ��Ż��
			}
			break;
		case 2:
			if (second == 1) {
				//�α���
			}
			else {
				//�α׾ƿ�
			}
			break;
		case 3:
			if (second == 1) {
				//�Ǹ� Ƽ�� ���
			}
			else {
				//��� Ƽ�� ��ȸ
			}
			break;
		case 4:
			if (second == 1) {
				//Ƽ�� �˻�
			}
			else if(second == 2) {
				//Ƽ�� ����
			}
			else if (second == 3) {
				//����� Ƽ�� �˻�
			}
			else if (second == 4) {
				//��� ����
			}
			else {
				//���� ���� ��ȸ
			}
			break;
		case 5:
			//����ð� ����
			break;
		case 6:
			if (second == 1) {
				//���� ����
			}
			else {
				//guest session���� ����
			}
			break;
		case 7:
			return 0;
		default:
			break;
		}
	}
}
