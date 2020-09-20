# CS205 C/C++ Program Design

## Assignment 2

#### Name: 李伯岩   	SID: 11912914

### Part 1. Description

##### 在本次Assignment2中，我实现的计算器功能有：

1.支持**超高精度整数、浮点数**的带有运算符优先级 ‘+’，‘-’，‘*’，‘/’以及左右括号的表达式运算

2.支持通过控制台输入来存储变量，其中变量名不仅限于单个英文字符，可额外扩展为**任何有效字符串**

3.支持表达式中数值与已存储的变量**组合**形成的表达式的运算

4.支持sqrt(x)、exp(x)、ln(x)、log(x) or log(x,a)、factorial(x)、abs(x)、sin(x)、 arcsin(x)、cos(x)、arccos(x)、tan(x)、arctan(x)总共**十三个内置函数**，**支持表达式中带有非嵌套的函数运算**（x为一个显式数值）

5.对于表达式中出现的”除0“异常，会输出提示信息

6.打开程序界面有欢迎信息以及帮助信息，此外内置了**7种操控命令**，分别为：

1. -h  or -help     (to get help messages)
2. -v  or -version  (to get the calculator version)
3. -hs or -history  (to get the input history)
4. -r  or -refresh  (to clear the screen)
5. -vb or -variable (to get the variables list input)
6. -i  or -initial  (to initial the calculator)
7. -q  or -quit     (to quit the calculator)

##### Project文件说明：

###### 1.Main.cpp  - 计算器入口

###### 2.Number.h Number.cpp - 计算器中数据的超高精度数类

###### 3.MathFunction.h MathFunction.cpp - 计算器内置函数（可继续扩展）

###### 4.MyCalculator.h MyCalculator.cpp - 计算器核心的运算以及其他操作

##### 详细函数说明：

因代码太长，此处只展示头文件，具体实现细节请看源文件。

###### MathFunction.h:

```c++
#pragma once
#include "Number.h"
#include <cmath>

Number abs(Number n);

Number sum(const Number nums[], const long long size);

Number sqrt(Number& n);

Number exp(const Number& n);

Number ln(Number& n);

//默认以10为底
Number log(Number& n, long long x = 10);

Number factorial(Number& n);

Number sin(Number& n);

Number cos(Number& n);

Number tan(Number& n);

Number exp(Number& n);

Number asin(Number& n);

Number acos(Number& n);

Number atan(Number& n);

Number pow(Number& n, long long x);


```

###### MyCalculator.h:

```c++
#pragma once
#include "Number.h"
#include <vector>
#include <stack>
#include <map>
#include "MathFunction.h"
#include <algorithm>
#include <string>


class MyCalculator {
private:
	long long cnt = 0;//记录已输入的总的表达式的数目
	vector<string> history;//历史记录vector
	stack<char> symbol;//运算符栈
	stack<Number> number;//数据栈
	map<string, Number> variables;
	vector<string> Math_function;//存储内置的数学函数的vector
public:
	MyCalculator();

	void initial();

	void calculate(const string& s);//进行基本运算,如果是赋值，那么number为空，如果是运算，那么number中的唯一元素为运算结果

	int priority(char c);//返回符号c的优先级

	bool calculateOne(char c);//返回是否正确进行
	
	void run(const string& s);

	void helpMessage();

	void versionMessage();
	
	void historyMessage();

	void variableMessage();

	void welcomeMessage();

	void quit();

	void refresh();


};
```

###### Number.h:

```c++
#pragma once
#include <iostream>
#include <string>
using namespace std;
//高精度浮点数借鉴模板Number类来源：https://blog.csdn.net/mkr67n/article/details/105219135
//本人在模板上新实现的函数有：
class Number
{
public:
	//运算容器
	static int digits1[101];
	static int digits2[101];
	static int digitsR[101];
	//数字属性
	int sign = 1;
	int length = 0;
	int integer = 0;
	int decimal = 0;
	string numString;//储存无符号的数字（同时去除前导0和后导0，但保留小数位的有效0）

	Number();

	Number(const string& inputString);

	Number(const int& inputNumber);
	

	Number(const long long int& inputNumber);
	
	//精度只有大概6位，太长的浮点数应用字符串录入
	Number(const double& inputNumber);
	
	//用于运算结果的Number对象构造，包含对-0的修正
	Number(int resultSign, int resultLength, int resultInteger, int resultDecimal, string resultString);

	//用于获取函数的字面字符串值
	string GetFullNumber();

	Number operator + (const Number& addend);

	Number operator - (const Number& subtractor);

	Number operator * (const Number& factor);

	Number operator / (const Number& divisor);

	//本人在模板基础上实现的新函数：
	bool operator < (const Number& b) const;
	bool operator > (const Number& b) const;
	bool operator <= (const Number& b) const;
	bool operator >= (const Number& b) const;
	bool operator == (const Number& b) const;
	bool operator != (const Number& b) const;




private:
	//用于构造函数中
	void constructNumber(const string& inputString);

	//两数字绝对值比较
	int absCompareB(const Number& b);

	//用于加减乘，校准结果数组中的前导0后导0带来的长度影响，返回删除的后导0个数
	int calibrateResultLength(int& length, int& decimal);

	//用于除，校准结果数组中的前导0后导0带来的长度影响，返回删除的前导0个数
	int calibrateResultLengthD(int& length, int& decimal);

	//把结果数组前n个位数重设为0
	void resetDigitsR(int length);

	void additionSort(const Number& otherNumber);

	void multiplicationSort(const Number& otherNumber);

	void divisionSort(const Number& otherNumber);


};

```



### Part 2. Result & Verification

##### 1.验证支持**超高精度整数、浮点数**的带有运算符优先级 ‘+’，‘-’，‘*’，‘/’以及左右括号的表达式运算

###### Test case #1:

Input: 

9999999999999999999999999999999999999999999999999999999999999999999.22222222+1.0

Output: 

10000000000000000000000000000000000000000000000000000000000000000000.22222222

![](Assignment2-CaseFile\case1-1.png)

###### Test case #2:

Input: 

3*6.6/(12+8)

Output: 

0.99

![case1-2](Assignment2-CaseFile\case1-2.png)

##### 2.验证支持通过控制台输入来存储变量，其中变量名不仅限于单个英文字符，可额外扩展为**任何有效字符串**，支持表达式中数值与已存储的变量**组合**形成的表达式的运算

###### Test case #1:

Input: 

x=3 

sam=6 

(x+1)/sam

Output: 0.666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666

![case2-1](Assignment2-CaseFile\case2-1.png)

##### 3.验证支持sqrt(x)、exp(x)、ln(x)、log(x) or log(x,a)、factorial(x)、abs(x)、sin(x)、 arcsin(x)、cos(x)、arccos(x)、tan(x)、arctan(x)总共**十三个内置函数**，**支持表达式中带有非嵌套的函数运算**(x为一个显式数值),对于表达式中出现的”除0“异常，会输出提示信息

###### Test case #1:

Input: 

sqrt(4)+ln(1)+exp(2)+log(10)+log(8,2)+factorial(2)+abs(-1.1)+sin(0)+arccos(1)

Output: 

16.489057031524

![case3-1](Assignment2-CaseFile\case3-1.png)

###### Test case #2:

Input: 

x=9
y=3
abs(-9)+x/y-factorial(2)

Output: 

10

![case3-2](Assignment2-CaseFile\case3-2.png)

###### Test case #3:

Input: 

x=9
y=0
abs(-9)+x/y-factorial(2)

Output: 

Divide by 0 error!

![case3-3](Assignment2-CaseFile\case3-3.png)

##### 4.验证7种操控命令

###### Test case :

"-h":

![case-h](Assignment2-CaseFile\case-h.png)

"-v":

![case-v](Assignment2-CaseFile\case-v.png)

"-hs":

![case-hs](Assignment2-CaseFile\case-hs.png)

"-vb":

![case-vb](Assignment2-CaseFile\case-vb.png)

"-i":

![case-i](Assignment2-CaseFile\case-i.png)

"-q":

![case-q](Assignment2-CaseFile\case-q.png)

### 

### Part 3. Difficulties & Solutions, or others

1. 本次作业用我遇到的最大的难题就是实现超高精度的数据输入以及计算并输出，通过使用Number类，将所有数据的输入、储存、运算全部转换成字符串类型的运算，这样就可以解决默认数据类型double等精度不足以及运算过程精度缺失的问题。
2. 第二个难点在于如果计算带有符号优先级的中缀表达式，通过搜索相关资料，我了解到了中缀表达式转换为后缀表达式的思路，通过后缀表达式就可以实现带有优先级的运算，这是我在这次作业中获得了一个很有意义的经验。
3. 在将函数运算实现到作业中时，主要遇到了两个Bug。第一是对于abs(-10.1)形式的单一函数输入，没有任何除括号外的运算符，这时候符号栈为空，在调用符号栈的top()时，就会报错；第二时对于abs(0)形式函数参数为0的输入，由于Number类设计的缺陷，对于0的Number对象，通过GetFullNumber()方法转为字符串时为空串，这就导致了后续一系列的错误。通过不断尝试，这两个Bug已被解决。
4. 对于函数的实现，我认为做的好的一方面是设计的函数调用比较容易扩展，方便后续增加更多的内置函数。