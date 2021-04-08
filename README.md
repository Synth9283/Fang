# 1. Fang
A programming language made in C
## 1.1. Meaning
> Fang stands for "Feline Language". In hopes of it being cool like a cat!  
> On top of it, you can _byte_ with fang!
## 1.2. Latest change
> Added a bunch of operators to the lexer
## 1.3. Example code
```
// variables
x: i32;
// functions
functionName(): i32 {
    ....
}
// if statement
(x>3)? {
    ....
}: {
    ....
}
// else if
(x>3)? {
    ....
}:(!x)? {
    ....
}
// match or switch
(x)? {
    1: 5,
    2: 3,
    _: 1
}
```
## 1.4. Conventions
> The file extentions for the source code is `.fang`

| Statement              | Syntax                                              | Example                                                |
| ---------------------- | --------------------------------------------------- | ------------------------------------------------------ |
| Comment                | `// text`                                           | `// comment`                                           |
| Variables              | `varName: type`                                     | `x: i32`                                               |
| Functions              | `func(): type`                                      | `func(): i32 {}`                                       |
| If and else statements | `(conditional)? {}: {}`                             | `(x>5)? {}`                                            |
| Switch statements      | `(variable)? {cmp: statement, _: defaultStatement}` | `(x)? {1: print(1), 2: print(2), _: print("Default")}` |
## 1.5. To-do
### 1.5.1. Front end
- [x] Lexer
- [ ] Parser
- [ ] Semantic analyzer
