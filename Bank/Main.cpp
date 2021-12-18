#include <iostream>
#include <string>

using namespace std;

/* function PhepCong, PhepTru, PhepNhan coded by H.T.Nguyen*/
string PhepCong(string s1, string s2, int dotPos) {
	string temp = "", result = "";
	int length1 = s1.length() - 1, length2 = s2.length() - 1;
	int ultra = 0;

	while (length1 >= 0 && length2 >= 0) {
		if (s1[length1] != '.' && s2[length2] != '.') {
			temp += to_string(((s1[length1] - '0') + (s2[length2] - '0') + ultra) % 10);
			ultra = ((s1[length1] - '0') + (s2[length2] - '0') + ultra) / 10;
		}
		length1--, length2--;
	}

	while (length1 >= 0) {
		if (s1[length1] != '.') {
			temp += to_string(((s1[length1] - '0') + ultra) % 10);
			ultra = ((s1[length1] - '0') + ultra) / 10;
		}
		length1--;
	}

	while (length2 >= 0) {
		if (s2[length2] != '.') {
			temp += to_string(((s2[length2] - '0') + ultra) % 10);
			ultra = ((s1[length2] - '0') + ultra) / 10;
		}
		length2--;
	}

	temp += (ultra != 0) ? to_string(ultra) : "";

	for (int i = temp.length() - 1; i >= 0; i--) {
		if (i == temp.length() - dotPos && dotPos != 0)
			result += '.';

		result += temp[i];
	}

	return result;
}

string PhepTru(string s1, string s2, int dotPos) {
	string temp = "", result = "";
	int length1 = s1.length() - 1, length2 = s2.length() - 1;
	int ultra = 0;

	while (length1 >= 0 && length2 >= 0) {
		if (s1[length1] != '.' && s2[length2] != '.') {
			temp += to_string(((s1[length1] - '0') - (s2[length2] - '0') - ultra) < 0 ? (10 + (s1[length1] - '0') - (s2[length2] - '0') - ultra) : ((s1[length1] - '0') - (s2[length2] - '0') - ultra));
			ultra = (((s1[length1] - '0') - (s2[length2] - '0') - ultra) < 0) ? 1 : 0;
		}
		length1--, length2--;
	}

	while (length1 >= 0) {
		if (s1[length1] != '.') {
			temp += to_string(((s1[length1] - '0') - ultra) < 0 ? (10 + (s1[length1] - '0') - ultra) : ((s1[length1] - '0') - ultra));
			ultra = (((s1[length1] - '0') - ultra) < 0) ? 1 : 0;
		}
		length1--;
	}

	while (length2 >= 0) {
		if (s2[length2] != '.') {
			temp += to_string(((s2[length2] - '0') - ultra) < 0 ? (10 + (s2[length2] - '0') - ultra) : ((s2[length2] - '0') - ultra));
			ultra = (((s2[length2] - '0') - ultra) < 0) ? 1 : 0;
		}
		length2--;
	}

	temp += (ultra == 1) ? to_string(ultra) : "";

	int flag = 0;

	for (int i = temp.length() - 1; i >= 0; i--) {
		if (i == temp.length() - dotPos && dotPos != 0)
			result += '.';

		if (flag == 1)
			result += temp[i];
		else if (temp[i] != '0') {
			result += temp[i];
			flag = 1;
		}
	}

	return (flag == 0 ? "0.0" : result);
}
/* function PhepCong, PhepTru, PhepNhan coded by H.T.Nguyen*/

int getDotPos(string s) {
	int result = 0;

	for (int i = 0; i < s.length(); i++, result++)
		if (s[i] == '.')
			break;

	return result;
}

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

	void setNum(string num) {
		this->num = num;
	}

	string getNum() {
		return this->num;
	}
	string numFormat(string num) {
		string result = "";

		for (int i = 0; i < num.length(); i++)
			if ((result.length() == 0 && (num[i] != '0' || num[i] != '+')) || result.length() > 0)
				result += num[i];

		if (result[0] == '.')
			result = "0" + result;
		else if (result.length() == 1 && result[0] != '.')
			result = result + ".0";

		return result;
	}
	
	bool numCheck(string num) {
		if ((num[0] >= '0' && num[0] <= '9') || num[0] == '+' || num[0] == '.') {
			int dotFlag = (num[0] == '.' ? 1 : 0);

			for (int i = 0; i < num.length(); i++) {
				if (num[i] == '.')
					if (dotFlag == 0)
						dotFlag = 1;
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
		int dotPos1 = getDotPos(num1.num), dotPos2 = getDotPos(num2.num);

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
			char a = (i < num1.num.length()) ? '0' : num1.num[i];
			char b = (i < num2.num.length()) ? '0' : num2.num[i];

			if (a > b)
				return false;
			else if (a < b)
				return true;
		}

		return true;
	}
};

class BankAccount {
private: 
	string id;
	string name;
	Number* balance;
public:
	BankAccount() {
		this->id = "";
		this->name = "";
		this->balance = new Number;
	}
	BankAccount(string id, string name, Number* balance) {
		this->id = id;
		this->name = name;
		this->balance = balance;
	}
	~BankAccount() { }

	Number* getBalance() {
		return this->balance;
	}

	void editBalance(Number* amount, string action) {
		string fromNum = this->balance->getNum(), toNum = amount->getNum();
		
		int dotPos1 = getDotPos(fromNum), dotPos2 = getDotPos(toNum);
		int dotPos;
		int length1 = fromNum.length(), length2 = toNum.length();
		
		// 234.56 - 12.345 -> 234.560 - 12.345
		if (length1 - dotPos1 > length2 - dotPos2) {
			dotPos = fromNum.length() - dotPos1;

			for (int i = 0; i < dotPos - (length2 - dotPos2); i++)
				toNum += "0";
		}
		else {
			dotPos = toNum.length() - dotPos2;

			for (int i = 0; i < dotPos - (length1 - dotPos1); i++)
				fromNum += "0";
		}

		if (action == "add")
			this->balance->setNum(PhepCong(fromNum, toNum, dotPos));
		else if (action == "subtract")
			this->balance->setNum(PhepTru(fromNum, toNum, dotPos));
	}
	void showDetail() {
		cout << "Id: " << this->id << ", Name: " << this->name << ", Amount: " << this->balance->getNum() << "." << endl;
	}
};


class Handler {
private: 
	Handler* handler;
public:
	Handler(Handler* handler) {
		this->handler = handler;
	}

	virtual void process(BankAccount* fromAccount, BankAccount* toAccount, Number* amount) {
		if (this->handler != NULL)
			this->handler->process(fromAccount, toAccount, amount);
	}
};

class Online : public Handler {
private:
	const Number* max = new Number("10000000.00"); // 10,000,000
public:
	Online(Handler* handler) : Handler(handler) { }
	~Online() {	}

	void process(BankAccount* fromAccount, BankAccount* toAccount, Number* amount) {
		if (*amount <= *this->max) {
			fromAccount->editBalance(amount, "subtract");
			toAccount->editBalance(amount, "add");
			cout << "Online Handler is processing this transfer ===> Money transfer" << endl << endl << endl;
			fromAccount->showDetail();
			toAccount->showDetail();
		}
		else {
			cout << "Online Handler can not process this transfer. Sending this request to Branch Handler ===> Request sent" << endl;
			Handler::process(fromAccount, toAccount, amount);
		}
	}
};

class Branch : public Handler {
private:
	const Number* max = new Number("1000000000.00"); // 1,000,000,000
public:
	Branch(Handler* handler) : Handler(handler) { }
	~Branch() {	}

	void process(BankAccount* fromAccount, BankAccount* toAccount, Number* amount) {
		if (*amount <= *this->max) {
			fromAccount->editBalance(amount, "subtract");
			toAccount->editBalance(amount, "add");
			cout << "Branch Handler is processing this transfer ===> Money transfer" << endl << endl << endl;
			fromAccount->showDetail();
			toAccount->showDetail();
		}
		else {
			cout << "Brank Handler can not process this transfer. Sending this request to Headquarter Handler ===> Request sent" << endl;
			Handler::process(fromAccount, toAccount, amount);
		}
	}
};

class Headquarter : public Handler {
private:
	const Number* max = new Number("1000000000000.00"); // 1,000,000,000,000
public:
	Headquarter(Handler* handler) : Handler(handler) { }
	~Headquarter() { }

	void process(BankAccount* fromAccount, BankAccount* toAccount, Number* amount) {
		if (*amount <= *this->max) {
			fromAccount->editBalance(amount, "subtract");
			toAccount->editBalance(amount, "add");
			cout << "Headquarter Handler is processing this transfer ===> Money transfer" << endl << endl << endl;
			fromAccount->showDetail();
			toAccount->showDetail();
		}
		else
			cout << "No Handler have enough fund to process this transfer ===> Money not transfer" << endl;
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

	void process(BankAccount* fromAccount, BankAccount* toAccount, Number* amount) {
		if (*amount <= *fromAccount->getBalance())
			this->chain->process(fromAccount, toAccount, amount);
		else
			cout << "Insufficient fund for this transfer. Plese reduce the amount or deposit more fund" << endl;
	}
};

int main() {
	// Set up db
	Chain* chain = new Chain();
	BankAccount* test1 = new BankAccount("1", "Nguyen Van A", new Number("234.56"));
	BankAccount* test2 = new BankAccount("2", "Tran Thi B", new Number("0"));

	while (true) {
		int Mode;
		string temp = "0";

		cout << "============DEMO PROGRAM FOR CHAIN OF RESPONSIBILITY============" << endl;
		cout << endl << endl;
		cout << "Transfer fund from BankAccount test1 to BankAccount test2" << endl;
		cout << "Bank account test 1: "; test1->showDetail();
		cout << "Bank account test 2: "; test2->showDetail();
		cout << endl;
		cout << "Enter amount you want to transfer: "; getline(cin >> ws, temp, '\n');
		chain->process(test1, test2, new Number(temp));

		system("pause");
		system("cls");

		cout << "Do you want to transfer again? (Press 1 to continue, Press another to exit): "; cin >> Mode;
		system("cls");

		if (Mode != 1)
			break;
	}

	cout << "Thanks for using this program. Have a nice. Welcome back!!!" << endl;


	return 0;
}