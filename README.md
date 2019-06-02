1. ANTECEDENTES:
Al principio nosotros habíamos pensamos en programar una simulación de la reproducción
de una bacteria y el imprimir cómo se vería después de un cierto tiempo, sin embargo nos
pareció algo bastante simple, entonces pensamos en algo que incrementara la dificultad,
nuestro código toma esta idea de la expansión exponencial de una bacteria pero dirigida a
un problema que, debemos admitir, es muy fantasioso y poco realista, sin embargo lo que
creemos importante dentro de este programa son los algoritmos de resolución de problemas y
la implementación de archivos y memoria dinámica.
2. PROBLEMA
En un cierto sistema planetario extraño en donde hay un sol enorme, lo suficiente para
albergar cientos de planetas con vida, y que tiene la característica de que todos los planetas
son planos y rectangulares, ha ocurrió una tragedia, empezó una infección zombie en varias
ciudades de varios planetas, resulta que como todos los planetas tenían tan buena relación
unos con otros, había una .Asociación Intergaláctica de Científicosünidos que trabajaba en
varias ciudades de todos los planetas y ésta asociación fue la responsable de crear el virus por
accidente, un planeta ya fue consumido por completo y al ver esto, los presidentes mundiales
de cada planeta (Sí, porque cada planeta tiene un presidente mundial) están preocupados y
han decidido contratar a tu profesor de programación Arturo González Vega que haga algunos
cálculos y simulaciones en computadora para salvar a los presidentes de los mundos, pero
como tu profesor está muy ocupado revisando los exámenes de sus alumnos y nada es más
importante que entregar calificaciones a tiempo, te encargó que hicieras esas tareas por él. Así
1
que tu tarea es hacer un programa que satisfaga todas las peticiones de los presidentes para
salvarlos o por lo menos avisarles cuánto tiempo de vida les queda.
Se te dará un mapa del planeta representado por una matriz de N x M donde cada elemento
representa algo dependiendo de lo que contenga:
’C’ Una ciudad normal.
’X’ Representa una sección de agua por donde el virus no puede pasar.
’#’ Representa una ciudad infectada por zombies.
El presidente se encuentra en las coordenadas (X,Y ) y el virus tarda un cierto tiempo Z
de horas en infectar por completo las ciudades. Curiosamente en estos planetas solo existen
puentes rectos que conectan una ciudad adyacente con otra, pero solo en dirección a los
cuatro puntos cardinales, es decir, que los zombies solo pueden reproducirse a las ciudades
que tengan arriba, abajo y a los lados, si es que ves a este planeta desde el espacio, entonces
tienes que resolver todo lo que el presidente te dicte porque esa es tu función:
1. En una cantidad de tiempo K, ¿Cuántas ciudades estarían infectadas y cómo se vería el
planeta después de esto?
2. ¿Habrá ciudades que no se infectan no importa el tiempo K? Muestre el planeta como
se vería después de una cantidad de tiempo infinita. Es decir, muestre si hay ciudades
que no importa cuánto tiempo tenga para reproducirse el virus, no llegan a infectarse y
diga cuántas son.
3. ¿En cuánto tiempo tardará el virus en alcanzar al señor presidente si se mantiene parado?
4. Si el presidente tiene un avión que se mueve a través del planeta pero el avión solo se
puede mover en dirección a los cuatro puntos cardinales porque pues... Si se moviera en
diagonal estaría incumpliendo las leyes intergalácticas que el mismo gobierno intergaláctico impuso, y este avión tarda un tiempo A en ir de una casilla a otra, ¿Es posible
que se salve sin tener que pasar por ninguna zona infectada ya que el virus también
se esparce por el aire que tienen las ciudades infectadas arriba de ellas? Diga Sí o No
y muestre en qué coordenadas está ahora (No es posible que el presidente se quede
en un océano, es decir, puede pasar por ahí sin embargo no se puede quedar ahí para
siempre, es necesario que vaya a una ciudad no infectada y si ésta no existe entonces el
presidente no se puede salvar y tienes que imprimir que se va a morir).
Recuerda que los planetas no solo son rectangulares, también son planos, entonces
tienen un borde por el cual se pueden caer, entonces el presidente no se puede salir del
planeta o moriría.
5. Como el presidente también es una persona y se aburre mientras está esperando que
su avión llegue a un lugar seguro o que los zombies lo infecten, te pidió hacer mapas
de planetas aleatorios y ver los posibles resultados, una función que haga que todos los
números sean aleatorios y la generación del mundo también.
2
3. ENTRADA DEL USUARIO
Dos números enteros N y M separados por espacios que representan las dimensiones del
planeta, seguido de N filas con M columnas cada una que represente el mapa del planeta en
el que están.
Luego, dos números enteros X y Y que representan las coordenadas del presidente donde X
es el número de fila en la que se encuentra y Y el número de columna. (La primera ciudad
arriba a la izquierda es la coordenada 0,0).
Después, dos números reales Z y A separados por espacios que representa el tiempo en horas
que tarda el virus en reproducirse y el tiempo que tarda el avión del presidente en ir de una
casilla a otra.
Y por último un número real K que representa el número de horas que quiere ver el
presidente cómo está el planeta después del inicio de la catástrofe.
4. RESTRICCIONES:
En este sistema planetario no hay planetas de más de 100 x 100 casillas puesto que la
naturaleza dentro de este universo así lo decidió.
