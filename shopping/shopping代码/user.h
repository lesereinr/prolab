#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cstdio>
#include<time.h>
#include<iomanip>
#include<string>
#include<sstream>
#include<cstdlib>
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
struct shipping_address
{
	char name[20];
	char phone_number[20];
	char region[100];
	char detial_area[100];
};
void user();
bool user_ligin(map<string,string>& src,string& user);
void user_check(vector<commodity>& dst, title tle);
void user_search(vector<commodity> dst,vector<string>& track,title tle);
void user_add(vector<commodity>& shop, vector<commodity>& rep, title tle, vector<string>& track);
void shopbus_check(vector<commodity>& shop, vector<commodity> rep, title tle);
void user_delete(vector<commodity>& shop, vector<commodity> rep, title tle, vector<string>& track);
void user_pay(vector<commodity>& shop, vector<commodity>& rep, title tle);
void tracks_check();