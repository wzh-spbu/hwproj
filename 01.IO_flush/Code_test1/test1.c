#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void Output_Normal(){
    printf("----------------------------------------------------------\n");
    printf("                    Normal output \n");
    printf("----------------------------------------------------------\n");
    for(int i = 1 ; i<10 ; i++){
        printf(" 'The %d-th message' " , i);
        fprintf(stderr , " 'The %d-th error message' " , i);
    }
}

void Output_with_fflush(){
    printf("----------------------------------------------------------\n");
    printf("                     Output with fflush()\n");
    printf("----------------------------------------------------------\n");
    for(int i = 1 ; i<10 ; i++){
        printf(" 'The %d-th message' " , i);
        fprintf(stderr , " 'The %d-th error message' " , i);
        fflush(stdout);
        fflush(stderr);
    }
}

void Output_with_n(){
    printf("----------------------------------------------------------\n");
    printf("                    Output no fflush() with \\n");
    printf("\n");
    printf("----------------------------------------------------------\n");
    for(int i = 1 ; i<10 ; i++){
        printf(" 'The %d-th message' " , i);
        fprintf(stderr , " 'The %d-th error message' " , i);
        fflush(stdout);
        fflush(stderr);
    }
}

void Redirect_Output_Normal() {
    FILE *outFile = freopen("output/output_normal.txt", "w", stdout);
    if (outFile == NULL) {
        perror("Failed to redirect stdout");
        return;
    }
    FILE *errFile = freopen("output/error_normal.txt", "w", stderr);
    if (errFile == NULL) {
        perror("Failed to redirect stderr");
        return;
    }
    Output_Normal();
    fclose(outFile);
    fclose(errFile);
}

void Redirect_Output_with_fflush() {
    FILE *outFile = freopen("output/output_fflush.txt", "w", stdout);
    if (outFile == NULL) {
        perror("Failed to redirect stdout");
        return;
    }
    FILE *errFile = freopen("output/error_fflush.txt", "w", stderr);
    if (errFile == NULL) {
        perror("Failed to redirect stderr");
        return;
    }
    Output_with_fflush();
    fclose(outFile);
    fclose(errFile);
}

void Redirect_Output_with_n() {
    FILE *outFile = freopen("output/output_with_n.txt", "w", stdout);
    if (outFile == NULL) {
        perror("Failed to redirect stdout");
        return;
    }
    FILE *errFile = freopen("output/error_with_n.txt", "w", stderr);
    if (errFile == NULL) {
        perror("Failed to redirect stderr");
        return;
    }
    Output_with_n();
    fclose(outFile);
    fclose(errFile);
}

int main(int argc, char *argv[]){
    int normal = 0, fflush_opt = 0, n_opt = 0, redirect_normal = 0, redirect_fflush = 0, redirect_n = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-normal") == 0) {
            normal = 1;
        } else if (strcmp(argv[i], "-fflush") == 0) {
            fflush_opt = 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            n_opt = 1;
        } else if (strcmp(argv[i], "-redirect_normal") == 0) {
            redirect_normal = 1;
        } else if (strcmp(argv[i], "-redirect_fflush") == 0) {
            redirect_fflush = 1;
        } else if (strcmp(argv[i], "-redirect_n") == 0) {
            redirect_n = 1;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    if (normal) {
        Output_Normal();
    }
    if (fflush_opt) {
        Output_with_fflush();
    }
    if (n_opt) {
        Output_with_n();
    }
    if (redirect_normal) {
        Redirect_Output_Normal();
    }
    if (redirect_fflush) {
        Redirect_Output_with_fflush();
    }
    if (redirect_n) {
        Redirect_Output_with_n();
    }

    return 0;
}