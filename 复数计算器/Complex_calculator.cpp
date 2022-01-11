#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <stack>
#include <cmath>
#include <iomanip>
#include<stdlib.h>
#define pai acos(-1)
using namespace std;
struct complex
{
    double real = 0;
    double image = 0;
};
float icp(char c, bool flag);
float isp(char c, bool flag);
bool calculate(stack<complex> &operand, char op, bool &flag);
bool judge(string initial);
string deal(string initial, bool &error);
bool calculator(string initial);
void f(string initial);
void dis(string initial);
void swap(string initial);
int main()
{
    bool error = false;
    string Expression;
    cout << "Please enter the expression you want to evaluate:" << endl;
    getline(cin, Expression, '\n');
    while (Expression != "quit")
    {
        error=false;
        if (Expression[0] == 'f')
            f(Expression);
        else if (Expression[0] == 'd')
            dis(Expression);
        else if (Expression[0] == 's')
            swap(Expression);
        else
        {
            Expression = deal(Expression, error);
            if (!error)
                error = judge(Expression);
            if (!error)
                calculator(Expression);
        }
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Please enter the expression you want to evaluate:" << endl;
        fflush(stdin);
        getline(cin, Expression, '\n');
    }
}
void f(string initial)
{
    bool error = false;
    int k = 0;
    double a = 0, b = 0, c = 0;
    for (int i = 0; i < initial.length(); ++i)
    {
        double x = 0, p1 = 10.0, p2 = 0.1;
        double sign = 1;
        if (initial[i] == '=')
        {
            i++;
            if (initial[i] == '-')
            {
                sign *= (-1);
                i++;
            }
            while (isdigit(initial[i]))
            {
                x = x * p1 + initial[i] - '0';
                i++;
            }
            if (initial[i] == '.')
            {
                i++;
                while (isdigit(initial[i]))
                {
                    x = x + p2 * (initial[i] - '0');
                    p2 = p2 * (0.1);
                    i++;
                }
            }
            if (initial[i] == 'x' && initial[i + 1] == '^')
                if (x == 0)
                    a = 1 * sign;
                else
                    a = sign * x;
            else
                error = true;
            k = i;
            break;
        }
    }
    for (int i = k; i < initial.length(); ++i)
    {
        double x = 0, p1 = 10.0, p2 = 0.1;
        double sign = 1;
        if (initial[i] == '2' && initial[i - 1] == '^')
        {
            i++;
            if (i == initial.length())
                break;
            if (initial[i] == '-')
                sign *= (-1);
            i++;
            while (i < initial.length() && isdigit(initial[i]))
            {
                x = x * p1 + initial[i] - '0';
                i++;
            }
            if (initial[i] == '.' && i < initial.length())
            {
                i++;
                while (isdigit(initial[i]))
                {
                    x = x + p2 * (initial[i] - '0');
                    p2 = p2 * (0.1);
                    i++;
                }
            }
            if (i == initial.length())
                c = x;
            if (initial[i] == 'x')
            {
                b = x;
                i++;
                double x = 0, p1 = 10.0, p2 = 0.1;
                double sign = 1;
                if (i == initial.length() - 1)
                    break;
                if (initial[i] == '-')
                    sign *= (-1);
                i++;
                while (i < initial.length() && isdigit(initial[i]))
                {
                    x = x * p1 + initial[i] - '0';
                    i++;
                }
                if (initial[i] == '.' && i < initial.length())
                {
                    i++;
                    while (isdigit(initial[i]))
                    {
                        x = x + p2 * (initial[i] - '0');
                        p2 = p2 * (0.1);
                        i++;
                    }
                }
                c = x;
            }
        }
    }
    if (error)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "error: "
             << "Invaild input!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        double t = b * b - 4 * a * c;
        if (t == 0)
            cout << "Result: "
                 << "x1=x2=" << (b) / (-2 * a) << endl;
        else if (t > 0)
            cout << "Result: "
                 << "x1=" << (-b + sqrt(t)) / (2 * a)
                 << "    "
                 << "x2=" << (-b - sqrt(t)) / (2 * a)
                 << endl;
        else
        {
            double img = fabs(sqrt(-t) / (2 * a));
            cout << "Rrsult: "
                 << "x1=" << (-b) / (2 * a) << "+" << img << 'i' << "    "
                 << "x2=" << (-b) / (2 * a) << "-" << img << 'i' << endl;
        }
    }
}
void dis(string initial)
{
    double a[2], b[2];
    int j = 0;
    for (int i = 0; i < initial.length(); ++i)
        if (initial[i] == '(' || initial[i] == ',')
        {
            i++;
            double p1 = 10.0, p2 = 0.1;
            double x = 0, sign = 1;
            if (initial[i] == '-')
            {
                sign *= (-1);
                i++;
            }
            while (isdigit(initial[i]))
            {
                x = x * p1 + initial[i] - '0';
                i++;
            }
            if (initial[i] == '.')
            {
                i++;
                while (isdigit(initial[i]))
                {
                    x = x + p2 * (initial[i] - '0');
                    p2 = p2 * (0.1);
                    i++;
                }
            }
            if (initial[i] == 'i')
            {
                a[j] = 0;
                b[j++] = (x == 0) ? 1 * sign : x * sign;
            }
            else
            {
                a[j] = x * sign;
                double p1 = 10.0, p2 = 0.1;
                double x = 0, sign = 1;
                if (initial[i] == '-')
                    sign *= (-1);
                i++;
                while (isdigit(initial[i]))
                {
                    x = x * p1 + initial[i] - '0';
                    i++;
                }
                if (initial[i] == '.')
                {
                    i++;
                    while (isdigit(initial[i]))
                    {
                        x = x + p2 * (initial[i] - '0');
                        p2 = p2 * (0.1);
                        i++;
                    }
                }
                b[j++] = x *= sign;
            }
        }
    double x = a[0] - a[1], y = b[0] - b[1];
    cout << "Result: " << sqrt(x * x + y * y) << endl;
}
void swap(string initial)
{
    double a, b;
    for (int i = 0; i < initial.length();++i)
    {
        if(initial[i]=='(')
        {
            i++;
            double p1 = 10.0, p2 = 0.1;
            double x = 0, sign = 1;
            if (initial[i] == '-')
            {
                sign *= (-1);
                i++;
            }
            while (isdigit(initial[i]))
            {
                x = x * p1 + initial[i] - '0';
                i++;
            }
            if (initial[i] == '.')
            {
                i++;
                while (isdigit(initial[i]))
                {
                    x = x + p2 * (initial[i] - '0');
                    p2 = p2 * (0.1);
                    i++;
                }
            }
            if (initial[i] == 'i')
            {
                a = 0;
                b = (x == 0) ? 1 * sign : x * sign;
            }
            else
            {
                a = x * sign;
                double p1 = 10.0, p2 = 0.1;
                double x = 0, sign = 1;
                if (initial[i] == '-')
                    sign *= (-1);
                i++;
                while (isdigit(initial[i]))
                {
                    x = x * p1 + initial[i] - '0';
                    i++;
                }
                if (initial[i] == '.')
                {
                    i++;
                    while (isdigit(initial[i]))
                    {
                        x = x + p2 * (initial[i] - '0');
                        p2 = p2 * (0.1);
                        i++;
                    }
                }
                b = x *= sign;
            }
        }
    }
    double r = sqrt(a * a + b * b), ang = atan(b / a);
    cout << "Result: " << r << 'e' << '(' << ang << 'i' << ')'<<endl;
}
bool calculator(string initial)
{
    bool flag = false;
    stack<char> sign;
    stack<complex> operand;
    for (int i = 0; i < initial.length(); ++i)
    {
        if (initial[i] == ','||initial[i]==' ')
            continue;
        else if (initial[i] == 'i')
        {
            if (i)
                if (initial[i - 1] == ')')
                {
                    initial[i] = '$';
                    i--;
                    continue;
                }
            complex temp;
            temp.image = 1.0;
            operand.push(temp);
            continue;
        }
        else if (isdigit(initial[i]))
        {
            double p1 = 10.0, p2 = 0.1;
            double x = 0;
            complex temp;
            while (isdigit(initial[i]))
            {
                x = x * p1 + initial[i] - '0';
                i++;
            }
            if (initial[i] == '.')
            {
                i++;
                while (isdigit(initial[i]))
                {
                    x = x + p2 * (initial[i] - '0');
                    p2 = p2 * (0.1);
                    i++;
                }
            }
            if (initial[i] == 'i')
            {
                temp.image = x;
            }
            else
            {
                temp.real = x;
                i--;
            }
            operand.push(temp);
            continue;
        }
        else
        {
            while ((!sign.empty()) && (icp(initial[i], flag) < isp(sign.top(), flag)))
            {
                char op = sign.top();
                sign.pop();
                calculate(operand, op, flag);
            }
            if (sign.empty())
            {
                sign.push(initial[i]);
                if (initial[i] == '|')
                    flag = true;
            }
            else
            {
                if (icp(initial[i], flag) > isp(sign.top(), flag))
                {
                    sign.push(initial[i]);
                    if (initial[i] == '|')
                        flag = true;
                }
                else if (icp(initial[i], flag) == isp(sign.top(), flag))
                {
                    if (initial[i] == '|')
                    {
                        char op = sign.top();
                        sign.pop();
                        calculate(operand, op, flag);
                    }
                    else
                        sign.pop();
                }
            }
        }
    }
    while (!sign.empty())
    {
        char op = sign.top();
        sign.pop();
        calculate(operand, op, flag);
    }
    if (operand.size() == 1)
    {
        complex result = operand.top();
        operand.pop();
        cout << "The result is ";
        if (result.image == 0 && result.real == 0)
            cout << 0;
        else if (result.image == 0)
        {
            if ((int)result.real == result.real)
                cout << result.real << endl;
            else
                cout << fixed << setprecision(6) << result.real << endl;
        }
        else if (result.real == 0)
        {
            if ((int)result.image == result.image)
                cout << result.image << 'i' << endl;
            else
                cout << fixed << setprecision(6) << result.image << 'i' << endl;
        }
        else
        {
            if ((int)result.real == result.real)
                cout << result.real;
            else
                cout << fixed << setprecision(6) << result.real;
            if (result.image > 0)
                cout << '+';
            if ((int)result.image == result.image)
                cout << result.image << 'i' << endl;
            else
                cout << fixed << setprecision(6) << result.image << 'i' << endl;
        }
        return true;
    }
    else
        return false;
}
float isp(char c, bool flag)
{
    if (c == '|' && flag)
        return 1.5;
    else if (c == '~' || c == '|' || c == 'c' || c == 'a' || c == 'd' || c == '$')
        return 9;
    else if (c == '^')
        return 7;
    else if (c == '*' || c == '/')
        return 5;
    else if (c == '+' || c == '-')
        return 3;
    else if (c == '(')
        return 1;
    else if (c == ')')
        return 10;
    return 0;
}
float icp(char c, bool flag)
{
    if (c == '|' && flag)
        return 1.5;
    else if (c == '~' || c == '|' || c == 'c' || c == 'a' || c == 'd' || c == '$')
        return 8;
    else if (c == '^')
        return 6;
    else if (c == '*' || c == '/')
        return 4;
    else if (c == '+' || c == '-')
        return 2;
    else if (c == '(')
        return 10;
    else if (c == ')')
        return 1;
    return 0;
}
bool calculate(stack<complex> &operand, char op, bool &flag)
{
    switch (op)
    {
    case '+':
    {
        complex a = operand.top();
        operand.pop();
        complex b = operand.top();
        operand.pop();
        complex temp;
        temp.image = a.image + b.image;
        temp.real = a.real + b.real;
        operand.push(temp);
        return true;
    }
    case '-':
    {
        complex a = operand.top();
        operand.pop();
        complex b = operand.top();
        operand.pop();
        complex temp;
        temp.image = b.image - a.image;
        temp.real = b.real - a.real;
        operand.push(temp);
        return true;
    }
    case '*':
    {
        complex a = operand.top();
        operand.pop();
        complex b = operand.top();
        operand.pop();
        complex temp;
        temp.image = a.image * b.real + b.image * a.real;
        temp.real = a.real * b.real + (-1) * a.image * b.image;
        operand.push(temp);
        return true;
    }
    break;
    case '/':
    {
        complex a = operand.top();
        operand.pop();
        complex b = operand.top();
        operand.pop();
        if (a.image == 0 && a.real == 0)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
            cout << "error: "
                 << "The divisior can't be zero!" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return false;
        }
        complex temp;
        temp.image = (-a.image) * b.real + b.image * a.real;
        temp.real = a.real * b.real + a.image * b.image;
        double den = a.real * a.real + a.image * a.image;
        temp.image /= den;
        temp.real /= den;
        operand.push(temp);
        return true;
    }
    case '|':
    {
        if (flag == false)
        {
            flag = true;
            return true;
        }
        if (flag)
        {
            flag = false;
            complex a = operand.top();
            operand.pop();
            complex temp;
            temp.real = a.real * a.real + a.image * a.image;
            temp.real = sqrt(temp.real);
            operand.push(temp);
            return true;
        }
    }
    case '^':
    {
        complex a = operand.top();
        operand.pop();
        complex b = operand.top();
        operand.pop();
        complex temp;
        double n = a.real, r = sqrt(pow(b.real, 2) + pow(b.image, 2));
        if (b.image == 0)
            temp.real = pow(b.real, n);
        else
        {
            temp.real = pow(r, n) * cos(atan(b.image / b.real) * n);
            temp.image = pow(r, n) * sin(atan(b.image / b.real) * n);
        }
        operand.push(temp);
        return true;
    }
    case 'a':
    {
        complex a = operand.top();
        operand.pop();
        complex temp;
        double x = a.real, y = a.image;
        if (x == 0 && y == 0)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
            cout << "error: "
                 << "The value of argument can't be zero!" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return false;
        }
        else if (x < 0 && y < 0)
            temp.real = atan(y / x) - pai;
        else if (x == 0 && y < 0)
            temp.real = (double)(-1 / 2) * pai;
        else if (x > 0 && y < 0)
            temp.real = atan(y / x);
        else if (x < 0 && y == 0)
            temp.real = pai;
        else if (x > 0 && y == 0)
            temp.real = 0;
        else if (x < 0 && y > 0)
            temp.real = atan(y / x) + pai;
        else if (x == 0 && y > 0)
            temp.real = (double)(1 / 2) * pai;
        else if (x > 0 && y > 0)
            temp.real = atan(y / x);
        operand.push(temp);
        return true;
    }
    case 'c':
    {
        complex a = operand.top();
        operand.pop();
        a.image = (double)(-1) * a.image;
        operand.push(a);
        return true;
    }
    case '$':
    {
        complex a = operand.top();
        operand.pop();
        a.image = a.real;
        a.real = 0;
        operand.push(a);
        return true;
    }
    case '~':
    {
        complex a = operand.top();
        operand.pop();
        a.real = -a.real;
        a.image = -a.image;
        operand.push(a);
        return true;
    }
    default:
        break;
    }
    return true;
}
bool judge(string initial)
{
    bool error = false;
    string errortype;//记录错误的类型
    vector<int> left;//用于后面的括号匹配
    int *arr = new int[initial.length()]{};//记录错误字符的位置
    for (int i = 0; i < initial.length(); ++i)
    {
        if (i == 0)
        {
            if (initial[i] == ')' || initial[i] == '+' || initial[i] == '*' || initial[i] == '/' || initial[i] == '^')
            {
                error = true;
                errortype = "Expressions can't start with ";
                errortype += initial[i];
                arr[i] = 1;
                break;
            }
        }
        if (initial[i] == '+' || initial[i] == '*' || initial[i] == '^' || initial[i] == '/' || (initial[i] == '-' && i != 0 && (i >= 1 && initial[i - 1] != '(')))
        {
            if (initial[i + 1] == '+' || initial[i + 1] == '^' || initial[i + 1] == '-' || initial[i + 1] == '*' || initial[i + 1] == '/' || initial[i + 1] == ')')
            {
                error = true;
                errortype = "Operators can't be followed by operators or ')'!";
                arr[i] = 1;
                arr[i + 1] = 1;
                break;
            }
        }
        else if (isdigit(initial[i]))
        {
            if (initial[i + 1] == '(' || initial[i + 1] == '|')
            {
                error = true;
                errortype = "Real numbers can't be followed by '|' or '('!";
                arr[i] = 1;
                arr[i + 1] = 1;
                break;
            }
        }
        else if (initial[i] == 'i')
        {
            if (i)
            {
                if (initial[i - 1] == ')')
                {
                    for (int j = i - 1; j >= 0; j--)
                        if (initial[j] == '(')
                        {
                            if (initial[j - 1] == '*' || initial[j - 1] == 'a' || initial[j - 1] == 'd' || (initial[j - 1] == 'c' && initial[j - 2] == '*'))
                                break;

                            else
                            {
                                error = true;
                                errortype = "'i' can't be directly connected to a noreal number!";
                                arr[i] = 1;
                                break;
                            }
                        }
                }
            }
            if (initial[i + 1] == '(' || initial[i + 1] == 'i' || isdigit(initial[i + 1]))
            {
                error = true;
                errortype = "'i' can't be followed by '|' or '(' or 'i' or real numbers! ";
                arr[i] = 1;
                arr[i + 1] = 1;
                break;
            }
        }
        else if (initial[i] == '(')
        {
            left.push_back(i);
            if (initial[i + 1] == ')' || initial[i + 1] == '+' || initial[i + 1] == '*' || initial[i + 1] == '/' || initial[i + 1] == '-')
            {
                error = true;
                errortype = "'(' can't be followed by ')' or operators('+' or '-' or '*' or '/')! ";
                arr[i] = 1;
                arr[i + 1] = 1;
                break;
            }
        }
        else if (initial[i] == ')')
        {
            if (left.empty())
            {
                error = true;
                errortype = "Bracket matching error! ";
                arr[i] = 1;
                break;
            }
            else
                left.pop_back();
            if (initial[i + 1] == '(' || isdigit(initial[i + 1]))
            {
                error = true;
                errortype = "')' can't be followed by '(' or real numbers ! ";
                arr[i] = 1;
                arr[i + 1] = 1;
                break;
            }
        }
        else if (initial[i] == ' ')
        {
            if (isdigit(initial[i + 1]) && isdigit(initial[i - 1]))
            {
                error = true;
                errortype = "Operands can't have Spaces inside them!";
                arr[i - 1] = 1;
                arr[i + 1] = 1;
                break;
            }
        }
        if (i == initial.length() - 1)
        {
            if (initial[i] == '(' || initial[i] == '+' || initial[i] == '*' || initial[i] == '/' || initial[i] == '^' || initial[i] == '-')
            {
                error = true;
                errortype = "Expressions can't end with ";
                errortype += initial[i];
                arr[i] = 1;
                break;
            }
            if (!left.empty())
            {
                error = true;
                errortype = "Bracket matching error!";
                arr[left[0]] = 1;
                break;
            }
        }
    }
    if (error)
    {
        for (int i = 0; i < initial.length(); ++i)
            if (arr[i])
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                cout << initial[i];
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << initial[i];
            }
        cout << ",  ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "error: " << errortype << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    return error;
}
string deal(string initial, bool &error)
{
    int *arr = new int[initial.length()]{};//用来记录错误字符的位置
    for (int i = 0; i < initial.length(); ++i)
        if (initial[i] >= 'A' && initial[i] <= 'Z')
            initial[i] = initial[i] - ('A' - 'a');//统一转化为大写
    string temp = "";
    for (int i = 0; i < initial.length(); ++i)
    {
        if ((i == 0 && initial[i] == '-') || (initial[i] == '-' && initial[i - 1] == '('))
            temp += '~';//判断‘-’是负号的情况并把它转化成‘~’
        else if (initial[i] == 'a' && initial[i + 1] == 'r' && initial[i + 2] == 'g')
        {
            temp += 'a';
            i += 2;
        }
        else if (initial[i] == 'c' && initial[i + 1] == 'j' && initial[i + 2] == 'g')
        {
            temp += 'c';
            i += 2;
        }
        else if (initial[i] == 'i' || initial[i] == '+' || initial[i] == '-' || initial[i] == '*' || initial[i] == '/' || initial[i] == '|' || initial[i] == '(' || initial[i] == ')' || initial[i] == '^' || initial[i] == '.' || isdigit(initial[i]))
            temp += initial[i];
        else
        {
            error = true;
            arr[i] = 1;
        }
    }
    if (error)
    {
        for (int i = 0; i < initial.length(); ++i)
            if (arr[i])
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                cout << initial[i];
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << initial[i];
            }
        cout << ",  ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "error: "
             << "Invaild input!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    return temp;
}