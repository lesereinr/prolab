#include<iostream>
#include<cstdio>
using namespace std;
extern void intial();
extern void user();
extern bool user_sign();
extern void admin();
int main()
{
	intial();
	cout << "�����������";
	int key;
	cin >> key;
	while (key)
	{
		switch (key)
		{
		case 0:return 0;
		case 1:user(); break;
		case 2:user_sign(); break;
		case 3:admin(); break;
		default:cout << "�������"; system("pause");
			break;
		}
		system("cls");
		intial();
		cout << "�����������";
		cin >> key;
	}
	return 0;
}
