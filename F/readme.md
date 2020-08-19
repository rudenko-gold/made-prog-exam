# Условия
Маруся организует застолье, и ей необходимо приготовить блюда для гостей, поэтому она составила меню: какие блюда и в каком количестве она собирается приготовить. 

Теперь ей необходимо обзавестись продуктами для готовки, поэтому Маруся составляет заказ в онлайн-магазине продуктов. К сожалению, в составленном ею меню слишком много блюд с замысловатыми рецептами, к тому же часть продуктов Маруся уже купила и сложила в холодильник, так что она совершенно запуталась.

Вам необходимо помочь Марусе составить заказ. Маруся передала вам всю необходимую для этого информацию:

Меню, в котором написан перечень из N блюд и их количеств.
Кулинарная книга, в которой содержится K рецептов. i-й рецепт содержит R_i ингредиентов и в каком количестве они нужны. Обратите внимание, что одно блюдо может выступать как ингредиент для другого. Например, рецепты лазаньи и пасты болоньезе включают в себя соус болоньезе, для которого в книге содержится отдельный рецепт. 
Опись холодильника, содержащую перечень из F продуктов и их количества.
Вам необходимо проанализировать эту информацию и составить заказ в магазине — список продуктов и их количество. Обратите внимание, что Маруся ненавидит полуфабрикаты, поэтому если для какого-то ингредиента есть рецепт в книге, то она его приготовит сама, и его не нужно покупать в магазине. Также можно быть уверенным, что в холодильнике Маруси нет таких полуфабрикатов.

## Ограничения
```sh
1 <= N, K, F, R_i <= 5000

Все числа (количества продуктов во вводе и корректном выводе) положительные и не превышают 2^63-1.

Гарантируется, что для всех блюд из меню в книге присутствуют рецепты.
```
## Пояснение к входным данным:
```sh
Меню: одна лазанья (lasagne) и две пасты болоньезе (bolognese_pasta).
```
Книга рецептов:

```sh
одна лазанья готовится из одного соуса бешамель (bechamel) и трех соусов Болоньезе (bolognese)
одна паста болоньезе готовится из четырех спагетти (spaghetti) и одного соуса Болоньезе
соус бешамель готовится из 10 молока (milk), 2 муки (flour), 2 сливочных масла (butter) и одного мускатного ореха (nutmeg)
соус болоньезе готовится из 3 говядины (beef), 1 красного вина (red_wine), 2 моркови (carrot), 2 лука (onion) и 2 сельдерея (celery)
Содержимое холодильника: 4 сельдерея, 1 морковь и 2 масла.
```
## Пояснение к выходным данным:

Всего для готовки потребуется 10 продуктов: celery, onion, carrot, red_wine, beef, nutmeg, butter, flour, milk, spaghetti. 
Ниже приведена таблица с пояснениями по количеству продуктов:
```sh
Продукт	| В холодильнике | Для lasagne | Для bolognese_pasta | Нужно купить

celery	4	6	4	6
onion	0	6	4	10
carrot	1	6	4	9
red_wine	0	3	2	5
beef	0	9	6	15
nutmeg	0	1	0	1
butter	2	2	0	0
flour	0	2	0	2
milk	0	10	0	10
spaghetti	0	0	8	8
```