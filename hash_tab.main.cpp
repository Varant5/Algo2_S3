//ALGO2 IS1 222A LAB05
//Łukasz Kasztelan
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;


template <typename T> 
class Vector
{
public:
	T* arr;
	int capacity;
	int current;
	Vector()
	{
		arr = new T[1];
		capacity = 1;
		current = 0;
	}

	void push(T data)
	{
		if (current == capacity) {
			T* temp = new T[2 * capacity];

			for (int i = 0; i < capacity; i++) {
				temp[i] = arr[i];
			}

			delete[] arr;
			capacity *= 2;
			arr = temp;
		}

		arr[current] = data;
		current++;
	}

	void push(T data, int index)
	{
		if (index == capacity)
			push(data);
		else
			arr[index] = data;
	}

	void popByIndex(int index)
	{
		current--;
		for (int i = index; i < current; i++)
		{
			arr[i] = arr[i + 1];
		}
	}

	void popFront(int x)
	{
		for (int i = 0; i < x; i++)
		{
			popByIndex(0);
		}
		cout << endl;
	}
	T get(int index)
	{
		if (index < current)
			return arr[index];
	}
	void pop() { current--; }

	int size() { return current; }

	int getcapacity() { return capacity; }

	void clear()
	{	
		T* temp = new T[1];
		delete[] arr;
		arr = nullptr;
		arr = temp;
		capacity = 1;
		current = 0;
	}
	T& operator[](int index)
	{
		if (index >= current) exit(999);
		return arr[index];
	}
};

struct Hash
{
	int count = 0;
	string key = "";
	int key1 = 0;
};


class HashTable
{
private:
	Vector<Hash> *table;
public:
	long long unsigned capacity;
	int current;

	HashTable()
	{
		capacity = 2;
		table = new Vector<Hash>[capacity];
		current = 0;
	}
	
	int hashFunction(string key, long long unsigned cap) {
		int hash = 0;
		int mno = 1;
		for (int i = key.length()-1; i >= 0; i--) {
			hash += key[i]*(mno);			
			mno *= 31;
		}
		hash = hash % cap;
		if (hash < 0)
		{
			hash += cap;
		}
		return hash;
	}

	void pushHash(string key, int key1) // dopisywanie do funkcji
	{
		int hashValue = hashFunction(key, capacity);
		Hash tmp;
		tmp.count = 1;
		tmp.key = key;
		tmp.key1 = key1;
		if (table[hashValue].arr[0].key == "") {
			table[hashValue].push(tmp);
		}
		else if (key == table[hashValue].arr[0].key && key1 == table[hashValue].arr[0].key1) {
			table[hashValue].arr[0].count += 1;
		}
		else { // kolizja
			for (int i = 1; i < table[hashValue].size(); i++) {
				if (table[hashValue].arr[i].key == "") {
					table[hashValue].push(tmp);
					return;
				}
				else if (key == table[hashValue].arr[i].key && key1 == table[hashValue].arr[i].key1) {
					table[hashValue].arr[i].count += 1;
					return;
				}
			}
			table[hashValue].push(tmp);
		}

	}

	void insertActuallyItem(Vector<Hash>*& newTable) // kopiowanie
	{
		for(int i = 0;i < capacity; i++)
		{
			if(table[i].arr[0].key != "") // cos tu jest
			{
				for(int j = 0;j<table[i].size();j++)
				{
					string key = table[i].arr[j].key;
					int key1 = table[i].arr[j].key1;
					int hashValue = hashFunction(key, capacity*2);
					Hash tmp;
					tmp.count = table[i].arr[j].count;
					tmp.key = key;
					tmp.key1 = table[i].arr[j].key1;

					if (newTable[hashValue].arr[0].key == "") {
						newTable[hashValue].push(tmp);
					}
					else { // kolizja
						for (int i = 1; i < newTable[hashValue].size(); i++) {
							if (newTable[hashValue].arr[i].key == "") {
								newTable[hashValue].push(tmp);
								return;
							}
						}
						newTable[hashValue].push(tmp);
					}
				}
			}
		}
	}

	void insertItem(string key, int key1) {

		if (current == capacity) {
			Vector<Hash>* temp = new Vector<Hash>[2 * capacity];

			insertActuallyItem(temp);

			delete[] table;
			capacity *= 2;
			table = temp;
		}

		pushHash(key, key1);
		current++;
	}


	void getCount(string key, int key1) {
		int hashValue = hashFunction(key, capacity);
		if (key == table[hashValue].arr[0].key && key1 == table[hashValue].arr[0].key1) {
			cout << table[hashValue].arr[0].count << endl;
		}
		else {
			for (int i = 1; i < table[hashValue].size(); i++) {
				if (key == table[hashValue].arr[i].key && key1 == table[hashValue].arr[i].key1) {
					cout << table[hashValue].arr[i].count << endl;
					return;
				}
			}
			exit(2);
		}
	}

	bool check(string key)
	{
		int hashValue = hashFunction(key, capacity);
		if (key == table[hashValue].arr[0].key) {
			return true;
		}
		else {
			for (int i = 1; i < table[hashValue].size(); i++) {
				if (key == table[hashValue].arr[i].key) {
					return true;
				}
			}
			return false;
		}
	}
	void find(string key, int key1)
	{
		int hashValue = hashFunction(key, capacity);
		if (key == table[hashValue].arr[0].key) {
			cout << "Znaleziono : " << table[hashValue].arr[0].key << "| Key1: " << table[hashValue].arr[0].key1 << endl;
		}
		else {
			for (int i = 1; i < table[hashValue].size(); i++) {
				if (key == table[hashValue].arr[i].key) {
					cout << "Znaleziono : " << table[i].arr[0].key << "| Key1: " << table[i].arr[0].key1 << endl;
				}
			}
			cout << "Nie znaleziono ";
		}
	}

	void deleteCount(string key, int key1) {
		int hashValue = hashFunction(key, capacity);
		if (key == table[hashValue].arr[0].key && key1 == table[hashValue].arr[0].key1) {
			table[hashValue].arr[0].count = 0;
		}
		else {
			for (int i = 1; i < table[hashValue].size(); i++) {
				if (table[i].arr[i].key == key && table[i].arr[i].key1 == key1) {
					table[i].arr[i].count = 0;
					return;
				}
			}
			exit(3);
		}
	}

	void kontrolnyPrint()
	{
		for(int i = 0;i<capacity;i++)
		{
			cout << i << ": ";
			for(int j = 0;j<table[i].size();j++)
			{
				cout << " Vector[" << j << "] = Key: " << table[i].arr[j].key << "| Key1: " << table[i].arr[j].key1 << " | Count: " << table[i].arr[j].count;
			}
			cout << endl;
		}
	}
	void stats()
	{
		cout << "Rozmiar: " << size() << endl;
		cout << "Romiar aktualny: " << getcurrent() << endl;
		cout << "Ilosc NotNULL: " << notNull() << endl;
		cout << "Ilosc srednia " << average() << endl;
	}
	float average()
	{
		float sum = 0;
			for (int i = 0; i < capacity; i++)
			{
				for (int j = 0; j < table[i].size(); j++) {
					sum++;
				}
			}
		return sum/capacity;
	}
	void clear()
	{
		table->clear();
		current = 0;
		capacity = 1;
	}
	int notNull()
	{
		int counter = 0;
		for (int i = 0; i < capacity; i++)
		{
			if (table[i].arr[0].key == "") counter++;
		}
		return counter;
	}
	int getcurrent() { return current; }
	int size() { return capacity; }
};
string randomString(int number)
{
	string key;
	key = "";
	string a;
	int ascii;
	for(int i = 0;i<number;i++)
	{
		ascii = (rand() % 24) + 65;
		a = ascii;
		key += ascii;
		a = "";
	}
	return key;
}
int randomInt()
{
	return (rand() % 899999) + 100000;
}

int main()
{
		srand(time(NULL));
		const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
		HashTable ht; // w tym przykladzie tablica mieszajaca par < string , int > jako < klucz, wartosc >
			for (int o = 1; o <= MAX_ORDER; o++)
			{
				int seed = time(NULL);
				srand(seed);
				const int n = pow(10, o); // rozmiar danych
				// dodawanie do tablicy mieszajacej
				clock_t t1 = clock();
				for (int i = 0; i < n; i++)
				{
					ht.insertItem(randomString(6),i); // klucze losowe 6 - znakowe , a jako wartosci indeks petli
				}						
				clock_t t2 = clock();
				//ht.kontrolnyPrint(); // wypis na ekran aktualnej postaci tablicy mieszajacej ( skrotowej ) oraz pomiarow czasowych
				cout << "Czas dod:" << t2 - t1 << endl;
				// wyszukiwanie w tablicy mieszajacej
				const int m = pow(10, 4);
				srand(seed);
				int hits = 0;
				t1 = clock();
				for (int i = 0; i < m; i++)
				{
					if (ht.check(randomString(6)) != NULL)
						hits++;
				}
				t2 = clock();
				cout << "Czas 2: " << t2 - t1 << endl; // wypis na ekran pomiarow czasowych i liczby trafien
				cout << "Trafienia : " << hits << endl;
				// wypis statystyk ( dlugosci list kryjacych sie w tablicy mieszajacej )
				ht.stats();
				ht.clear();
			}
		//ht.clear();					// czyszczenie tablicy mieszajacej
		return 0;
	
}