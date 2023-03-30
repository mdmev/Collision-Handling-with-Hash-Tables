#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../include/main.h"
//          DEFINE          //
#define TABLE_SIZE 2000


unsigned long hash_function(unsigned long k) {
    return k % TABLE_SIZE; // k mod m
}

unsigned long hash_function_2(unsigned long k){
    int t1 = TABLE_SIZE-1;
    return 1 + (k % t1);  // 1 + (k mod (m-1))
}

hash_item* create_item(int key, char* value){
    hash_item* item = (hash_item*)malloc(sizeof(hash_item));        //Se crea espacio de memoria para un item
    item->key = (int)malloc(sizeof(int));                           //Se crea espacio de memoria para la key del item
    item->value = (char*)malloc(strlen(value)+1);                   //Se crea espacio de memoria para el valor del item

    item->key = key;                                                //Se asigna la key a la key de item creado
    strcpy(item->value,value);                                      //Se asignae value al value del item creado
    return item;                                                    //Se devuelve el item completo = {key,val}
}

Hash_table* create_table(int size){
    Hash_table* table = (Hash_table*)malloc(sizeof(Hash_table));        //Creamos espacio de memoria para la tabla hash
    table->items = (hash_item**)calloc(table->size,sizeof(hash_item*)); // Creamos espacio de memoria para los items de la tabla hash
    table->size = size;                                                 //Asignamos el tamaño de la tabla a table->size
    int i;
    for( i = 0; i<table->size;i++){                                     //Inicializamos la tabla en NULL
        table->items[i] = NULL;
    }
    return table;                                                       //Retornamos una tabla de tamaño variable vacia
}

void free_item(hash_item* item){                                        
    free(item->value);                                                  //Liberamos memoria del value
    free(item);                                                         //Liberamos memoria del item
}

void free_table(Hash_table* table){
    int i;
    for( i = 0; i<table->size;i++){
        hash_item* item = table->items[i];                              //asignamos cada item de la tabla a item
        if ( item != NULL)  free(item);                                 //Si no esta vacía liberamos memoria
    }
    free(table->items);                                                 //Liberamos memoria
    free(table);                                                        //Liberamos memoria
}

unsigned long linear_prob(Hash_table* ht,unsigned long key, int i){
    int index = hash_function(key);                                     //Se busca el index mediante la funcion hash
    return (index+i)% ht->size;                                         //Algoritmo linear probing = (h(k)+i) mod m
}

unsigned long quadratic_prob(Hash_table* ht, unsigned long key, int i){
    int index = hash_function(key);                                     
    return (index + i + 3*i*i)% ht->size;                               //Algoritmo quadratic probing = (k(k)+i + 3*i^2}) mod m
}

unsigned long double_hashing(Hash_table* ht, unsigned long key, int i){
    int index = hash_function(key);                                     
    return (index + i*hash_function_2(key)) % ht->size;                 //Algoritmo double hashing = (h(k) + ih_2(k)) mod m
}

void ht_insert(Hash_table* table, unsigned long key, char* value,char* type){
    hash_item* item = create_item(key,value);                           //Creamos el item que insertaremos a la tabla
    int j,i=0;
    while(i != table->size){                                            //Se recorre la tabla mediante un while
        if(type == "l")         j = linear_prob(table,key,i);           //Si la tabla es de tipo linear_probing se asigna la funcion
        else if(type == "q")    j = quadratic_prob(table,key,i);        //Si la tabla es de tipo quadratic_probing se asigna la funcion
        else if (type == "d")   j = double_hashing(table,key,i);        //Si la tabla es del tipo double_hashing se asigna la funcion
        if(table->items[j]==NULL){
            table->items[j] = item;                                     //Se rellena la casilla si esta vacía

            return;                                                     //Si rellenamos la casilla salimos de la función
        }
        else i++;                                                       //si la casilla esta ocupada se itera y se buca resolver la colision mediante cada metodo correspondiente
    }

}

int contar(Hash_table* table){                                          //Funcion que cuenta las casillas vacias (se realizan menos conteos)
    int cont = 0,i;                                                     
    
    for(i = 0;i < table->size;i++){                                     
        if(table->items[i] == NULL) cont++;                             //Si el item de la tabla esta vacío se cuenta
    }
    return cont;                                                        //Retorna las casillas vacías de cada función
}

int main(int argc, char* argv[]){
    //          CREAMOS ARCHIVOS            //
    FILE *linear_file;
    FILE *quadratic_file;
    FILE *double_file;
    //          CREAMOS EL TIPO DE ESCRITURA DEL ARCHIVO            //
    char* linear_type = "hash_linear_%d.txt";
    char* quadratic_type = "hash_qudratic_%d.txt";
    char* double_type = "hash_double_%d.txt";
    //          ASIGNAMOS EL ARRAY DE CHAR QUE GUARDARÁ EL NOMBRE COMPLETO DEL ARCHIVO          //
    char linear_name[21];
    char quadratic_name[23];
    char double_name[21];
    //          CONTADORES          //
    int linear_cont,quadratic_cont,double_cont;

    int N_MAX = atoi(argv[1]);  //Valor de la cantidad de numeros que se busca ingresar a la tabla hsah

    //          CREAMOS 3 TABLAS            //
    Hash_table* ht_linear = create_table(TABLE_SIZE);
    Hash_table* ht_quadratic = create_table(TABLE_SIZE);
    Hash_table* ht_double = create_table(TABLE_SIZE);

    //Creamos un array de numeros al azar entre 0 y 1000000 y os ingresamos a cada tabla//
    unsigned int numeros[N_MAX];
    int i;
    for(i = 0; i< N_MAX;i++){
        numeros[i] = rand()%1000001;
        ht_insert(ht_linear,numeros[i],"X","l");        //Se ingresan las keys, "X" como valor y "l" como el tipo de colision que se busca resolver luego
        ht_insert(ht_quadratic,numeros[i],"X","q");
        ht_insert(ht_double,numeros[i],"X","d");
    }

    //Calculamos la cantidad de casillas ocupadas en cada tabla//
    linear_cont = ht_linear->size - contar(ht_linear);
    quadratic_cont = ht_quadratic->size - contar(ht_quadratic);
    double_cont = ht_double->size - contar(ht_double);
    //Asignamos a x_name el nombre completo del archivo a crear//
    sprintf(linear_name,linear_type,linear_cont);
    sprintf(quadratic_name,quadratic_type,quadratic_cont);
    sprintf(double_name,double_type,double_cont);

    //Abrimos nuestros archivos//
    linear_file = fopen(linear_name,"w");
    quadratic_file = fopen(quadratic_name,"w");
    double_file = fopen(double_name,"w");


    int cont =1 ,j;
    for(j = 0; j < TABLE_SIZE;j++){
        if(j == 100*cont){              //Realizamos un salto de linea cada 100 columnas
            fprintf(linear_file,"\n");
            fprintf(double_file,"\n");
            fprintf(quadratic_file,"\n");
            cont++;}

        if(ht_linear->items[j] != NULL)
            fprintf(linear_file,"%s ",ht_linear->items[j]->value);          //Agregamos un "X" al .txt si la casilla está ocupada
        else
            fprintf(linear_file,"%s "," ");                                 //Agregamos un espacio al .txt si la casia está vacía
        
        //Se sigue igual que con linear
        if(ht_quadratic->items[j] != NULL)
            fprintf(quadratic_file,"%s ",ht_quadratic->items[j]->value);
        else
            fprintf(quadratic_file,"%s "," ");

        if(ht_double->items[j] != NULL)
            fprintf(double_file,"%s ",ht_double->items[j]->value);
        else
            fprintf(double_file,"%s "," ");
    }
    //Liberamos espacios de memoria y cerramos archivos
    free_table(ht_double);
    free_table(ht_quadratic);
    free_table(ht_linear);
    fclose(quadratic_file);
    fclose(double_file);
    fclose(linear_file);
    return 0;
}
