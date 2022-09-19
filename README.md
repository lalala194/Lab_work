# Лабораторная работа "Сравнение скорости работы динамического массива и односвязного списка"

Тут не будет кучи формализма как в классических лабораторных по физике.

## Подготовка

 Все вопросы по их написанию можно адресовать гуглу или семинаристу. Далее необходимо написать два стека: на списке и на массиве.

Необходимо для динамического массива и списка реализовать следующие функции:

1. *`Construct(uint64_t start_size)`* создает массив заданного размера, который потом будет изменяться в ходе исполнения (только для массива)

2. *`Push(int value)`* добавляет элемент в конец контейнера

3. *`Top()`* возвращает последний элемент

4. *`Pop()`* удаляет последний элемент, не возвращая его

5. *`Destroy()`* уничтожает контейнер, освобождая память

## Часть 1. Нахождение оптимальной для вашей платформы политики реаллокации массива

Здесь и далее во всей работе считается, что массив не может уменьшаться в размере.

### 1.1. Поиск изначального оптимального размера

Как обговаривалось на семинаре, при создании динамического массива у него имеется изначальный размер. Вам предлагается рассмотреть следующие варианты: 10, 100, 1000, 5000, 10000, 50000. Далее необходимо провести тест с политикой реаллокации "увеличение размера на изначальную длину". То есть, выбрав параметр 1000, массив при расширении будет увеличиваться на тысячу.

Тест: запушить $`10^6`$ интов в цикле. Далее удалить половину элементов и снова довести размер массива до миллиона. Засечь время исполнения теста.

Далее необходимо построить график (хоть в Excel, хоть на миллиметровке, хоть через python) зависимости времени теста от изначального размера. Минимум на этом графике и будет изначальным размером массива, с которым будем работать далее.

### 1.2. Поиск оптимальной политики реаллокации

#### 1.2.1. Увеличение на константу

Необходимо провести тот же тест, что и в пункте 1.1. с изначальным размером, выбранным там же. Увеличивать размер массива надо на одну из следующих констант: 1000, 5000, 10000, 50000, 75000, 100000. Далее построить график времени теста от константы реаллокации.

#### 1.2.2. Увеличение в константу

Необходимо провести тот же тест, что и в пункте 1.1. с изначальным размером, выбранным там же. Увеличивать размер массива надо в одну из следующих констант: 9/8, 4/3, 3/2, 8/5, 2, 9/4, 10/4. Далее построить график времени теста от константы реаллокации. Исходя из выбранных параметров, реализовать массив с оптимальной по времени политикой реаллокации.

## Часть 2. Сравнение для стека

Необходимо реализвать два стека: `ArrayStack` и `ListStack`. Далее провести для них следующие тесты (каждый провести хотя бы по три раза и усреднить время тестов):

1. Моделирование стека вызова функций. Надо запушить $`10^6`$ интов, потом удалить половину элементов и запушить четверть - останется 750000 интов. Повторять удаление половины и вставку четверти, пока не останется в стеке меньше 100000 элементов (получится 9 итераций).

2. Моделирование нагруженного стека вызова функций. Надо запушить $`10^6`$ интов, потом 100 раз удалить 10000 элементов и добавить столько же. Далее как в первом тесте провести 9 итераций удаления-вставки и снова 100 раз удалить 10000 элементов и добавить столько же.

3. Моделирование случайной последовательности команд. Надо научиться средствами языка генерировать случайные числа из множества $`\{1, 2\}`$. Далее сначала довести размер стека до миллиона, а потом выполнить миллион инструкций следующего вида: каждое выпадение единицы добавлять элемент, а на двойку - попать из стека. Засекать время после доведения размера стека до миллиона.

## Выводы

Необходимо ответить на единственный вопрос: какой стек, по вашему мнению, лучше.
