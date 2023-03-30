#include <stdio.h>
#ifndef INCLUDE
#define INCLUDE
//          STRUCTURES          //
typedef struct hash_item{ //Struct para cada item de la hashtable
    int key;
    char* value;
}hash_item;

typedef struct Hash_table{ //Estructura de la hashtable como tal, cada item = {key,val}, y su tamaño
    hash_item** items;
    int size;
}Hash_table;

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

#endif //INCLUDE//