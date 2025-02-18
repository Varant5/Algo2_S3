//ALGO2 IS1 222A LAB02
//Łuaksz Kasztelan
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>
#include <random>
using namespace std;
template <typename T> 
class vectorClass
{
	T* arr;
	int capacity;
	int size;

public:
	vectorClass()
	{
		arr = new T[1];
		capacity = 1;
		size = 0;
	}
	~vectorClass()
	{
		delete[] arr;
	}
	void push(T data)
	{
		if (size == capacity) 
		{
			T* temp = new T[2 * capacity];

			// Kopiowanie do nowej
			for (int i = 0; i < capacity; i++) 
			{
				temp[i] = arr[i];
			}
			// Usuwanie starej
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		// Włożenie danych
		arr[size] = data;
		size++;
	}
	// Dodawanie elementu
	void PushInIndex(T data, int index)
	{
		// Jeżeli jest równy pojemności
		if (index == capacity)
			push(data);
		else if (index < 0 || index > size)
			cout << "Poza wartoscia";
		else
			arr[index] = data;
	}
	// Odwołanie do elementu
	T get(int index)
	{
		if (index < size && index >= 0)
		{
			return arr[index];
		}		
		cout << "Poza wartoscia";
		abort();
	}
	void bubble_sort()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 1; j < size - i; j++)
			{
				if (arr[j - 1] > arr[j])
				{
					swap(arr[j - 1], arr[j]);
				}	
			}	
		}		
	}
	// Rozmiar
	int getsize() { return size; }

	// Pojemnosc
	int getcapacity() { return capacity; }

	// Wypisywanie 
	void print()
	{
		for (int i = 0; i < 3; i++) {
			cout << arr[i] << " ";
		}
		cout << "::: ";
		for (int i = size-3; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	void deletee()
	{		
		T* tmp = new T[1];
		delete[] arr;
		arr = tmp;
		capacity = 1;
		size = 0;
	}
};
struct some_object
{
	int a;
	char b;
	bool operator>(const some_object& data) const
	{
		return a > data.a || a == data.a && b > data.b;
	}
	default_random_engine end;
};
ostream& operator<<(ostream& ret, const some_object& arr)
{
	return ret << arr.a << " " << arr.b;
}
int main()
{
	/*vectorClass<int> l;
	l.push(1);
	l.push(5);
	l.push(3);
	l.push(2);
	l.PushInIndex(4, 1);
	l.print();
	l.bubble_sort();
	cout << l.get(2) << endl;
	l.print();
	cout << l.getsize() << endl;
	l.deletee();
	cout << l.getsize() << endl;
	return 0;*/
	srand(time(NULL));
	char random{};
	vectorClass <some_object>* da = new vectorClass <some_object>(); // stworzenie tablicy
	const int order = 2; // rzad wielkosci rozmiaru dodawanych danych
	const int n = pow(10, order); // rozmiar danych
	// dodawanie do tablicy
	clock_t t1 = clock();
	double max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
	for (int i = 0; i < n; i++) {
		random = ((rand() % ('z' + 1 - 'a')) + 'a');
		some_object so = some_object{ rand() % 10001, random }; // losowe dane
		clock_t t1_element = clock();
		da->push(so);
		clock_t t2_element = clock();
		double time_per_element = t2_element - t1_element; // obliczenie czasu pojedynczej operacji dodawania
		if (time_per_element > max_time_per_element)
			{
				max_time_per_element = time_per_element;
				cout << " Nowy najgorszy czas " << max_time_per_element << " " << i << endl;
			}
	}
	clock_t t2 = clock();
	da->print(); // wypis na ekran aktualnej postaci tablicy ( skrotowej ) i pomiarow czasowych ( czas calkowity i zamortyzowany )
	//da->bubble_sort();
	//da->PushInIndex(some_object{ 1, 'a' }, 0);
	cout << "Czas : " << t2 - t1 << endl;
	cout << "Czas (n) : " << (t1 - t2)/n << endl;
	da->deletee(); // czyszczenie tablicy wraz z uwalnianiem pamieci danych
	da->push(some_object{ rand() % 10001, random });
	da->print();
	delete da;
	return 0;
}