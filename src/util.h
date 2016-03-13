/* 
 * Copyright 2016 Emaad Ahmed Manzoor
 * License: Apache License, Version 2.0
 * https://github.com/emaadmanzoor/sigmod16
 */
#ifndef SIGMOD16_UTIL_H_
#define SIGMOD16_UTIL_H_

namespace std {

#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

#define BUFSZ   100

} // namespace std

#endif
