#include <stdio.h>
#include <string.h>
unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p){
        int* ip = (int*)p;
        int i;
        int res=0;
        for(i=0; i<5; i++){
                printf("%d -> %d\tres: %d\n",i,ip[i],res);
                res += ip[i];
        }
        printf("%d -> %d\tres: %d\n",i,ip[i],res);
        return res;
}

int main(int argc, char* argv[]){
        if(argc<2){
                printf("usage : %s [passcode]\n", argv[0]);
                return 0;
        }
        if(strlen(argv[1]) != 20){
                printf("passcode length should be 20 bytes\n");
                printf("len: %ld\n",strlen(argv[1]));
                return 0;
        }

        if(hashcode == check_password( argv[1] )){
                printf("output\n");
        }
        else
                printf("wrong passcode.\n");
        return 0;
}