#include"user.h"
string USER;
extern void getpassword(string& password);
extern void user_intial();
extern void print(int num, char c);
void user()
{
	fstream file;
	vector<string> tracks;
	file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\用户.txt", ios::in);
	if (!file.is_open())
		exit(-1);
	map<string, string> pswd;
	string name, password;
	while (!file.eof())
	{
		file >> name >> password;
		pswd.insert(pair<string, string>(name, password));
	}
	file.close();
	user_ligin(pswd, USER);
	system("cls");
	user_intial();
	bool flag = true;
	vector<commodity> repertory, bus;
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
			file >> temp.ID >> temp.name >> temp.brand >> temp.price >> temp.real_num >> temp.expect_num;
			repertory.push_back(temp);
		}
	}
	file.close();
	string shopbus = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + USER + ".txt";
	file.open(shopbus, ios::in);
	if (!file.is_open())
		exit(-1);
	flag = true;
	while (!file.eof())
	{
		if (flag)
		{
			flag = false;
			file >> tle_s.ID >> tle_s.name >> tle_s.brand >> tle_s.price >> tle_s.real_num ;
		}
		else
		{
			file >> temp.ID >> temp.name >> temp.brand >> temp.price >> temp.real_num ;
			bus.push_back(temp);
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
		case 0: return;
		case 1:  user_check(repertory, tle_r);   break;
		case 2:  user_search(repertory,tracks,tle_r); break;
		case 3:  user_add(bus,repertory,tle_r,tracks); break;
		case 4:  user_delete(bus, repertory, tle_r, tracks); break;
		case 5:  shopbus_check(bus, repertory, tle_r); break;
		case 6:  user_pay(bus,repertory,tle_r); break;
		case 7:  tracks_check(); break;
		default:cout << "输入错误！"; system("pause");
			break;
		}
		file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\库存.txt", ios::out);
		if (!file.is_open())
			exit(-1);
		file << setiosflags(ios::left);
		file << setw(10) << tle_r.ID << setw(10) << tle_r.name << setw(10) << tle_r.brand << setw(10) << tle_r.price << setw(10) << tle_r.real_num << tle_r.ext;
		for (auto& kv : repertory)
			file << endl << setw(10) << kv.ID << setw(10) << kv.name << setw(10) << kv.brand << setw(10) << kv.price << setw(10) << kv.real_num << kv.expect_num;
		file.close();
		file.open(shopbus, ios::out);
		if (!file.is_open())
			exit(-1);
		file << setiosflags(ios::left);
		file << setw(10) << tle_r.ID << setw(10) << tle_r.name << setw(10) << tle_r.brand << setw(10) << tle_r.price << tle_r.real_num;
		for (auto& kv : bus)
			file << endl << setw(10) << kv.ID << setw(10) << kv.name << setw(10) << kv.brand << setw(10) << kv.price  << kv.real_num ;
		file.close();
		system("cls");
		user_intial();
		cout << "请输入操作：";
		cin >> key;
	}

}
bool user_ligin(map<string, string>& src, string& user)
{
	string name, password;
	cout << "请输入您的用户名：";
	cin >> name;
	while (!src.count(name))
	{
		cout << "用户名不存在，请重新输入！" << endl;
		cout << "请输入您的用户名：";
		cin >> name;
	}
	cout << "请输入您的密码：";
	getpassword(password);
	while (src[name]!=password)
	{
		cout << "密码错误，请重新输入！" << endl;
		cout << "请输入密码：";
		getpassword(password);
	}
	print(10, '*');
	cout << endl;
	cout << "登录成功！" << endl;
	print(10, '*');
	USER = name;
	cout << endl;
	system("pause");
	return true;
}
void user_check(vector<commodity>& dst, title tle)
{
	map<string, commodity> reptority;
	for (auto& it : dst)
		reptority.insert(pair<string, commodity>(it.ID, it));
	print(60, '*');
	cout << endl;
	cout << setiosflags(ios::left);
	cout << setw(10) << tle.ID << setw(10) << tle.name << setw(10) << tle.brand << setw(10) << tle.price << setw(10) << tle.real_num << endl;
	for (auto& it : reptority)
		if (it.second.real_num > 0)
			cout << setw(10) << it.second.ID << setw(10) << it.second.name << setw(10) << it.second.brand << setw(10) << it.second.price << setw(10) << it.second.real_num << endl;
	print(60, '*');
	cout << endl;
	system("pause");
}
void user_search(vector<commodity> dst, vector<string>& track,title tle)
{
	string temp, s1="", s2="";
	cout << "请输入您要查询的商品：";
	cin >> s1;
	getline(cin, temp);
	for (int i = 0; i < temp.size(); ++i)
		if (temp[i] != ' ')
			s2 += temp[i];
	bool flag = false;
	if (s2.size())
		flag = true;
	if (flag)
	{
		for (auto it = dst.begin(); it != dst.end(); )
			if (it->name == s1 && it->brand == s2||it->name==s2&&it->brand==s1)
				it++;
			else
				it=dst.erase(it);
	}
	else
	{
		for (auto it = dst.begin(); it != dst.end(); )
			if (it->name == s1 || it->brand == s2)
				it++;
			else
				it=dst.erase(it);
	}
	if (dst.empty())
		cout << "您搜索的商品不存在！";
	else
	{
		print(60, '*');
		cout << endl;
		cout << setiosflags(ios::left);
		cout << setw(10) << tle.ID << setw(10) << tle.name << setw(10) << tle.brand << setw(10) << tle.price << setw(10) << tle.real_num << endl;
		for (auto& it : dst)
			if (it.real_num > 0)
				cout << setw(10) << it.ID << setw(10) << it.name << setw(10) << it.brand << setw(10) << it.price << setw(10) << it.real_num << endl;
		print(60, '*');
		string userdo = "";
		time_t cur_time = time(NULL);
		char* curdata = ctime(&cur_time);
		userdo += curdata;
		userdo += "您查看了商品:  ";
		userdo += s1;
		userdo += s2;
		track.push_back(userdo);
		string track_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + USER + "_track.txt";
		fstream f;
		f.open(track_path, ios::app);
		if (!f.is_open())
			exit(-1);
		f << endl << userdo;
		f.close();
	}
	cout << endl;
	system("pause");
}
void shopbus_check(vector<commodity>& shop, vector<commodity> rep, title tle)
{
	map<string, commodity> repertory, shopbus;
	for (auto& it : rep)
		repertory.insert(pair<string, commodity>(it.ID, it));
	for (auto& it : shop)
		shopbus.insert(pair<string, commodity>(it.ID, it));
	for (auto it = shop.begin(); it != shop.end();)
		if (repertory[it->ID].real_num == -1)
			it = shop.erase(it);
		else
			it++;
	print(60, '*');
	cout << endl;
	cout << setiosflags(ios::left);
	cout << setw(10) << tle.ID << setw(10) << tle.name << setw(10) << tle.brand << setw(10) << tle.price << setw(10) << tle.real_num << endl;
	for (auto& it : shopbus)
		if (it.second.real_num > 0)
		{
			cout << setw(10) << it.second.ID << setw(10) << it.second.name << setw(10) << it.second.brand << setw(10) << it.second.price << setw(10) << it.second.real_num;
			if (repertory[it.second.ID].expect_num < 0)
				cout << "库存不足，请及时结账！";
			cout << endl;
		}
	print(60, '*');
	cout << endl;
	system("pause");

}
void user_add(vector<commodity>& shop, vector<commodity> &rep, title tle, vector<string>& track)
{
	cout << "请输入您要添加的商品ID和数量：";
	string ID;
	int num;
	cin >> ID >> num;
	map<string, commodity> repertory;
	for (auto& it : rep)
		repertory.insert(pair<string, commodity>(it.ID, it));
	if (!repertory.count(ID))
		cout << "商品ID不存在！"<<endl;
	else if (num > repertory[ID].real_num)
		cout << "商品库存不足，添加失败！"<<endl;
	else
	{
		bool flag = true;
		for(auto &kv:shop)
			if (kv.ID == ID)
			{
				kv.real_num += num;
				for (auto& it : rep)
					if (it.ID == ID)
						it.expect_num -= num;
				flag = false;
			}
		if (flag)
		{
			commodity add = repertory[ID];
			add.real_num = num;
			shop.push_back(add);
			for (auto& it : rep)
				if (it.ID == ID)
					it.expect_num -= num;
		}
		cout << "已加入购物车！"<<endl;
		string userdo = "";
		time_t cur_time = time(NULL);
		char* curdata = ctime(&cur_time);
		userdo += curdata;
		userdo += "您添加了";
		userdo += repertory[ID].brand;
		userdo += "牌的";
		userdo += repertory[ID].name;
		char a[10];
		itoa(num, a, 10);
		userdo += a;
		userdo += "份至购物车中。";
		track.push_back(userdo);
		string track_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + USER + "_track.txt";
		fstream f;
		f.open(track_path, ios::app);
		if (!f.is_open())
			exit(-1);
		f << endl << userdo;
		f.close();
	}
	cout << "当前购物车中有：" << endl;
	shopbus_check(shop, rep, tle);
}
void user_delete(vector<commodity>& shop, vector<commodity> rep, title tle, vector<string>& track)
{
	cout << "请输入您要删除的商品ID和数量：";
	string ID;
	int num;
	cin >> ID >> num;
	map<string, commodity> shopbus;
	for (auto& it : shop)
		shopbus.insert(pair<string, commodity>(it.ID, it));
	map<string, commodity> repertory;
	for (auto& it : rep)
		repertory.insert(pair<string, commodity>(it.ID, it));
	if (!shopbus.count(ID))
		cout << "购物车中不含该商品！" << endl;
	else
	{
		for (auto it = shop.begin(); it != shop.end();)
			if (it->ID == ID)
			{
				if (it->real_num >= num)
				{
					if (it->real_num == num)
						it = shop.erase(it);
					else
						it->real_num -= num;
					for (auto& kv : rep)
						if (kv.ID == ID)
						{
							kv.expect_num = min(kv.real_num, kv.expect_num + num);
						}
					cout << "删除成功！" << endl;
					string userdo = "";
					time_t cur_time = time(NULL);
					char* curdata = ctime(&cur_time);
					userdo += curdata;
					userdo += "您从购物车中删除了";
					userdo += repertory[ID].brand;
					userdo += "牌的";
					userdo += repertory[ID].name;
					char a[10];
					itoa(num, a, 10);
					userdo += a;
					userdo += "份。";
					track.push_back(userdo);
					string track_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + USER + "_track.txt";
					fstream f;
					f.open(track_path, ios::app);
					if (!f.is_open())
						exit(-1);
					f << endl << userdo;
					f.close();
					cout << "当前购物车中有：" << endl;
					shopbus_check(shop, rep, tle);
				}

				else
				{
					cout << "购物车中不含那么多商品" << endl;
					system("pause");
				}
				break;
			}
			else
				it++;
	}
}
void user_pay(vector<commodity>& shop, vector<commodity>& rep, title tle)
{
	map<string, commodity> repertory, shopbus;
	for (auto& it : rep)
		repertory.insert(pair<string, commodity>(it.ID, it));
	for (auto& it : shop)
		shopbus.insert(pair<string, commodity>(it.ID, it));
	for (auto it = shop.begin(); it != shop.end();)
		if (repertory[it->ID].real_num == -1)
			it = shop.erase(it);
		else
			it++;
	for (auto& it : rep)
		if (shopbus.count(it.ID))
			it.real_num -= shopbus[it.ID].real_num;
	print(60, '*');
	cout << endl;
	cout << setiosflags(ios::left);
	cout << setw(10) << tle.ID << setw(10) << tle.name << setw(10) << tle.brand << setw(10) << tle.price << setw(10) << tle.real_num << endl;
	for (auto& it : shopbus)
		if (it.second.real_num > 0)
		{
			cout << setw(10) << it.second.ID << setw(10) << it.second.name << setw(10) << it.second.brand << setw(10) << it.second.price << setw(10) << it.second.real_num;
			cout << endl;
		}
	print(60, '*');
	cout << endl;
	print(32, '>');
	cout << endl;
	double sum = 0;
	for (auto& kv : shop)
		sum += kv.price * kv.real_num;
	cout << "一共需要付款" << sum << "元" << endl;
	int key;
	cout << "确认支付请按1    " << "取消支付请按0" << endl;
	cin >> key;
	if (key)
	{
		print(16, '*');
		cout << endl << "付款成功！" << endl;
		print(16,'*');
		cout << endl;
		fstream file;
		file.open("C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\已售清单.txt", ios::app);
		if (!file.is_open())
			exit(-1);
		file << setiosflags(ios::left);
		for (auto& kv : shop)
			file << endl << setw(10) << kv.ID << setw(10) << kv.name << setw(10) << kv.brand << setw(10) << kv.price << setw(10) << kv.real_num << USER;
		shop.clear();
	}
	else
		cout << "取消成功！" << endl;
	system("pause");
}
void tracks_check()
{
	cout << "您的历史记录为：" << endl;
	string track_path = "C:\\Users\\27506\\Desktop\\项目二（shopping)\\提供的txt文件 - GBK\\" + USER + "_track.txt";
	fstream f;
	string s;
	f.open(track_path, ios::in);
	if (!f.is_open())
		exit(-1);
	while (!f.eof())
	{
		f >> s;
		cout << s << endl;
	}
	system("pause");
}