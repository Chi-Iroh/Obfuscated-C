// This file is a kind of tutorial to introduce some syntaxes and concepts useful for obfuscation in C
// Don't try compile this file as there are many main functions
// It is necessary to know all these concepts before trying to clean this repository.
// This file should be read in order, because each step introduces a concept that is considered fully understood in the next sections and thus no longer explained.

#include <stdio.h>

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Honorable mentions : things I do not (or not much) cover in this repository but which must be tackled due to their wide use over obfuscated code.
// I'm covering these at the very beginning because explaining why I don't like use them helps me introducing some useful concepts that I will refer to below.

// A bunch of nonsense defines is the fastest and easiest way to produce seemingly obfuscated code, but it can also be easily defeated by compilers' flags to show preprocessed code.
// For instance, gcc has the flag -E
#define _ int
#define __ char
_ main(_ argc, __* argv[]){} /* will be desobfuscated after the preprocessor to become */ int main(int argc, char** argv){}
// So it's quite inefficient but sufficient for newbies to grasp the basic concept of obfuscation.
// I personnaly don't like use silly defines for obfuscation purposes due to their inefficiency as shown above,
// but also because there isn't real technical work behind this practice, as it's juste a way to replace identifiers and keywords with some garbage.

// Still in the same spirit, I won't linger over random variables / functions / structures / enumerations names, as it won't teach technical things.
// This practice however is worth a few words, as it has a huge advantage over defines, there isn't some "identifier decrypter" which acts as the preprocessor.
// The reason is that a define is a preprocessor instruction which replaces an identifier by some characters or not, and the preprocessor acts like a find-and-replace algorithm.
// Compilers offers us a chance to view their output as preprocessing comes before the real compilation stuff, so it may be useful for some debugging or educational goals.
// But when a variable for example is named n, this is the description we add to understand easily what really means that value.
// For a computer it is just some random bytes but for a programmer it has a meaning, for insytance the number of spaces in a user input.
// So basically, scrambling identifiers is way more too powerful and difficult to defeat than #define them, as the preprocessor doesn't compile anything but juste replaces text in the code.
int xzbk42;

// Even if this isn't my favourite way to obfuscate a code, I'm using it to obfuscate variable names with Unicode characters (there are funny ones).
// However, I'm doing this just for fun, as I believe garbage identifiers name are way less interesting than a good old twisted obfuscated logic.
// So you will encounter some things as
int ፷;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Let's begin with one of the easiest but rather powerful idea : messing with strings.
// From the moment you use string literals (a literal is a hardcoded value, such as 4, '4' or "444", known at compile-time), your code usually become less obfuscated.
// That's because string literals are very often used to display a text to the user, so it must have a meaning and not be too ununderstandable.
// For instance, a more-or-less game implementation probably will display messages such as 'More', 'Less', 'You lose', 'You win', which may be super helpful to grasp the idea behind an obfuscatd code.
// The point with strings is that they contain numbers which are printable and meaningfull for humans.
// It can be easily verified by compiling a C program containing printf, puts or some I/O function with string literal, and then display the binary file (command in terminal or GUI text editor are fine).
// Despite being reading a binary file with CPU instructions, some bytes are understandable and contain our string literal.
// All the issue now is to find a solution to prevent one from having access to important information thanks to strings.

// A first solution would be make the string difficult to read in the source code, as a string is nothing more than an array of numbers.
char *str = "hello";                            // usual syntax
char str[] = { 'h', 'e', 'l', 'l', 'o', '\0' }; // cumbersome syntax
char str[] = { 104, 101, 108, 108, 111, 0 };    // hardcoding each char as a number according to ASCII table (numbers > 127 belong to the extended ASCII table) makes no difference in binary but hinders reading
char str[] = {
    10 * 10 + 4,                                // easy math
    0145,                                       // bases are not hard to deal with using a calculator (this octal base (base 8))
    0x6C,                                       // same, hexadecimal base here (base 16)
    0b01101100,                                 // binary here (base 2) (standard in C23, GNU extension before)
    '\x6F',                                     // strictly equivalent to 0x6F without single quotes, useful in string literals
    2 ^ (3 ^ 1)                                 // just some fancy bitwise operations (XOR), here 2 ^ (3 ^ 1) = 0b010 ^ (0b101 ^ 0b001) = 0b010 ^ 0b100 = 0b000 = 0 (NULL terminator)
};
// Mixing bases in a single calculation is also very disturbing and adds complexity.

// Such an array is awful to read but perfectly fine, and it totally hides our text at first glance.
// Nevertheless, it's not so hard to make it readable, especially using a calculator.
// It's quite more difficult given the binary executable containing this array, because generally (it depends of its storage class (static or not for example)) it won't be treated as a string literal.
// Though it's still possible to get those characters from the binary file, but it needs disassembling into assembly and then looking for the code initializing the string.
// For instance, a compiler will initialize it by setting the four first bytes at once, by copying the value (104 << 24 | 101 << 16 | 108 << 8 | 108) at the starting address.
// Then it will set the value (111 << 8 + 0) in the two remaining bytes.
// That requires mor work but once you've found these values in the assembly code, you can easily get the string using bitwise operations.

// Another solution slightly more difficult to deal with in our context is encrypting the string, and then decrypting it later.
// Let's take a simple algorithm as an example, each character will be encrypted using XOR and its index in the string, for instance, 'h' is the first char so its encrypter value if 'h' XOR 1, then 'e' will be 'e' ^ 2 etc..
// h : 105 (i), e : 103 (g), l : 111 (o), l : 104 (h), o : 106 (j), \0 : 6 (non printable) | note that the two 'l' haven't the same encrypted value because it depends of its index, which is useful to avoid patterns.
// XOR is very straightforward to decrypt, as (a XOR b) XOR b equals a
int main(void) {
    char str[] = { 105, 103, 111, 104, 106, 6 };    // may be obfuscated using bases and/or arithmetic
    for (unsigned i = 0; i < 6; i++) {
        str[i] ^= (i + 1);                          // decryption algorithm
    }
    puts(&str[0]);                                  // Be careful to have a working decryption algorithm, the string must end by a NULL terminator !
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Usually, a function is defined as 'type function(type1 var1, ..., typeN varN) {}'.
// But a very old syntax enables doing 'type function(var1, ..., varN) type1 var1; ... ; typeN varN {}'
// This syntax is however still supported nowadays for retrocompatibility purposes.
// See also https://stackoverflow.com/questions/1585390/c-function-syntax-parameter-types-declared-after-parameter-list
// Note that this syntax is removed in C23 : https://en.cppreference.com/w/c/23
int main(argc, argv) int argc; char *argv[]; { return 0; } /* is equivalent to */ int main(int argc, char *argv[]) { return 0; }

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// In C, str[index] is exactly equivalent to index[str]
// Firstly, only two value types accept array subscript operators, pointers and static arrays (arrays defined like 'type array[size] = {...}')
// Then, in C, a static array behaves like a pointer (please note that is said behaves and not is) to its first element, thus array is implicitly casted to &array[0].
// That's why you'll see both char** argv or char* argv[] in main function prototype.
// After these explanations, let's dive into how the compiler deals with str[index].

// In C str[index] is defined as *(str + index).
// Thus index[str] = *(index + str).
// As addition is commutative, index + str = str + index, so str[index] = index[str].
int main(int argc, char *argv[]) {
    puts(argv[argc - 1]);   // Usual way to display the last command line argument
    puts((argc - 1)[argv]); // Also correct
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Everything in C (functions return type, variables) is defaultly of int type, unless we specify another type
// This rule applies to the main function by the way
// The main function is also a special one which defaultly returns 0, even if no return statement is present
// Don't do this in any other function than main, in that case the return value will be undefined !
implicit_max(a, b) { return a > b ? a : b; } /* is equivalent to */ int explicit_max(int a, int b) { return a > b ? a : b; }

// Combination is the implicit int rule, old parameter syntax and implicit return 0 in main.
main(argc, argv) char *argv[]; {}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// It should be relevant to recall some things about Boole algebra, as it abusing of it may very useful to create compact code or recursion.
// In C, a builtin type value (int, char, double, enum.., no struct can appear in condition) is considered false if equals 0, otherwise true (4 is true, 0 is false).
// Logic and (&&) has an interesting and useful property, when executing A && B, B isn't executed if A is false.
// There's also a rule for logical or (||), when executing A || B, B isn't executed if a is true.
int main(int argc, char *argv[]) {
    if (argc) {                 // The usual way
        puts(argv[argc - 1]);
    }
    argc && puts(argv[argc - 1]);   // One-liner
    argc-- && puts(argv[argc]);     // Working too
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// How could one speak about obfuscation without mentionning labels and the goto keyword ?
// A goto is by far the best mean to cause a big mess in your brain, as it can not less than to jump to another line of code in the same function.
int main(int argc, char* argv[]) {
display:                            // Label : where to jump later
    puts(argv[--argc]);             // Displaying the last command line argument and decreasing argc to go back toward the first one
    if (argc) {                     // Continuing only if argc isn't zero
        goto display;               // Jumping back to the "loop" beginning.
    }
}

// Serious warning, the use of goto is generally not encouraged, as it is an open door to the so-called "spaghetti code".
// Spaghetti code is a code with a difficult to follow and understand control flow (the "path" of executed instructions).
// Control flow is impacted by loops (as for, while, do ... while), conditions (if, else).
// Remain jumps (goto (local jumps), function calls, or non-local jumps (setjmp / longjmp, see below)) and switch which is a bit special, it is covered below.
// The problem of goto is that the compiler cannot prevent you from coding nonsense because you have more control, in opposite to usual for or while-based loops whichs are delimited by brackets.
// You are now fully aware of the risks, so be sure to know what you're doing and read your code twice.
// Note that in some assembly languages (an intermediate language before the creation of a binary executable file, depending of CPUs), there may be only goto-like jumps and no strictly speaking loops.
// Obviously, every loop or condition can be written with jumps.
int main(int argc, char *argv[]) {
    do {                            // Same code as above, but goto is replace by a do-while loop.
        puts(argv[--argc]);
    } while (argc);                 // As the condition is checked at the end of the "loop" in the above code, a do-while loop is used instead of a simple while loop.
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------
