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
	long long cnt = 0;//��¼��������ܵı��ʽ����Ŀ
	vector<string> history;//��ʷ��¼vector
	stack<char> symbol;//�����ջ
	stack<Number> number;//����ջ
	map<string, Number> variables;
	vector<string> Math_function;//�洢���õ���ѧ������vector
public:
	MyCalculator();

	void initial();

	void calculate(const string& s);//���л�������,����Ǹ�ֵ����ônumberΪ�գ���������㣬��ônumber�е�ΨһԪ��Ϊ������

	int priority(char c);//���ط���c�����ȼ�

	bool calculateOne(char c);//�����Ƿ���ȷ����
	
	void run(const string& s);

	void helpMessage();

	void versionMessage();
	
	void historyMessage();

	void variableMessage();

	void welcomeMessage();

	void quit();

	void refresh();


};