#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdbool.h>
#include <sstream>
#include <time.h>
#include <ctime>
using namespace std;

#define SIZE 10

struct student
{
	long id;
	char name[30];
	char address[50];
	double gpa;

};

class HashNode
{
public:
	char hash_key[SIZE];
	student s;
	HashNode* next;
	HashNode(char* key, student s)
	{
		strcpy(this->hash_key, key);
		this->s = s;
		this->next = NULL;
	}
};

class hashTable
{


	HashNode** table;
	int arr[3] = { 0,1,2 };


public:
	hashTable(int n);
	//constructor
	void insert(student s);
	//insert a student into hash table
	void remove(student s);
	//delete a student from hash table
	bool search(student s);
	//return true if s is found in the hashTable, false if not found in the hashTable
	void destroy();
	//delete the hashTable object
	void hashTemplate(int (*p[3])(student s));
	//wrapper function e.g. wrapper(&hash1)
	void display();
	//display function
	void utilization(student s);
	//it will change the order of the function array

private:
	//hash functions will not be used in main, wrapper function will be used instead
	int hash1(student s, char* c);
	//hashing #1
	int hash2(student s, char* c);
	//hashing #2
	int hash3(student s, char* c);
	//hashing #3

};

hashTable::hashTable(int n)
{
	table = new HashNode * [SIZE];
	for (int i = 0; i < SIZE; i++)
		table[i] = NULL;
}

int hashTable::hash1(student s, char* c) //converts the number to base 9 (radix transformation	)
{

	int idx;
	int baseNine = 0;
	int rem = 0;
	int i = 1;
	idx = (int)s.id;

	while (idx > 0)
	{
		rem = idx % 9;
		baseNine = baseNine + (rem * i);
		idx = idx / 9;
		i *= 10;
	}

	return baseNine % SIZE;

}

int hashTable::hash2(student s, char* c) //shift folding (sum up ascii values of the first 5 character of the string and mod SIZE to fit in)
{
	int a = 0;
	for (int i = 0; i < 5; i++)
		a += s.name[i];
	a = a % SIZE;

	return a;
}

int hashTable::hash3(student s, char* c)
//extraction first 2 characters of the string and the last two digits of the id 
//is used and added together then mod SIZE to fit in
{
	int a = 0;
	int part1 = s.id / 10000000;
	int part2 = s.name[0] + s.name[1];

	a = part2 + part1 * (100);
	a = a % SIZE;
	return a;
}

//void hashTable::hashTemplate(int (*p[3])(student s))
//{
//	p[0] = hash1;
//	p[1] = hash2;
//	p[2] = hash3;
//}

void hashTable::insert(student s)
{
	char key[SIZE];
	int hash_val;

	/*if (arr[0] == 0)
		hash_val = hash1(s, key);
	else if (arr[0] == 1)
		hash_val = hash2(s, key);
	else if (arr[0] == 2)
		hash_val = hash3(s, key);
	*/


	hash_val = hash3(s, key);
	cout << "Hash : " << hash_val << endl;

	if (table[hash_val] == nullptr)
	{
		table[hash_val] = new HashNode(key, s);
		return;
	}
	HashNode* entry = table[hash_val];
	while (entry->next != nullptr)
	{
		entry = entry->next;
	}
	entry->next = new HashNode(key, s);


}

void hashTable::remove(student s)
{
	char key[SIZE];
	int hash_val;

	hash_val = hash3(s, key);
	HashNode* entry = table[hash_val];
	HashNode* prev = NULL;
	if (entry == NULL)
	{
		cout << "No Student with name " << s.name << endl;
		return;
	}
	while (entry->next != NULL)
	{
		prev = entry;
		entry = entry->next;
	}
	if (prev != NULL)
	{
		prev->next = entry->next;
	}
	delete entry;
	cout << "Student is removed" << endl;
}

bool hashTable::search(student s)
{
	char key[SIZE];
	int idx;

	idx = hash1(s, key);
	HashNode* entry = table[idx];
	HashNode* prev = NULL;
	if (entry == NULL)
	{

		return false;
	}
	while (entry->next != NULL)
	{
		prev = entry;
		entry = entry->next;
	}
	if (prev != NULL)
	{
		prev->next = entry->next;
	}
	return true;

}

void hashTable::display()
{
	for (int i = 0; i < SIZE; i++)
	{
		HashNode* temp = table[i];

		for (; temp != nullptr; temp = temp->next)
		{

			cout << "Id: " << temp->s.id << "\n" << "Name: " << temp->s.name << "\n" << "Address: " << temp->s.address << "\n" << "GPA: " << temp->s.gpa;


			if (temp->next != nullptr)
				cout << endl;
				
			
		}
		cout << endl;
	}
}

//burasý hashTemplate oluþturulunca düzelecek
//void hashTable::utilization(student s)
//{
//	arr[0] = 1;
//	
// 
//	//clock_t begin1 = clock();
//	
//	insert(s);
//	clock_t end1 = clock();
//	cout << end1<<endl;
//	double elapsed_secs1 = double(end1);
//	cout << elapsed_secs1<<endl;
//
//	arr[0] = 1;
//	clock_t begin2 = clock();
//	insert(s);
//	clock_t end2 = clock();
//	double elapsed_secs2 = double(end1-begin2);
//	cout << elapsed_secs1 << endl;
//
//	arr[0] = 2;
//	clock_t begin3 = clock();
//	insert(s);
//	clock_t end3 = clock();
//	double elapsed_secs2 = double(end3 - begin3);
//	cout << elapsed_secs1 << endl;
//}

void hashTable::destroy()
{
	for (int i = 0; i < SIZE; ++i)
	{
		HashNode* entry = table[i];
		while (entry != NULL)
		{
			HashNode* prev = entry;
			entry = entry->next;
			delete prev;
		}
	}
	delete[] table;
}