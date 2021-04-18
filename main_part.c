#include <stdio.h>
#include <math.h>

void root(double a, double b, double eps1) { 

}

void integral(double a, double b, double eps2) { // используется метод Симпсона
    // оценим шаг интегрирования
    long double grade = pow(eps2, 0.25);
    // прикинем кол-во шагов в разбиении
    int n = ceil((b - a) / grade);
    // округлим до ближайшего целого делящегося на 4 в большую сторону
    n += (4 - (n % 4)) % 4;
    // найдём шаг и двойной шаг - заведём новую переменную, чтобы не домножать 
    // на 2 каждый раз
    long double h = (b - a) / n;
    long double h2 = 2 * h;
    // посчитаем значение интеграла в каждой рассмотренной точке - сохраним 
    //после это в массив 
    long double value[n];
    for (int i = 0; i < n; ++i) { 
        // пишем value[i] = f(x), где x - нужное значение под шагом
    }

}

int main(void) { 

    return 0;
}
