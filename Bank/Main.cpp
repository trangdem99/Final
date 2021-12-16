#include <iostream>

using namespace std;

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
	const float max = 10000000.00;// 10.000.000
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