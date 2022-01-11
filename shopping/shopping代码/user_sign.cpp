#include"user_sign.h"
extern void getpassword(string& password);
bool user_sign()
{
	string name, password,again, temp;
	fstream in_file;
	in_file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\用户.txt", ios::in);
	if (!in_file.is_open())
		exit(-1);
	map<string, string> names;
	while (!in_file.eof())
	{
		in_file >> name >> password;
		names.insert(pair<string,string>(name,password));
	}
	in_file.close();
	cout << "请输入您的用户名：";
	cin >> name;
	while (names.count(name))
	{
		cout << "用户名已存在，请您重新输入！" << endl;
		cout << "请输入您的用户名：";
		cin >> name;
	}
	cout << "请输入您的密码：";
	getpassword(password);
	cout << "请确认您的密码：";
	getpassword(again);
	while (password != again)
	{
		cout << "确认失败，请重新输入！"<<endl;
		cout << "请输入您的密码：";
		getpassword(password);
		cout << "请确认您的密码：";
		getpassword(again);
	}
	in_file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\用户.txt", ios::app);
	if (!in_file.is_open())
		exit(-1);
		in_file <<endl<< name << "   " << password;
	in_file.close();
	string shopbus_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + name + ".txt";
	string track_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + name + "_track.txt";
	string addr_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + name + "_addr.txt";
	in_file.open(shopbus_path, ios::out);
	in_file.close();
	in_file.open(track_path, ios::out);
	in_file.close();
	//in_file.open(addr_path, ios::out);
	//in_file.close();
	cout << "恭喜!您已成功注册！" << endl;
	cout << "请您返回后登陆！" << endl;
	system("pause");
	return true;
}