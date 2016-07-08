
#include "MainApp.h"


int main()
{
	// An array of creators
	Creator* lpCreators[2];
	lpCreators[0] = new ConcreteCreatorA;
	if (NULL == lpCreators[0])
		return 0;
	lpCreators[1] = new ConcreteCreatorB;
	if (NULL == lpCreators[1])
		return 0;

	const int nCount = sizeof(lpCreators) / sizeof(Creator*);
	for (int i = 0; i < nCount; i++)
	{
		Product* lpProduct = lpCreators[i]->FactoryMethod();
		cout << lpProduct->GetName().data() << endl;
	}

	// Wait for user
	int input;
	cin >> input;

	return 0;
}