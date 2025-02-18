//ALGO2 IS1 222A LAB07
//Łukasz Kasztelan
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
template<typename T>
class Binary_heap
{
private:
    vector<T> Bin_heap;
public:
    Binary_heap(T* &arr, int size) : Bin_heap(arr, arr + size) 
    {}
    ~Binary_heap()
    {}
    void heapify_up(int i)//bottom-up
    {
        int parent_index = (i - 1) / 2;
        if (i > 0 && Bin_heap[i] > Bin_heap[parent_index]) {
            swap(Bin_heap[i], Bin_heap[parent_index]);
            heapify_up(parent_index);
        }
    }
    void heapify_down(int i, int n)//Top-down
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < n && Bin_heap[left] > Bin_heap[largest])
            largest = left;

        if (right < n && Bin_heap[right] > Bin_heap[largest])
            largest = right;

        if (largest != i)
        {
            swap(Bin_heap[i], Bin_heap[largest]);
            heapify_down(largest, n);
        }
    }
    void add(const T& data)
    {
        Bin_heap.push_back(data);
        int index = Bin_heap.size() - 1;
        heapify_up(Bin_heap, index);
    }
    /*void printArray()
    {
        if (Bin_heap.size() <= 0)
            cout << "Pusty kopiec" << endl;
        for (int i = 0; i < Bin_heap.size(); i++)
        {
            cout << " { ";
            cout << Bin_heap[i];
            cout << "} " << endl;
        }
    }*/
    T deleteRoot()
    {
        if (Bin_heap.empty()) return T();
        T max_value = Bin_heap[0];
        if (Bin_heap.size() == 1) {
            Bin_heap.pop_back();
            return max_value;
        }
        Bin_heap[0] = Bin_heap.back();
        Bin_heap.pop_back();

        heapify_down(Bin_heap, 0);

        return max_value;
    }
    void clear() {
        Bin_heap.clear();
    }
    void heap_sort()
    {
        int n = Bin_heap.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify_down(i, n);

        /*for (int i = n - 1; i > 0; i--)
        {
            swap(Bin_heap[0], Bin_heap[i]);
            heapify_down(0, i);
        }*/
    }
    vector<T> get_sorted_array() const
    {
        return Bin_heap;
    }
    string to_string() const
    {
        if (Bin_heap.size() == 0)
            return "[]";         
        ostringstream str; // pamiętaj o #include <sstream>
        str << "|^|3 pierwsze liczby heap_sort: ";
        for (int i = 0; i < Bin_heap.size(); i++)
            str << *Bin_heap[i] << " ";
        /*str << "||| ";
        for (int i = Bin_heap.size()-3; i < Bin_heap.size(); i++)
            str << *Bin_heap[i] << " ";
        str << endl;*/
        return str.str(); // wydobycie napisu ze strumienia
    }
};
template<typename T>
vector<T> counting_sort(const T* arr, int n, int max_value)
{
    vector<T> counts(max_value + 1);
    for (int i = 0; i < n; i++)
        counts[arr[i]]++;
    vector<T> indices(max_value + 1);
    for (int i = 0; i < max_value + 1; i++)
        indices[i] = counts[i];
    for (int i = 1; i < max_value + 1; i++)
        indices[i] += indices[i - 1];
    vector<T> sorted_arr(n);
    for (int i = n - 1; i >= 0; i--)
    {
        sorted_arr[indices[arr[i]] - 1] = arr[i];
        indices[arr[i]]--;
    }
    return sorted_arr;
}
template<typename T>
vector<T> bucket_sort(T* arr, int n, float max_value)
{
    vector<T> buckets(max_value + 1);
    for (int i = 0; i < n; i++)
        buckets.at(arr[i])++;
    vector<T> sorted_arr;
    for (int i = 0; i < max_value + 1; i++)
        for (int j = 0; j < buckets[i]; j++)
            sorted_arr.push_back(i);
    return sorted_arr;
}
template <typename T>
void bucket_sort_s(T* arr, int size, int bucket_size)
{
    vector<vector<T>> buckets(size);

    for (int i = 0; i < size; i++)
    {
        buckets[(arr[i]->a/bucket_size)*static_cast<double>(size)].push_back(arr[i]);
    }
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        sort(buckets[i].begin(), buckets[i].end());
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            arr[index] = buckets[i][j];
            index++;
        }
    }
}
struct some_object
{
    float a;
    char b;
    bool operator<(const some_object& data) const
    {
        return a < data.a || (a == data.a && b < data.b);
    }
    bool operator>(const some_object& data) const
    {
        return a > data.a || (a == data.a && b > data.b);
    }
    some_object& operator=(const some_object& rhs) { return *this; }
    int operator[](int i) const
    {
        if (i == 0)
            return a;
        else if (i == 1)
            return b;
        else
            throw std::out_of_range("Invalid index for some_object");
    }
};
template <typename T>
bool operator<(const some_object& a, const some_object& b)
{
    return a < b;
}
ostream& operator<<(ostream& out, const some_object& date)
{
    return out << date.a << " " << date.b;
}
bool operator==(const some_object& a, const some_object& b)
{
    return a.a == b.a && a.b == b.b;
}
//template <typename T>
/*string printt(vector<T> Bin_heap)
{
    if (Bin_heap.size() == 0)
        return "[]";
    ostringstream str; // pamiętaj o #include <sstream>
    str << "|_|3 pierwsze liczby Bucket_sort: ";
    for (int i = 0; i < 3; i++)
        str << *Bin_heap[i] << " ";
    str << "||| ";
    for (int i = Bin_heap.size() - 3; i < Bin_heap.size(); i++)
        str << *Bin_heap[i] << " ";
    str << endl;
    return str.str(); // wydobycie napisu ze strumienia
}*/
/*int main()
{
    srand(time(NULL));
    const int MAX_ORDER = 2; // maksymalny rzad wielkosci sortowanych danych
    const int m = (int)pow(10, 7); // sortowane liczby ze zbioru {0 , ... , m - 1}
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = (int)pow(10, o); // rozmiar tablicy z danymi
        int* array1 = new int[n];
        for (int i = 0; i < n; i++)
        {
            int rand_val = (rand() % 20) + 1; // tu losowanie liczby calkowitej
                array1[i] = rand_val;
        }
         // skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )
        int* array2 = new int[n];
        int* array3 = new int[n];
        memcpy(array2, array1, n * sizeof(int)); // pierwsza kopia
        memcpy(array3, array1, n * sizeof(int)); // druga kopia
        // sortowanie przez zliczanie ( do wykonania w miejscu )
        clock_t t1 = clock();
        vector<int> sorted_array1 = counting_sort(array1, n, m);
        clock_t t2 = clock();
        cout << "***3 pierwsze liczby counting_sort: ";
        for (int i = 0; i < 3; i++) 
            cout << sorted_array1[i] << " ";
        cout << endl;
        cout << "***3 ostatnie liczby counting_sort: ";
        for (int i = sorted_array1.size() - 3; i < sorted_array1.size(); i++)
            cout << sorted_array1[i] << " ";
        cout << "" << endl;
        cout << "Czas dla couting_sort: " << t2 - t1 << endl;
        // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
        // sortowanie przez kopcowanie ( do wykonania w miejscu )
        t1 = clock();
        Binary_heap<int>* bh = new Binary_heap<int>(array2, n); // konstruktor kopca z
        //mozliwoscia przekazania zewnetrznej tablicy(ostatni argument wskazuje kierunek naprawy :
        //top - down lub bottom - up)
        bh->heap_sort();
        vector<int> sorted_arr2 = bh->get_sorted_array();
        t2 = clock();        
        cout << "|^|3 pierwsze liczby heap_sort: ";
        for (int i = 0; i < 3; i++)
            cout << sorted_arr2[i] << " ";
        cout << endl;
        cout << "|^|3 ostatnie liczby heap_sort: ";
        for (int i = sorted_arr2.size() - 3; i < sorted_arr2.size(); i++)
            cout << sorted_arr2[i] << " ";
        cout << endl;
        cout << "Czas dla heap_sort: " << t2 - t1 << endl;
        // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
        // sortowanie kubelkowe ( do wykonania w miejscu )
        t1 = clock();
        vector<int> sorted_array3 = bucket_sort(array3, n, m); // szczegolna wersja bucket sort tylko dla liczb calkowitych
        t2 = clock();
        cout << "|_|3 pierwsze liczby bucket_sort: ";
        for (int i = 0; i < 3; i++)
            cout << sorted_array3[i] << " ";
        cout << endl;
        cout << "|_|3 ostatnie liczby bucket_sort: ";
        for (int i = sorted_array3.size() - 3; i < sorted_array3.size(); i++)
            cout << sorted_array3[i] << " ";
        cout << "" << endl;
        cout << "Czas dla bucket_sort: " << t2 - t1 << endl;
        // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
        // sprawdzenie zgodnosci tablic array1 , array2 , array3 i wypis informacji o zgodnosci na
        if (sorted_array1 == sorted_arr2 && sorted_array1 == sorted_array3)
        {
            cout << "Takie same"<<endl;
        }
        cout << endl;
        delete[] array1;
        delete[] array2;
        delete[] array3;
    }
}*/
int main()
{
    const int MAX_ORDER = 1; // maksymalny rzad wielkosci sortowanych danych
    const double m_double = (double)pow(2, 30); // mianownik przy ustalaniu losowej liczby
        for (int o = 1; o <= MAX_ORDER; o++)
        {
            const int n = (int)pow(10, o); // rozmiar tablicy z danymi
            some_object** array1 = new some_object * [n];
            for (int i = 0; i < n; i++)
            {
                some_object* so = new some_object();
                so->a = ((rand() << 15) + rand()) / m_double; // przykladowy sposob wylosowania pola typu double(ktore bedzie stanowilo klucz sortowania)
                so->b = 'a' + rand() % 26; // przykladowy sposob wylosowania pola typu char
                array1[i] = so;
            }
            // skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )
            some_object** array2 = new some_object*[n];
            memcpy(array2, array1, n * sizeof(some_object*)); // kopia
            // sortowanie przez kopcowanie
            clock_t t1 = clock();
            Binary_heap<some_object*>* bh = new Binary_heap<some_object*>(array1, n); // konstruktor kopca z mozliwoscia przekazania zewnetrznej tablicy ( ostatni argument wskazuje kierunek naprawy : top - down lub bottom - up )
            bh->heap_sort();
            clock_t t2 = clock();
            cout << bh->to_string();
            t2 = clock();
             // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
            // sortowanie kubelkowe
            t1 = clock();
            bucket_sort_s<some_object*>(array2, n, 1.0); // trzeci argument wskazuje, ze liczby sa z przedzialu[0, 1]
            t2 = clock();
            /*for (int i = 0; i < 5; i++)
            {
                cout << *array2[i] << "  ";
            }*/
            // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
            // sprawdzenie zgodnosci tablic array1 , array2 i wypis informacji o zgodnosci na ekran
            delete[] array1;
            delete[] array2;
        }
        return 0;
}