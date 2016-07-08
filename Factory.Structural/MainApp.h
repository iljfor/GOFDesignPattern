
#pragma once
//
// MainApp startup class for Structural
// Factory Method Design Pattern.

#include <iostream>
using namespace std;


//
// The 'Product' abstract class
class Product
{
public:
	virtual string GetName(void) = NULL;
};


//
// A 'ConcreteProductA' class
class ConcreteProductA : public Product
{
	virtual string GetName(void) { return "ConcreteProductA"; }
};


//
// A 'ConcreteProductB' class
class ConcreteProductB : public Product
{
	virtual string GetName(void) { return "ConcreteProductB"; }
};


//
// The 'Creator' abstract class
class Creator
{
public:
	virtual Product* FactoryMethod(void) = NULL;
};


//
// A 'ConcreteCreatorA' class
class ConcreteCreatorA : public Creator
{
	virtual Product* FactoryMethod(void)
	{
		return new ConcreteProductA;
	}
};


//
// A 'ConcreteCreatorB' class
class ConcreteCreatorB : public Creator
{
	virtual Product* FactoryMethod(void)
	{
		return new ConcreteProductB;
	}
};

