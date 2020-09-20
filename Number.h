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
