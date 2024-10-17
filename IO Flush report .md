# ubuntu 24.10
## 1.Откомпилировать и собрать программу, запустить, как есть.
![alt text](image-4.png)


'''c
#include<stdio.h>
int main(){

for(int i = 0 ; i<50; i++){
    printf(" message ");
    fflush(stdout);
    fprintf(stderr,"error");
    fflush(stderr);
}
return 0;
}

### Обнаружено, что результат состоит из чередующихся выводов "message" и "error", потому что функция fflush() принудительно очистила буфер.


## 2.del fflush()

![alt text](image-1.png)

'''c
#include<stdio.h>
int main(){

for(int i = 0 ; i<50; i++){
    printf(" message ");
    fprintf(stderr,"error");
}
return 0;
}

### "stdout" (стандартный вывод) буферизуется построчно, а "stderr" (стандартный вывод ошибок) не буферизуется.Итак, (error) предшествует (message).






## 3.Добвить символы '\n' в конец строк.
![alt text](image-2.png)

'''c
#include<stdio.h>
int main(){
/*
for(int i = 0 ; i<100; i++){
    printf(" message ");
    fprintf(stderr,"error");
}
*/
for(int i = 0 ; i<100; i++){
    printf(" message \n");
    fprintf(stderr,"error");
    }
return 0;
}

### Обнаружено, что при добавлении \n в код вывод происходит чередующимися строками. Это означает, что если вывод содержит символ новой строки (\n), буфер будет немедленно сброшен.

## 4.Перенаправить вывод (оба потока) в файл.

![alt text](image-5.png)

'''
./io>output.txt 2>error.txt
./io0>output.txt 2>error.txt
./io2>output.txt 2>error.txt

### Независимо от используемого способа, файлы output.txt и error.txt содержат только "message" и "error" соответственно. Это указывает на то, что стандартный вывод и стандартный вывод ошибок являются двумя независимыми потоками вывода, которые по умолчанию отправляются на экран терминала.











