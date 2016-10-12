//
//  eval.c
//  Scheme
//
//  Created by Vincent Maladiere on 20/09/16.
//  Copyright © 2016 Vincent Maladiere. All rights reserved.
//

/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

object sfs_eval( object expr ) {
    restart :
    if((expr->type==SFS_NUMBER || expr->type==SFS_STRING || expr->type==SFS_BOOLEAN  || expr->type== SFS_PAIR || expr->type==SFS_CHARACTER)){
        return expr;  /* pas d'eval donc autoevaluant */
    }
    if(is_form("quote",expr)) {
        return expr->this.pair.cdr;
    }
    if(is_form("if",expr)) {
        if(true == eval(cdr(car(expr)))){
            expr = cdr(cdr(car(expr)));
            goto restart;
        }
        else{
            expr = cdr(cdr(cdr(car(expr))));
            goto restart;
        }
    expr = caddr
    }
    
    
    }
}


int is_form (char *name, object expr) {   /* detecter si c'est une forme oui==1, 0 sinon */
    if ((expr->type == SFS_PAIR) && (expr->this.pair.car->type == SFS_SYMBOL) && (0 == strcmp(name, expr->this.pair.car->this.string))){
        return 1;
    }
    else{
        return 0;
    }
}

