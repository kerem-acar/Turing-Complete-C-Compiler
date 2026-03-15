#include <stdlib.h>

typedef struct {
    int* array;
    int capacity;
} IntArray;



IntArray* initalizeIntArray(int capacity) {
    IntArray* myArray = malloc(sizeof(IntArray));
    myArray->array = NULL;
    myArray->capacity = 0;
    if (capacity > 0) {
        myArray->array = malloc(capacity * sizeof(int));
        myArray->capacity = capacity;
    }
    return myArray;
}




void setArrayIndex(IntArray* myArray, int index, int val) {
    int cap = myArray->capacity;

    if (myArray->array != NULL && index < cap && index >= 0) {
        myArray->array[index] = val;
    }
}



void pushBack(IntArray* myArray, int val) {
    IntArray* tmp = initalizeIntArray(myArray->capacity + 1);

    for (int i = 0; i < myArray->capacity; ++i) {
        setArrayIndex(tmp, i, myArray->array[i]);
    }

    setArrayIndex(tmp, myArray->capacity, val);

    free(myArray->array);
    myArray->array = NULL;
    
    myArray->array = tmp->array;
    myArray->capacity = tmp->capacity;

    tmp->array = NULL;
    free(tmp);
}



void deleteArray(IntArray* myArray) {
    if (myArray != NULL) {
        if (myArray->array != NULL) {
            free(myArray->array);
            myArray->array = NULL;
        }
        free(myArray);
        myArray = NULL;
    }   
}
