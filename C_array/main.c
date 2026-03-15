#include "array.c"

int main() {
    //Example usage
    IntArray* myArray = initalizeIntArray(3);

    setArrayIndex(myArray, 0, 5);
    setArrayIndex(myArray, 1, 2);
    setArrayIndex(myArray, 2, 9);

    pushBack(myArray, 11);

    deleteArray(myArray);
    
    return 0;
}