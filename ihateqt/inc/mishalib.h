//
// Created by dev on 3/14/22.
//

#ifndef IHATEQT_MISHALIB_H
#define IHATEQT_MISHALIB_H

#define BIG_STRING_SIZE 512
#define SMALL_STRING_SIZE 16

typedef struct big_string {
	char buf[BIG_STRING_SIZE]{};
	int length = BIG_STRING_SIZE;
} big_string;

typedef char small_string[SMALL_STRING_SIZE];

#endif //IHATEQT_MISHALIB_H
