# recursive-descent-parser
A recursive-descent parser in C, that evaluates arithmetic expressions

```
$ gcc parser.c -o parser
$ parser
> 3+9
12
> 10 * 4  * 2 * 3 / 8
30
> 5 - - - + - (3 + 4) - +2
10
> 2^10
1024
```

## what does it do?

- [x] addition
- [x] subtraction
- [x] single-digit numbers
- [x] multi-digit numbers
- [x] multiplication
- [x] division
- [x] negation
- [x] parentheses
- [x] exponentiation
- [x] floating point
- [x] error handling
