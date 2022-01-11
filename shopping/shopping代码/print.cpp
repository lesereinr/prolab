#include"print.h"
void print(int num, char c)
{
	for (int i = 0; i < num; ++i)
		cout << c;
}
void getpassword(string& password)
{
	char psw[20];
	int index = 0;
	while (1)
	{
		char ch;
		ch = _getch();
		if (ch == 8)
		{
			if (index != 0)
			{
				cout << char(8) << " " << char(8);
				index--;
			}
		}
		else if (ch == '\r')
		{
			psw[index] = '\0';
			password = psw;
			cout << endl;
			return;
		}
		else
		{
			cout << '*';
			psw[index++] = ch;
		}
	}
}
void intial()
{
	print(72, '=');
	cout << endl;
	cout << "1.�û���½";
	print(10, ' ');
	cout << "2.�û�ע��";
	print(10, ' ');
	cout << "3.����Ա��½";
	print(10, ' ');
	cout << "0.�˳�����" << endl;
	print(72, '=');
	cout << endl;
}
void admin_intial()
{
	print(80, '=');
	cout << endl;
	cout << "0.ע����¼   ";
	cout << "1.��ѯ��Ʒ   ";
	cout << "2.������Ʒ   ";
	cout << "3.ɾ����Ʒ   ";
	cout << "4.�޸���Ʒ����   ";
	cout << "5.�ۻ��嵥   ";
	cout << endl;
	print(80, '=');
	cout << endl;
}
void user_intial()
{
	print(114, '=');
	cout << endl;
	cout << "0.ע����¼   ";
	cout << "1.�鿴��Ʒ   ";
	cout << "2.��Ʒ����   ";
	cout << "3.�����Ʒ�����ﳵ   ";
	cout << "4.ɾ�����ﳵ��Ʒ   ";
	cout << "5.�鿴���ﳵ   ";
	cout << "6.����   ";
	cout << "7.�鿴��ʷ   ";
	cout << endl;
	print(114, '=');
	cout << endl;
}