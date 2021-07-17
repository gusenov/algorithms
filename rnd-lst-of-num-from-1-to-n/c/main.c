#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>  // https://stackoverflow.com/questions/2254075/using-true-and-false-in-c

typedef void (*solution_ptr_t)(int[], int);

// https://fuckingfunctionpointers.com/
void measure(solution_ptr_t solution, int list[], int N)
{
  // https://stackoverflow.com/questions/3557221/how-do-i-measure-time-in-c
  clock_t start = clock();

  solution(list, N);

  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("seconds = %f\n", seconds);
}

//---------------------------------------------------------------------------

// https://stackoverflow.com/questions/36244924/passing-static-array-as-an-argument
void print_arr(int list[], int N)
{
  for (int i = 0; i < N; ++i)
    printf("%d ", list[i]);
  printf("\n");
}

//---------------------------------------------------------------------------

bool check_solution(int list[], int N)
{
  for (int i = 0; i < N; ++i)
  {

    // Uniqueness check
    for (int j = 0; j < N; ++j)
    {
      if (i == j)
        continue;
      if (list[i] == list[j])
        return false;
    }

    bool found = false;
    for (int j = 0; j < N; ++j)
    {
        if (i + 1 == list[j])
        {
          found = true;
          break;
        }
    }
    if (!found)
    {
      return false;
    }

  }
  return true;
}

//---------------------------------------------------------------------------

// https://www.freepascal.org/docs-html/rtl/system/random.html
// https://stackoverflow.com/a/6219525/9370853
float RanNum()
{
  // a Real number between 0 and 1 is returned (0 included, 1 excluded)
  return rand() / (RAND_MAX + 1.0f);
  // https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
}

//---------------------------------------------------------------------------

void solution1(int list[], int N)
{
  int location = 0;

repeat:
  // Первый наивный подход генерировать число.
  list[location] = N * RanNum() + 1;
  // Примеры:
  //  [10 * 0 + 1] = [0 + 1] = [1] = 1
  //  [10 * 0.99 + 1] = [9.9 + 1] = [10.9] = 10
  //
  // [x] - https://ru.wikipedia.org/wiki/Целая_часть

  // Потом проверяем есть ли уже такое число.
  for (int i = 0; i < location; ++i)
    if (list[i] == list[location])
      goto repeat;  // https://docs.microsoft.com/en-us/cpp/c-language/goto-and-labeled-statements-c?view=msvc-160

  ++location;
  if (location < N)
    goto repeat;
}

//---------------------------------------------------------------------------

// Меняем подход: будем генерировать номер ячейки, а не число.
// Дуальность: можно генерировать число, можно генерировать номер ячейки.
/*     | 1         | 2
Ячейка | Итерация  | Генерация
Число  | Генерация | Итерация
*/
void solution2(int list[], int N)
{
  int location = 0;
  for (int i = 1; i <= N; ++i)
  {
    do
    {
      location = N * RanNum();
    }
    while (0 != list[location]);

    list[location] = i;
  }
}

// Первые несколько значений быстро займут свои места в списке;
// по мере заполнения списка становится все труднее и труднее помещать в него очередное значение.

//---------------------------------------------------------------------------

// Модифицируем подход.
// Если попали в занятую ячейку, то двигаемся от нее пока не найдем свободную.
void solution3(int list[], int N)
{
  int location = 0;
  for (int i = 1; i <= N; ++i)
  {
    location = N * RanNum();

    while (0 != list[location])       // Обнаружив заполненную ячейку,
      location = (location + 1) % N;  // проверяем следующие за ней до тех пор, пока не найдем свободную.

    list[location] = i;
  }
}

// Если в списке появится блок из подряд идущих заполненных клеток, то будет
// подсписок содержащий числа с сохранением их относительного порядка.
//
// Если первые 25 из 100 ячеек уже заполнены случайными числами.
// Тогда имеется 25%-я вероятность того, что очередная выбранная ячейка окажется среди первых 25,
// и соответствующее значение будет занесено в ячейку 26.
// При последующих выпаданиях одной из первых ячеек мы занесем соответствующие значения в 27, 28 и т.д. ячейки.
//
// Такое может случиться в любой части списка, и получается блок ячеек,
// значения которых последовательны или почти последовательны.
//
//                                 ** **    ** ** **                                          ** **                                                   ** ** **             ** **             ** **                            ** **    ** ***                            * *
// 40 57 3 7 46 4 58 13 2 23 30 36 60 61 68 70 71 72 9 33 20 10 41 65 73 75 44 62 42 50 64 76 78 79 81 27 48 59 26 67 15 8 83 56 84 16 14 25 85 88 39 90 91 92 80 51 19 87 93 94 17 95 12 43 54 55 74 22 52 69 77 96 47 66 45 97 98 11 99 100 21 63 37 18 82 89 86 32 49 5 6 29 31 28 34 1 24 35 38 53


//---------------------------------------------------------------------------

// Иной подход: генерируем не число и не ячейку, а количество шагов, которое
// нужно сделать вперед (шаг не засчитывается, если содержимое ячейки != 0).
// Количество шагов не превышает количества свободных ячеек, потому что
// зачем проходить по одной ячейке два раза, когда можно было остановиться на ней
// при первом прохождении.
void solution4(int list[], int N)
{
  int location = 0;
  int freeCount = N;  // счетчик свободных ячеек
  for (int i = 1; i <= N; ++i)
  {
    int steps = freeCount * RanNum() + 1;  // случайное число, не превышающее значения счетчика,
                                           // чтобы не было необходимости проходить по списку несколько раз
    while (steps > 0)
    {
      location = (location + 1) % N;
      if (0 == list[location])
        --steps;

      // Цикл всегда завершается, поскольку даже на последнем проходе остается
      // по крайней мере одна пустая ячейка.
    }

    list[location] = i;
    --freeCount;
  }
}

// Плюсы:
//  + Используем каждое сгенерированное число.
//  + Низкая вероятность записи последовательных значений в последовательные ячейки.
//    Такое может произойти, только если последовательные ячейки свободны,
//    а сгенерированное число сравнимо с единицией по модулю числа оставшихся свободными ячеек:
//                            steps ≡ 1 (mod freeCount)
//    иными словами steps и 1 имеют одинаковые остатки при делении на freeCount.

/*

Т.е. если мы количество шагов сгенерировали таким что делая один шаг сразу
попадаем в следующую клетку от текущей, которая к тому же должна быть свободной,
либо делаем круг и в результате на ней останавливаемся,
то будет запись последовательных значений.

| freeCount | 1 % freeCount   | steps % freeCount                |
| --------- | --------------- | -------------------------------- |
| 5         | 1 % 5 = 1       | 1 % 5 = 1, 6 % 5 = 1, 11 % 5 = 1 |
| 4         | 1 % 4 = 1       | 1 % 4 = 1, 5 % 4 = 1, 9 % 4 = 1  |
| 3         | 1 % 3 = 1       | 1 % 3 = 1, 4 % 3 = 1, 7 % 3 = 1  |
| 2         | 1 % 2 = 1       | 1 % 2 = 1, 3 % 2 = 1, 5 % 2 = 1  |
| 1         | 1 % 1 = 0       | 1 % 1 = 0, x % 1 = 0             |

Третий столбец должен вести себя также как и второй, поэтому сравниваем с ним.
Хотя steps не превышает freeCount, это сравнение имеет более широкий охват.

1) Case # 1

Предпоследняя итерация:

i = 4
location = 4 (заняли 4-ю позицию)
freeCount = 1 (после этого осталась одна клетка свободной)

1 2 3 4 5
3 1 2 4 0

Последняя итерация:

i = 5
steps = 1 (можем сделать только 1 шаг вперед) | x
location = 5 (занимаем оставшуюся клетку)

1 2 3 4 5
3 1 2 4 5

2) Case # 2

В самом начале:

location = 1 (инициализация)
freeCount = 5 (все клетки свободны)

1 2 3 4 5
0 0 0 0 0

Первая итерация:

i = 1
steps = 1 (шаг вперед с текущего location)
location = 2 (заняли 2-й location)
freeCount = 4 (осталось 4 клетки)

1 2 3 4 5
0 1 0 0 0

Вторая итерация:

i = 2
steps = 1 | 5 | 9
location = 3
freeCount = 3

1 2 3 4 5
0 1 2 0 0

*/

//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  printf("RAND_MAX = %d\n", RAND_MAX);
  printf("\n");

  int const N = 100;
  int list[N];

  solution_ptr_t solutions[] = {
    solution1, solution2, solution3, solution4
  };

  int cnt = sizeof(solutions) / sizeof(solutions[0]);  // https://stackoverflow.com/questions/10283375/c-find-static-array-size
  for (int s = 0; s < cnt; ++s)
  {
    printf("Solution # %d\n", s + 1);
    memset(list, 0, sizeof list);  // https://stackoverflow.com/a/5636096/9370853
    measure(solutions[s], list, N);
    print_arr(list, N);
    if (!check_solution(list, N))
    {
      assert(false);
      exit(EXIT_FAILURE);  // http://www.c-cpp.ru/books/exit
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
