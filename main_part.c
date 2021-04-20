#include <stdio.h>
#include <math.h>

double f(double x) { 
    return x * x + 4;
}

void root(double a, double b, double eps1) { 
        
}

void integral(double a, double b, double eps2) { // используется метод Симпсона
    // оценим шаг интегрирования
    long double grade = pow(eps2, 0.25);
    //long double grade = eps2;
    // прикинем кол-во шагов в разбиении
    int n = ceil((b - a) / grade);
    printf("%d\n", n);
    // округлим до ближайшего целого делящегося на 4 в большую сторону
    n += (4 - (n % 4)) % 4;
    // найдём шаг и двойной шаг - заведём новую переменную
    long double h = (b - a) / n;
    printf("h = %Lf\n", h);
    // посчитаем значение интеграла в каждой рассмотренной точке - сохраним 
    //после это в массив 
    long double value[n + 1];
    double start = a;
    for (int i = 0; i <= n; ++i) { 
        // пишем value[i] = f(x), где x - нужное значение под шагом
        value[i] = f(start);
        printf("i = %9d start = %9.4lf %9.4Lf\n", i, start, value[i]);
        start += h;
    }
    
    long double res1 = value[0] + value[n];
    long double res2 = res1;
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 1) res1 += 4 * value[i];
        else res1 += 2 * value[i];
    }
    for (int i = 2; i < n; i += 2) {
        if (i % 4 == 2) res2 += 4 * value[i];    
        else res2 += 2 * value[i];
    }
    res1 *= h / 3;
    res2 *= 2 * h / 3;
    if (fabsl(res2 - res1) / 15 <= eps2) {
        printf("Calculated correctly\n");
    }
    printf("%Lf %Lf", res1, res2);
}

int main(void) { 
    double a, b, eps; scanf("%lf%lf%lf", &a, &b, &eps);
    integral(a, b, eps);
    return 0;
}
