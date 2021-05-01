#include <stdio.h>
#include <math.h>
#include <string.h>

int SHOW_INTERATION_FLAG = 0;
int SHOW_ROOTCALC_FLAG = 0;

// Данные для проверки интеграла - Функция - Доказательство коррекности через вольфрам - правильный ответ
long double test_integral_func1(long double x);
// long double test_integral_func1(long double x) { return 0.5 * x * x - 6; }
// 0.5x^2 - 6 -> https://www.wolframalpha.com/input/?i=integrate+0.5x%5E2+-+6+from+1+to+8
// рассмотрим промежуток [1;8]
long double ans_integral_func1 = 43.1667;

long double test_integral_func2(long double x);
// long double test_integral_func2(long double x) { return x * 4 + 3; }
// 4x + 3 -> https://www.wolframalpha.com/input/?i=integrate+4x+%2B+3+from+-2000+to+1000
// рассмотрим промежуток [-2000;1000]
long double ans_integral_func2 = -5991000;

// long double test_integral_func3(long double x) { return pow(M_E, x); }
// // e^x -> https://www.wolframalpha.com/input/?i=integrate+f%28x%29+%3D+e%5Ex+from+1+to+5
// // рассмотрим промужеток [1;5]
// long double ans_integral_func3 = 145.69;

// Данные для проверки корня - Функция - Доказальство коррекности через вольфрам - правильный ответ
// long double test_root_0(long double x) { return 0; }            // OX
long double test_root_0(long double x);
long double test_root_f1(long double x);
long double test_root_g1(long double x);
// long double test_root_f1(long double x) { return x; } 
//long double test_root_g1(long double x) { return -x; }
// x = -x -> тут даже вольфрам не нужен
// рассмотрим промежуток [-10000;10000]
long double ans_root_func1 = 0;

long double test_root_f2(long double x) { return -pow(x, 4) + x * x - x; }
// -x^4 + x^2 - x -> https://www.wolframalpha.com/input/?i=-x%5E4+%2B+x%5E2+-+x+%3D+0
// рассмотрим промежуток [-1.5; -1.0] - пересечение с OX
long double ans_root_func2 = -1.3247;

long double test_root_f3(long double x) { return sqrt(x) + x; }
// sqrt(x) + x -> https://www.wolframalpha.com/input/?i=real+sqrt%28x%29+%2B+x
// рассмотрим промужеток [0;3] - пересечение с OX
long double ans_root_func3 = 0;

long double integral(long double (*f) (long double), long double a, long double b, long double eps) { // используется метод Симпсона
    if (SHOW_INTERATION_FLAG) printf("a = %6Lf b = %6Lf eps = %6Lf\n", a, b, eps);
    // оценим шаг интегрирования
    long double grade = pow(eps, 0.25);
    //long double grade = eps2;
    // прикинем кол-во шагов в разбиении
    int n = ceil((b - a) / grade);
    // округлим до ближайшего целого делящегося на 4 в большую сторону
    n += (4 - (n % 4)) % 4;
    if (SHOW_INTERATION_FLAG) printf("parts = %d\n", n);

    // найдём шаг и двойной шаг - заведём новую переменную
    long double h = (b - a) / n;
    if (SHOW_INTERATION_FLAG) printf("h = %Lf\n", h);
    // посчитаем значение интеграла в каждой рассмотренной точке - сохраним 
    //после это в массив 
    long double value[n + 1];
    long double start = a;
    // printf("        i              start              value\n");
    for (int i = 0; i <= n; ++i) { 
        // пишем value[i] = f(x), где x - нужное значение под шагом
        value[i] = f(start);
        // printf("%9d %18.4lf %18.4Lf\n", i, start, value[i]);
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
    if (fabsl(res2 - res1) / 15 <= eps) {
        printf("Calculated correctly - Difference less than eps\n");
    }
    printf("res1 = %Lf res2 = %Lf\n", res1, res2);
    return res1;
}

long double root(long double (*f)(long double), long double (*g)(long double), long double a, long double b, long double eps) {
    // Взяли готовую формулу
    if (SHOW_ROOTCALC_FLAG) {
        printf("a = %6Lf b = %6Lf eps = %6Lf\n", a, b, eps);
    }
    int counter = 0;
    while (fabsl(b - a) > eps) { 
        counter++;
        long double t = b;
        b = a - (g(a) - f(a)) * (b - a) / (g(b) - f(b) - g(a) + f(a));
        a = t;
    }
    if (SHOW_ROOTCALC_FLAG) {
        printf("Root is calculated with %d iterations\n", counter);
        printf("%Lf\n", b);
    }
    return b;
}

void test(long double a, long double b, long double eps) { 
    printf("%Lf", a);
    if (fabsl(b - a) < eps) 
        printf(" - answer is correct\n");
    else
        printf(" - answer is incorrect, %Lf - is correct\n", b);
    puts("");
}

void help_key(char *argv[]) {
    puts(""); 
    printf("Usage: %s [-help] [-root] [-int]\n\n", argv[0]);
    puts("Options:");
    puts("  -help             Shows usage and option settings.");
    puts("                    Can only be used as first and only option.\n");
    puts("  -root             Shows amount of iterations during root calculation,");
    puts("                    boundaries and precision.\n");
    puts("  -int              Shows amount of parts, that function is divided on,");
    puts("                    integration boundatries and precision.\n");
    puts("You can only run using showing options or -help.");
}

int main(int argc, char *argv[]) { 
    if (argc > 3) {
        puts("Wrong usage!");
        printf("Try %s -help for information\n", argv[0]);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        help_key(argv);
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        if (SHOW_ROOTCALC_FLAG == 0 && strcmp(argv[i], "-root") == 0) { 
            SHOW_ROOTCALC_FLAG = 1;
        }
        if (SHOW_INTERATION_FLAG == 0 && strcmp(argv[i], "-int") == 0) { 
            SHOW_INTERATION_FLAG = 1;
        }
    }

    printf("debug : %Lf\b", test_root_f1(1.0));

    puts("  Integral Test Results\n");
    puts("f(x) = 0.5x^2 - 6");
    long double test_integral_val1 = integral(test_integral_func1, 1, 8, 0.0001);
    test(test_integral_val1, ans_integral_func1, 0.0001);
    puts("f(x) = 4x + 3");
    long double test_integral_val2 = integral(test_integral_func2, -2000, 1000, 0.0001);
    test(test_integral_val2, ans_integral_func2, 0.0001);
    // puts("f(x) = e^x");
    // long double test_integral_val3 = integral(test_integral_func3, 1, 5, 0.0001);
    // test(test_integral_val3, ans_integral_func3, 0.01);
    
    puts("  Root Test Results\n");
    puts("f(x) = x and g(x) = -x");
    long double test_root_val1 = root(test_root_f1, test_root_g1, -10000, 10000, 0.00001);
    test(test_root_val1, ans_root_func1, 0.00001);
    puts("f(x) = -x^4 + x^2 - x and OX");
    long double test_root_val2 = root(test_root_f2, test_root_0, -1.5, -1, 0.0001);
    test(test_root_val2, ans_root_func2, 0.0001);
    puts("f(x) = sqrt(x) + x and OX");
    long double test_root_val3 = root(test_root_f3, test_root_0, 0, 3, 0.000001);
    test(test_root_val3, ans_root_func3, 0.000001);
    
    return 0;
}
