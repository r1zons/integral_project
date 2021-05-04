# integral_project
Необходимо написать программу с вставками из NASM, которая считает площадь фигуры ограниченной 3 заранее заданными линиями. Для удобства также необходимо подготовить Makefile. Программа также должна поддерживать ключи, например, -help.
![image](https://user-images.githubusercontent.com/63977372/117045281-020a9380-ad18-11eb-971d-12ac84e9be67.png)
Данный график иллюстрирует область, площадь которой надо искать.
f1 = 0.35x^2 - 0.95x + 2.7 - синий
f2 = 3x + 1 - жёлтый
f3 = 1 / (x + 2) - красный

Корень f1 = f2 = 0.4482 https://www.wolframalpha.com/input/?i=3x+%2B+1+%3D+0.35x%5E2+-+0.95x+%2B+2.7

Корень f2 = f3 = -0.1529 https://www.wolframalpha.com/input/?i=3x+%2B+1+%3D+1+%2F+%28x+%2B+2%29 (корень - 7/6)

Корень f1 = f3 = -1.8211 https://www.wolframalpha.com/input/?i=1+%2F+%28x+%2B+2%29+%3D+0.35x%5E2+-+0.95x+%2B+2.7

Надо найти соответствующие интегралы и просто вычесть из площади под жёлтым графиком площадь двух оставшихся
Площадь под f1 на [-1.8211;0.4482] s1 = 8.3221 https://www.wolframalpha.com/input/?i=integrate+0.35x%5E2+-+0.95x+%2B+2.7+from+-1.8211+to+0.4482

Площадь под f2 на [-0.1529;0.4482] s2 = 0.867357 https://www.wolframalpha.com/input/?i=integrate+3x+%2B+1+from+-0.1529+to+0.4482

Площадь под f3 на [-1.8211;-0.1529] s3 = 2.33455 https://www.wolframalpha.com/input/?i=integrate+1%2F%28x+%2B+2%29+from+-1.8211+to+-0.1529

ans = s1 - s2 - s3 = 8.3221 - 0.867357 - 2.33455 = 5.120193 (проверьте!)
