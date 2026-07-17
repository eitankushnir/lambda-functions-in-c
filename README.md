# lambda-functions-in-c
Adding lambda expressions to the c language using macros. (not practical)

## Notice
This only works on GNU C (C compiled using gcc with the -std=gnuX flag).  
Utilizes gnu extensions like statement expressions and nested functions, of which the latter is gnu only. 

## The Macro
```c
#define lambda_impl(ret, params, linenr, counter, func)  \
  ({                                                     \
    ret genid__lambda(lmb_, linenr, counter) params func \
        &genid__lambda(lmb_, linenr, counter);           \
  })

#define lambda(ret, params, arrow, func) \
  lambda_impl(ret, params, __LINE__, __COUNTER__, func)

```

The `lambda` macro creates a nested function with an id (comprising of the line the lambda is written in the number of lambda functions created beforehand) that minimizes naming conflicts across translation units.
The pointer to the nested function is then returned using the statement expression, meaning it can be used inline.
There are more variant of the lambda macro shown in the examples.

## Example
```c
void void_callback(void (*cb)(void)) {
  printf("Calling cb...\n");
  cb();
}

void int_callback(int (*cb)(int), int cb_arg) {
  printf("Callback result: %d\n", cb(cb_arg));
}

int main() {
  void_callback(lambda(void, (), ->, { printf("Regular lambda\n"); })); // Will print "Regular lambda".
  void_callback(action({ printf("Action lambda"); }));                  // Will print "Action lambda".

  int_callback(lambda_expr(int, (int x), ->, x + 5), 6); // Will be called with x = 6. and then print "Callback result: 11".
  int_callback(fn(int, (int x), { return x + 5; }), 6);  // Equivilent to the line above (but no need for the arrow).
}
```
