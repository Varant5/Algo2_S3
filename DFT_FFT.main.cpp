//ALGO2 IS1 222A LAB10
//Łukasz Kasztelan
#include <complex>
#include <cmath>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double pi = acos(-1);
const complex<double> i(0, 1);

complex<double>* DFT(double* f, int N) {
    complex<double>* c = new complex<double>[N];
    for (int k = 0; k < N; k++) {
        complex<double> sum(0, 0);
        for (int n = 0; n < N; n++) {
            complex<double> x(f[n], 0);
            complex<double> e = exp(complex<double>(0, -2 * pi * k * n / N));
            sum = sum + x * e;
        }
        c[k] = sum;
    }
    return c;
}

complex<double>* FFT(double* fn, int N, int step = 1) {
    if (N == 1) {
        complex<double>* F = new complex<double>[1];
        F[0] = fn[0];
        return F;
    }
    complex<double>* F_even = FFT(fn, N / 2, step * 2);
    complex<double>* F_odd = FFT(fn + step, N / 2, step * 2);
    complex<double>* F = new complex<double>[N];
    for (int k = 0; k < N / 2; k++) {
        double angle = 2 * pi * k / N;
        complex<double> w(cos(angle), -sin(angle));
        F[k] = F_even[k] + w * F_odd[k];
        F[k + N / 2] = F_even[k] - w * F_odd[k];
    }
    delete[] F_even;
    delete[] F_odd;
    return F;
}

double calculateError(complex<double>* cDFT, complex<double>* cFFT, int N) {
    double error = 0;
    for (int i = 0; i < N; i++) {
        double result = abs(cDFT[i] - cFFT[i]);
        error += result;
    }
    error /= N;
    return error;
}
void printFFT(complex<double>* cFFT, int N) {
    cout << "Wspolczynniki FFT: " << endl;
    for (int i = 0; i < N; i++) {
        cout << cFFT[i].real() << " + " << cFFT[i].imag() << "i" << endl;
    }
}
void printDFT(complex<double>* cDFT, int N) {
    cout << "Wspolczynniki DFT: " << endl;
    for (int i = 0; i < N; i++) {
        cout << cDFT[i].real() << " + " << cDFT[i].imag() << "i" << endl;
    }
}

int main() {
    const int MAX_ORDER = 13; // maksymalny rzad wielkosci danych ( w ramach bazy 2)
    const bool PRINT_COEFS = false; // przelacznik do ewentualnego wypisu na ekran rezultatow DFT , FFT
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int N = 1 << o; // rozmiar problemu ( potega dwojki - przesuniecie bitowe w lewo )
        printf("N: % i \n", N);
        double* f = new double[N];
        for (int n = 0; n < N; n++)
            f[n] = n / (double)N; // przykladowe dane ( tu akurat : probki funkcji liniowej )
        clock_t t1 = clock();
        complex < double >* cDFT = DFT(f, N);
        clock_t t2 = clock();
        double dft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("DFT time[ms] : % f \n", dft_time);
        t1 = clock();
        complex < double >* cFFT = FFT(f, N);
        t2 = clock();
        double fft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("FFT time[ms] : % f \n", fft_time);
        printf("mean error : % e \n", calculateError(cDFT, cFFT, N));       
        if (PRINT_COEFS) {
            printDFT(cDFT, N);
            printFFT(cFFT, N);
        }
        printf("______%d______ \n", N);

        delete[] f;
        delete[] cDFT;
        delete[] cFFT;
    }
    return 0;

}
