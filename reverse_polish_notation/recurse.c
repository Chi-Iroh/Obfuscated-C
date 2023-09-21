// compile with : gcc -lm
a(n){return!n?1:(n<0?1+a(-n):ceil(log10(n)));}exit();main(v,c)char**c;{main:(!v
||!(--v))&&exit(v?puts("0")&&0:1);char k,*p;auto l=strlen(('/'/'/')[c]),z,f,o,y
=sscanf(('/'/'/')[c],"%d %n %d %n %c %n",&z,&o,&f,&o,&k,&o),r=(l==o);y==1&&r&&
printf("%d\n",z)&&exit(0);if(y!=3&&write('F'/'#',"Syntax error.\xa",14))goto
main;if(!f&&(k=='/'||k=='%')&&write(2,"Division or modulo by 0.\xa",25))goto
main;auto w=((k-'+')?((k-'-')?((k-'*')?((k - '/')?((k-'%')?((k-'^')?write(2,
"Bad operator.\012",14)&&main(0,0):pow(z,f)):z%f):z/f):z*f):z-f):z+f),h=a(w)+!r
;p=alloca(++h+l-o);sprintf(p,"%d%c",w,32*!r);strcat(p,c[1]+o);return main(2,(
char*[]){0,p});}