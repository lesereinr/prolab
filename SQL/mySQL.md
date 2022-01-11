# <center>mySQL</center>
[TOC]

​                                                                                                                            姓名： 陈慧毅

​                                                                                                                            学号：201870199
## 1.数据结构设计
+ 结构体information用于存储表格的基本信息，包括表格的文件名字、行数、列数和表格的属性
```
struct information
{
    int row = 0;
    int col = 0;
    string filename;
    vector<string> attribute;
};
```
+ TABLE用于存储整个数据库各个表格的信息，用map实现
```
map<string, information> TABLE;
```
+ table用于存储各个表格的具体信息，是一个结构体
```
struct table
{
    string tablename;
    vector<string> val;
    vector<map<string,string>> content;
};
```
## 2.功能分解
mysql主要分解为如下功能：
+ 利用正则表达式对输入的字符串进行匹配分析，根据结果调用不同的命令函数
+ 支持CREAT TABLE命令，能够根据输入或者已经存在的文件创建表格，在命令行输出并将表格的信息存到总表中
+ 支持DROP TABLE命令，能够根据输入删除table
+ 支持TABLE LIST命令，输出总表中各个table的主要信息
+ 支持INSERT INTO命令，能根据输入向table中插入行
+ 支持DELETE命令，根据输入删除特定的行
+ 支持UPDATA命令，根据输入更新指定列或者全部列
+ 支持SELECT命令，根据输入选择不同的列进行特定的操作后进行展示
+ 支持事务文件，根据事务文件自动执行里面的命令
+ 对相关的文件进行读写操作
## 3.模块设计
主要分为3个模块
+ main函数模块
模仿终端，会自动打印'~$ ’，同时接受输入，当为“mysql”时，调用mysql函数，进入数据库界面，当输入为“quit”时退出程序，当输入为其他命令时，会输出“Command not found!”。
+ mysql函数
模仿数据库，当输入为“quit”时返回main函数，当输入为其他时，会利用正则表达式对字符串进行分析，分别调用不同的命令，当调用的命令格式不正确时会输出“Command format error!”。
+ command模块
该模块主要包括SQL支持的各种命令的函数实现。

## 4.核心函数声明
```
void mysql();
void create_table(string &data);
void file_write(vector<string> inf, string path);
void file_read(vector<string> &inf, string path);
void print(vector<string> inf);
void drop_ttable(string data);
void table_list();
void insert_into(string data);
void delete_table(string data);
void updata_table(string data);
void select_table(string data);
void file_do();
```