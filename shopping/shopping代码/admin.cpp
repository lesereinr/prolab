#include"admin.h"
string admin_ID = "Mofes";
string admin_psw = "03131027";
extern void admin_intial();
extern void getpassword(string& password);
extern void print(int num, char c);
void admin()
{
	admin_login();
	system("cls");
	admin_intial();
	fstream file;
	bool flag = true;
	vector<commodity> repertory, sold_list;
	commodity temp;
	title tle_r,tle_s;
	file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\库存.txt", ios::in);
	if (!file.is_open())
		exit(-1);
	while (!file.eof())
	{
		if (flag)
		{
			flag = false;
			file >> tle_r.ID >> tle_r.name >> tle_r.brand >> tle_r.price >> tle_r.real_num >> tle_r.ext;
		}
		else
		{
			file >> temp.ID >> temp.name >> temp.brand >> temp.price >> temp.real_num>>temp.expect_num ;
			repertory.push_back(temp);
		}
	}
	file.close();
	file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\已售清单.txt", ios::in);
	if (!file.is_open())
		exit(-1);
	flag = true;
	while (!file.eof())
	{
		if (flag)
		{
			flag = false;
			file >> tle_s.ID >> tle_s.name >> tle_s.brand >> tle_s.price >> tle_s.real_num>>tle_s.ext;
		}
		else
		{
			file >> temp.ID >> temp.name >> temp.brand >> temp.price >> temp.real_num>>temp.user_name ;
			sold_list.push_back(temp);
		}
	}
	file.close();
	int key;
	cout << "请输入您的操作：";
	cin >> key;
	while (key)
	{
		switch (key)
		{
		case 0: return ;
		case 1: admin_repcheck(repertory,tle_r); break;
		case 2: admin_insert(repertory); break;
		case 3: admin_delete(repertory); break;
		case 4: admin_change(repertory); break;
		case 5: admin_sldcheck(sold_list,tle_s); break;
		default:cout << "输入错误！"; system("pause");
			break;
		}
		file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\库存.txt", ios::out);
		if (!file.is_open())
			exit(-1);
		file << setiosflags(ios::left);
		file << setw(10) <<tle_r.ID << setw(10) <<tle_r.name << setw(10) << tle_r.brand << setw(10) << tle_r.price << setw(10) << tle_r.real_num  << tle_r.ext;
		for (auto& kv : repertory)
			file << endl << setw(10) << kv.ID << setw(10) << kv.name << setw(10) << kv.brand << setw(10) << kv.price << setw(10) << kv.real_num  << kv.expect_num;
		file.close();
		file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\已售清单.txt", ios::out);
		if (!file.is_open())
			exit(-1);
		file << setiosflags(ios::left);
		file << setw(10) << tle_s.ID << setw(10) << tle_s.name << setw(10) << tle_s.brand << setw(10) << tle_s.price << setw(10) << tle_s.real_num  << tle_s.ext;
		for (auto& kv : sold_list)
			file << endl << setw(10) << kv.ID << setw(10) << kv.name << setw(10) << kv.brand << setw(10) << kv.price << setw(10) << kv.real_num  << kv.user_name;
		file.close();
		system("cls");
		admin_intial();
		cout << "请输入操作：";
		cin >> key;
	}
	return;
}
void admin_login()
{
	string name, password;
	cout << "请输入管理员ID：";
	cin >> name;
	while (name != admin_ID)
	{
		cout << "ID错误，请重新输入！" << endl;
		cout << "请输入管理员ID：";
		cin >> name;
	}
	cout << "请输入密码：";
	getpassword(password);
	while (password != admin_psw)
	{
		cout << "密码错误，请重新输入！" << endl;
		cout << "请输入密码：";
		getpassword(password);
	}
	print(10, '*');
	cout << endl;
	cout << "登录成功！" << endl;
	print(10, '*');
	cout << endl;
	system("pause");
}
void admin_repcheck(vector<commodity>& dst, title tle)
{
	print(60, '*');
	cout << endl;
	cout << setiosflags(ios::left);
	cout << setw(10) << tle.ID << setw(10) << tle.name << setw(10) << tle.brand << setw(10) << tle.price << setw(10) << tle.real_num << endl;
	for (auto& it : dst)
		if (it.real_num >= 0)
			cout << setw(10) << it.ID << setw(10) << it.name << setw(10) << it.brand << setw(10) << it.price << setw(10) << it.real_num << endl;
	print(60, '*');
	cout << endl;
	system("pause");
}
void admin_insert(vector<commodity>& dst)
{
	commodity add;
	bool change = true;
	cout << "请输入您要增加的商品名称：";
	cin >> add.name;
	cout << "请输入您要增加的商品品牌：";
	cin >> add.brand;
	cout << "请输入您要增加的商品价格：";
	cin >> add.price;
	cout << "请输入您要增加的商品数量：";
	cin >> add.real_num;
	for(auto it=dst.begin();it!=dst.end();++it)
		if (it->brand == add.brand && it->name == add.name)
		{
			change = false;
			if (it->real_num >= 0)
			{
				it->real_num += add.real_num;
				it->expect_num += add.real_num;
			}
			else
			{
				it->real_num = add.real_num;
				it->expect_num = add.real_num;
			}
		}
	if (change)
	{
		admin_swap(dst.back().ID, add.ID);
		add.expect_num = add.real_num;
		dst.push_back(add);
	}
	cout << "增加成功！" << endl;
	system("pause");
}
void admin_swap(string& src, string& dst)
{
	int x1, x2, x3, x4;
	x1 = src[1] - '0';
	x2 = src[2] - '0';
	x3 = src[3] - '0';
	x4 = src[4] - '0';
	int temp = x1 * 1000 + x2 * 100 + x3 * 10 + x4 + 1;
	x1 = temp / 1000;
	x2 = (temp % 1000) / 100;
	x3 = (temp % 100) / 10;
	x4 = temp % 10;
	char arr[11] = { '0','1','2','3','4','5','6','7','8','9' };
	string s = "F";
	s += arr[x1];
	s += arr[x2];
	s += arr[x3];
	s += arr[x4];
	dst = s;
}
void admin_delete(vector<commodity>& dst)
{
	string ID;
	cout << "请输入您要删除的商品ID：";
	while (1)
	{
		cin >> ID;
		for(auto &it:dst)
			if (it.ID == ID)
			{
				it.real_num = -1;
				it.expect_num = -1;
				cout << "删除成功！" << endl;
				system("pause");
				return;
			}
		cout << "输入ID不存在！请重新输入：";
	}
}
void admin_change(vector<commodity>& dst)
{
	string ID;
	cout << "请输入您要修改数量的商品ID：";
	while (1)
	{
		cin >> ID;
		for (auto& it : dst)
			if (it.ID == ID)
			{
				print(48, '*');
				cout << endl;
				cout << setiosflags(ios::left);
				cout << setw(10) << it.ID << setw(10) << it.name << setw(10) << it.brand << setw(10) << it.real_num << endl;
				print(48, '*');
				cout << endl;
				cout << "请输入您要更改的数量：";
				int num;
				cin >> num;
				int t = num - it.real_num;
				it.real_num = num;
				it.expect_num += t;
				cout << "修改成功！" << endl;
				system("pause");
				return;
			}
		cout << "输入ID不存在！请重新输入："; 
	}
}
void admin_sldcheck(vector<commodity>& dst, title tle)
{
	multimap<string, commodity> temp;
	for (auto& it : dst)
		if (!temp.count(it.ID))
			temp.insert(pair<string,commodity>(it.ID,it));
		else
		{
			bool flag = true;
			for (auto kv = temp.begin(); kv != temp.end(); ++kv)
				if (it.price == kv->second.price)
				{
					kv->second.real_num += it.real_num;
					flag = false;
					break;
				}
			if(flag)
				temp.insert(pair<string, commodity>(it.ID, it));
		}
	print(60, '*');
	cout << endl;
	cout << setiosflags(ios::left);
	cout << setw(10) << tle.ID << setw(10) << tle.name << setw(10) << tle.brand << setw(10) << tle.price << setw(10) << tle.real_num << endl;
	for(auto &it: temp)
		cout << setw(10) << it.second.ID << setw(10) << it.second.name << setw(10) << it.second.brand << setw(10) << it.second.price << setw(10) << it.second.real_num << endl;
	print(60, '*');
	cout << endl;
	system("pause");
}