#include"user.h"
string USER;
extern void getpassword(string& password);
extern void user_intial();
extern void print(int num, char c);
void user()
{
	fstream file;
	vector<string> tracks;
	file.open("C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\�û�.txt", ios::in);
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
	file.open("C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\���.txt", ios::in);
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
	string shopbus = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + USER + ".txt";
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
	cout << "���������Ĳ�����";
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
		default:cout << "�������"; system("pause");
			break;
		}
		file.open("C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\���.txt", ios::out);
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
		cout << "�����������";
		cin >> key;
	}

}
bool user_ligin(map<string, string>& src, string& user)
{
	string name, password;
	cout << "�����������û�����";
	cin >> name;
	while (!src.count(name))
	{
		cout << "�û��������ڣ����������룡" << endl;
		cout << "�����������û�����";
		cin >> name;
	}
	cout << "�������������룺";
	getpassword(password);
	while (src[name]!=password)
	{
		cout << "����������������룡" << endl;
		cout << "���������룺";
		getpassword(password);
	}
	print(10, '*');
	cout << endl;
	cout << "��¼�ɹ���" << endl;
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
	cout << "��������Ҫ��ѯ����Ʒ��";
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
		cout << "����������Ʒ�����ڣ�";
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
		userdo += "���鿴����Ʒ:  ";
		userdo += s1;
		userdo += s2;
		track.push_back(userdo);
		string track_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + USER + "_track.txt";
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
				cout << "��治�㣬�뼰ʱ���ˣ�";
			cout << endl;
		}
	print(60, '*');
	cout << endl;
	system("pause");

}
void user_add(vector<commodity>& shop, vector<commodity> &rep, title tle, vector<string>& track)
{
	cout << "��������Ҫ��ӵ���ƷID��������";
	string ID;
	int num;
	cin >> ID >> num;
	map<string, commodity> repertory;
	for (auto& it : rep)
		repertory.insert(pair<string, commodity>(it.ID, it));
	if (!repertory.count(ID))
		cout << "��ƷID�����ڣ�"<<endl;
	else if (num > repertory[ID].real_num)
		cout << "��Ʒ��治�㣬���ʧ�ܣ�"<<endl;
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
		cout << "�Ѽ��빺�ﳵ��"<<endl;
		string userdo = "";
		time_t cur_time = time(NULL);
		char* curdata = ctime(&cur_time);
		userdo += curdata;
		userdo += "�������";
		userdo += repertory[ID].brand;
		userdo += "�Ƶ�";
		userdo += repertory[ID].name;
		char a[10];
		itoa(num, a, 10);
		userdo += a;
		userdo += "�������ﳵ�С�";
		track.push_back(userdo);
		string track_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + USER + "_track.txt";
		fstream f;
		f.open(track_path, ios::app);
		if (!f.is_open())
			exit(-1);
		f << endl << userdo;
		f.close();
	}
	cout << "��ǰ���ﳵ���У�" << endl;
	shopbus_check(shop, rep, tle);
}
void user_delete(vector<commodity>& shop, vector<commodity> rep, title tle, vector<string>& track)
{
	cout << "��������Ҫɾ������ƷID��������";
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
		cout << "���ﳵ�в�������Ʒ��" << endl;
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
					cout << "ɾ���ɹ���" << endl;
					string userdo = "";
					time_t cur_time = time(NULL);
					char* curdata = ctime(&cur_time);
					userdo += curdata;
					userdo += "���ӹ��ﳵ��ɾ����";
					userdo += repertory[ID].brand;
					userdo += "�Ƶ�";
					userdo += repertory[ID].name;
					char a[10];
					itoa(num, a, 10);
					userdo += a;
					userdo += "�ݡ�";
					track.push_back(userdo);
					string track_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + USER + "_track.txt";
					fstream f;
					f.open(track_path, ios::app);
					if (!f.is_open())
						exit(-1);
					f << endl << userdo;
					f.close();
					cout << "��ǰ���ﳵ���У�" << endl;
					shopbus_check(shop, rep, tle);
				}

				else
				{
					cout << "���ﳵ�в�����ô����Ʒ" << endl;
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
	cout << "һ����Ҫ����" << sum << "Ԫ" << endl;
	int key;
	cout << "ȷ��֧���밴1    " << "ȡ��֧���밴0" << endl;
	cin >> key;
	if (key)
	{
		print(16, '*');
		cout << endl << "����ɹ���" << endl;
		print(16,'*');
		cout << endl;
		fstream file;
		file.open("C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\�����嵥.txt", ios::app);
		if (!file.is_open())
			exit(-1);
		file << setiosflags(ios::left);
		for (auto& kv : shop)
			file << endl << setw(10) << kv.ID << setw(10) << kv.name << setw(10) << kv.brand << setw(10) << kv.price << setw(10) << kv.real_num << USER;
		shop.clear();
	}
	else
		cout << "ȡ���ɹ���" << endl;
	system("pause");
}
void tracks_check()
{
	cout << "������ʷ��¼Ϊ��" << endl;
	string track_path = "C:\\Users\\27506\\Desktop\\��Ŀ����shopping)\\�ṩ��txt�ļ� - GBK\\" + USER + "_track.txt";
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