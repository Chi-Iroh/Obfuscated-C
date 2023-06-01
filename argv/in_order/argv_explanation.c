// Original code
main(Ⲿ,፷)char**፷;{Ⲿ--&&puts(main(Ⲿ,፷)+Ⲿ[፷]);}

// Let's replace those weird identifiers by argc and argv
// And also add spaces and tabulations to increase readability
main(argc,argv) char** argv; {
    argc-- && puts(main(argc, argv) + argc[argv]);
}

// Everything in C (functions return type, variables) is defaultly of int type, unless we specify another type
// This rule applies to the main function by the way
// The main function is also a special one which defaultly returns 0, even if no return statement is present
// Don't do this in any other function than main, in that case the return value will be undefined !
// Usually, a function is defined as 'type function(type1 var1, ..., typeN varN) {}'.
// But a very old syntax enables doing 'type function(var1, ..., varN) type1 var1; ... ; typeN varN {}'
// So 'int main(argc, argv) int argc; char *argv[];' is exactly the same as 'int main(int argc, char *argv[])'
// Argv is declared as char** but argc is leaved as implicit int.
int main(int argc, char** argv) {
    argc-- && puts(main(argc, argv) + argc[argv]);
    return 0;
}

// A last strange syntax occurs when using subscript operator (square brackets [])
// In C, str[index] is exactly equivalent to index[str]
// Firstly, only two value types accept subscript operators, pointers and static arrays (arrays defined like 'type array[size] = {...}')
// Then, in C, a static array behaves like a pointer (please note that is said behaves and not is) to its first element, thus array is implicitly casted to &array[0].
// After these explanations, let's dive into how the compiler deals with str[index].
// In C str[index] is defined as *(str + index), thus index[str] = *(index + str), and as addition is commutative, index + str is equal to str + index and str[index] equal to index[str].
int main(int argc, char** argv) {
    argc-- && puts(main(argc, argv) + argv[argc]);
    return 0;
}

// OK, for now syntax-only tricks, now let's explain the logic
// In C (and numerous other languages), logic and (&&) has an interesting and useful property, when doing A && B, if a is false then B isn't executed.
// In C, a builtin type value (int, char, double, enum.., no struct can appear in condition) is considered false if equals 0, otherwise true (4 is true, 0 is false)
// Note that the -- to decrement argc is a post-increment, it means that argc is decremented after have been compared in the logic and
// That statement become cleaner in the code below
// We can replace that logic and with an if condition to make it cleaner
int main(int argc, char** argv) {
    if (argc != 0) {
        argc--;
        puts(main(argc, argv) + argv[argc]);
    }
    return 0;
}

// Now, let's focus on the puts statement to demystify the algorithm
// You should've noticed that the main function is recursive.
// Main returns 0 in any case, so main(argc, argv) + argv[argc] is exactly the same as argv[argc], so this line displays a string in argv.
// So as we don't care of the call's return value, we can move it out of the puts statement.
int main(int argc, char** argv) {
    if (argc != 0) {
        argc--;
        main(argc, argv);
        puts(argv[argc]);
    }
    return 0;
}

// Hurray, the code is fully readable now !
// The last thing to explain is the main recursion, here we go :
// main(3, { "./a.out", "hello", "world" })
//  argc-- = 2;
//  main(2, { "./a.out", "hello", "world" })    -->     argc-- = 1;
//  puts(argv[2] = "world");                    |       main(1, { "./a.out", "hello", "world" })    -->     argc-- = 0;
// return 0;                                    |       puts(argv[1] = "hello");                    |       main(0, { "./a.out", "hello", "world" }) --> argc = 0 --> return 0;
//                                              |       return 0;                                   |       puts(argv[0] = "./a.out");
//                                              |                                                   |       return 0;
// Pay attention to the fact that main is called recursively before puts, so argv is displayed in order.