#include <stdio.h>
#include <math.h>
#include <string.h>

int SHOW_INTERATION_FLAG = 0;
int SHOW_ROOTCALC_FLAG = 0;

long double f1(long double x); // 0.35x^2 - 0.95x + 2.7
long double f2(long double x); // 3x + 1
long double f3(long double x); // 1 / (x + 2)

long double integral(long double (*f) (long double), long double a, long double b, long double eps) { // используется метод Симпсона
    if (SHOW_INTERATION_FLAG) printf("a = %6Lf b = %6Lf eps = %6Lf\n", a, b, eps);
    // оценим шаг интегрирования
    long double grade = pow(eps, 0.33);
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
    if (SHOW_INTERATION_FLAG)  printf("        i            start            value\n");
    for (int i = 0; i <= n; ++i) { 
        // пишем value[i] = f(x), где x - нужное значение под шагом
        value[i] = f(start);
        if (SHOW_INTERATION_FLAG) printf("%9d % *.4Lf % *.4Lf\n", i, 16, start, 16, value[i]);
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
    } else {
        printf("ERROR! Calculated incorrectly - Difference more than eps\n");
    }
    printf("res1 = %Lf res2 = %Lf eps = %Lf\n\n", res1, res2, eps);
    return res1;
}

long double root(long double (*f)(long double), long double (*g)(long double), long double a, long double b, long double eps) {
    // Взяли готовую формулу
    if (SHOW_ROOTCALC_FLAG)  {
        printf("a = %6Lf b = %6Lf eps = %6Lf\n\n", a, b, eps);
        printf("        i                a                b\n");
    }
    int counter = 0;
    while (fabsl(b - a) > eps) { 
        counter++;
        long double t = b;
        b = a - (g(a) - f(a)) * (b - a) / (g(b) - f(b) - g(a) + f(a));
        a = t;
        if (SHOW_ROOTCALC_FLAG) printf("%9d % *.4Lf % *.4Lf\n", counter, 16, a, 16, b);
    }
    if (SHOW_ROOTCALC_FLAG) {
        printf("Root is calculated with %d iterations\n", counter);
        printf("%Lf\n\n", b);
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

    long double root_f1_f2_x = root(f1, f2, -10, 5, 0.0001);
    printf("root of f1 and f2 x = % *.4Lf y1 = % *.4Lf y2 = % *.4Lf\n\n", 8, root_f1_f2_x, 8, f1(root_f1_f2_x), 8, f2(root_f1_f2_x));
    
    long double root_f2_f3_x = root(f2, f3, -10, 10, 0.0001);
    printf("root of f2 and f3 x = % *.4Lf y1 = % *.4Lf y2 = % *.4Lf\n\n", 8, root_f2_f3_x, 8, f2(root_f2_f3_x), 8, f3(root_f2_f3_x));

    long double root_f1_f3_x = root(f1, f3, -10, 10, 0.0001);
    printf("root of f1 and f3 x = % *.4Lf y1 = % *.4Lf y3 = % *.4Lf\n\n", 8, root_f1_f3_x, 8, f1(root_f1_f3_x), 8, f3(root_f1_f3_x));
        
    long double ans =   integral(f1, root_f1_f3_x, root_f1_f2_x, 0.0001)
                       -integral(f3, root_f1_f3_x, root_f2_f3_x, 0.0001)
                       -integral(f2, root_f2_f3_x, root_f1_f2_x, 0.0001);

    printf("Ans = %Lf\n", ans);
    return 0;
}
