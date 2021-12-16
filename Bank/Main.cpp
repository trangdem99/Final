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
		this->num = num;
	}

	bool numCheck() {
		if ((this->num[0] >= '0' && this->num[0] <= '9') || this->num[0] == '-' || this->num[0] == '+' || this->num[0] == '.') {
			int dotFlag = (this->num[0] == '.' ? 1 : 0);

			for (int i = 0; i < this->num.length(); i++) {
				if (this->num[i] == '.')
					if (dotFlag == 0)
						dotFlag == 1;
					else
						return false;
				else if (this->num[0] < '0' || this->num[0] > '9')
					return false;
			}

			return true;
		}

		return false;
	}

	friend bool operator>=(const Number& num1, const Number& num2) {
		if (num1.num[0] == '+' && num2.num[0] == '-')
			return true;
		else if (num1.num[0] == '-' && num2.num[0] == '+')
			return false;
		else {
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
				return true;
			else if (dotPos1 < dotPos2)
				return false;
			
			for (int i = 0; i < dotPos1; i++) {
				if (num1.num[i] > num2.num[i])
					return true;
				else if (num1.num[i] < num2.num[i])
					return false;
			}

			int temp = (dotPos1 - num1.num.length() > dotPos2 - num2.num.length() ? dotPos1 - num1.num.length() : dotPos2 - num2.num.length());

			for (int i = dotPos1; i < temp; i++) {
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
					return true;
				else if (a < b)
					return false;
			}
		}

		return true;
	}
};

class Processor {
private: 
	Processor* processor;
public:
	Processor(Processor* processor) {
		this->processor = processor;
	}
	virtual void process(float amount) {
		if (this->processor != NULL)
			this->processor->process(amount);
	}
};

class Online : public Processor {
private:
	const float max = 10000000.00;// 10,000,000
public:
	Online(Processor* processor) : Processor(processor) { }
	~Online() {	}
	void process(float amount) {
		if (amount <= this->max)
			cout << "Online Processor is processing this transfer ===> Money transfer" << endl;
		else {
			cout << "Online Processor can not process this transfer. Sending this request to Branch Processor ===> Request sent" << endl;
			Processor::process(amount);
		}
	}
};

class Branch : public Processor {
private:
	const float max = 1000000000.00;// 1.000.000.000
public:
	Branch(Processor* processor) : Processor(processor) { }
	~Branch() {	}
	void process(float amount) {
		if (amount <= this->max)
			cout << "Branch Processor is processing this transfer ===> Money transfer" << endl;
		else {
			cout << "Brank Processor can not process this transfer. Sending this request to Headquarter Processor ===> Request sent" << endl;
			Processor::process(amount);
		}
	}
};

class Headquarter : public Processor {
private:
	const float min = 1000000000.00;// 1.000.000.000
public:
	Headquarter(Processor* processor) : Processor(processor) { }
	~Headquarter() { }
	void process(float amount) {
		if (amount > this->min)
			cout << "Headquarter Processor is processing this transfer ===> Money transfer" << endl;
		else
			cout << "Something went wrong here" << endl;
	}
};

class Chain {
private:
	Processor* chain;
public:
	Chain() {
		this->chain = new Online(new Branch(new Headquarter(NULL)));
	}
	~Chain(){
		delete[]chain;
	}
	void process(float amount) {
		this->chain->process(amount);
	}
};

int main() {
	Chain* chain = new Chain();

	chain->process(999999999.99);

	return 0;
}