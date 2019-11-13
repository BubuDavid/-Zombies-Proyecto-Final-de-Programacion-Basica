//Bibliotecas utilizadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definici�n de las funciones.

int Abrir_Archivo(char[], int*, int*, int*, int*, double*, double*, double*);

int Manual(int*, int*, int*, int*, double*, double*, double*);

void Variables(int*, int*, int*, int*, double*, double*, double*, FILE*);

char ** PedirMemoriaChar(int, int);

double ** PedirMemoriadouble(int, int);

void ImprimeMapa(int, int);

void Expansion_Zombie(int, int, int, int, double, double, double, int*);

//FIXME: No usar typedef en las estructuras
typedef struct { //Se crea una estructura para poder guardar la posici�n del presidente y la m�nima de tiempo para llegar
          //a un lugar seguro. Todo eso compactado en un tipo de variable llamado Presi.
        double m;
        int x; //Guarda la posici�n en x.
        int y; //Guarda la posici�n en y.
}Presi;

void Expansion_Presidencial(int, int, int, int, double, double, Presi*);

int Aleatorio(int*, int*, int*, int*, double*, double*, double*);

//Se tuvo que hacer a la variable "mapa" una variable global ya que fue la �nica manera que encontramos de
//hacer que el programa funcionara, ya que si la hac�amos local ten�amos que pasarla a las dem�s funciones
//como un par�metro y dentro de esas "llamadas" como par�metro ocurr�an varios errores de los cuales descono-
//c�amos la soluci�n, as� que la �nica manera que se nos ocurri� de resolver esto fue haci�ndola global y al
//parecer funcion�.
//Lo mismo es para "mapaint".
char **mapa;
double **mapad;

int main()
{
//------------------Inicio del programa, donde todo es declarado y donde se decidir� que hacer------------------//

        //Declaraci�n de variables.
        int menu;
        int n, m, x, y, sum, ciudades;
        double z, a, k;
        Presi mini;
        int ciclo = 1;

        //Ciclo principal del programa, donde se decide de qu� se va a hacer.
        //Es un ciclo ya que queremos que exista la opci�n de hacerlo m�s de una vez.

        while(ciclo == 1) {

                //Este system("cls") indica que se limpiar� la pantalla al comienzo de cada nuevo ciclo del programa.
                //Todos los system("cls") y system("pause") son simplemente por est�tica.
                system("cls");

                //Igualaci�n de datos.
                sum = 0;
                mini.m = 100000000;
                mini.x = -1;
                mini.y = -1;

                //Indicaciones.
                printf("Bienvenido senor presidente, escriba el numero que guste:\n");
                printf("1.Abrir un caso ejemplo como los del reporte.\n");
                printf("2.Abrir uno de sus propios casos.\n");
                printf("3.Crear un caso completamente nuevo y guardarlo.\n");
                printf("4.Analizar un planeta aleatorio por diversion mientras que los zombies lo comen.\n");
                printf("5.Salir del programa.\n");

                scanf("%d", &menu);

                system("cls");

                //En esta secci�n se ejecuta el c�digo correspondiente a lo que el usuario introdujo.
                switch(menu) {
                case 1:
                        printf("Indique por favor el numero del caso ejemplo que desea abrir:\n");
                        ciclo = Abrir_Archivo("Ejemplos\\Caso", &n, &m, &x, &y, &z, &a, &k);
                        break;
                case 2:
                        printf("Escriba el nombre de su archivo:\n");
                        ciclo = Abrir_Archivo("Usuario\\", &n, &m, &x, &y, &z, &a, &k);
                        break;
                case 3:
                        ciclo = Manual(&n, &m, &x, &y, &z, &a, &k);
                        break;
                case 4:
                        ciclo = Aleatorio(&n, &m, &x, &y, &z, &a, &k);
                        break;
                case 5:
                        return 0;
                default:
                        printf("No es posible analizar ese numero, intentelo de nuevo.\n");
                        ciclo = 1;
                        system("pause");
                }

                if (ciclo == 0) {
                        //Ahora le tenemos que mostrar al usuario el caso que seleccion� para que lo pueda analizar bien.
                        system("cls");

                        ciudades = (int)mapad[0][0] + 1; //Aqu� recuperamos el n�mero de ciudades que hay en total, el "+ 1" es porque la cuenta inici� en -1.
                        //El cast es porque la variable mapad[0][0] es un double.
                        mapad[0][0] = -1.0; //Luego le devolvemos su valor de -1 puesto por conveniencia nuestra.

                        printf("Tu caso es:\n");
                        printf("%d %d\n", n, m);
                        ImprimeMapa(n, m);
                        printf("%d %d\n", x, y);
                        printf("%lf %lf \n%lf\n", z, a, k);

                        //Este sistem("pause") le da el tiempo necesario al usuario para analizar el caso que escogi�.
                        //De hecho le da el tiempo que el usuario decida.
                        system("pause");

                        //Aqu� se indica que si el caso es aleatorio, el usuario puede guardarlo en la carpeta de Usuario.
                        if(menu == 4) {
                                system("cls");
                                printf("Escriba:\n1.Si desea guardar este caso en la carpeta \"Usuario\"\nSi no, cualquier otro numero.\n");
                                scanf("%d", &menu); //Escog� esta variable para no crear una nueva, fue arbitrario.
                                if(menu == 1) {
                                        if(Save(&n, &m, &x, &y, &z, &a, &k) == 1) {
                                                return 0;
                                        }
                                }
                        }

                        //------------------Aqu� empiezan los algoritmos para resolver las tareas del presidente------------------//


                        //----------------------------------------------Tarea 1----------------------------------------------//
                        //�Cu�ntas ciudades son afectadas en una cantidad de tiempo K y c�mo se ve el mapa despu�s de esto?

                        //En este for se recorre la matriz "mapa" y se detecta en d�nde est�n los zombies, para desde ese punto
                        //ejecutar un "algoritmo de expansi�n" dentro de una funci�n.
                        for(int i = 0; i < n; i++) {
                                for(int j = 0; j < m; j++) {
                                        if(mapa[i][j] == '#') {
                                                Expansion_Zombie(i, j, n, m, z, 0, k, &sum);
                                        }
                                }
                        }

                        system("cls");

                        printf("Despues de %lf horas hay %d Ciudades infectadas:\n", k, sum);

                        ImprimeMapa(n, m);

                        system("pause");

                        //----------------------------------------------Tarea 2----------------------------------------------//
                        //�Habr� ciudades que no se infectan no importa el tiempo K?

                        //Ahora hacemos lo mismo que en la tarea 1, solo que tenemos que ponerle un tiempo K rid�culamente grande
                        //Digamos 1000 * 1000 ya que consideramos que ese ser�a el l�mite de los planetas que nos podr�an dar.
                        //Y como es recursi�n entonces si hay menos de 1000 * 1000 casillas el programa no se tardar� m�s del tiempo
                        //que le toma a los zombies llegar a las casillas disponibles.
                        //Adem�s hay que cambiar la condici�n de chequeo del if dentro de los for para que inicie siempre donde estuvo
                        //el primer brote de zombies.

                        for(int i = 0; i < n; i++) {
                                for(int j = 0; j < m; j++) {
                                        if(mapad[i][j] == 0.0) {
                                                Expansion_Zombie(i, j, n, m, z, 0.0, 1000 * 1000, &sum);
                                        }
                                }
                        }

                        system("cls");

                        //Imprimimos lo que el se�or presidente quiere, en este caso el n�mero de ciudades que se salvaron es:
                        //El n�mero de ciudades totales menos las ciudades que se infectaron, es decir "ciudades - sum".
                        sum = ciudades - sum; //Y guardemoslo en "sum" para ya no crear m�s variables.
                        if(sum == 1) {
                                printf("Despues del brote de zombies solo %d ciudad se salva:\n", sum);
                        } else {
                                printf("Despues del brote de zombies %d ciudades se salvan:\n", sum);
                        }
           
                        ImprimeMapa(n, m);

                        system("pause");

                        //----------------------------------------------Tarea 3----------------------------------------------//
                        //�En cu�nto tiempo tardar� el virus en alcanzar al se�or presidente si se mantiene parado?

                        //Para este inciso simplemente debemos que de acceder a la matriz mapad que tiene registrado el tiempo que tardan los
                        //zombies en llegar a todos los lugares que pueden llegar, si algunos de �stos coincide con la posici�n del
                        //presidente en ese caso habr� que imprimirlo, sino entonces el presidente o est� a salvo o est� en un oceano.
                        //Y tambi�n hay que imprimirlo.

                        system("cls");

                        if (mapa[x][y] == '#') { //Esto checa si puede haber zombies en la posici�n actual del presidente.
                                printf("Si el presidente se queda ahi, entonces los zombies lo alcanzaran en %lf horas.\n", mapad[x][y]);
                        } else {
                                if(mapa[x][y] == 'X') { //Checa si est� en una casilla con oceano.
                                        printf("No es alcanzado por los zombies, sin embargo esta en un oceano, o sea que muere cuando la gasolina de su avion se acabe.\n");
                                } else {
                                        printf("El presidente esta a salvo, no hay nada de que preocuparse... Bueno si, del resto del mundo.\n");
                                }
                        }

                        system("pause");

                        system("cls");


                        //----------------------------------------------Tarea 4----------------------------------------------//
                        //�Es posible que se salve en su avi�n?

                        //Para responder esta pregunta implementaremos el mismo algoritmo que usamos para los zombies,
                        //es deicr, "expandiremos" las posibles posiciones que tiene el presidente sin que pase por ninguna zona infectada
                        //es como si el presidente pudiera estar en todas las posiciones posibles pero en distintos tiempos, y as�
                        //podremos saber si puede estar en una ciudad no infectada o si lo infectar�n los zombies, recordando que los
                        //zombies se reproducen a distinta velocidad que el avi�n se mueve, no necesariamente tiene que ser mayor la
                        //velocidad del avi�n.

                        if(mapad[x][y] == 0.0) {
                                ciclo = -1; //Escog� la variable ciclo simplemente para no crear una nueva.
                                printf("El presidente ya es un zombie, no hay nada que hacer.\n");
                        }

                        //Esto es para ayudar a resolver bugs.
                        /* Use gdb instead */

                        Expansion_Presidencial(x, y, n, m, a, a, &mini);

                        mini.m = mini.m - a; //Le descontamos uno porque inicializamos la casilla del presidente en "a" y no en 0.
                        //Para fines pr�cticos.

                        //Checamos que el presidente si puede llegar a alg�n lugar seguro.

                        if((mini.m == 100000000 - a && (mapa[x][y] == '#' || mapa[x][y] == 'X') && ciclo != -1)) {
                                printf("El presidente no puede llegar a ninguna ciudad, se va a morir.\n");
                        } else {
                                if(ciclo != -1) {
                                        if(mini.m != 0.0 && mini.x != -1) {
                                                printf("El Senor Presidente tiene que ir a las coordenadas (%d, %d) al que puede llegar en %lf horas.\n", mini.x, mini.y, mini.m);
                                        } else {
                                                printf("Quedese justo donde esta Senor Presidente.\n");
                                        }
                                }
                        }

                        system("pause");
                        system("cls");
                        printf("Escriba:\n1.Si quiere hacer otro test.\nCualquier otro numero.Si quiere terminar el programa.\n");
                        scanf("%d", &ciclo);
                        //Al final se libera la memoria de las matrices para posteriormente volverla a usar si fuese necesario.

                        for(int i = 0; i < n; i++)
                                free(mapa[i]);
                        free(mapa);

                        for(int i = 0; i < n; i++)
                                free(mapad[i]);
                        free(mapad);
                }
        }

        return 0;
}

int Abrir_Archivo(char dir[50], int *n, int *m, int *x, int *y, double *z, double *a, double *k)
{
        //Esta funci�n sirve para Abrir archivos desde una cierta direcci�n anteriormente dada en los par�metros de �sta.
        //Regresar� 1 en caso de que no se pueda abrir el archivo, si s� se puede abrir el archivo regresar� 0.
        //Y tiene par�metros apuntadores porque queremos llenar estas variables para poder hacer el "proceso"
        //En otras funciones y en el main.
        //Declaraci�n de variables.
        char caso[50], aux[50];
        FILE *fd;


        //Por alguna raz�n que desconocemos, la funci�n "strcat" no admite como par�metros el par�metro de esta funci�n
        //(Es decir el par�metro llamado "dir" de la funci�n Abrir_Archivo no es admitida dentro de "strcat").
        //As� que creamos una copia de �ste par�metro y la nombramos "aux" para poder as� ejecutar la funci�n "strcat"
        //sin problemas, lo utilizaremos sin ninguna funci�n de string.h para evitar problemas.
        for(int i = 0; 1; i++) {
                aux[i] = dir[i];
                if(dir[i] == '\0')
                        break;
        }

        //Pidiendo el nombre del caso deseado.
        scanf("%s", caso);

        //Concatenaci�n de lo necesario para poder acceder al archivo en cuesti�n.
        strcat(aux, caso);
        strcat(aux, ".txt");

        //Solo para checar errores:
        //printf("%s", aux);

        //Ahora aux tiene la direcci�n exacta del caso que queremos, en ese caso ya podemos abrir el archivo.
        fd = fopen(aux, "r");

        if(fd == NULL) {
                fclose(fd);
                printf("El archivo que ha querido abrir no existe, tal vez no es el nombre correcto, intentelo de nuevo.\n");
                system("pause");
                return 1;
        }

        //Asignamos los valores de las variables.
        Variables(n, m, x, y, z, a, k, fd);

        fclose(fd);

        if(*n == -1) {
                system("pause");
                return 1;
        }
        return 0;
}

int Manual(int *n, int *m, int *x, int *y, double *z, double *a, double *k)
{
        //Esta secci�n es para que el usuario ingrese todos los datos a mano para despu�s guardarlo en la carpeta
        //Usuario.

        //Declaraci�n de las variables necesarias.
        FILE *fd;
        char direccion[50], aux[50];

        //Pidiendo datos.
        system("cls");
        printf("Ingrese el tamano de filas de su mapa-matriz:\n");
        scanf("%d", n);
        printf("Ingrese el tamano de columnas de su mapa-matriz:\n");
        scanf("%d", m);

        //Una vez teniendo los datos de n y m ya podemos saber cuanta memoria solicitar para las matrices.
        mapa = (char**)malloc(sizeof(char*)*(*n));
        mapad = (double**)malloc(sizeof(double*)*(*n));

        if(mapa == NULL || mapad == NULL) {
                printf("Ocurrio un problema con la memoria, intentelo de nuevo.\n");
                system("pause");
                return 1;
        }

        for(int i = 0; i < *n; i++) {
                mapa[i] = (char*)malloc(sizeof(char)*(*m));
                mapad[i] = (double*)malloc(sizeof(double)*(*m));
        }

        //Luego leemos las matrices.

        printf("Ahora ingrese su mapa-matriz como usted considere correcto:\n");
        printf("Recuerde, \"X\" significa que hay una parte de Oceano.\n");
        printf("\"C\" Significa que hay una ciudad.\n");
        printf("Y \"#\" Significa que hay una ciudad infectada por los zombies.\n");

        for(int i = 0; i < *n; i++) {
                for(int j = 0 ; j < *m; j++) {
                        mapad[i][j] = -1;
                        scanf("%c", &mapa[i][j]);
                        if(mapa[i][j] == 'C' || mapa[i][j] == '#')  //Contamos el n�mero de ciudades para una tarea del presidente.
                                mapad[0][0]++;                          //y lo guardamos en un lugar arbitrario al que podamos acceder
                        //despu�s, por ejemplo en mapad[0][0] luego ya le
                        //devolveremos el -1. Note que los "#" tambi�n son ciudades
                        //as� que tambi�n cuentan para el senso de ciudades.
                        //Son ciudades infectadas.

                        //En el caso en el que con el "scanf" detectemos un salto de l�nea, cosa que no queremos en nuestro
                        //mapa puesto que nosotros nos encargaremos de imprimir los saltos de l�nea a mano para no afectar
                        // en el algoritmo de b�squeda y expansi�n, entonces hacemos como que no vale y le restamos a la variable
                        //"j" uno para que vuelva a leer esa casilla.
                        if(mapa[i][j] == '\n')
                                j--;
                }
        }

        //Ahora leemos las variables que siguen.
        printf("Ahora ingrese la coordenada X del presidente:\n");
        scanf("%d", x);
        printf("Ahora ingrese la coordenada Y del presidente:\n");
        scanf("%d", y);
        printf("Ingrese la cantidad Z de tiempo en el que los zombies se reproducen:\n");
        scanf("%lf", z);
        printf("Ingrese la cantidad A de tiempo en el que el avion del presidente vuela de una casilla a otra:\n");
        scanf("%lf", a);
        printf("Ingrese la cantidad K de tiempo que desea analizar el senor presidente:\n");
        scanf("%lf", k);

        //Ahora guardaremos:

        //Esta parte solo es para corregir errores.
        //printf("%d %d %d %d %lf %lf %lf", *n, *m, *x, *y, *z, *a, *k);
        //system("pause");

        return Save(n, m, x, y, z, a, k);
}

void Variables(int *n, int *m, int *x, int *y, double *z, double *a, double *k, FILE *fd)
{
        //Esta funci�n asigna los valores de las variables correspondientes cuando se trata de la apertura de un archivo.
        //Y son apuntadores porque queremos trabajar con ellos en otras funciones.

        //Primero leemos a "n" y "m" que est�n dentro del archivo para poder definir el tama�o de nuestra matriz mapa.
        fscanf(fd, "%d%d", n, m);

        //Esta parte es solo para checar problemas.

        //Ahora apartamos el espacio de memoria necesario para guardar nuestras matrices.
        mapa = (char**)malloc(sizeof(char *) * (*n));
        mapad = (double**)malloc(sizeof(double *) * (*n));

        if(mapa == NULL || mapad == NULL) {
                printf("Hubo un error con la memoria, intentelo de nuevo por favor");
                *n = -1; //Si el valor de n es -1 significa que hay un error en la memoria.
                //El hecho de que sea la variable "n" no significa nada, fue arbitrario.
                return;
        }

        for(int i = 0; i < *n; i++) {
                mapa[i] = (char *)malloc(sizeof(char) * (*m));
                mapad[i] = (double *)malloc(sizeof(double) * (*m));
        }

        //Una vez apartado el espacio de memoria necesario ya podemos guardar cosas en mapa.

        for(int i = 0; i < *n; i++) {
                for(int j = 0; j < *m; j++) {
                        fscanf(fd, "%c", &mapa[i][j]);
                        //En el caso en el que con el fscanf detectemos un salto de l�nea, cosa que no queremos en nuestro
                        //mapa puesto que nosotros nos encargaremos de imprimir los saltos de l�nea a mano para no afectar
                        // en el algoritmo de b�squeda, entonces hacemos como que no vale y le restamos a la variable "j"
                        //uno para que vuelva a leer esa casilla.
                        mapad[i][j] = -1; //Aqu� inicializamos "mapad" en -1 por conveniencia para un futuro algoritmo.
                        if(mapa[i][j] == 'C' || mapa[i][j] == '#') //Contamos el n�mero de ciudades para una tarea del presidente.
                                mapad[0][0]++;                         //y lo guardamos en un lugar arbitrario al que podamos acceder
                        if(mapa[i][j] == '\n')                     //despu�s, por ejemplo en mapad[0][0] luego ya le
                                j--;                                   //devolveremos el -1. Note que los "#" tambi�n son ciudades
                }                                              //as� que tambi�n cuentan para el senso de ciudades.
        }                                                  //Son ciudades infectadas.

        //Ahora guardamos los dem�s datos que nos piden.
        fscanf(fd, "%d %d %lf %lf %lf", x, y, z, a, k);
}

void ImprimeMapa(int n, int m)
{
    //Esta parte imprime el mapa, lo hicimos funci�n para no tener que escribir todo eso una y otra vez.
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
                if(mapa[i][j] == '$') { //Aqu� resolvemos algunos problemas al imprimir el mapa despu�s de el algoritmo
                                        //De expansi�n zombie, ya que en vez de imprimirse '#' se imprim�a '$'.
                        mapa[i][j] = '#';
                }

                printf("%c", mapa[i][j]);
        }
        printf("\n");
    }

}

void Expansion_Zombie(int x, int y, int n, int m, double z, double cont, double k, int *sum)
{
        //Esta parte solo es para observar errores m�s facilmente.
        //printf("\nEntre en las coordenadas %d %d\n", x, y);
        //printf("\n%lf %d\n", cont, *sum);
        //ImprimeMapa(n, m);


        //Dentro de esta funci�n haremos que los zombies se "expantan" en un tiempo determinado, este algoritmo se basa en
        //la recursi�n, la funci�n se manda a llamar a s� misma hasta que se cumpla alguna de las condiciones de la
        //serie de condiciones espec�ficas.

        //Las condiciones son las siguientes:
        if(x < 0 || y < 0 || x >= n || y >= m || cont > k) //--->Detecta si la posici�n est� fuera de la matriz.
                return;                                        //Y detecta tambi�n si el contador "cont"  excede el tiempo "k".
        if(mapa[x][y] == 'X') //--->Detecta si est� en un oceano.
                return;
        if((mapa[x][y] == '$' || (mapa[x][y] == '#' && cont != 0)) && cont > mapad[x][y])//--->Detecta que no se haya pasado por ah� anteriormente.
                return;                                 //Y aparte que ese sea el camino m�s corto para llegar esa casilla.
        if(mapad[x][y] < cont && mapad[x][y] != -1) //--->Detecta si hay un camino m�s corto por el cual pueda reproducirse el
                return;                                  //virus zombie, si no lo hay es porque mapad[x][y] es menor que cualquier
        //otro "cont" que no sea �l mismo.

        //Todas las condiciones de los if que est�n aqu� pueden ir juntas separ�ndolas con un signo de 'o' (||).
        //Pero por cuesti�n de espacio y de que sea m�s comprensible el c�digo, se pusieron separados.

        //Si ninguna de las condiciones anteriores se cumplen, entonces entra a la funci�n en donde alteramos el mapa
        //original y en donde asignamos n�meros a nuestra otra matriz contadora llamada "mapad" para saber en cu�nto
        //tiempo los zombies llegan a ciertas partes espec�ficas.

        if(mapad[x][y] == -1)//Si y solo si, nunca hemos pisado esa casilla, es decir, mapad[x][y] es igual a -1.
                *sum = *sum + 1; //Y se le suma 1 a la suma por cada zombie que expandido.
        mapad[x][y] = cont;
        mapa[x][y] = '$';
        //Se coloca este s�mbolo para que se diferenc�e de los "#" puestos al principio, porque si no se hiciera entonces
        //El ciclo for en donde est� entrando a esta funci�n detectar�a estos "#" y se repetir�a una cantidad indefinida.

        Expansion_Zombie(x + 1, y, n, m, z, cont + z, k, sum);
        Expansion_Zombie(x, y + 1, n, m, z, cont + z, k, sum);
        Expansion_Zombie(x - 1, y, n, m, z, cont + z, k, sum);
        Expansion_Zombie(x, y - 1, n, m, z, cont + z, k, sum);

        return;

}

void Expansion_Presidencial(int x, int y, int n, int m, double a, double cont, Presi *mini)
{
        //Esta funci�n se basa en lo mismo que la Expansion_Zombie, solo que este tiene par�metros distintos y lo �nico
        //que vamos a alterar es la matriz "mapad" puesto que no es necesaria "mapa" y no es necesario crear una nueva.
        //Aunque a "mapa" la vamos a utilizar para verificar si el algoritmo ya pas� por esa casilla espec�fica.

        //Las condiciones de la funci�n para que pare son.
        if(x < 0 || y < 0 || x >= n || y >= m) //--->Detecta si la posici�n est� fuera de la matriz.
                return;
        if(mapad[x][y] < cont && mapad[x][y] != -1) //--->Detecta si los zombies pasan antes o al mismo tiempo que el
                return;                                  //Presidente.
        if((mapa[x][y] == 'P' || mapa[x][y] == 'M') && cont >= mapad[x][y])//---> Detecta que el presidente ya pas� por ah� en un tiempo menor.
                return;

        if(mapa[x][y] == 'X') {
                mapa[x][y] = 'M'; // Una 'M' para indicar que es un oceano
        } else {
                if(mapa[x][y] == 'C')
                        mapa[x][y] = 'P'; //Ponemos una marca de que el presidente ya pas� por ah� para no volver a pasar y que no se cicle.
        }

        if(mapa[x][y] == 'P' && mini->m > cont) {
                mini->m = cont;//Tenemos que regresar el m�nimo de tiempo que hace el Presidente en llegar a un lugar seguro.
                mini->x = x;   //Se hace a partir de un apuntador porque lo tenemos que imprimir en el main.
                mini->y = y;   //Y adem�s se guardan las coordenadas de este mismo.
        }

        mapad[x][y] = cont;

        //Esta parte solo es para observar errores m�s facilmente.
        //printf("\n%lf %lf %d %d\n", mini->m, cont, x, y);
        //ImprimeMapa(n, m);

        Expansion_Presidencial(x + 1, y, n, m, a, cont + a, mini);
        Expansion_Presidencial(x, y + 1, n, m, a, cont + a, mini);
        Expansion_Presidencial(x - 1, y, n, m, a, cont + a, mini);
        Expansion_Presidencial(x, y - 1, n, m, a, cont + a, mini);
}

int Aleatorio(int *n, int *m, int *x, int *y, double *z, double *a, double *k)
{
        //En esta funci�n todos los datos son aleatorios en un rango que el usuario decida.

        //Declaraci�n de variables necesarias.
        int r, R;

        //Esta funci�n nos permite general n�meros lo m�s aleatorio posibles, enteros positivos claro.
        srand(time(NULL));

        system("cls");
        printf("Por favor, escriba el limite inferior del randomizador, es decir, cual es el numero minimo que pueden tener las variables:\n(Tiene que ser minimo 1)\n");
        scanf("%d", &r);
        printf("Ahora por favor, escriba el limite superior:\n(Tiene que ser maximo 100)\n");
        scanf("%d", &R);

        //Asignando n�meros aleatorio a los enteros.
        *n = r + rand()%(R + 1 - r);
        *m = r + rand()%(R + 1 - r);
        //Las coordenadas tienen que estar dentro de los l�mites de n y m.
        *x = r + rand()%(*n + 1 - r);
        *y = r + rand()%(*m + 1 - r);

        //Para solucionar algunos errores.
        if(*x >= *n)
                *x = *n - 1;
        if(*y >= *m)
                *y = *m - 1;

        //Asignando n�meros aleatorio a los reales. Ya que no supimos como se generan de una manera m�s aleatoria nosotros le pusimos
        //una relaci�n con las otras variables aleatorias, as� tecnicamente son aleatorios pero no del todo porque dependen de las
        //variables anteriores.
        *z = (double) *n / (double) *m;
        *a = (double) *x / (double) *y;
        //printf("%lf %lf\n", *z, *a);
        *k = (double) *z / (double) *a;

        //Una vez teniendo los datos de n y m ya podemos saber cuanta memoria solicitar para las matrices.
        mapa = (char**)malloc(sizeof(char*)*(*n));
        mapad = (double**)malloc(sizeof(double*)*(*n));

        if(mapa == NULL || mapad == NULL) {
                printf("Ocurrio un problema con la memoria, intentelo de nuevo.\n");
                system("pause");
                return 1;
        }

        for(int i = 0; i < *n; i++) {
                mapa[i] = (char*)malloc(sizeof(char)*(*m));
                mapad[i] = (double*)malloc(sizeof(double)*(*m));
        }


        //Asignando numeros
        for(int i = 0 ; i < *n; i++)
        {
                for(int j = 0 ; j < *m; j++)
                {
                        int aux = 1 + rand()%(6); //As� disminuuimos la probabilidad de que haya tantos zombies.
                        switch(aux)
                        {
                        case 1:
                                mapa[i][j] = 'C';
                                break;
                        case 2:
                                mapa[i][j] = 'C';
                                break;
                        case 3:
                                mapa[i][j] = '#';
                                break;
                        default:
                                mapa[i][j] = 'X';
                        }
                        mapad[i][j] = -1;
                        if(mapa[i][j] == 'C' || mapa[i][j] == '#')
                                mapad[0][0]++;
                }
        }

        return 0;

}

int Save(int *n, int *m, int *x, int *y, double *z, double *a, double *k)
{
        //Ahora le pediremos el nombre de su archivo.

        //Declaramos todo las variables.
        char aux[50], direccion[50];
        FILE *fd;

        while(1) { //Es un ciclo por si es que el usuario introduce un nombre ya existente

                system("cls");
                //Despu�s de tener todos los datos ahora tenemos que guardar el caso.
                printf("Ahora ingrese el nombre con el que desea guardar su caso.\nRecuerde que su nombre no tiene que sobrepasar los 30 caracteres y que estara en la carpeta \"Usuario\"");
                printf("\nNo es necesaria la extension .txt y no puede llevar espacios.\n");

                char direccion2[50] = "Usuario\\"; //Creamos un string nuevo que nos va a "auxiliar" creandose y destruyendose en cada iteraci�n.
                //Empezamos a "armar" la direcci�n del archivo.
                scanf("%s", aux); //Pedimos el nombre del archivo.

                strcat(direccion2, aux);
                strcat(direccion2, ".txt"); //Le agregamos .txt para que sea de tipo texto.

                strcpy(direccion, direccion2); //Y se la mandamos a direccion para que tenga la direcci�n de lo que queremos trabajar.

                fd = fopen(direccion2, "r"); //Vemos si existe una direcci�n como la escrita.

                if(fd != NULL) { //Si ya existe esa direci�n entonces el "fd" no nos devolver� NULL, sino un puntero.
                        int decision;
                        printf("Ese nombre ya existe, escriba: \n1.Si quiere reemplazar el caso.\n2.Si quiere volver a escribir el caso.\n");
                        scanf("%d", &decision);
                        if(decision == 1) {
                                break;
                        }
                        fclose(fd);
                } else {
                        break;
                }
        }

        fclose(fd); //Cerramos el archivo para abrir uno nuevo con tipo escritura en la direcci�n escrita.

        fd = fopen(direccion, "w+");

        if(fd == NULL) {
                printf("Hubo un error con la creacion de su archivo intentelo de nuevo.\n");
                system("pause");
                fclose(fd);
                return 1;
        }

        //Usando el fprintf de manera adecuada podemos escribir sobre el archivo que acabamos de abrir para as�
        //poner el texto en un archivo .txt

        fprintf(fd, "%d %d\n", *n, *m);

        for(int i =  0; i < *n; i++) {
                for(int j = 0; j < *m; j++) {
                        fprintf(fd, "%c", mapa[i][j]);
                }
                fprintf(fd, "\n");
        }

        fprintf(fd, "%d %d\n%lf %lf\n%lf", *x, *y, *z, *a, *k);

        system("cls");

        printf("Tu caso fue guardado con exito.\n");

        system("pause");

        fclose(fd);

        return 0;
}
