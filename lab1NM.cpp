#include <bits/stdc++.h>

using namespace std;

double F(double x){
    return x * x * x - 4 * x * x - 4 * x + 13;
}

double dF (double x){
    return 3 * x * x - 8 * x - 4;
}

double Phi (double x){
    return cbrt(4 * x * x + 4 * x - 13);
}

void OutputIter(int it){
    if (it == 0) cout << "zero";
    else if (it == 1) cout << "1-st";
    else if (it == 2) cout << "2-nd";
    else if (it == 3) cout << "3-rd";
    else cout << it << "-th";
    cout << " iteration: ";
}

void Simple(double eps){
    cout << "Simple iteration method\n\n";
    double xn = 4.5;
    double q = 36 / (3 * cbrt(67 * 67));
    double nextx;
    int i = 0;
    cout << "A priori estimation is equal to: ";
    cout << int(log(abs(Phi(xn)-xn) / ((1 - q) * eps)) / log(1 / q)) + 1 << '\n';
    cout << "q = " << q << '\n';
    OutputIter(i++);
    cout << fixed << setprecision(8) << "xn = " << xn << " xn - phi(xn) = " << xn - Phi(xn) << '\n';
    while (true){
        nextx = Phi(xn);
        if (abs(nextx - xn) < (1 - q) / q * eps){
            break;
        }
        OutputIter(i++);
        xn = nextx;
        cout << fixed << setprecision(8) << "xn = " << xn << " xn - phi(xn) = " << xn - Phi(xn) << '\n';
    }
}

int sign(double x){
    if (x > 0) return 1;
    else if (x < 0) return -1;
    else return 0;
}

void Dichotomy(double eps){
    cout << "Dichotomy method\n\n";
    double an = 4, bn = 5;
    cout << "n0(eps) >= " << int(log2((bn - an) / eps) + 1) << '\n';
    double xn = (an + bn) / 2;
    int i = 0;
    OutputIter(i++);
    cout << fixed << setprecision(8) << "an = " << an << " bn = " << bn << " xn = " << xn << '\n';
    while (true){
        double anext = (sign(F(an)) == sign(F(xn)) ? xn : an);
        double bnext = (sign(F(bn)) == sign(F(xn)) ? xn : bn);
        double xnext =(anext + bnext) / 2;
        OutputIter(i++);
        cout << fixed << setprecision(8) << "an = " << anext << " bn = " << bnext << " xn = " << xnext << '\n';
        if (abs(xnext - xn) < eps) break;
        an = anext;
        bn = bnext;
        xn = xnext;
    }
}

void Relaxation(double eps){
    cout << "Relaxation method\n\n";
    double a = 4, b = 5;
    double M = abs(dF(b));
    double m = abs(dF(a));
    double q = double(M - m) / (M + m);
    cout << "m1 = " << m << " M1 = " << M << " tao = 2 / (m1 + M1) = " << 2. / 43;
    cout << " q = (M1 - m1) / (M1 + m1) = " << q << '\n';
    cout << "A priori estimation is equal to: ";
    cout << int(log(0.5 / eps) / log(1 / q) + 1) << '\n';
    double tao = 2 / (m + M);
    double x0 = b, xn;
    double dif;
    int i = 0;
    OutputIter(i++);
    cout << fixed << setprecision(8) << "xn = " << x0 << " F(xn) = " << F(x0) << '\n';
    do{
        xn = x0 - tao * F(x0);
        dif = abs(xn - x0);
        x0 = xn;
        OutputIter(i++);
        cout << fixed << setprecision(8) << "xn = " << xn << " F(xn) = " << F(xn) << '\n';
    }
    while(dif > eps);
}

int main (){
    double eps = 1e-4;
    Relaxation(eps);
    Dichotomy(eps);
    Simple(eps);
    return 0;
}
