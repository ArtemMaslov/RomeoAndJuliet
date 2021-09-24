﻿# RomeoAndJuliet
RomeoAndJuliet - это программа, которая форматирует файл (удаляет пустые строки, убирает лишние проблы, символы табуляции между строками) и сортирует строки в файле.

1. [Компиляция.](#компиляция)
2. [Использование программы.](#использование-программы)
2. [Документация.](#документация)

### Компиляция
* Скачать папки исходного кода `src` и `inc`.
* Создать новый пустой C++ проект в Microsoft Visual Studio.
* Добавить в проект папки `src` и `inc` с файлами исходного кода.
* Скомпилировать проект `Build->Build Solution`.
* Можно использовать другой компилятор, но возможны непредвиденные ошибки.

### Использование программы:

Способ 1:
* Поместить файл `formate.txt` в папку с исполняемым файлом.
* Запустить программу.
* Программа отформатирует исходный файл и результат запишет в файл `formate_out.txt`.

Способ 2:
* Запустить программу через консоль, указав в качестве первого параметра исходный файл, а вторым параметром файл, в который нужно сохранить отформатированный текст.
* Пример для Windows (пусть программа `program.exe`, файл с текстом `text.txt` лежит в папке с исполняемым файлом): команда `program.exe text.txt out.txt` отформатирует текст и сохранит его в файле `out.txt`.