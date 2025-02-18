//ALGO IS1 kl51000 LAB01
//Łukasz Kasztelan
//kl51000@zut.edu.pl
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <sstream>
#include <time.h>
#include <cstdlib>
using namespace std;
struct some_object;
template<typename T>
class lista
{
public:
    lista() noexcept
        : glowa(nullptr), dlugosc(0), ogon(nullptr)
    {
    }
    ~lista()
    {
        while (glowa)
        {
            wezel_listy* temp = glowa;
            glowa = temp->nast;
            delete temp;
        }
    }
    struct wezel_listy
    {
        wezel_listy(const T& dane, wezel_listy* nast = nullptr, wezel_listy* prev = nullptr)
            : dane(dane), nast(nast), prev(prev)
        {
        }
        ~wezel_listy()
        {
            nast = nullptr;
            prev = nullptr;
        }
        T dane;
        wezel_listy* nast;
        wezel_listy* prev;
    };
private:
    wezel_listy* glowa;
    wezel_listy* ogon;
    unsigned dlugosc;
public:
    unsigned pobierz_dlugosc() const noexcept
    {
        return dlugosc;
    }
    void wstaw_na_poczatek(const T& dane)
    {
        if (dlugosc == 0)
        {
            glowa = new wezel_listy(dane);
            ogon = glowa;
        }
        else
        {
            wezel_listy* element = new wezel_listy(dane);
            element->nast = glowa;
            glowa->prev = element;
            glowa = element;
        }
        ++dlugosc;
    }
    void wstaw_na_koniec(const T& dane)
    {
        if (dlugosc == 0)
        {
            glowa = new wezel_listy(dane);
            ogon = glowa;
        }
        else
        {
            wezel_listy* element = new wezel_listy(dane);
            element->prev = ogon;
            ogon->nast = element;
            ogon = element;
        }
        ++dlugosc;
    }
    void del_front()
    {
        if (dlugosc == 0)
        {
            throw domain_error("Lista jest pusta");
        }
        else if (dlugosc == 1)
        {
            delete ogon;
            glowa = NULL;
            ogon = NULL;
            dlugosc--;
            return;

        }
        else
        {
            wezel_listy* tmp = glowa;
            glowa = glowa->nast;
            glowa->prev = nullptr;
            delete tmp;
            dlugosc--;
        }
    }
    void del_back()
    {
        if (dlugosc == 0)
        {
            throw domain_error("Lista jest pusta");
        }
        else if (dlugosc == 1)
        {
            delete glowa;
            glowa = NULL;
            ogon = NULL;
            dlugosc--;
            return;

        }
        else if (dlugosc > 1)
        {
            wezel_listy* tmp = ogon;
            ogon = ogon->prev;
            ogon->nast = nullptr;
            delete tmp;
            dlugosc--;
        }
    }
    void wstaw_w_indeks(const T& dane, int indeks)
    {
        if (indeks == 0)
        {
            wstaw_na_poczatek(dane);
            return;
        }
        else if (indeks == dlugosc)
        {
            wstaw_na_koniec(dane);
            return;
        }
        else
        {
            wezel_listy* tmp = glowa;
            for (unsigned i = 0; i < indeks; i++)
            {
                tmp = tmp->nast;
            }
            wezel_listy* nowy = new wezel_listy(dane, tmp->nast, tmp->prev);
            tmp->dane = dane;
            tmp->prev->nast = nowy;
            if (tmp->nast)
            {
                tmp->nast->prev = nowy;
            }          
            return;
        }
    }
    wezel_listy* znajdz(const T& dane1)
    {
        wezel_listy* tmp = glowa;
        for (int i = 0; i < dlugosc; i++)
        {
            if (tmp->dane == dane1)
            {
                return tmp;
            }
            else
            {
                tmp = tmp->nast;
            }
        }
        return 0;
    }
    bool znajdz_usun(const T& dane1)
    {
        wezel_listy* tmp = glowa;
        for (int i = 0; i < dlugosc; i++)
        {
            if (tmp->dane == dane1)
            {
                if (tmp->prev == nullptr) // glowa
                {
                    del_front();
                }
                else if (tmp->nast == nullptr)
                {
                    del_back();
                }
                else
                {
                    tmp->prev->nast = tmp->nast;
                    tmp->nast->prev = tmp->prev;
                    delete tmp;
                }
                dlugosc--;
                return true;
            }
            else
            {
                tmp = tmp->nast;
            }
        }
        return false;
    }
    void usun_liste()
    {
        for (unsigned i = dlugosc; i > 0; i--)
        {
            del_front();
        }
    }
    string wypisz() const
    {
        if (dlugosc < 10)
        {
            return to_string();
        }
        if (dlugosc == 0)
            return "[]";
        ostringstream str; // pamiętaj o #include <sstream>
        str << "3 pierwsze elementy\n[" << glowa->dane;
        auto p = glowa->nast;
        for (int i = 0; i < 2; i++)
        {
            str << ", " << p->dane;
            p = p->nast;
        }
        str << "]\n 3 ostatnie elementy\n[" << ogon->prev->prev->dane;
        p = ogon->prev;
        for (int i = 0; i < 2; i++)
        {
            str << ", " << p->dane;
            p = p->nast;
        }
        str << "]";
        return str.str(); // wydobycie napisu ze strumienia
    }
    void zwrot(int kol)
    {
        wezel_listy* tmp = glowa;
        for (int i = 0; i <= kol; i++)
        {
            if (i == kol)
            {

                cout << "..................." << endl;
                cout << tmp->dane << endl;
                cout << "..................." << endl;
            }
            else
            {
                tmp = tmp->nast;
            }
        }
    }
    void zamiana(const T& dane1, int kol)
    {
        wezel_listy* tmp = glowa;
        for (int i = 0; i <= kol; i++)
        {
            if (i == kol)
            {
                tmp->dane = dane1;
            }
            else
            {
                tmp = tmp->nast;
            }
        }
    }
    string to_string() const
    {
        if (dlugosc == 0)
            return "[]";
        ostringstream str; // pamiętaj o #include <sstream>
        str << "[" << glowa->dane;
        for (auto p = glowa->nast; p; p = p->nast)
            str << ", " << p->dane;
        str << "]";
        return str.str(); // wydobycie napisu ze strumienia
    }
};
struct some_object
{
    int a;
    char b;
};
ostream& operator<<(ostream& out, const some_object& dane)
{
    return out << dane.a << " " << dane.b;
}
bool operator==(const some_object& a, const some_object& b)
{
    return a.a == b.a && a.b == b.b;
}

int main()
{
   /* {
        lista<int> l;
        l.wstaw_na_koniec(1);
        l.wstaw_na_koniec(1);
        l.wstaw_w_indeks(2,1);
        cout<<l.wypisz();
        l.znajdz(1);
        cout << l.pobierz_dlugosc();
        return 0;
    }*/
    srand(time(NULL));
    char random;
    const int MAX_ORDER = 6; // maksymalny rzad wielkosci rozmiaru dodawanych danych
    lista <some_object>* list = new lista <some_object>(); // stworzenie listy
    for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
    {
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do listy
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            random = ((rand() % ('z' + 1 - 'a')) + 'a');
            some_object so = some_object{ rand() % 10001, random };// losowe dane
            list->wstaw_na_poczatek(so);
        }
        random = ((rand() % ('z' + 1 - 'a')) + 'a');
        clock_t t2 = clock();
        // wypis na ekran aktualnej postaci listy ( skrotowej ) i pomiarow czasowych
        cout << list->wypisz();
        cout << "Czas dod:" << t2 - t1 << endl;
        // wyszukiwanie i usuwanie z listy
        const int m = pow(10, 4); // liczba prob wyszukania
        t1 = clock();
        list->wstaw_w_indeks(some_object{ rand() % 10001, random }, 2);
        for (int i = 0; i < m; i++)
        {
            random = ((rand() % ('z' + 1 - 'a')) + 'a');            
            some_object so1 = some_object{ rand() % 10001, random };// losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
            list->znajdz_usun(so1);
            so1 = some_object{ NULL };
        }
        cout << list->pobierz_dlugosc() << endl;
        t2 = clock();
        cout << list->wypisz();
        cout << "Czas usu:" << t2 - t1 << endl;
        list->zwrot(2);
        list->znajdz(some_object{ rand() % 10001, random });
        list->usun_liste(); // czyszczenie listy wraz z uwalnianiem pamieci danych
    }
    cout << "Dlugosc: " << list->pobierz_dlugosc();
    delete list;
    return 0;
}