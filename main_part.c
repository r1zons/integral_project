#include <stdio.h>
#include <math.h>

long double func1(long double x) { 
    return x * x - 4;
}

long double func2(long double x) { 
    return 3 * x;
}

long double func3(long double x) { 
    return 1 / (x + 2);
}

void root(long double (*f)(long double), long double (*g)(long double), long double a, long double b, long double eps) {
    while (fabsl(b - a) > eps) { 
        long double t = b;
        b = a - (g(a) - f(a)) * (b - a) / (g(b) - f(b) - g(a) + f(a));
        a = t;
    }
    puts("Root is calculated");
    printf("%Lf\n", b);
}

void integral(long double (*f) (long double), long double a, long double b, long double eps2) { // используется метод Симпсона
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
    printf("        i              start              value\n");
    for (int i = 0; i <= n; ++i) { 
        // пишем value[i] = f(x), где x - нужное значение под шагом
        value[i] = f(start);
        printf("%9d %18.4lf %18.4Lf\n", i, start, value[i]);
        start += h;
    }
    
    long double res1 = value[0] + value[n];
    long double res2 = res1;
    // сразу считаем результаты для шага h и 2h - res1 и res2, соответственно
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
    // проверка на правильность по Рунге
    if (fabsl(res2 - res1) / 15 <= eps2) {
        printf("Calculated correctly\nDifference less than eps\n");
    }
    printf("%Lf %Lf\n", res1, res2);
}

int main(void) { 
    long double a, b, eps1, eps2; 
    scanf("%Lf%Lf%Lf%Lf", &a, &b, &eps1, &eps2);
    printf("%Lf %Lf\n", a, b);
    integral(func2, a, b, eps1);
    root(func1, func2, a, b, eps2);
    return 0;
}
