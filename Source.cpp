#include "Header.h"


int main()
{
	//student structs created here
	char std1[30] = "Mike";
	char std2[30] = "Jake";
	char std3[30] = "Harold";
	char std4[30] = "Mark";
	char add1[30] = "TestTestAddress1";
	char add2[30] = "TestTestAddress22";
	char add3[30] = "TestTestAddress333";

	student x,x1,x2,x3;

	x.id = 123456789;
	x.gpa = 2.5;
	x1.id = 123456780;
	x1.gpa = 3.2;
	x2.id = 123456781;
	x2.gpa = 1.5;
	x3.id = 123456782;
	x3.gpa = 0.6;
	strcpy(x.address, add1);
	strcpy(x1.address, add2);
	strcpy(x2.address, add3);
	strcpy(x3.address, add1);
	strcpy(x.name, std1);
	strcpy(x1.name, std2);
	strcpy(x2.name, std3);
	strcpy(x3.name, std4);
	
	hashTable h(3);

	//insert demo
	//x3 and x2 are not inserted
	h.insert(x);
	h.insert(x1);
	

	h.display();


	//search demo for x3 which isnot inserted
	bool a=h.search(x3);

	if (a)
		cout << "found\n";
	else
		cout << "not found\n";

	//search demo for x1 which is inserted
	a = h.search(x1);

	if (a)
		cout << "found\n";
	else
		cout << "not found\n";

	//delete demo x1 deleted which was inserted before

	h.remove(x1);
	
	bool b=h.search(x1);
	if (b)
		cout << "found\n";
	else
		cout << "not found\n";

	//utalization demo
	//h.utilization(x2);

	
	
	return 0;
}