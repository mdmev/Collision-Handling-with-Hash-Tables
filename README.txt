La carpeta actual contiene 2 archivos principales, Tarea3.c y Tarea3.h, en donde
Tarea3.c es el archivo principal el cual contiene todas las funciones ejecutables
del programa, por otro lado Tarea3.h contiene la inicialización de las funciones
que existen en Tarea3.c. Las principales funciones que estos archivos poseen son:

//          FUNCIONES           //
unsigned long hash_function(unsigned long k);                                  //Funcion hash default del tipo h(k) = k mod m
unsigned long hash_function_2(unsigned long k);                                //Funcion hash2 para el double hashing del tipo h(k) = 1 + (k mod(m-1))
void free_item(hash_item* item);                                               //Funcion que libera memoria de item
void free_table(Hash_table* table);                                            //Funcion que llibera memoria de la tabla hash
unsigned long linear_prob(Hash_table* ht,unsigned long key, int i);            //Funcion que resuelve colisiones por linear probing
unsigned long quadratic_prob(Hash_table* ht, unsigned long key, int i);        //Funcion que resuelve colisiones por quadratic_probing
unsigned long double_hashing(Hash_table* ht, unsigned long key, int i);        //Funcion que resuelve colisioes por double_hashing
void ht_insert(Hash_table* table, unsigned long key, char* value,char* type);            //Funcion que inserta una key y un valor a la tabla hash en cuestion, también recibe un parámetro que indica el tipo de colision por e cual se desea resolver
int contar(Hash_table* table);                                                 //Funcion que cuenta los items vacíos en una tabla hash

Juntas estas funciones ejecutan un programa que se encarga de crear una tabla hash
y manejar sus colisiones mediante la estrategia de open adressing, la cual consiste
en 3 distintas funciones, linear probing, quadratic probing y double hashing que se
encargan de manejar estas colisiones de formas distintas. El programa crea una tabla
hash con una estructura para la tabla del tipo items, size, y para cada item 
del tipo key,value, esta tabla tiene un tamaño de 2000 elementos, y esta misma
resuelve colisiones para distintos datos que se puedan ingresar. Para compilar este
programa se debe escribir:

                    gcc Tarea3.c -o Tarea3.exe
Para ejecutar se deben ingresar como parámetros la cantidad de datos que se quieran
ingresar a la tabla hash, de la siguiente manera
                    ./Tarea3.exe 1500

Finalmente la carpeta posee una carpeta con todos los archivos solicitados creados, es decir,
manejar colisiones para cada tipo y para 100, 500, 1000 ty 1500 datos.

Analizando estos datos podemos notar que para resolver colisiones el linear probing suma
se debe sumar 1 al indice donde se ubicará el nuevo dato a ingresar, el principal problema
con esto es que al sumar 1 los datos se agruparán muy seguido, por lo que luego
la búsqueda se complica, esto lo notamos en los archivos mostrados, donde mientras
mas datos se agrupan, más seguidos estos se encuentran

Por otro lado el quadratic probing ingresa datos sumando datos al cuadrado, por lo que
se soluciona de cierta manera los datos agrupados lineramente, el problema que este método puede
causar es que al ingresar datos al cuadrado, es más problable que se genere overflow y
los datos no se puedan ingresar de buena forma.

Finalmente para el double hashing, notamos que los datos ingresados dependen de
otra función hash, y a su vez se modifica la principal, los principales problemas
que nos pueden traer esto es que el tiempo de compilación de este será mayor que los
2 anteriores juntos. Sin embargo, el método de resolvere estas colisiones es mucho más óptimo
que los otros.

PD: al compilar el programa se genera un warning, no un error, este warning no afecta
a la ejecución del problema, por lo que se puede ejecutar igual.
