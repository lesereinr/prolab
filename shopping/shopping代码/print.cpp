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
	cout << "1.用户登陆";
	print(10, ' ');
	cout << "2.用户注册";
	print(10, ' ');
	cout << "3.管理员登陆";
	print(10, ' ');
	cout << "0.退出程序" << endl;
	print(72, '=');
	cout << endl;
}
void admin_intial()
{
	print(80, '=');
	cout << endl;
	cout << "0.注销登录   ";
	cout << "1.查询商品   ";
	cout << "2.增加商品   ";
	cout << "3.删除商品   ";
	cout << "4.修改商品数量   ";
	cout << "5.售货清单   ";
	cout << endl;
	print(80, '=');
	cout << endl;
}
void user_intial()
{
	print(114, '=');
	cout << endl;
	cout << "0.注销登录   ";
	cout << "1.查看商品   ";
	cout << "2.商品搜索   ";
	cout << "3.添加商品至购物车   ";
	cout << "4.删除购物车商品   ";
	cout << "5.查看购物车   ";
	cout << "6.结账   ";
	cout << "7.查看历史   ";
	cout << endl;
	print(114, '=');
	cout << endl;
}