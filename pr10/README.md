# Практична робота 10

## Загальні завдання
## Приклад 1
Crash handler із SA_SIGINFO і register dump.
### Програмна реалізація
Для виконання завдання було протестовано програму crash_diag.c, яка демонструє роботу розширеного обробника сигналів аварійного завершення.
### Результат виконання
```
gcc -Wall -Wextra -O0 -g -fno-omit-frame-pointer -no-pie crash_diag.c -o crash_diag
```
**Вивід терміналу:**
```
./crash_diag
About to crash. PID=4280

=== crash captured ===
signal: 11
si_code: 1
fault address: 0x0
RIP: 0x401818
RSP: 0x7ffe8979cbc0
RBP: 0x7ffe8979cbc0
RAX: 0x0
RBX: 0x7ffe8979ccf8
RCX: 0x7ff09311c5a4
RDX: 0x1
RSI: 0x402035
RDI: 0x2


addr2line -e ./crash_diag -f -C 0x401818
crash_here
/home/nastasia/pr10/crash_diag.c:165
```

## Приклад 2
Correct sleeping: nanosleep() restart loop і clock_nanosleep() absolute deadline.
### Програмна реалізація
Для виконання завдання було досліджено коректні підходи до організації затримок (sleep) в умовах асинхронного переривання сигналами (EINTR).
### Результат виконання
```
gcc -Wall -Wextra -O2 sleep_correct.c -o sleep_correct
```
**Вивід терміналу:**
```
./sleep_correct
PID=4719. In another terminal: kill -USR1 4719
Relative sleep for 5 seconds using nanosleep restart loop...
Relative sleep finished. got_usr1=0
Now 5 periodic ticks with absolute clock_nanosleep deadlines...
tick 1
tick 2
tick 3
tick 4
tick 5
```

## Приклад 3
Малий publisher-subscriber на real-time signals, sigqueue(), sigwaitinfo() і sigtimedwait()
### Програмна реалізація
Програма реалізує патерн взаємодії видавець-підписник на базі сигналів реального часу (SIGRTMIN).
### Результат виконання
```
gcc -Wall -Wextra -O2 rt_pubsub.c -o rt_pubsub
```
**Вивід терміналу:**
Сценарій 1:
```
/// Термінал 1

./rt_pubsub sub
subscriber PID=5102, waiting for signal 34 (SIGRTMIN)
received signal=34 value=10 from pid=5277 uid=1000
received signal=34 value=20 from pid=5277 uid=1000
received signal=34 value=30 from pid=5277 uid=1000
received signal=34 value=-1 from pid=5277 uid=1000
negative value received: shutting down subscriber

/// Термінал 2
./rt_pubsub pub 5102 10 20 30 -1
sent value=10 to pid=5102 via signal=34
sent value=20 to pid=5102 via signal=34
sent value=30 to pid=5102 via signal=34
sent value=-1 to pid=5102 via signal=34
```
Сценарій 2:
```
./rt_pubsub sub-timeout
subscriber PID=5397, waiting for signal 34 (SIGRTMIN)
timeout: no messages for 5 seconds
timeout: no messages for 5 seconds
timeout: no messages for 5 seconds
received signal=34 value=10 from pid=5588 uid=1000
received signal=34 value=20 from pid=5588 uid=1000
received signal=34 value=30 from pid=5588 uid=1000
received signal=34 value=-1 from pid=5588 uid=1000
negative value received: shutting down subscriber
```
## Завдання по варіантам
### Завдання 10.4
Створіть файл, відкрийте його у програмі, виконайте fork() і зробіть запис у файл як у батьківському, так і в дочірньому процесі. Перевірте результат у вмісті файлу.
### Програмна реалізація
Для виконання завдання було розроблено програму, яка створює та відкриває файл для запису за допомогою системного виклику open(). Після цього викликається функція fork(), що створює дочірній процес. Оскільки після fork() дескриптор відкритого файлу дублюється та посилається на один і той самий системний опис відкритого файлу, обидва процеси розділяють поточну позицію зміщення.
### Результат виконання
```
gcc -Wall task_10_4.c -o task_10_4
```
**Вивід терміналу:**
```
./task_10_4
File 'output.txt' opened successfully before fork().
Child process completed writing.
Parent process completed writing.

cat output.txt
This is a Child process! (PID: 3677)
This is a Parent Process! (PID: 3676)
```

## Інструкція із запуску
### Підготовка системи
Для виконання роботи вам знадобиться стандартний набір інструментів розробника для мови C.

Встановіть необхідні компоненти у вашій системі:
```
sudo apt update
sudo apt install -y build-essential
```
### Завантаження проекту
```
git clone https://github.com/nanahhr/SystemSoftwareArchitecturePrs.git
cd SystemSoftwareArchitecturePrs/pr10
```

### Компіляція та запуск
Для завдання в директорії підготовлено відповідний вихідний файл (task_10_4.c). Загальна схема запуску виглядає наступним чином:

**Для завдання за варіантом №4:**
```
gcc -Wall task_10_4.c -o task_10_4

./task_10_4
```