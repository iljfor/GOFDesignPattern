
#include "MainApp.h"


int main()
{
	// Create director and builders
	Director* lpDirector = new Director;

	Builder* lpBuilder1 = new ConcreteBuilder1;
	Builder* lpBuilder2 = new ConcreteBuilder2;

	// Construct two products
	lpDirector->Construct(lpBuilder1);
	Product* lpProduct1 = lpBuilder1->GetResult();
	lpProduct1->Show();

	lpDirector->Construct(lpBuilder2);
	Product* lpProduct2 = lpBuilder2->GetResult();
	lpProduct2->Show();

	// Wait for user
	int input;
	cin >> input;

	return 0;
}