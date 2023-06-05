// Original code
main(Ⲿ,፷)char**፷;{Ⲿ--&&puts(main(Ⲿ,፷)+Ⲿ[፷]);}

// Let's replace those weird identifiers by argc and argv
// And also add spaces and tabulations to increase readability
main(argc, argv) char** argv; {
    argc-- && puts(main(argc, argv) + argc[argv]);
}

// Let's get rid of this old function parameter syntax and also add implicit int.
int main(int argc, char** argv) {
    argc-- && puts(main(argc, argv) + argc[argv]);
    return 0;
}

// Reverse operands of the array subscript operator [], array[index] is more readable than index[array], right ?
int main(int argc, char** argv) {
    argc-- && puts(main(argc, argv) + argv[argc]);
    return 0;
}

// Note that the -- to decrement argc is a post-increment, it means that argc is decremented after have been compared in the logic and
// Let's replace the logical and by an if condition.
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