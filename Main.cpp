#include <iostream>
using namespace std;

#include "MyCalculator.cpp"

string s;

int main() {
	MyCalculator cal;
	cal.welcomeMessage();
	while (true)
	{
		cin >> s;
		cal.run(s);
	}
	return 0;
}