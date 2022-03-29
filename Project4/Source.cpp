#include  <iostream>
#include <random>
#include <chrono>

int getRandomNumber();

class Password
{
private:
	std::string generated{};
	std::string lowerCase{};
	std::string upperCase{};
	int length{};

public:
	Password()
	{
		generated = "";
		lowerCase = "abcdefghijklmnopqrstuvwxyz";
		upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		length = 0;
	}

	int getLowerCase(int i) { return lowerCase[i]; }

	int getUpperCase(int i) { return upperCase[i]; }

	void assignLength(int leng)
	{
		length = leng;
	}

	void generateRandom()
	{

		generated.resize(length);

		for ( int i { 0 }; i < length; ++i)
		{
			
			generated[i] = lowerCase[getRandomNumber()];
		}
	}

	void print()
	{
		std::cout << generated << std::endl;
	}



	friend int getRandomNumber();

};

int getRandomNumber()
{
	std::mt19937 mt{ static_cast<unsigned int>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	std::uniform_int_distribution letters{ 0, 25 };

	return letters(mt);
}

int getLength()
{
	std::cout << " How long do you want the password is? ";
	int length;
	std::cin >> length;

	return length;
	
}

int main()
{
	Password password;

	password.assignLength(getLength());

	password.generateRandom();

	password.print();


}