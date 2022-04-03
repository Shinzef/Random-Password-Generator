#include  <iostream>
#include <random>
#include <chrono>

int getRandomNumber(int min, int max, bool isOther);

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
	Password() : generated{""}, lowerCase{"abcdefghijklmnopqrstuvwxyz"}, upperCase{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
	             numbers{"0123456789"} 
	{
	}

	int getLowerCase(int i) { return lowerCase[i]; }

	int getUpperCase(int i) { return upperCase[i]; }

	std::string getGenerated() { return generated; }

	void assignLength(const int tempLength)
	{
		length = tempLength;
	}

	void generateRandom() // generates password using the guide
	{

		generated.resize(length);

		for ( int i { 0 }; i < length; ++i)
		{

			if (guide[i] == 1)
			{
				generated[i] = lowerCase[getRandomNumber(0, 25, false)];
			}
			else if (guide[i] == 2 )
			{
				generated[i] = upperCase[getRandomNumber(0, 25, false)];
			}
			else if (guide[i] == 3)
			{
				generated[i] = numbers[getRandomNumber(1, 9, false)];
			}
			else
			{
				std::cerr << "error";
			}

		}
	}

	
	void generateGuide(const bool lowercase, const bool uppercase, const bool numbers);

	void print(std::string hm)
	{
		std::cout << hm << std::endl;
	}

	friend int getRandomNumber(int min, int max, bool isother);

};

class Options
{
private:
	bool isUppercase{};
	bool isLowercase{};
	bool isNumber{};

public:
	Options() : isUppercase{ false }, isLowercase{ false }, isNumber{ false }
	{
	}

	bool getUppercase() { return isUppercase; }
	bool getLowercase() { return isLowercase; }
	bool getNumber() { return isNumber; }

	bool getOptions(int type) // asks user about the options 
	{
		if (type == 1)
		{
			std::cout << "Enable lowercase letters on the generated password? ";
			std::cin >> isLowercase;
			return isLowercase;
		}
		if (type == 2)
		{
			std::cout << "Enable uppercase letters on the generated password? ";
			std::cin >> isUppercase;
			return isUppercase;
		}
		if (type == 3)
		{
			std::cout << "Enables numbers on the generated password? ";
			std::cin >> isNumber;
			return isNumber;
		} // for readability
	}
};

int getRandomNumber(const int min, const int max, bool isOther) // generates a random number
{
	std::mt19937 mt{ static_cast<unsigned int>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	std::uniform_int_distribution letters{ min, max };

	if ( isOther == true)
	{
		int temp = letters(mt);

		if (temp == 2)
		{
			return 3;
		}
		return temp;
	}
	return letters(mt);
}

void Password::generateGuide(const bool lowercase, const bool uppercase, const bool numbers) // generates the guide
{
	guide.resize(length);

	for ( int i { 0 }; i < length; ++i)
	{
		if (lowercase == true && uppercase == true && numbers == false) // only lower and upper
		{
			guide[i] = getRandomNumber(1, 2, false);
		}
		else if (lowercase == false && uppercase == true && numbers == true) // only upper and numbers
		{
			guide[i] = getRandomNumber(2, 3, false);
		}
		else if (lowercase == true && uppercase == false && numbers == true) // only lower and number
		{
			guide[i] = getRandomNumber(1, 2, true);
		}
		else if (lowercase == true && uppercase == true && numbers == true) // all 
		{
			guide[i] = getRandomNumber(1, 3, false);
		}
		else 
		{
			std::cerr << "error";
		}
	}
}

int getLength() // ask user how long the password is
{
	std::cout << "How long do you want the password is? ";
	int length;
	std::cin >> length;

	return length;
	
}

int main()
{
	Password password; // initialize

	Options options; // initialize

	std::cout << "Enter 1 for yes and 0 for no\n";
	std::cout << "Note: select two options single option isnt implemented yet\n";
	options.getOptions(1); // gets option for lower
	options.getOptions(2); // gets option for upper
	options.getOptions(3); // gets option for numbers

	password.assignLength(getLength()); // assigns length

	password.generateGuide(options.getLowercase(), options.getUppercase(), options.getNumber());
	// generates the guide 1 = number 2 = upper 3 = number

	password.generateRandom(); // generates password using the guide 

	password.print(password.getGenerated()); // prints password

	return 0;
}