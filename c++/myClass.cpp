#include "childClass.h"
#include <stdio.h>
using namespace std;

#define GREEN	"\E[32m"
#define ORANGE	"\E[33m"
#define AQUA	"\E[36m"
#define CLEAR	"\E[0m"

int main(int argc, char const *argv[])
{
	myClass *c = new myClass;
	printf("%sPrinting original values...%s\n", ORANGE, CLEAR);
	printf("public: %d, private: %d, protected: %d\n", c->getPublic(), c->getPrivate(), c->getProtected());
	printf("%sCalling setters...%s\n", AQUA, CLEAR);
	c->setPublic(4);
	c->setPrivate(5);
	c->setProtected(6);
	printf("%sPrinting new values...%s\n", GREEN, CLEAR);
	printf("public: %d, private: %d, protected: %d\n", c->getPublic(), c->getPrivate(), c->getProtected());

	printf("%sInheritance...%s\n", AQUA, CLEAR);
	delete c;
	c = new childClass;
	printf("public: %d, private: %d, protected: %d\n", c->getPublic(), c->getPrivate(), c->getProtected());
	printf("%sChanging protected variable...%s\n", AQUA, CLEAR);
	c->protectedInt = 5;
	printf("public: %d, private: %d, protected: %d\n", c->getPublic(), c->getPrivate(), c->getProtected());

	return 0;
}