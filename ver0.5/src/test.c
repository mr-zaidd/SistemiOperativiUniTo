#include "include/inc.h"
#include "include/mylib.h"

void createKeyFile(int key){



}

int main(){

    int key;
    key = ftok(".", 'b');
    createKeyFile(key);
    return 0;

}


