# Практична робота 1

**Завдання**
1. Встановити Ubuntu (dual-boot, WSL або VirtualBox).
2. Запустити операційну систему.
3. Встановити необхідні інструменти для програмування.
4. Створити, скомпілювати та виконати просту програму мовою C.

### Встановлення VirtualBox та Ubuntu
Для виконання практичної роботи було обрано метод віртуалізації за допомогою Oracle VM VirtualBox. Це дозволило створити ізольоване Linux-середовище без змін у основній операційній системі.

Було завантажено:
* **VirtualBox**: Програмне забезпечення завантажено з офіційного сайту [virtualbox.org](https://www.virtualbox.org/). Було обрано останню стабільну версію для Windows.
* **Ubuntu Server**: Образ операційної системи (ISO-файл) завантажено з офіційного ресурсу [ubuntu.com](https://ubuntu.com/download/server). Обрано версію Ubuntu Server 24.04.3 LTS.

### Конфігурація віртуальної машини
Встановлення відбувалося у напівавтоматичному режимі (Unattended Installation). В інтерфейсі VirtualBox ще до старту машини було вказано параметри облікового запису (username, password) та ім'я хоста. Після запуску віртуальної машини інсталятор Ubuntu самостійно виконав розмітку диска, налаштування локалізації та створення користувача, базуючись на введених раніше даних.  

Для роботи серверу було виділено:
* 3 ГБ оперативної пам'яті;
* 2 ядра центрального процесора;
* 16 ГБ віртуального дискового простору.

Оскільки система була встановлена автоматично, після першого входу в консоль я виконала перевірку та фінальне налаштування:
```
sudo apt update
sudo apt upgrade -y
```
Для виконання практичних завдань було встановлено пакет build-essential, який містить компілятор gcc, make та інші необхідні утиліти:
```
sudo apt install build-essential -y
```

## Виконання завдання 1.4
**Завдання**  
У вас є програма на C, яка складається з кількох модулів (main.c, module1.c, module2.c) та використовує бібліотеку pthread.

1. Напишіть команду компіляції з підтримкою багатопоточності (-pthread).
2. Змініть код так, щоб він використовував OpenMP (#pragma omp parallel).
3. Використовуйте valgrind або gprof для аналізу продуктивності.
* gcc -Wall -Wextra -pthread main.c module1.c module2.c -o threaded_program
* Оптимізуйте код для роботи з багатоядерними процесорами.
* Використовуйте асинхронний ввід/вивід (aio.h) замість стандартного stdio.h.
* Реалізуйте версію програми на C++ з використанням std::thread.

### Програмна реалізація та аналіз

Перш ніж переходити до паралелізму, було розроблено спільну логіку обчислень у папці src/common.

**Опис обчислювальних модулів**
* Module 1 (module1.c): Реалізує функцію інтенсивного додавання. Вона приймає покажчик на число та в циклі ($10^9$ ітерацій) накопичує суму. Результат записується безпосередньо за адресою аргументу.
* Module 2 (module2.c): Реалізує обчислення факторіала числа. Використовує тип unsigned long long для запобігання переповненню при великих вхідних даних. Результат також повертається через розіменування покажчика.

### Базова багатопоточність (POSIX Threads)
pthread - це низькорівневий інтерфейс для керування потоками. Кожен потік створюється вручну, має власний стек і виконує задану функцію паралельно з основним потоком.

У main.c було використано pthread_create для запуску обох модулів та pthread_join для очікування їх завершення. Це дозволяє задіяти два ядра процесора одночасно.

**Команда компіляції та перевірка пам'яті:**
```
gcc -Wall -Wextra -pthread src/pthread/main.c src/common/module1.c src/common/module2.c -Iinclude -o pr1_pthread
valgrind --leak-check=full ./pr1_pthread
```
**Результат виконання:**  
За допомогою Valgrind було підтверджено відсутність витоків пам'яті.

```
valgrind --leak-check=full ./pr1_pthread
==7284== Memcheck, a memory error detector
==7284== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==7284== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==7284== Command: ./pr1_pthread
==7284== 
Main: Creating threads...
Module 2: Finished. Result saved: 479001600
Module 1: Finished. Result saved: 5000000000
Main: All threads finished. Exiting.
==7284== 
==7284== HEAP SUMMARY:
==7284==     in use at exit: 0 bytes in 0 blocks
==7284==   total heap usage: 3 allocs, 3 frees, 1,568 bytes allocated
==7284== 
==7284== All heap blocks were freed -- no leaks are possible
==7284== 
==7284== For lists of detected and suppressed errors, rerun with: -s
==7284== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
### Оптимізація (OpenMP) та Асинхронний вивід (AIO)
* OpenMP (Open Multi-Processing)- це стандарт API для розпаралелювання програм. Замість ручного створення кожного потоку (як у pthread), ми використовуємо директиву #pragma omp parallel sections. Це вказує компілятору автоматично розподілити виконання функцій module1 та module2 між різними ядрами процесора.

* POSIX AIO (aio.h) - технологія асинхронного вводу/виводу. Звичайний запис (printf або write) є блокуючим: процесор чекає, поки диск запише дані. aio_write дозволяє процесору лише "дати команду" на запис і миттєво повернутися до виконання коду, що пришвидшує роботу високонавантажених систем.

**Реалізація**
* Використано #pragma omp parallel sections для запуску модулів.
* Стандартний printf у файл замінено на aio_write для асинхронного логування.
* Застосовано агресивну оптимізацію компілятора -O3.

**Команди компіляції (O0 vs O3):**
```
gcc -O0 src/openmp/main.c src/common/module1.c src/common/module2.c -Iinclude -fopenmp -lrt -o pr1_openmp
gcc -O3 src/openmp/main.c src/common/module1.c src/common/module2.c -Iinclude -fopenmp -lrt -o pr1_openmp_optimized
```
**Команди для порівняння продуктивності:**
```
time ./pr1_openmp
time ./pr1_openmp_optimized
```
**Результати:**  
Використання команди time показує колосальну різницю у швидкості обчислень завдяки прапорцю -O3.
Неоптимізована версія.
```
time ./pr1_openmp
=== SYSTEM START (OpenMP + AIO) ===
[Thread 1] Calculating Module 1...
[Thread 2] Calculating Module 2...
Module 2: Finished. Result saved: 479001600
Module 1: Finished. Result saved: 5000000000
Main: Sending report to disk asynchronously...
Main: Disk is busy writing...
Main: Write completed. 116 bytes saved to log.
Program finished.

real    0m2.764s
user    0m2.529s
sys     0m0.275s

```
Оптимізована версія.
```
time ./pr1_openmp_optimized
=== SYSTEM START (OpenMP + AIO) ===
[Thread 2] Calculating Module 1...
[Thread 0] Calculating Module 2...
Module 2: Finished. Result saved: 479001600
Module 1: Finished. Result saved: 5000000000
Main: Sending report to disk asynchronously...
Main: Disk is busy writing...
Main: Write completed. 116 bytes saved to log.
Program finished.

real    0m1.901s
user    0m1.112s
sys     0m0.845s
```
Завдяки OpenMP обчислення виконуються паралельно, а оптимізація -O3 прискорила математичні операції у циклах. Використання AIO дозволило завершити програму, не очікуючи фізичного завершення операції запису на диск.

### Реалізація на C++
**Основні відмінності від C:**
* Не потрібно маніпулювати void* покажчиками;
* Потік - це об'єкт класу std::thread, який має власні методи (наприклад, .join());
* Аргументи у функцію потоку передаються так само просто, як у звичайну функцію.

**Команда компіляції:**
```
g++ -O3 src/cpp_version/main.cpp src/cpp_version/module1.cpp src/cpp_version/module2.cpp -Iinclude -pthread -o pr1_cpp
```
**Результати:**
```
./pr1_cpp
Main: Starting threads (C++ style, no headers)...
Thread 1: Starting...
Thread 1: Done. Sum = 5000000000
Thread 2: Starting...
Thread 2: Factorial of 12 = 479001600
Main: All done!
```

## Як запустити проект
### Підготовка системи
Перш за все, необхідно оновити списки пакетів та встановити інструменти для збірки (компілятори gcc/g++, утиліту make) та інструменти аналізу (valgrind).

У терміналі Ubuntu виконайте:
```
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential valgrind git -y
```
### Завантаження проекту
```
git clone https://github.com/nanahhr/SystemSoftwareArchitecturePrs.git
cd pr1
```
### Структура файлів
Перед запуском важливо розуміти архітектуру проекту:
* src/common/ - спільна математична логіка (обчислення суми та факторіала);
* src/pthread/ - базова багатопоточна версія на С;
* src/openmp/ - оптимізована версія з використанням OpenMP та асинхронного вводу/виводу (AIO);
* src/cpp_version/ -  реалізація на C++ (std::thread);
* include/ - заголовні файли (.h);
* Makefile - сценарій для автоматичної збірки всього проекту.

### Збірка та запуск
**Автоматично через Makefile**  
Це найшвидший спосіб скомпілювати всі три версії програми:
```
make
```
Після цього у кореневій папці з'являться три файли: pr1_pthread, pr1_openmp_optimized та pr1_cpp.

**Ручна компіляція**
* Pthread версія:
```
gcc -Wall -pthread src/pthread/main.c src/common/module1.c src/common/module2.c -Iinclude -o pr1_pthread
./pr1_pthread
```
* OpenMP + AIO версія:
```
gcc -Wall -pthread src/pthread/main.c src/common/module1.c src/common/module2.c -Iinclude -o pr1_pthread
./pr1_pthread
```
* C++ версія:
```
g++ -O3 src/cpp_version/main.cpp src/common/module1.c src/common/module2.c -Iinclude -pthread -o pr1_cpp
./pr1_cpp
```

Після запусків ви можете перевірити створені звіти та логи:
* Лог асинхронного запису (C): 
```
cat execution_results.log
```
* Перевірка пам'яті (Pthread): 
```
valgrind --leak-check=full ./pr1_pthread
```

Щоб видалити всі скомпільовані файли та очистити робочу директорію, виконайте:
```
make clean
```