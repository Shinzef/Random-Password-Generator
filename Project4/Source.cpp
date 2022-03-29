#include  <iostream>
#include <random>
#include <chrono>

int getRandomNumber(int min, int max);

class Password
{
private:
	std::string guide{};
	std::string generated{};
	std::string lowerCase{};
	std::string upperCase{};
	std::string numbers{};
	int length{};

public:
	Password() : generated{ "" }, lowerCase{ "abcdefghijklmnopqrstuvwxyz" }, upperCase{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" }, numbers{ "0123456789" }
	{
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

			if (guide[i] == 1)
			{
				generated[i] = lowerCase[getRandomNumber(0, 25)];
			}
			else if (guide[i] == 2 )
			{
				generated[i] = upperCase[getRandomNumber(0, 25)];
			}
			else
			{
				generated[i] = numbers[getRandomNumber(1, 9)];
			}

		}
	}

	void generateGuide()
	{
		guide.resize(length);

		for ( int i { 0 }; i < length; ++i)
		{
			guide[i] = getRandomNumber(1, 3);
		}
	}

	void print()
	{
		std::cout << generated << std::endl;
	}

	friend int getRandomNumber(int min, int max);

};

int getRandomNumber(int min, int max)
{
	std::mt19937 mt{ static_cast<unsigned int>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	std::uniform_int_distribution letters{ min, max };

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

	password.generateGuide();
	password.generateRandom();

	password.print();

	return 0;
}