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