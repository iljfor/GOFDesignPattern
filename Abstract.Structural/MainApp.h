
#pragma once
//
// MainApp startup class for Structural
// Abstract Factory Design Pattern.

#include <iostream>
using namespace std;


//
// The 'AbstractProductA' abstract class
class AbstractProductA
{
};


//
// The 'ProductA1' class
class ProductA1 : public AbstractProductA
{
};


//
// The 'ProductA2' class
class ProductA2 : public AbstractProductA
{
};


//
// The 'AbstractProductB' abstract class
class AbstractProductB
{
public:
	virtual void Interact(AbstractProductA* lpProductA) = NULL;
};


//
// The 'ProductB1' class
class ProductB1 : public AbstractProductB
{
public:
	virtual void Interact(AbstractProductA* lpProductA) { cout << "ProductB1 Input ProductA" << lpProductA << endl; }
};


//
// The 'ProductB2' class
class ProductB2 : public AbstractProductB
{
public:
	virtual void Interact(AbstractProductA* lpProductA) { cout << "ProductB2 Input ProductA" << lpProductA << endl; };
};


//
// The 'AbstractFactory' abstract class
class AbstractFactory
{
public:
	virtual AbstractProductA*	CreateProductA(void) = NULL;
	virtual AbstractProductB*	CreateProductB(void) = NULL;
};


//
// The 'ConcreteFactory1' class
class ConcreteFactory1 : public AbstractFactory
{
public:
	virtual AbstractProductA*	CreateProductA(void) { return new ProductA1; }
	virtual AbstractProductB*	CreateProductB(void) { return new ProductB1; }
};


//
// The 'ConcreteFactory2' class
class ConcreteFactory2 : public AbstractFactory
{
public:
	virtual AbstractProductA*	CreateProductA(void) { return new ProductA2; }
	virtual AbstractProductB*	CreateProductB(void) { return new ProductB2; }
};


//
// The 'Client' class. Interaction environment for the products.
class Client
{
private:
	AbstractProductA* lpAbstractProductA;
	AbstractProductB* lpAbstractProductB;

	// Constructor
public:
	Client(AbstractFactory* lpFactory)
	{
		lpAbstractProductA = lpFactory->CreateProductA();
		lpAbstractProductB = lpFactory->CreateProductB();
	}

	void Run(void)
	{
		lpAbstractProductB->Interact(lpAbstractProductA);
	}
};