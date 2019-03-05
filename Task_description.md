# Задание 1.
Реализовать класс представляющий [граф](https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)), с поддержкой операций:
  - Добавления вершины
  - Удаления вершины и всех связанных с ней ребер.
  - Слияния вершин
  - Объединения графов

Дополнительные требования:
  - Поддержка двух возможностей задания графов: список смежности и матрица смежности.
  - Возможность генерации графов.
  - Поддержка ориентированных и взвешенных графов.
  - Вся реализованная функциональность должна быть протестирована.

Опционально:
  - Загрузка/выгрузка графа в файл.

# Задание 2.
Простые алгоритмы поиска путей на графах:
  - [Алгоритм Дейкстры](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
  - [Алгоритм Беллмана-Форда](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

Дополнительные требования:
  - Вся реализованная функциональность должна быть протестирована.

# Задание 3.
Реализация benchmark'а для сравнения времени выполнения реализованных алгоритмов, объема потребляемой памяти, а также оценки сложности.

Требования:
  - Реализация собственного класса [Allocator](https://en.cppreference.com/w/cpp/memory/allocator), позволяющего отслеживать объем выделяемой памяти.
  - Реализация класса Benchmark для проведения экспериментов.

Дополнительные требования:
  - Вся реализованная функциональность должна быть протестирована.