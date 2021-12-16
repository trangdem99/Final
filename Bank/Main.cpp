#include <iostream>

using namespace std;

class Number {
private:
	string num;
public:
	Number() {
		this->num = "0.0";
	}

	~Number() { }

	Number(string num) {
		this->num = (numCheck(num) == true ? numFormat(num) : "0.0");
	}

	string numFormat(string num) {
		string result = "";

		for (int i = 0; i < num.length(); i++)
			if ((result.length() == 0 && (num[i] != '0' || num[i] != '+')) || result.length() > 0)
				result += num[i];

		return result;
	}

	bool numCheck(string num) {
		if ((num[0] >= '0' && num[0] <= '9') || num[0] == '+' || num[0] == '.') {
			int dotFlag = (num[0] == '.' ? 1 : 0);

			for (int i = 0; i < num.length(); i++) {
				if (num[i] == '.')
					if (dotFlag == 0)
						dotFlag == 1;
					else
						return false;
				else if (num[0] < '0' || num[0] > '9')
					return false;
			}

			return true;
		}

		return false;
	}

	friend bool operator<=(const Number& num1, const Number& num2) {
		int dotPos1 = 0, dotPos2 = 0;

		for (int i = 0; i < num1.num.length(); i++)
			if (num1.num[i] == '.') {
				dotPos1 = i; 
				break;
			}

		for (int i = 0; i < num2.num.length(); i++)
			if (num2.num[i] == '.') {
				dotPos2 = i;
				break;
			}

		if (dotPos1 > dotPos2)
			return false;
		else if (dotPos1 < dotPos2)
			return true;
			
		for (int i = 0; i < dotPos1; i++) {
			if (num1.num[i] > num2.num[i])
				return false;
			else if (num1.num[i] < num2.num[i])
				return true;
		}

		int temp = (num1.num.length() - dotPos1 > num2.num.length() - dotPos2 ? num1.num.length() - dotPos1 : num2.num.length() - dotPos2);

		for (int i = dotPos1; i < dotPos1 + temp; i++) {
			char a, b;

			if (i > num1.num.length() - 1) {
				a = '0';
				b = num2.num[i];
			}
			else if (i > num2.num.length() - 1) {
				a = num1.num[i];
				b = '0';
			}
			else {
				a = num1.num[i];
				b = num2.num[i];
			}

			if (a > b)
				return false;
			else if (a < b)
				return true;
		}

		return true;
	}
};

class Handler {
private: 
	Handler* handler;
public:
	Handler(Handler* handler) {
		this->handler = handler;
	}

	virtual void process(Number* amount) {
		if (this->handler != NULL)
			this->handler->process(amount);
	}
};

class Online : public Handler {
private:
	const Number* max = new Number("10000000.00"); // 10,000,000
public:
	Online(Handler* handler) : Handler(handler) { }

	~Online() {	}

	void process(Number* amount) {
		if (*amount <= *this->max)
			cout << "Online Handler is processing this transfer ===> Money transfer" << endl;
		else {
			cout << "Online Handler can not process this transfer. Sending this request to Branch Handler ===> Request sent" << endl;
			Handler::process(amount);
		}
	}
};

class Branch : public Handler {
private:
	const Number* max = new Number("1000000000.00"); // 1,000,000,000
public:
	Branch(Handler* handler) : Handler(handler) { }

	~Branch() {	}

	void process(Number* amount) {
		if (*amount <= *this->max)
			cout << "Branch Handler is processing this transfer ===> Money transfer" << endl;
		else {
			cout << "Brank Handler can not process this transfer. Sending this request to Headquarter Handler ===> Request sent" << endl;
			Handler::process(amount);
		}
	}
};

class Headquarter : public Handler {

public:
	Headquarter(Handler* handler) : Handler(handler) { }

	~Headquarter() { }

	void process(Number* amount) {
		cout << "Headquarter Handler is processing this transfer ===> Money transfer" << endl;
	}
};

class Chain {
private:
	Handler* chain;
public:
	Chain() {
		this->chain = new Online(new Branch(new Headquarter(NULL)));
	}
	~Chain(){
		delete[]chain;
	}
	void process(Number* amount) {
		this->chain->process(amount);
	}
};

int main() {
	Chain* chain = new Chain();

	chain->process(new Number("1000000000.00001"));

	return 0;
}