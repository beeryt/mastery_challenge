#ifndef MYCLASS_H
#define MYCLASS_H

class myClass
{
private:
	int privateInt;
protected:
	int protectedInt;
public:
	int publicInt;
	/* Lifecycle functions */
	myClass() {
		publicInt = 1;
		privateInt = 2;
		protectedInt = 3;
	}
	~myClass() {}
	/* Getters */
	int getPublic(){ return publicInt; }
	int getPrivate(){ return privateInt; }
	int getProtected(){ return protectedInt; }
	/* Setters */
	void setPublic(int i) { publicInt = i; }
	void setPrivate(int i) { privateInt = i; }
	void setProtected(int i) { protectedInt = i; }

};

#endif