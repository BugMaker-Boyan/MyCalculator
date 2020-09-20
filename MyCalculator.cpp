#include "MyCalculator.h"

MyCalculator::MyCalculator() {
	//可扩展设计
	Math_function.push_back("abs");
	Math_function.push_back("sum");
	Math_function.push_back("sqrt");
	Math_function.push_back("exp");
	Math_function.push_back("ln");
	Math_function.push_back("log");
	initial();
}

void MyCalculator::initial() {
	//清空容器
	history.clear();
	while (!symbol.empty())
	{
		symbol.pop();
	}
	while (!number.empty())
	{
		number.pop();
	}
	variables.clear();
}

void MyCalculator::calculate(const string& s) {
	long long index = s.find('=');
	if (index != s.npos)
	{	
		//是赋值表达式
		string name = s.substr(0, index);
		Number val(s.substr(index + 1, s.size() - index - 1));
		variables[name] = val;
	}
	else {
		//是算术表达式
		long long length = s.size();
		symbol.push('?');//防止遇到第一个+号时，symbol栈为空报错
		long long i = 0;
		if (s[0] == '-')
		{
			for ( i = 1; i < length; i++)
			{
				if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
					break;//i位置是第一个运算符
				}
			}
			Number first(s.substr(0, i));
			number.push(first);
		}


		for (; i < length; i++)
		{

			if (s[i] == '(') {
				symbol.push(s[i]);
			}
			else if (s[i] == ')')
			{
				while (symbol.top() != '(') {
					if (calculateOne(symbol.top()))
					{
						symbol.pop();
					}
					else {
						cout << "Divide by 0 error!" << endl;
						return;
					}
				}
				//pop掉'('
				symbol.pop();
			}
			else if (s[i] == '+' || s[i] == '-')
			{
				if (priority(symbol.top())>=priority(s[i])&&symbol.top()!= '(')
				{
					while (priority(symbol.top()) >= priority(s[i]) && symbol.top() != '(') {
						if (calculateOne(symbol.top()))
						{
							symbol.pop();
						}
						else {
							cout << "Divide by 0 error!" << endl;
							return;
						}
					}
				}
				symbol.push(s[i]);
			}
			else if (s[i] == '*' || s[i] == '/')
			{
				if (priority(symbol.top()) == priority(s[i]))
				{
					while (priority(symbol.top()) == priority(s[i])) {
						if (calculateOne(symbol.top()))
						{
							symbol.pop();
						}
						else {
							cout << "Divide by 0 error!" << endl;
							return;
						}
					}
				}
				symbol.push(s[i]);
			}
			else {
				//数值或变量或调用函数,压入数值
				long long start = i;
				long long L = -1;
				while (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != ')'&& i<length)
				{
					if (s[i] == '(')
					{
						L = i;
						//防止abs（-1）中参数的第一个“-”对遍历造成影响，所以需要跳过这个负号
						if (s[i+1] == '-')
						{
							i++;
						}
					}
					i++;
					
				}
				//是函数
				if (L != -1)
				{
					string func_name = s.substr(start, L - start);
					string par = s.substr(L + 1, i - L - 1);
					long long index = par.npos;//","
					string par1, par2;//针对log的两个参数
					if ((index = par.find(","))!=par.npos)
					{
						par1 = par.substr(0, index);
						par2 = par.substr(index + 1, par.size() - index - 1);
					}

					//函数计算
					Number val(par);

					if (func_name == "sqrt")
					{
						val = sqrt(val);
					}
					else if (func_name == "abs")
					{
						val = abs(val);
					}
					else if (func_name == "exp")
					{
						val = exp(val);
					}
					else if (func_name == "ln")
					{
						val = ln(val);
					}
					else if (func_name == "log")
					{
						if (index != par.npos)
						{
							Number parN1(par1);
							long long parL2 = stoll(par2);
							val = log(parN1, parL2);
						}
						else {
							val = log(val);
						}

					}
					else if (func_name == "factorial")
					{
						val = factorial(val);
					}
					else if (func_name == "sin")
					{
						val = sin(val);
					}
					else if (func_name == "cos")
					{
						val = cos(val);
					}
					else if (func_name == "tan")
					{
						val = tan(val);
					}
					else if (func_name == "arcsin")
					{
						val = asin(val);
					}
					else if (func_name == "arccos")
					{
						val = acos(val);
					}
					else if (func_name == "arctan")
					{
						val = atan(val);
					}
					else if (func_name == "pow")
					{
						Number parN1(par1);
						long long parL2 = stoll(par2);
						val = pow(parN1, parL2);
					}
					number.push(val);

				}
				else {
					//是数值或者变量，区分数值和变量，拿到真正的val值
					string num = s.substr(start, i - start);
					Number val("0.0");
					if (num[0] == '-')
					{
						if (variables.find(num.substr(1, num.size() - 1)) != variables.end())
						{
							val = variables[num.substr(1, num.size() - 1)];
							val.sign = -1;
						}
						else {
							Number temp(num);
							val = temp;
						}
					}
					else {
						if (variables.find(num) != variables.end())
						{
							val = variables[num];
						}
						else {

							Number temp(num);
							val = temp;
						}
					}
					number.push(val);
					i--;//防止下次循环跳过i处的符号
				}




				
			}
		}
		//处理剩余的后缀表达式
		while (symbol.top()!='?')
		{
			if (!calculateOne(symbol.top()))
			{
				cout << "Divide by 0 error!" << endl;
				return;
			}
			symbol.pop();
		}
		cout << number.top().GetFullNumber() << endl;
		//处理残余
		while (!symbol.empty())
		{
			symbol.pop();
		}
		while (!number.empty())
		{
			number.pop();
		}
	}



	
}

int MyCalculator::priority(char c) {
	switch (c)
	{
	case '(':
	case ')':
		return 3;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	case '?':
		return -1;
	}

}

bool MyCalculator::calculateOne(char c) {
	Number n1(0);
	Number n2(0);
	Number n3(0);
	n1 = number.top();
	number.pop();
	n2 = number.top();
	number.pop();
	switch (c)
	{
	case '+': {
		n3 = n2 + n1;
		number.push(n3);
		break;
	}
	case '-': {
		n3 = n2 - n1;
		number.push(n3);
		break;
	}
	case '*': {
		n3 = n1 * n2;
		number.push(n3);
		break;
	}
	case '/': {
		Number error(0);
		if (n1 == error)
		{
			number.push(error);
			return false;
		}
		n3 = n2 / n1;
		number.push(n3);
		break;
	}
	}
	return true;

}

void MyCalculator::helpMessage() {
	cout << " _____________________________________________________________________________" << endl;
	cout << "|The calculator can support BigInteger and BigDecimal with infinite precision!|" << endl;
	cout << "|          The functions supported by the calculator are as followed:         |" << endl;
	cout << "|                  1:  sqrt(x)               2:  exp(x)                       |" << endl;
	cout << "|                  3:  ln(x)                 4:  log(x) or log(x,a)           |" << endl;
	cout << "|                  5:  factorial(x)          6:  abs(x)                       |" << endl;
	cout << "|                  7:  sin(x)                8:  arcsin(x)                    |" << endl;
	cout << "|                  9:  cos(x)               10:  arccos(x)                    |" << endl;
	cout << "|                 11:  tan(x)               12:  arctan(x)                    |" << endl;
	cout << "|                   Attention: Only a Number x is allowed                     |" << endl;
	cout << "| The calculator supports four operations with symbolic priorty and variables |" << endl;
	cout << "|                Also, calculate with some functions is OK!                   |" << endl;
	cout << "|   For example: Input are x=6 y=4 5+x*(y-5.4/2)+factorial(3) in three lines  |" << endl;
	cout << "|                      The Output will be 18.8                                |" << endl;
	cout << "|                    There are some special instructions:                     |" << endl;
	cout << "|                1.-h  or -help     (to get help messages)                    |" << endl;
	cout << "|                2.-v  or -version  (to get the calculator version)           |" << endl;
	cout << "|                3.-hs or -history  (to get the input history)                |" << endl;
	cout << "|                4.-r  or -refresh  (to clear the screen)                     |" << endl;
	cout << "|                5.-vb or -variable (to get the variables list input)         |" << endl;
	cout << "|                6.-i  or -initial  (to initial the calculator)               |" << endl;
	cout << "|                7.-q  or -quit     (to quit the calculator)                  |" << endl;
	cout << "|                       Good luck with your use!                              |" << endl;
	cout << "|_____________________________________________________________________________|" << endl;

	cout << endl;

}

void MyCalculator::versionMessage() {
	cout << " _____________________________________________________________________________" << endl;
	cout << "|                          MyCalculator version-1.0.0                         |" << endl;
	cout << "|                            Implemented by Li Boyan                          |" << endl;
	cout << "|                           Student Number : 11912914                         |" << endl;
	cout << "|_____________________________________________________________________________|" << endl;
	cout << endl;
}

void MyCalculator::historyMessage() {
	if (history.size()==0)
	{
		cout << "No any input!" << endl;
		cout << endl;
		return;
	}
	cout << "Input history:" << endl;
	for (long long i = 0;i < history.size();i++)
	{
		cout << i + 1 << ": " << history[i] << endl;
	}
	cout << endl;
}

void MyCalculator::variableMessage() {
	if (variables.size()== 0)
	{
		cout << "No any variable input!" << endl;
		cout << endl;
		return;
	}
	else {
		long long cnt = 1;
		for (map<string,Number>::iterator it = variables.begin();it != variables.end();it++)
		{
			cout << cnt << ": " << it->first << " = " << it->second.GetFullNumber() << endl;
			cnt++;
		}
	}
	cout << endl;
}

void MyCalculator::welcomeMessage() {
	cout << " _____________________________________________________________________________" << endl;
	cout << "|The calculator can support BigInteger and BigDecimal with infinite precision!|" << endl;
	cout << "|          The functions supported by the calculator are as followed:         |" << endl;
	cout << "|                  1:  sqrt(x)               2:  exp(x)                       |" << endl;
	cout << "|                  3:  ln(x)                 4:  log(x) or log(x,a)           |" << endl;
	cout << "|                  5:  factorial(x)          6:  abs(x)                       |" << endl;
	cout << "|                  7:  sin(x)                8:  arcsin(x)                    |" << endl;
	cout << "|                  9:  cos(x)               10:  arccos(x)                    |" << endl;
	cout << "|                 11:  tan(x)               12:  arctan(x)                    |" << endl;
	cout << "|                   Attention: Only a Number x is allowed                     |" << endl;
	cout << "| The calculator supports four operations with symbolic priorty and variables |" << endl;
	cout << "|                Also, calculate with some functions is OK!                   |" << endl;
	cout << "|   For example: Input are x=6 y=4 5+x*(y-5.4/2)+factorial(3) in three lines  |" << endl;
	cout << "|                      The Output will be 18.8                                |" << endl;
	cout << "|                    There are some special instructions:                     |" << endl;
	cout << "|                1.-h  or -help     (to get help messages)                    |" << endl;
	cout << "|                2.-v  or -version  (to get the calculator version)           |" << endl;
	cout << "|                3.-hs or -history  (to get the input history)                |" << endl;
	cout << "|                4.-r  or -refresh  (to clear the screen)                     |" << endl;
	cout << "|                5.-vb or -variable (to get the variables list input)         |" << endl;
	cout << "|                6.-i  or -initial  (to initial the calculator)               |" << endl;
	cout << "|                7.-q  or -quit     (to quit the calculator)                  |" << endl;
	cout << "|                       Good luck with your use!                              |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                      MyCalculator version-1.0.0                             |" << endl;
	cout << "|                       Implemented by Li Boyan                               |" << endl;
	cout << "|                      Student Number : 11912914                              |" << endl;
	cout << "|_____________________________________________________________________________|" << endl;
	cout << endl;
}

void MyCalculator::quit() {
	cout << "Thank you for your use!" << endl;
	system("pause");
	exit(0);
}

void MyCalculator::refresh() {
	system("cls");
}

void MyCalculator::run(const string& s) {
	if (s == "-version" || s == "-v")
	{
		versionMessage();
	}
	else if (s == "-h" || s == "-help")
	{
		helpMessage();
	}
	else if (s == "-q" || s == "-quit") {
		quit();
	}
	else if (s == "-r" || s == "-refresh")
	{
		refresh();
	}
	else if (s == "-hs" || s == "-history")
	{
		historyMessage();
	}
	else if (s == "-i" || s == "-initial")
	{
		initial();
	}
	else if (s == "-vb" || s == "-variable")
	{
		variableMessage();
	}
	else {
		history.push_back(s);
		calculate(s);
	}
	
	
	
}