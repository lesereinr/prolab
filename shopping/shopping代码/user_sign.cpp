#include"user_sign.h"
extern void getpassword(string& password);
bool user_sign()
{
	string name, password,again, temp;
	fstream in_file;
	in_file.open("C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\�û�.txt", ios::in);
	if (!in_file.is_open())
		exit(-1);
	map<string, string> names;
	while (!in_file.eof())
	{
		in_file >> name >> password;
		names.insert(pair<string,string>(name,password));
	}
	in_file.close();
	cout << "�����������û�����";
	cin >> name;
	while (names.count(name))
	{
		cout << "�û����Ѵ��ڣ������������룡" << endl;
		cout << "�����������û�����";
		cin >> name;
	}
	cout << "�������������룺";
	getpassword(password);
	cout << "��ȷ���������룺";
	getpassword(again);
	while (password != again)
	{
		cout << "ȷ��ʧ�ܣ����������룡"<<endl;
		cout << "�������������룺";
		getpassword(password);
		cout << "��ȷ���������룺";
		getpassword(again);
	}
	in_file.open("C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\�û�.txt", ios::app);
	if (!in_file.is_open())
		exit(-1);
		in_file <<endl<< name << "   " << password;
	in_file.close();
	string shopbus_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + name + ".txt";
	string track_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + name + "_track.txt";
	string addr_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + name + "_addr.txt";
	in_file.open(shopbus_path, ios::out);
	in_file.close();
	in_file.open(track_path, ios::out);
	in_file.close();
	//in_file.open(addr_path, ios::out);
	//in_file.close();
	cout << "��ϲ!���ѳɹ�ע�ᣡ" << endl;
	cout << "�������غ��½��" << endl;
	system("pause");
	return true;
}