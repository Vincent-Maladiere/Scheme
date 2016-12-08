#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif
  
            
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
    
    
#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

    
    object sfs_eval( object expr, object env );
    int is_form (char *name, object expr);
    object make_lambda(object expr);
    
#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
