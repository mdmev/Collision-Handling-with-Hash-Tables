# Collision-Handling-with-Hash-Tables

The current folder contains 2 main files, src/main.c and include/main.h, where Tarea3.c is the main file that contains all the executable functions of the program, while Tarea3.h contains the initialization of the functions that exist in Tarea3.c. The main functions that these files have are:

// FUNCTIONS //
  * unsigned long hash_function(unsigned long k); // Default hash function of the type h(k) = k mod m
  * unsigned long hash_function_2(unsigned long k); // Hash2 function for double hashing of the type h(k) = 1 + (k mod(m-1))
  * void free_item(hash_item* item); // Function that frees memory of an item
  * void free_table(Hash_table* table); // Function that frees memory of the hash table
  * unsigned long linear_prob(Hash_table* ht,unsigned long key, int i); // Function that resolves collisions through linear probing
  * unsigned long quadratic_prob(Hash_table* ht, unsigned long key, int i); // Function that resolves collisions through quadratic probing
  * unsigned long double_hashing(Hash_table* ht, unsigned long key, int i); // Function that resolves collisions through double hashing
  * void ht_insert(Hash_table* table, unsigned long key, char* value,char* type); // Function that inserts a key and a value into the specified hash table, also receives   * a parameter that indicates the type of collision resolution to be used
  * int contar(Hash_table* table); // Function that counts the number of empty items in a hash table

Together, these functions execute a program that creates a hash table and manages its collisions through the open addressing strategy, which consists of 3 different functions: linear probing, quadratic probing, and double hashing, which handle these collisions in different ways. The program creates a hash table with a structure for the table of items, size, and for each item of the key-value type. This table has a size of 2000 elements and resolves collisions for different data that can be entered. To compile this program, you must write:
```bash
  gcc main.c -o main.exe
```

To execute it, you must enter the number of data you want to enter into the hash table as parameters, in the following way:

```bash
  src/main.exe <parameter>
```

Finally, the folder contains a subfolder with all the requested files created, i.e., handling collisions for each type and for 100, 500, 1000, and 1500 data.

Analyzing this data, we can notice that for resolving collisions, linear probing must add 1 to the index where the new data will be located. The main problem with this is that by adding 1, the data will be grouped very frequently, making the search more complicated, as shown in the files displayed, where the more data is grouped, the closer they are.

On the other hand, quadratic probing enters data by adding the square of the data, so it solves the linearly grouped data to some extent. The problem that this method can cause is that by entering data squared, it is more likely to generate overflow, and the data may not be entered properly.

Finally, for double hashing, we notice that the entered data depends on another hash function, and in turn, the main hash function is modified. The main problems that this can bring us are that the compilation time of this method will be greater than the other two combined. However, the method of resolving these collisions is much more optimal than the others.

Note: when compiling the program, a warning is generated, not an error. This warning does not affect the execution of the program, so it can be executed as usual.
