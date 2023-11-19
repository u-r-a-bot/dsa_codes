/*
 * File: hashing_doublehashing.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: November 1, 2023
 * Description: This program implements hashing using using double hashing for collision resolution
 */


// IMPORTANT: Use hash2(x) = 11 - (x % 11) as the 2nd hash function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 23

typedef struct KeyValue {
    char *key;
    char *value;
    bool isDeleted;
} KeyValue;

typedef struct {
    KeyValue **array;
    int size;
    float load_factor;
    // num of keys present
    int num_keys;
    // num of array indices of the table that are occupied
    int num_occupied_indices;
    // num of ops done so far
    int num_ops;
} HashTable;


KeyValue *createKeyValue(char *key, char *value) {
    KeyValue* newKeyValue = (KeyValue*)malloc(sizeof(KeyValue));
    if (newKeyValue != NULL) {
        newKeyValue->key = key;
        newKeyValue->value = value;
        newKeyValue->isDeleted =false;
    }
    return newKeyValue;
}

HashTable* createHashTable() {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->array = (KeyValue **)malloc(TABLE_SIZE * sizeof(KeyValue *));
    for (int i=0; i<TABLE_SIZE; i++)
        newTable->array[i] = NULL;

    newTable->size = TABLE_SIZE;
    newTable->load_factor = 0;
    newTable->num_keys = 0;
    newTable->num_occupied_indices = 0;
    newTable->num_ops = 0;
    return newTable;
}


// use sum of ascii values to convert string to int
int key_to_int(char* key){
    int sum =0;
    for (int i = 0; i < strlen(key); i++)
    {
        sum += (int)key[i];
    }
    return sum;
}
int hash1func(int key){
    return (key+2394)%TABLE_SIZE;
}
int hash2func(int key){
    return 11 - (key%11);
}

// this equals the number of keys in table/size of table
float get_load_factor(HashTable *ht){
    return (float)ht->num_keys /(float)TABLE_SIZE;
}
// return the index position in the table where the insertion happens
// return -1 if insertion fails
int insert_key_value(HashTable *ht, char* key, char* value){
    KeyValue* ins = createKeyValue(key, value);
    for (int i = 0; i < 23; i++)
    {
        int index = hash1func(key_to_int(key)) + i* hash2func(key_to_int(key));
        if (ht->array[index] == NULL )
        {
            ht->array[index] = ins;
            ht->num_ops++;
            ht->num_keys++;
            ht->size++;
            ht->num_keys++;
            ht->load_factor = get_load_factor(ht);
            return index;
        } 
        
    }
      
}

// return the value of the key in the table
// return NULL if key not found
char* search_key(HashTable *ht, char* key){
    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = hash1func(key_to_int(key)) + i* hash2func(key_to_int(key)); 
        if(ht->array == NULL){
            return NULL;
        }
        else if(strcmp(ht->array[index]->key, key) == 0 && ht->array[index]->isDeleted ==false)
        {
           return ht->array[index]->value;
    }
}

    return NULL;
}
// return the index position in the table where the deletion happens
// return -1 if deletion fails
int delete_key(HashTable *ht, char* key){
        int index =0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            index = hash1func(key_to_int(key)) + i* hash2func(key_to_int(key)); 
            if(strcmp(ht->array[index]->key, key) == 0)
            {
                ht->array[index]->isDeleted =true;
                ht->num_ops++;
                ht->size--;
                ht->load_factor = get_load_factor(ht);
                return index;
            }
    }
    return -1;
}



// this equals the number of operations done so far/num of elems in table
int get_avg_probes(HashTable *ht){
    return ht->num_ops / ht->num_occupied_indices;
}

// display hash table visually
void display(HashTable *ht){
    printf("\n---------------------------------------------\n");
    printf("\nindex\t\tkey\t\tValue");
     printf("\n---------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(ht->array[i] == NULL){
            printf("\n%d" , i);
        }
        else if(ht->array[i]->isDeleted == true){
            printf("\n%d\t\tDeleted\t\tDeleted",i);
        }
        else{
            printf("\n%d\t\t%s\t\t%s" , i , ht->array[i]->key , ht->array[i]->value);
        }
    }
    


    printf("\n---------------------------------------------\n");
}


// -> Insert the following key, values in the table:
// 1. 'first name' -> <your first name>
// 2. 'last name' -> <your last name>
// 3. 'uid' -> <your uid>
// 4. 'sport' -> <your favorite sport>
// 5. 'food' -> <your favorite food>
// 6. 'holiday' -> <your favorite holiday destination>
// 7. 'role_model' -> <your role model>
// 8. 'subject' -> <your favourite subject>
// 9. 'song' -> <your favourite song>
// 10. 'movie' -> <your favorite movie>
// 11. 'colour' -> <your favorite colour>
// 12. 'book' -> <your favorite book>

// -> Test the table with search and delete operations


int main(){
    HashTable* a  = createHashTable();
    char* key1 = "first name";
    char* key2 = "last name";
    char* key3 = "uid";
    char* key4 = "uid";
    char* val1 = "Prath";
    char* val2 = "Khac";
    char* val3 = "20233400047";
    char* val4 = "20233400047";
    int inserted[4];
    int deleted[3];
    inserted[0] = insert_key_value(a,key1,val1);
    inserted[1] = insert_key_value(a,key2,val2);
    inserted[2] = insert_key_value(a,key3,val3);
    inserted[3] = insert_key_value(a,key4,val4);
    deleted[0] = delete_key(a , key1);
    display(a);
    char* found = search_key(a , key2);
    printf("\nThe following value is present at the given key:-  %s" , found);
    
    
    

}