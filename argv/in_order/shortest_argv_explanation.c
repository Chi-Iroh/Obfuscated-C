#include <stdio.h>

// Original code
main(c,v)int**v;{for(;*v;)puts(*v++);}

// Let's indent the code and complete main parameters and return type
int main(int argc, int** argv) {
    for (; *argv; ) {
        puts(*argv++);
    }
}

// Now let's replace *argv by argv[0]
int main(int argc, int** argv) {
    for (; argv[0]; ) {
        puts(argv++[0]); // argv[0]++ is wrong because ++ applies to argv[0], and in *argv++, ++ only applies to argv and not *argv
    }
}

// Let's be a little more explicit
int main(int argc, int** argv) {
    while (argv[0] != NULL) {
        puts(argv[0]);
        argv++;
    }
}

// or
int main(int argc, int** argv) {
    unsigned i = 0;
    while (argv[i] != NULL) {
        puts(argv[i]);
        i++;
    }
}

// Why argv is int** ? And why does it work ?
// int** was to save 1 character and be the more compact as I could be, instead of char**.
// int** argv is working here, because only argv[a] is accessed, not argv[a][b]
// let int** argvi and char** argvc. sizeof(argvi[i]) == sizeof(argvc[i]) | both are pointers (int* or char*), same size
// Very often, sizeof(argvi[i][j]) != sizeof(argvc[i][j]) because argvi[i][j] is int and argvc[i][j], and sizeof(int) is very likely to be strictly greater than sizeof(char)
// So, it does work because there is one level of dereference (*ptr), which is the same size, and puts will cast int* to char*, then do its stuff