#ifndef primitive_h
#define primitive_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

object make_primitive(void);
object plus_p (object ArbreAAditionner);
object moins_p (object arbreASoustraire);





#endif /* primitive_h */
