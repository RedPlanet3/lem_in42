# lem_in42

Lem_in проект школы 42(21).
Проект написан на С.

**Цель проекта** - как можно больше пропустить муравьев из старта в финиш по графу за меньшее число шагов.

## На вход программы подается:
1. Количество муравьев, которых необходимо провести через граф.
2. Перечень комнат 3-х видов: старт(обозначаются с помощью ##start), финиш(##end), промежуточные точки.
3. Связи комнат друг с другом.
4. Комментарии (#comment).


## Вывод программы
каждая строка - единица времени(ход), в котором отображается какой ход был сделан.

> L<ant_number>-<room_name>


## Как запустить программу
> ./lem-in < MAP_FILE



<img width="546" alt="image" src="https://user-images.githubusercontent.com/26433084/209679967-e3452fbd-93fb-4979-992c-5a6b14e0e3ac.png">

## Описание алгоритма

Алгоритм ищет максимальное количество непересекающихся путей, по которым параллельно, без пробок, будут пущены муравьи. 
За один ход муравей шагает в следующую свободную комнату.
Если промежуточная комната занята, муравей ожидает, когда она освободится. Старт, финиш - комнаты без ограничений присутствия. Поведение ожидания реализовано, но т.к. алгоритм не предполагает пересекающихся путей, муравьи ожидать очереди не должны.

Реализованы алгоритмы:

Поиск в ширину

Эдмонса-Карпа



## Бонус

Вывод на экран матрицы смежности, количество найденных путей и сами пути. 
Вывод разноцветный)

Для запуска визаулизации необходимо использовать флаг -v.
> ./lem-in -v < MAP_FILE

<img width="595" alt="image" src="https://user-images.githubusercontent.com/26433084/209680319-dbd73b8c-cdde-47a1-adcf-69a8b0d4aafc.png">

Клонировать и скомпилировать: вы можете клонировать и скомпилировать программу на своем терминале:
> git clone https://github.com/RedPlanet3/lem_in42.git && cd lem_in42 && make
