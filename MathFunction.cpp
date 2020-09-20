#include "MathFunction.h"

//precision 精度
const double precision = 1e-8;

Number abs(Number n) {
	if (n.GetFullNumber()=="")
	{
		Number n1(0);
		Number n2(0);
		n = n1 + n2;
	}
	n.sign = 1;
	return n;
}

Number sum(const Number nums[],const long long size) {
	Number sum(0);
	for (long long i = 0; i < size; i++)
	{
		sum = sum + nums[i];
	}
	return sum;
}

Number sqrt(Number& n) {
	//牛顿迭代求算术平方根
	if (n.GetFullNumber() == "")
	{
		//Number（0） 无法用getfullNumber输出，故用0+0表示0
		Number n1(0);
		Number n2(0);
		Number ret = n1+n2;
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double root = stod(n_str);
	while (abs(n_double - root*root)>=precision)
	{
		root = (root + n_double / root) / 2.0;
	}
	Number ret(root);
	return ret;
	
}

Number exp(Number& n) {
	if (n.GetFullNumber() == "")
	{
		Number ret(1);
		return ret;
	}
	double e = exp(1);
	Number result(1);
	for (Number i = 0; i < n; i = i + 1)
	{
		result = result * e;
	}
	return result;
}

Number ln(Number& n) {
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = log(n_double);
	Number ret(result);
	return ret;
}

Number log(Number& n, long long x) {
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = log(n_double) / log(x);
	Number ret(result);
	return ret;
}

Number factorial(Number& n) {
	if (n.GetFullNumber() == "")
	{
		Number ret(1);
		return ret;
	}
	string n_str = n.GetFullNumber();
	long long n_ll = stoll(n_str);
	long long result = 1;
	for (long long i = 1; i <= n_ll; i++)
	{
		result = result * i;
	}
	Number ret(result);
	return ret;
}

Number sin(Number& n) {
	if (n.GetFullNumber() == "")
	{
		//Number（0） 无法用getfullNumber输出，故用0+0表示0
		Number n1(0);
		Number n2(0);
		Number ret = n1 + n2;
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = sin(n_double);
	//先转string，防止出现e-10 等情况，使Number初始化失败
	string ret_str = to_string(result);
	Number ret(ret_str);
	return ret;
}

Number cos(Number& n) {
	if (n.GetFullNumber() == "")
	{
		Number ret(1);
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = cos(n_double);
	string ret_str = to_string(result);
	Number ret(ret_str);
	return ret;
}

Number tan(Number& n) {
	if (n.GetFullNumber() == "")
	{
		//Number（0） 无法用getfullNumber输出，故用0+0表示0
		Number n1(0);
		Number n2(0);
		Number ret = n1 + n2;
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = tan(n_double);
	string ret_str = to_string(result);
	Number ret(ret_str);
	return ret;
}

Number asin(Number& n) {
	if (n.GetFullNumber() == "")
	{
		//Number（0） 无法用getfullNumber输出，故用0+0表示0
		Number n1(0);
		Number n2(0);
		Number ret = n1 + n2;
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = asin(n_double);
	string ret_str = to_string(result);
	Number ret(ret_str);
	return ret;
}

Number acos(Number& n) {
	if (n.GetFullNumber() == "")
	{
		Number ret("1.5707963267949");
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = acos(n_double);
	string ret_str = to_string(result);
	Number ret(ret_str);
	return ret;
}

Number atan(Number& n) {
	if (n.GetFullNumber() == "")
	{
		//Number（0） 无法用getfullNumber输出，故用0+0表示0
		Number n1(0);
		Number n2(0);
		Number ret = n1 + n2;
		return ret;
	}
	string n_str = n.GetFullNumber();
	double n_double = stod(n_str);
	double result = atan(n_double);
	string ret_str = to_string(result);
	Number ret(ret_str);
	return ret;
}

Number pow(Number& n,long long x) {
	if (n.GetFullNumber() == "")
	{
		//Number（0） 无法用getfullNumber输出，故用0+0表示0
		Number n1(0);
		Number n2(0);
		Number ret = n1 + n2;
		return ret;
	}
	Number ret(1);
	for (long long i = 0; i < x; i++)
	{
		ret = ret * n;
	}
	return ret;
}


