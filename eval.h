

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

    
    object sfs_eval( object expr, object env );
    int is_form (char *name, object expr);
    object make_lambda(object expr);
    object lambda_a_evaluer(object expr, object env_lambda);
    object lambda_a_evaluer_apres_define(object expr, object env_lambda);
    object conversion_fonction_lambda(object expr);
    object execution_primitive(object expr, object prim_object, object env);
    
#ifdef __cplusplus
}
#endif
