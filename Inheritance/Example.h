// Example.h
// Written by Jared Bruni
// www.lostsidedead.com
#include <iostream.h>

// a ADT (Abstract Data Type) do not try to create a instance of this object! inhert it !
class Life
{
public:
	// pure virtual functions
	virtual void Born() = 0;
	virtual void Die() = 0;
	virtual void Reproduce() = 0;
};

// to turn your classes into a Object that has characterisitcs of life
class Animal : Life 
{
	int age;
public:

	inline Animal()
	{
		Born();
	}

	inline ~Animal()
	{
		Die();
	}

	// override pure virtual function
	virtual void Born()
	{
		cout << " I was just born " << endl;
	}

	// override pure virtual function
	virtual void Die()
	{
		cout << " I just died" << endl;
	}

	// override pure virtual function
	virtual void Reproduce()
	{
		cout << " I just had babys with your girlfriend " << endl;
	}
	// override pure virtual function
	virtual void SetAge(int age)
	{
		age = age;
	}
};

// misc functions, to inhert into any class
class ImporantFunctions
{
public:
	void func1();
	void func2();
};


// the dog class, which multiple inherts from animal, and important functions
class Dog : public Animal , public ImporantFunctions
{
public:

	inline void Bark()
	{
		cout << "im a dog so i can bark" << endl;
	}
};