#pragma once
#include <iostream>
#include <string>
using namespace std;
//�߾��ȸ��������ģ��Number����Դ��https://blog.csdn.net/mkr67n/article/details/105219135
//������ģ������ʵ�ֵĺ����У�
class Number
{
public:
	//��������
	static int digits1[101];
	static int digits2[101];
	static int digitsR[101];
	//��������
	int sign = 1;
	int length = 0;
	int integer = 0;
	int decimal = 0;
	string numString;//�����޷��ŵ����֣�ͬʱȥ��ǰ��0�ͺ�0��������С��λ����Ч0��

	Number();

	Number(const string& inputString);

	Number(const int& inputNumber);
	

	Number(const long long int& inputNumber);
	
	//����ֻ�д��6λ��̫���ĸ�����Ӧ���ַ���¼��
	Number(const double& inputNumber);
	
	//������������Number�����죬������-0������
	Number(int resultSign, int resultLength, int resultInteger, int resultDecimal, string resultString);

	//���ڻ�ȡ�����������ַ���ֵ
	string GetFullNumber();

	Number operator + (const Number& addend);

	Number operator - (const Number& subtractor);

	Number operator * (const Number& factor);

	Number operator / (const Number& divisor);

	//������ģ�������ʵ�ֵ��º�����
	bool operator < (const Number& b) const;
	bool operator > (const Number& b) const;
	bool operator <= (const Number& b) const;
	bool operator >= (const Number& b) const;
	bool operator == (const Number& b) const;
	bool operator != (const Number& b) const;




private:
	//���ڹ��캯����
	void constructNumber(const string& inputString);

	//�����־���ֵ�Ƚ�
	int absCompareB(const Number& b);

	//���ڼӼ��ˣ�У׼��������е�ǰ��0��0�����ĳ���Ӱ�죬����ɾ���ĺ�0����
	int calibrateResultLength(int& length, int& decimal);

	//���ڳ���У׼��������е�ǰ��0��0�����ĳ���Ӱ�죬����ɾ����ǰ��0����
	int calibrateResultLengthD(int& length, int& decimal);

	//�ѽ������ǰn��λ������Ϊ0
	void resetDigitsR(int length);

	void additionSort(const Number& otherNumber);

	void multiplicationSort(const Number& otherNumber);

	void divisionSort(const Number& otherNumber);


};
