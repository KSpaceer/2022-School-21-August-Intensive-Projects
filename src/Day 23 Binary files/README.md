Как проверить работу проекта:
    - Запустить "make all" или "make rebuild"
    - Запустить ../build/Quest_1. На вход принимается путь к файлу(представляет собой массив структур) и режим работы:
      0 - вывод содержимого файла
      1 - сортировка файла и вывод содержимого
      2 - добавление новой записи, сортировка и вывод содержимого файла
      При выборе пункта 2 вводятся значения структуры: год, номер месяца, день в месяце, час, минута, секунда,
      статус (0 или 1), код.
    - Запустить ../build/Quest_2. На вход принимается путь к файлу(массив структур) и дата формата "ДД.ММ.ГГГГ".
      Выводится код первого совпадения.
    - Запустить ../build/Quest_3. На вход принимается путь к файлу и временной промежуток формата "ДД.ММ.ГГГГ ДД.ММ.ГГГГ".
      Программа производит удаление записей в данном временном промежутке из файла и выводит новое содержимое файла.