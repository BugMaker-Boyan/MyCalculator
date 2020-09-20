#include <iostream>
#include <string>
#include <stack>
using namespace std;
#include "Number.h"

//�߾��ȸ�����ģ��Number����Դ��https://blog.csdn.net/mkr67n/article/details/105219135



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

	resultDecimal = decimal > addend.decimal ? decimal : addend.decimal;//��ȡ�������
	loopTime = (integer > addend.integer ? integer : addend.integer) + resultDecimal;//���С��+�������
	resultLength = loopTime + 1;//��ȡ�㹻��

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

	addIndex = calibrateResultLength(resultLength, resultDecimal);//����¼��λ��
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

	resultDecimal = decimal > subtractor.decimal ? decimal : subtractor.decimal;//��ȡ�������
	loopTime = (integer > subtractor.integer ? integer : subtractor.integer) + resultDecimal;//���С��+�������
	resultLength = loopTime + 1;//��ȡ�㹻��

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

	addIndex = calibrateResultLength(resultLength, resultDecimal);//����¼��λ��
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
	resultDecimal = decimal + factor.decimal;//�������
	resultLength = length + factor.length;//��ȡ�㹻��

	resetDigitsR(resultLength);

	for (int secondDigit = 1; secondDigit <= factor.length; secondDigit++)//��������ʽ�ĵڶ�����
	{
		for (int firstDigit = 1; firstDigit <= length; firstDigit++)//��������ʽ�ĵ�һ����
		{
			//ģ����ʽ�е�ĳ��λ�����
			digitsR[firstDigit + secondDigit - 1] += digits1[firstDigit] * digits2[secondDigit];
			//�����λ
			digitsR[firstDigit + secondDigit] += digitsR[firstDigit + secondDigit - 1] / 10;
			digitsR[firstDigit + secondDigit - 1] = digitsR[firstDigit + secondDigit - 1] % 10;
		}
	}

	resultSign = sign * factor.sign;

	addIndex = calibrateResultLength(resultLength, resultDecimal);//����¼��λ��
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

	int checkPointFront = 1;//��ǰ����ʱ����������ǰ����
	int checkPointTrail = divisor.length;//��ǰ����ʱ��������������
	int divisorcheckTrail;//��¼����ʱ������������
	//У����С�����ֵļ���
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
			//�ж��Ƿ��ܹ����м������̣�����������
			if (digits1[checkPointFront - 1] == 0)
			{
				//������������
				for (int i = checkPointFront, j = 1; i <= checkPointTrail; i++, j++)
				{
					//���˵����ڵ����
					if (digits1[i] > digits2[j])
					{
						break;
					}
					//���ִ�е���һ�䣬Ψһ���������ǰһλ���ڣ�����һλС�ڣ��������ֵΪС�ڣ����ܼ�
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
						//������н�λ����
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

	addStartIndex = calibrateResultLengthD(resultLength, resultDecimal);//����¼��λ��
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
		//ȥ��������
		if (inputString[i] == '-')
		{
			sign = -1;
			length--;
			i++;
		}
		//ȥ��ǰ��0
		for (i; i < checkLength; i++)
		{
			if (inputString[i] == '0')
				length--;
			else
				break;
		}
		//��������¼��
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
				//���̼�����������¼��С����ĩβ0
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
		//���������ų�ǰ��0
		for (int i = 0; length > decimal; i++)
		{
			if (digitsR[length] == 0)
				length--;
			else
				break;
		}
		//С�������ų���0
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
		//С�������ų���0
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
		//���������ų�ǰ��0
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
		//i1,i2��¼�������ݵ���ʼλ��
		int i1 = 1, i2 = 1;
		if (decimal > otherNumber.decimal)
		{
			i2 += decimal - otherNumber.decimal;
			//�ڶ�������ĳЩ�����õ���Ԫ����Ҫ��0��ֵ
			for (int i = 1; i < i2; i++)
			{
				digits2[i] = 0;
			}
		}
		else if (decimal < otherNumber.decimal)
		{
			i1 += otherNumber.decimal - decimal;
			//��һ������ĳЩ�����õ���Ԫ����Ҫ��0��ֵ
			for (int i = 1; i < i1; i++)
			{
				digits1[i] = 0;
			}
		}
		//���������¸�ֵ
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
		//�������
		int j = 1;
		if (otherNumber.length == 0)
		{
			digits2[1] = 1;
		}
		else
		{
			//ȥ��������ǰ��0
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
