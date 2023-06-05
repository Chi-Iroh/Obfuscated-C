// true is used when cleaning the code
#include <stdbool.h>

// Original code
#define _GNU_SOURCE

#include <signal.h>
#include <fenv.h>
_;
void ፷(int){exit(_);}
void ፷፷(volatile int){}
void my_strlen(ඞ)char*ඞ;{
    feenableexcept(FE_DIVBYZERO);
    signal(SIGFPE,፷);
    _^=_;
    do{፷፷(_/0[ඞ++]);}while(-1^++_);
}

main(a,b)char**b;{my_strlen(1[b]?1[b]:"");}

// Let's replace identifiers :
// a and b obviously stand for argv and argv, as they're in the main function
// ፷ is a call to exit, let's call it my_exit
// ፷፷ seems to do nothing, so dummy may be appropriate
// ඞ is a generic string passed to my_strlen, so str is fine
// Remains the global _, we have no clue of what it is for now, we'll just leave it
// And also add spaces and tabulations to increase readability
// _ and main are also implicitly int
#define _GNU_SOURCE

#include <signal.h>
#include <fenv.h>
int _;
void my_exit(int) {
    exit(_);
}

void dummy(volatile int) {

}

void my_strlen(char* str) {
    feenableexcept(FE_DIVBYZERO);
    signal(SIGFPE, my_exit);
    _ ^= _;
    do {
        dummy(_ / 0[str++]);
    } while(-1 ^ ++_);
}

int main(int argc, char** argv) {
    my_strlen(1[argv] ? 1[argv] : "");
}

// As the code is a bit cleaner now, we can deduce some things :
// #define _GNU_SOURCE grants us access to non-standard functions
// signal.h is the header to handle signals (SIGINT, SIGSEGV, SIGTERM, etc..)
// fenv.h is a floating-point-arithmetic-related header
// feenableexcept(FE_DIVBYZERO) enables trigerring a signal when encountering a division by zero (as it defaultly is an implementation-defined behaviour, here we are forcing the signal)
// signal(SIGFPE, my_exit) sets my_exit as a handler when encountering SIGFPE
// With these things, we can easily understand this code will trigger division by zero and use it to exit with a specific code (the global _)

// As XOR is true only when the two bits are differents, a XOR on multiple bits is true (nonzero) when at least one bit is different
// So A XOR A (A a random number) is false (0) as all bits are the same (it's the same number)
// So _ ^= _ is exactly the same as _ = 0;
// A do ... while loop continues if its condition is true (nonzero)
// The condition is -1 ^ ++_, and we said that a XOR result is when the two operands have the same value
// Here _ is zero-initialized then only incremented, it can't be equal to -1 so the XOR is always true
// The XOR is useless as _ is pre-incremented (++_ will never be 0), this is an infinite loop
// We can move the incrementation inside the loop and replace the loop by a while true loop

// We can also reverse operands of the array subscript operator []
#define _GNU_SOURCE

#include <signal.h>
#include <fenv.h>
int _;
void my_exit(int) {
    exit(_);
}

void dummy(volatile int) {

}

void my_strlen(char* str) {
    feenableexcept(FE_DIVBYZERO);
    signal(SIGFPE, my_exit);
    _ = 0;
    while (true) {
        dummy(_ / str++[0]);
        length++;
    }
}

int main(int argc, char** argv) {
    my_strlen(argv[1] ? argv[1] : "");
}

// As we're working with a function called my_strlen, _ is very likely to be the length of str
// This is correct because each loop iteration, _ is incremented, and str too.
// _ is thus the length of the string
// With that information, we can also notice that my_exit exits with _ as code.
// At this point, we have understood that the length is returned as exit code only when a division by zero occured

// We can see a division in the loop, _ / str++[0] : the length is divided by the current character
// In C, a string always ends with the NULL character (equals 0), so the division is an error (division by zero) only when the end of the string is reached
// Then, the signal handler is called and exits the length.
#define _GNU_SOURCE

#include <signal.h>
#include <fenv.h>
int length;
void my_exit(int) {
    exit(_);
}

void dummy(volatile int) {

}

void my_strlen(char* str) {
    feenableexcept(FE_DIVBYZERO);
    signal(SIGFPE, my_exit);
    length = 0;
    while (true) {
        dummy(length / str++[0]);
        length++;
    }
}

int main(int argc, char** argv) {
    my_strlen(argv[1] ? argv[1] : "");
}

// A little explanation about the dummy function, I added it to prevent the compiler from optimizing and then removing the division
// The dummy function takes a volatile int as parameter because volatile helps to prevent it