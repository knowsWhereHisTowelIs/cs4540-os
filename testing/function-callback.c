#include "function-callback.h"

//https://stackoverflow.com/questions/142789/what-is-a-callback-in-c-and-how-are-they-implemented
// http://www.geeksforgeeks.org/function-pointer-in-c/

void useCallback(void (*callbackPtr)()){
    (*callbackPtr)();
}

void hello() {
    printf("Hello World\n");
}

void goodbye() {
    printf("Goodbye\n");
}

int main(int argc, char* argv[]) {
    // 2nd parathn used for params
    void (*helloPtr)() = &hello;
    (*helloPtr)();

    useCallback(&goodbye);
    return 0;
}
