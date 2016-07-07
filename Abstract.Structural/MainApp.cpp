
#include "MainApp.h"


int main()
{
	// Abstract factory #1
	AbstractFactory* lpFactory1 = new ConcreteFactory1();
	Client* lpClient1 = new Client(lpFactory1);
	lpClient1->Run();

	// Abstract factory #2
	AbstractFactory* lpFactory2 = new ConcreteFactory2();
	Client* client2 = new Client(lpFactory2);
	client2->Run();

	int input;
	cin >> input;

	return 0;
}