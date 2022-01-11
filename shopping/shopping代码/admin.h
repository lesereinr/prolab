#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<cstdio>
#include<iomanip>
using namespace std;
struct commodity
{
	string ID, name, brand;
	double price;
	int real_num;
	string user_name;
	int expect_num;
};
struct title
{
	string ID, name, brand, price, real_num, ext;
};
void admin();
void admin_login();
void admin_insert(vector<commodity>& dst);
void admin_repcheck(vector<commodity>& dst, title tle);
void admin_swap(string& src, string& dst);
void admin_delete(vector<commodity>& dst);
void admin_change(vector<commodity>& dst);
void admin_sldcheck(vector<commodity>& dst, title tle);
