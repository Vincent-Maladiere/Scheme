

/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

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
    
    
    object sfs_eval( object );
    int is_form (char *name, object expr);
    
    
#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */