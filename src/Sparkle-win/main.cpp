#include <iostream>
#include "SSharedPtr.h"


class Base
{
public:
	Base(int val)
		:val_(val)
	{

	}

	virtual ~Base()
	{

	}

	int getVal()const
	{
		return val_;
	}

	virtual void print()
	{
		std::cout << val_ << std::endl;
	}
private:
	int val_;
};

class Child:public Base
{
public:
	Child(int val)
		:Base(val)
	{

	}

	virtual ~Child()
	{

	}
	virtual void print()
	{
		std::cout << "value is " << getVal() << std::endl;
	}

};


void test(SShardPtr<Base> ptr)
{
	ptr->print();
}


int main(int argc, char** argv)
{
	std::cout << "Hello World" << std::endl;
	{

		SShardPtr<Base> ptr1 = new Child(7);
		SShardPtr<Base> ptr2 = ptr1;
		test(ptr2);

	}

	return 0;
}