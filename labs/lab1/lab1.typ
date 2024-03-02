#import "@docs/bmstu:1.0.0":*
#show: student_work.with(
  caf_name: "Компьютерные системы и сети",
  faculty_name: "Информатика и системы управления",
  work_type: "лабораторной работе",
  work_num: "1",
  discipline_name: "Технология разработки программных систем",
  theme: "Выбор структур и методов обработки данных (Вариант 11)",
  author: (group: "ИУ6-42Б", nwa: "А. П. Плютто"),
  adviser: (nwa: "Е. К. Пугачёв"),
  city: "Москва",
  table_of_contents: true,
)

= Цель Лабораторной работы
Определить основные критерии оценки структуры данных и методов ее обработки применительно к конкретной задаче.

= Описание задания

== Задания

1. На основе теоретических сведений выделить критерии оценки структур данных, принципы работы и критерии оценки операций поиска, сортировки и корректировки.

2. В соответствии с вариантом задания (Вариант 11) предложить конкретную схему структуры данных (в задании указана абстрактная структура данных) и способ ее реализации на выбранном языке программирования.

3. Определить качественные критерии оценки (универсальность, тип доступа и др.) полученной на шаге 2 структуры данных с учетом специфики задачи по выданному варианту.

4. Определить качественные критерии оценки полученной на шаге 2 структуры данных: требуемый объем памяти на единицу информации, на структуру данных в целом и др.

5. Провести сравнительный анализ структуры данных, предложенной на шаге 2, на основе оценок, полученных на шаге 3 и шаге 4, с другими возможными вариантами реализации с целью поиска лучшей структуры данных к заданию по варианту.

6. Если цель шага 5 достигнута, то необходимо выполнить шаг 2, но для новой абстрактной структуры данных с указанием качественных и количественных критериев.

7. Оценить применимость метода поиска, который указан в варианте задания, с учетом структуры данных.

8. Если метод поиска применим, то необходимо сформулировать его достоинства и недостатки, используя качественные и количественные критерии: универсальность, требуемые ресурсы для реализации, среднее количество сравнений, время выполнения (такты) и др.

9. Предложить альтернативный, более эффективный метод поиска (отличный от задания), если такой существует, с учетом специфики задачи по варианту, а также с учетом структур данных, полученных на предыдущих шагах. Для обоснования выбора альтернативного метода поиска использовать качественные и количественные критерии.

10. Оценить применимость метода упорядочивания, который указан в варианте задания, с учетом структуры данных.

11. Если метод упорядочивания применим, то необходимо сформулировать его достоинства и недостатки, используя качественные и количественные критерии: универсальность, требуемые ресурсы для реализации, среднее количество сравнений, время выполнения (такты) и др.

12. Предложить альтернативный метод упорядочивания, более эффективный и отличный от задания, если такой существует. При этом должны учитываться задача по варианту и структура данных. Для обоснования выбора альтернативного метода упорядочивания использовать качественные и количественные критерии.

13. Оценить применимость метода корректировки, который указан в задании, к структуре данных.

14. Если метод корректировки применим, то необходимо сформулировать его достоинства и недостатки, используя качественные и количественные критерии: универсальность, требуемые ресурсы для реализации, время выполнения (такты) и др.

15. Предложить альтернативный способ корректировки, более эффективный и отличный от задания, если такой существует. При этом должны учитываться задача по варианту, структура данных. Для обоснования выбора альтернативного способа корректировки использовать качественные и количественные критерии.
16. Определить влияние метода корректировки на выполнение операций поиска и упорядочивания.

17. Определить основной режим работы программы и с учетом этого сделать выводы, а итоговые полученные результаты внести в таблицу. Из данной таблицы должно следовать, что предложенный альтернативный вариант решения задачи лучше. Как минимум должно быть одно улучшение, но могут быть заменены все методы обработки и сама структура данных.

== Основные требования

Основные требования приведены в таблице ниже:

#align(center)[
  #table(
    columns: 5,
    inset: 10pt,
    align: horizon,
    [Номер\ задачи],[Структура\ данных],[Поиск],[Упорядочение],[Корректировка],
    [2],[Таблица],[Вычисление\ адреса],[Пузырьком],[Удаление\ сдвигом],
  )
]

== Задача

Дана таблица материальных нормативов, состоящая из K записей фиксированной длины вида: код детали, код материала, единица измерения, номер цеха, норма расхода.

= Описание основного варианта задания

== Структура данных

В заданной таблице указана абстрактная структура данных -- таблица. Это означает, что нам необходимо явно выбрать структуру данных, элементы которой связанны неявно. Из задачи следует, что столбцами таблицы будут код детали, код материала, еденица измерения, номер цеха, норма расхода. Строками мы будем заносить записи.

Каждая строка будет занимать одно и тоже место в памяти. Для реализации строк, так как типы данных у столбцов разные, будем использовать структуры. Они занимают столько же места, сколько бы занимали переменные, хранящиеся по отдельности. Определим тип данных для каждого столбца в зависимости от информации, которую необходимо в нем хранить.

#align(center)[
  #table(
    columns: 2,
    inset: 10pt,
    align: horizon,
    [Столбец],[Тип данных],
    [Код детали],[```cpp unsigned int```],
    [Код материала],[```cpp unsigned int```],
    [Единица измерения],[```cpp String (char[])```],
    [Номер цеха],[```cpp unsigned int```],
    [Норма расхода],[```cpp unsigned int```],
  )
]

Везде (кроме единиц измерения) будем использовать беззнаковый целочисленный тип, для того, чтобы увеличить количество чисел, которые можно сохранить в двое, по сравнению со знаковым типом. Коды, номера изначально не могут быть отрицательными в силу здравного смысла. Норма расхода -- максимально допустимое плановое количество сырья, материалов, топлива, энергии на производство какой-либо единицы какой-либо продукции. Т. е. это значение тоже не может быть отрицательным, но в зависимости от едениц измерения оно может перестать быть целочисленным. В данной задаче не сказано, что данное число будет вещественным, поэтому примем правило: если необходимо ввести вещественную норму расхода, необходимо ввести целую норму расхода и изменить еденицы измерения на более меньшие.

После определения структуры необходимо задуматься о том, как хранить строки в памяти. Самым простым в реализации способом будет хранение их друг за другом -- в массиве. Таким образом общей структурой данных будет массив записей. Вот его схема: 

== Реализация структуры на языке C++




