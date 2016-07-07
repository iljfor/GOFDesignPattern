
#pragma once
//
// MainApp startup class for Structural
// Builder Design Pattern.

#include <iostream>
#include <list>
using namespace std;


//
// The 'Product' class
class Product
{
public:
	void Add(string part)
	{
		m_Parts.insert(m_Parts.end(), part);
	}

	void Show()
	{
		cout << "\nProduct Parts ----- " << endl;
		for (list<string>::const_iterator iterator = m_Parts.begin(), end = m_Parts.end(); iterator != end; ++iterator)
			cout << iterator->data() << endl;
	}

protected:
	list<string>	m_Parts;
};


//
// The 'Builder' abstract class
class Builder
{
public:
	virtual void BuildPartA(void) = NULL;
	virtual void BuildPartB(void) = NULL;
	virtual Product* GetResult(void) = NULL;
};


//
// The 'ConcreteBuilder1' class
class ConcreteBuilder1 : public Builder
{
public:
	ConcreteBuilder1(void)
	{
		m_lpProduct = new Product;
		_ASSERTE(NULL != m_lpProduct);
	}
	~ConcreteBuilder1(void)
	{
		if (NULL != m_lpProduct)
		{
			delete m_lpProduct;
			m_lpProduct = NULL;
		}
	}

	virtual void BuildPartA(void)
	{
		m_lpProduct->Add("PartA");
	}

	virtual void BuildPartB(void)
	{
		m_lpProduct->Add("PartB");
	}

	virtual Product* GetResult(void)
	{
		return m_lpProduct;
	}

protected:
	Product*	m_lpProduct;
};

//
// The 'ConcreteBuilder2' class
class ConcreteBuilder2 : public Builder
{
public:
	ConcreteBuilder2(void)
	{
		m_lpProduct = new Product;
		_ASSERTE(NULL != m_lpProduct);
	}
	~ConcreteBuilder2(void)
	{
		if (NULL != m_lpProduct)
		{
			delete m_lpProduct;
			m_lpProduct = NULL;
		}
	}

	virtual void BuildPartA(void)
	{
		m_lpProduct->Add("PartX");
	}

	virtual void BuildPartB(void)
	{
		m_lpProduct->Add("PartY");
	}

	virtual Product* GetResult(void)
	{
		return m_lpProduct;
	}

protected:
	Product*	m_lpProduct;
};


//
// The 'Director' class
class Director
{
	// Builder uses a complex series of steps
public:
	void Construct(Builder* lpBuilder)
	{
		lpBuilder->BuildPartA();
		lpBuilder->BuildPartB();
	}
};