#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const long double TEST_INTEGRATION_1 = 8.325;   // https://www.wolframalpha.com/input/?i=integral+0.35x%5E2+-+0.95x+%2B+2.7+from+1+to+4
const long double TEST_INTEGRATION_2 = 516;     // https://www.wolframalpha.com/input/?i=integral+3x+%2B+1+from+8+to+20
const long double TEST_INTEGRATION_3 = 0.9163;  // https://www.wolframalpha.com/input/?i=integral+1+%2F+%28x+%2B+2%29+from+2+to+8        

const long double TEST_ROOT_1 = 0.4482;         // https://www.wolframalpha.com/input/?i=3x+%2B+1+%3D+0.35x%5E2+-+0.95x+%2B+2.7
const long double TEST_ROOT_2 = -0.1529;        // https://www.wolframalpha.com/input/?i=3x+%2B+1+%3D+1+%2F+%28x+%2B+2%29
const long double TEST_ROOT_3 = -1.8211;        // https://www.wolframalpha.com/input/?i=1+%2F+%28x+%2B+2%29+%3D+0.35x%5E2+-+0.95x+%2B+2.7

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

void correct(long double a, long double b, long double eps) { 
    printf("%Lf", a);
    if (fabsl(b - a) < eps) 
        printf(" - answer is correct\n");
    else
        printf(" - answer is incorrect, %Lf - is correct\n", b);
    puts("");
}

void test_integration() { 
    puts("Choose one function of these to test integration\nWrite down only number");
    puts("[1]               0.35x^2 - 0.95x + 2.7 on [1;4]");
    puts("[2]               3x + 1 on [8;20]");
    puts("[3]               1 / (x + 2) on [2;8]");
    puts("");
    int test; scanf("%d", &test);
    system("clear");
    if (test == 1) { 
        long double ans = integral(f1, 1, 4, 0.001);
        correct(ans, TEST_INTEGRATION_1, 0.001);
    } else if (test == 2) { 
        long double ans = integral(f2, 8, 20, 0.001);
        correct(ans, TEST_INTEGRATION_2, 0.001);
    } else if (test == 3) { 
        long double ans = integral(f3, 2, 8, 0.0001);
        correct(ans, TEST_INTEGRATION_3, 0.0001);
    } else {
        puts("Wrong usage! Number should be only 1, 2 or 3");
    }
}

void test_root() { 
    puts("Choose two function of these to test root\nWrite down only two numbers");
    puts("[1]               0.35x^2 - 0.95x + 2.7");
    puts("[2]               3x + 1");
    puts("[3]               1 / (x + 2)");
    puts("");
    int test1, test2; scanf("%d%d", &test1, &test2);
    system("clear");
    if (test1 == 1 && test2 == 2 || test1 == 2 && test2 == 1) { 
        long double ans = root(f1, f2, -2, 1, 0.0001);
        correct(ans, TEST_ROOT_1, 0.0001);
    } else if (test1 == 2 && test2 == 3 || test1 == 3 && test2 == 2) { 
        long double ans = root(f2, f3, -2, -2, 0.0001);
        correct(ans, TEST_ROOT_2, 0.0001);
    } else if (test1 == 1 && test2 == 3 || test1 == 3 && test2 == 1) { 
        long double ans = root(f1, f3, -2, 2, 0.0001);
        correct(ans, TEST_ROOT_3, 0.0001);
    } else {
        puts("Wrong usage! Example: 2 1 or 1 3");
    }
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

    if (argc == 2 && strcmp(argv[1], "-test") == 0) {
        system("clear");
        puts("Choose one number");
        puts("");
        puts("[1] Integrate test");
        puts("[2] Root test");
        int test; scanf("%d", &test);
        system("clear");
        if (test == 1) test_integration();
        else if (test == 2) test_root();
        else puts("Wrong usage! Number should be only 1 or 2");
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
        if (SHOW_INTERATION_FLAG + SHOW_ROOTCALC_FLAG == 0) { 
            puts("Wrong usage!");
            printf("Try %s -help for information\n", argv[0]);
        }
    }

    system("clear");

    long double root_f1_f2_x = root(f1, f2, -10, 5, 0.00001);
    printf("root of f1 and f2 x = % *.4Lf y1 = % *.4Lf y2 = % *.4Lf\n\n", 8, root_f1_f2_x, 8, f1(root_f1_f2_x), 8, f2(root_f1_f2_x));
    
    long double root_f2_f3_x = root(f2, f3, -10, 10, 0.00001);
    printf("root of f2 and f3 x = % *.4Lf y1 = % *.4Lf y2 = % *.4Lf\n\n", 8, root_f2_f3_x, 8, f2(root_f2_f3_x), 8, f3(root_f2_f3_x));

    long double root_f1_f3_x = root(f1, f3, -10, 10, 0.00001);
    printf("root of f1 and f3 x = % *.4Lf y1 = % *.4Lf y3 = % *.4Lf\n\n", 8, root_f1_f3_x, 8, f1(root_f1_f3_x), 8, f3(root_f1_f3_x));
        
    long double ans =   integral(f1, root_f1_f3_x, root_f1_f2_x, 0.00001)
                       -integral(f3, root_f1_f3_x, root_f2_f3_x, 0.00001)
                       -integral(f2, root_f2_f3_x, root_f1_f2_x, 0.00001);

    printf("Ans = %Lf\n", ans);
    return 0;
}
