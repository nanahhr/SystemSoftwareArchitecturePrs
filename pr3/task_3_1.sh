#!/bin/bash

# 1. Поточний ліміт
ulimit -n
# 2. М'який (Soft) ліміт
ulimit -aS | grep "open files"
# 3. Жорсткий (Hard) ліміт
ulimit -aH | grep "open files"

# 4. Встановлюємо 3000
ulimit -n 3000
# 5. Перевіряємо знову
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"

# 6. Спроба встановити 3001
ulimit -n 3001

# 7. Встановлюємо 2000
ulimit -n 2000

# 8. Фінальна перевірка
ulimit -n
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"

# 9. Спроба повернути 3000
ulimit -n 3000
