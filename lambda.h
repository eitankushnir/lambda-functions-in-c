#ifndef LAMBDA__H
#define LAMBDA__H

#if defined(__clang__) || defined(_MSC_VER)
#define lambda_impl(ret, params, linenr, counter, func) NULL
#elif defined(__GNUC__) || defined(__GNUG__)
#define genid__lambda_helper(a, b, c) a##b##_##c
#define genid__lambda(a, b, c) genid__lambda_helper(a, b, c)
#define lambda_impl(ret, params, linenr, counter, func)  \
  ({                                                     \
    ret genid__lambda(lmb_, linenr, counter) params func \
        &genid__lambda(lmb_, linenr, counter);           \
  })
#endif // Compiler check for lambda_impl

#define lambda(ret, params, arrow, func) \
  lambda_impl(ret, params, __LINE__, __COUNTER__, func)

#define lambda_expr(ret, params, arrow, expr) \
  lambda_impl(ret, params, __LINE__, __COUNTER__, { return (expr); })

#define action(func) \
  lambda_impl(void, (void), __LINE__, __COUNTER__, func)

#define fn(ret, params, func) \
  lambda_impl(ret, params, __LINE__, __COUNTER__, func)

#endif // LAMBDA__H
