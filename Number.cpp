#include <iostream>
#include <string>
#include <stack>
using namespace std;
#include "Number.h"

//高精度浮点数模板Number类来源：https://blog.csdn.net/mkr67n/article/details/105219135



int Number::digits1[101];
int Number::digits2[101];
int Number::digitsR[101];


Number::Number() {
	constructNumber("0");
}

Number::Number(const string& inputString)
{
	constructNumber(inputString);
}

Number::Number(const int& inputNumber)
{
	string tempString = to_string(inputNumber);
	constructNumber(tempString);
}

Number::Number(const long long int& inputNumber)
{
	string tempString = to_string(inputNumber);
	constructNumber(tempString);
}

Number::Number(const double& inputNumber)
{
	string tempString = to_string(inputNumber);
	constructNumber(tempString);
}

Number::Number(int resultSign, int resultLength, int resultInteger, int resultDecimal, string resultString)
{
	if (length == 1 && resultString[0] == '0')
		sign = 1;
	else
		sign = resultSign;
	length = resultLength;
	integer = resultInteger;
	decimal = resultDecimal;
	numString = resultString;

}

string Number::GetFullNumber()
{
	string outString;
	if (sign == -1)
	{
		outString += "-";

	}
	for (int i = 0; i < length; i++)
	{
		if (i == length - decimal)
		{
			if (i != 0)
				outString += ".";
			else
				outString += "0.";
		}
		outString += numString[i];

	}
	return outString;
}

Number Number::operator + (const Number& addend)
{
	additionSort(addend);

	int resultSign;
	int resultLength;
	int resultDecimal;
	string resultString;

	int addIndex;
	int loopTime;

	resultDecimal = decimal > addend.decimal ? decimal : addend.decimal;//先取两者最大
	loopTime = (integer > addend.integer ? integer : addend.integer) + resultDecimal;//最大小数+最大整数
	resultLength = loopTime + 1;//先取足够大

	resetDigitsR(resultLength);

	if (sign == addend.sign)
	{
		for (int i = 1; i <= loopTime; i++)
		{
			digitsR[i] += digits1[i] + digits2[i];
			digitsR[i + 1] += digitsR[i] / 10;
			digitsR[i] = digitsR[i] % 10;
		}
		resultSign = sign;
	}
	else
	{
		switch (absCompareB(addend))
		{
		case 1:
			for (int i = 1; i <= loopTime; i++)
			{
				if (digits1[i] + digitsR[i] >= digits2[i])
					digitsR[i] += digits1[i] - digits2[i];
				else
				{
					digitsR[i + 1]--;
					digitsR[i] += 10 + digits1[i] - digits2[i];
				}
			}
			resultSign = sign;
			break;
		case 0:
			digitsR[1] = 0;
			resultLength = 1;
			resultSign = 1;
		case -1:
			for (int i = 1; i <= loopTime; i++)
			{
				if (digits2[i] + digitsR[i] >= digits1[i])
					digitsR[i] += digits2[i] - digits1[i];
				else
				{
					digitsR[i + 1]--;
					digitsR[i] += 10 + digits2[i] - digits1[i];
				}
			}
			resultSign = addend.sign;
			break;
		}

	}

	addIndex = calibrateResultLength(resultLength, resultDecimal);//修正录入位置
	for (int i = resultLength + addIndex; i >= 1 + addIndex; i--)
	{
		resultString += (char)(digitsR[i] + '0');
	}

	return Number(resultSign, resultLength, resultLength - resultDecimal, resultDecimal, resultString);
}

Number Number::operator - (const Number& subtractor)
{
	additionSort(subtractor);

	int resultSign;
	int resultLength;
	int resultDecimal;
	string resultString;

	int addIndex;
	int loopTime;

	resultDecimal = decimal > subtractor.decimal ? decimal : subtractor.decimal;//先取两者最大
	loopTime = (integer > subtractor.integer ? integer : subtractor.integer) + resultDecimal;//最大小数+最大整数
	resultLength = loopTime + 1;//先取足够大

	resetDigitsR(resultLength);

	if (sign != subtractor.sign)
	{
		for (int i = 1; i <= loopTime; i++)
		{
			digitsR[i] += digits1[i] + digits2[i];
			digitsR[i + 1] += digitsR[i] / 10;
			digitsR[i] = digitsR[i] % 10;
		}
		resultSign = sign;
	}
	else
	{
		switch (absCompareB(subtractor))
		{
		case 1:
			for (int i = 1; i <= loopTime; i++)
			{
				if (digits1[i] + digitsR[i] >= digits2[i])
					digitsR[i] += digits1[i] - digits2[i];
				else
				{
					digitsR[i + 1]--;
					digitsR[i] += 10 + digits1[i] - digits2[i];
				}
			}
			resultSign = sign;
			break;
		case 0:
			digitsR[1] = 0;
			resultLength = 1;
			resultSign = 1;
			break;
		case -1:
			for (int i = 1; i <= loopTime; i++)
			{
				if (digits2[i] + digitsR[i] >= digits1[i])
					digitsR[i] += digits2[i] - digits1[i];
				else
				{
					digitsR[i + 1]--;
					digitsR[i] += 10 + digits2[i] - digits1[i];
				}
			}
			resultSign = -sign;
			break;
		}
	}

	addIndex = calibrateResultLength(resultLength, resultDecimal);//修正录入位置
	for (int i = resultLength + addIndex; i >= 1 + addIndex; i--)
	{
		resultString += (char)(digitsR[i] + '0');
	}

	return Number(resultSign, resultLength, resultLength - resultDecimal, resultDecimal, resultString);
}

Number Number::operator * (const Number& factor)
{
	multiplicationSort(factor);

	int resultSign;
	int resultLength;
	int resultDecimal;
	string resultString;

	int addIndex;
	resultDecimal = decimal + factor.decimal;//两者相加
	resultLength = length + factor.length;//先取足够大

	resetDigitsR(resultLength);

	for (int secondDigit = 1; secondDigit <= factor.length; secondDigit++)//遍历到竖式的第二个数
	{
		for (int firstDigit = 1; firstDigit <= length; firstDigit++)//遍历到竖式的第一个数
		{
			//模拟竖式中的某两位数相乘
			digitsR[firstDigit + secondDigit - 1] += digits1[firstDigit] * digits2[secondDigit];
			//处理进位
			digitsR[firstDigit + secondDigit] += digitsR[firstDigit + secondDigit - 1] / 10;
			digitsR[firstDigit + secondDigit - 1] = digitsR[firstDigit + secondDigit - 1] % 10;
		}
	}

	resultSign = sign * factor.sign;

	addIndex = calibrateResultLength(resultLength, resultDecimal);//修正录入位置
	for (int i = resultLength + addIndex; i >= 1 + addIndex; i--)
	{
		resultString += (char)(digitsR[i] + '0');
	}

	return Number(resultSign, resultLength, resultLength - resultDecimal, resultDecimal, resultString);
}

Number Number::operator / (const Number& divisor)
{
	divisionSort(divisor);

	int resultSign;
	int resultLength;
	int resultDecimal;
	string resultString;

	bool canSub;
	int addStartIndex;
	int tempIntLength;

	int checkPointFront = 1;//当前试商时被除数的最前检查点
	int checkPointTrail = divisor.length;//当前试商时被除数的最后检查点
	int divisorcheckTrail;//记录试商时除数的最后检查点
	//校正纯小数数字的检查点
	if (divisor.length == divisor.decimal)
	{
		for (int i = 0; i < divisor.length; i++)
			if (divisor.numString[i] == '0')
				checkPointTrail--;
			else
				break;
	}
	divisorcheckTrail = checkPointTrail;

	resetDigitsR(sizeof(digitsR) / sizeof(int) - 1);

	for (checkPointTrail; checkPointTrail <= 100; checkPointFront++, checkPointTrail++)
	{
		while (1)
		{
			canSub = true;
			//判断是否能够进行减法试商（够不够减）
			if (digits1[checkPointFront - 1] == 0)
			{
				//看看够不够减
				for (int i = checkPointFront, j = 1; i <= checkPointTrail; i++, j++)
				{
					//过滤掉大于的情况
					if (digits1[i] > digits2[j])
					{
						break;
					}
					//如果执行到这一句，唯一的情况就是前一位等于，且这一位小于，因此整体值为小于，不能减
					if (digits1[i] < digits2[j])
					{
						canSub = false;
						break;
					}
				}
			}
			if (canSub)
			{
				for (int i = checkPointTrail, j = divisorcheckTrail; j > 0; i--, j--)
				{
					if (digits1[i] >= digits2[j])
						digits1[i] -= digits2[j];
					else
					{
						//否则进行借位减法
						digits1[i - 1]--;
						digits1[i] = 10 + digits1[i] - digits2[j];
					}
				}
				digitsR[checkPointTrail]++;
			}
			else
			{
				break;
			}
		}
	}
	checkPointTrail--;

	tempIntLength = integer + divisor.decimal;
	resultDecimal = checkPointTrail - tempIntLength;
	resultLength = resultDecimal + tempIntLength;

	resultSign = sign * divisor.sign;

	addStartIndex = calibrateResultLengthD(resultLength, resultDecimal);//修正录入位置
	for (int i = 1 + addStartIndex; i <= resultLength + addStartIndex; i++)
	{
		resultString += (char)(digitsR[i] + '0');
	}

	return Number(resultSign, resultLength, resultLength - resultDecimal, resultDecimal, resultString);
}

void Number::constructNumber(const string& inputString)
	{
		bool decimalCount = false;
		bool frontZero = true;
		int checkLength = length = inputString.length();

		int i = 0;
		//去除正负号
		if (inputString[i] == '-')
		{
			sign = -1;
			length--;
			i++;
		}
		//去除前导0
		for (i; i < checkLength; i++)
		{
			if (inputString[i] == '0')
				length--;
			else
				break;
		}
		//其它数字录入
		for (i; i < checkLength; i++)
		{
			if (decimalCount)
			{
				decimal++;
			}
			if (inputString[i] == '.')
			{
				decimalCount = true;
				length--;
				//缩短检测次数来避免录入小数的末尾0
				for (checkLength; checkLength > i; checkLength--)
				{
					if (inputString[checkLength - 1] == '0')
						length--;
					else
						break;
				}

			}
			else
			{
				numString += inputString[i];
			}
		}
		integer = length - decimal;
	}

int Number::absCompareB(const Number& b)
	{
		if (integer > b.integer)
			return 1;
		else if (integer < b.integer)
			return -1;
		else if (numString > b.numString)
			return 1;
		else if (numString == b.numString)
			return 0;
		else
			return -1;
	}

int Number::calibrateResultLength(int& length, int& decimal)
	{
		int deleteZero = 0;
		//整数部分排除前导0
		for (int i = 0; length > decimal; i++)
		{
			if (digitsR[length] == 0)
				length--;
			else
				break;
		}
		//小数部分排除后导0
		for (int i = 1; decimal != 0; i++)
		{
			if (digitsR[i] == 0)
			{
				decimal--;
				length--;
				deleteZero++;
			}
			else
				break;
		}
		if (0 == length)
		{
			length++;
		}
		return deleteZero;
	}

int Number::calibrateResultLengthD(int& length, int& decimal)
	{
		int deleteZero = 0;
		//小数部分排除后导0
		for (int i = 1; decimal != 0; i++)
		{
			if (digitsR[length] == 0)
			{
				decimal--;
				length--;
			}
			else
				break;
		}
		//整数部分排除前导0
		for (int i = 0; length > decimal; i++)
		{
			if (digitsR[i + 1] == 0)
			{
				length--;
				deleteZero++;
			}
			else
				break;
		}
		if (0 == length)
		{
			length++;
		}
		return deleteZero;
	}

void Number::resetDigitsR(int length)
	{
		for (int i = 1; i <= length; i++)
		{
			digitsR[i] = 0;
		}
	}

void Number::additionSort(const Number& otherNumber)
	{
		//i1,i2记录导入数据的起始位置
		int i1 = 1, i2 = 1;
		if (decimal > otherNumber.decimal)
		{
			i2 += decimal - otherNumber.decimal;
			//第二个数组某些可能用到的元素需要用0赋值
			for (int i = 1; i < i2; i++)
			{
				digits2[i] = 0;
			}
		}
		else if (decimal < otherNumber.decimal)
		{
			i1 += otherNumber.decimal - decimal;
			//第一个数组某些可能用到的元素需要用0赋值
			for (int i = 1; i < i1; i++)
			{
				digits1[i] = 0;
			}
		}
		//对数组重新赋值
		for (int j = 1; j <= length; i1++, j++)
		{
			digits1[i1] = numString[length - j] - '0';
		}
		for (int j = 1; j <= otherNumber.length; i2++, j++)
		{
			digits2[i2] = otherNumber.numString[otherNumber.length - j] - '0';
		}
		for (i1; i1 <= i2; i1++)
		{
			digits1[i1] = 0;
		}
		for (i2; i2 <= i1; i2++)
		{
			digits2[i2] = 0;
		}
	}

void Number::multiplicationSort(const Number& otherNumber)
	{
		for (int i = 1; i <= length; i++)
		{
			digits1[i] = numString[length - i] - '0';
		}
		for (int i = 1; i <= otherNumber.length; i++)
		{
			digits2[i] = otherNumber.numString[otherNumber.length - i] - '0';
		}
	}

void Number::divisionSort(const Number& otherNumber)
	{
		int arrayLength = sizeof(digits1) / sizeof(int) - 1;
		for (int i = 1; i <= arrayLength; i++)
		{
			if (i <= length)
				digits1[i] = numString[i - 1] - '0';
			else
				digits1[i] = 0;
		}
		//处理除数
		int j = 1;
		if (otherNumber.length == 0)
		{
			digits2[1] = 1;
		}
		else
		{
			//去除除数的前导0
			for (j; j <= otherNumber.length; j++)
			{
				if (otherNumber.numString[j - 1] != '0')
					break;
			}
		}
		for (int i = 1; j <= otherNumber.length; i++, j++)
		{
			digits2[i] = otherNumber.numString[j - 1] - '0';
		}

	}

bool Number::operator < (const Number& b) const {
	if (sign < b.sign)
	{
		return true;
	}
	else if (sign > b.sign)
	{
		return false;
	}
	else if (sign == 1)
	{
		if (integer > b.integer)
			return false;
		else if (integer < b.integer)
			return true;
		else if (numString > b.numString)
			return false;
		else if (numString == b.numString)
			return false;
		else
			return true;
	} 
}

bool Number::operator > (const Number& b) const {
	return b < *this;
}


bool Number::operator <= (const Number& b) const {
	return !(b < *this);
}

bool Number::operator >= (const Number& b) const {
	return !(*this < b);
}

bool Number::operator == (const Number& b) const {
	return !(b < *this) && !(b > * this);
}

bool Number::operator != (const Number& b) const {
	return b < *this || b > * this;
}
