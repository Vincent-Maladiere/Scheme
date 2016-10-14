

#include "eval.h"

object sfs_eval( object expr ) {
    
    restart :
    
    if((expr->type==SFS_NUMBER || expr->type==SFS_STRING || expr->type==SFS_BOOLEAN  || expr->type== SFS_PAIR|| expr->type==SFS_CHARACTER)){
        return expr; * /* pas d'eval donc autoevaluant */
    }
    if(is_form("quote",expr) == 0) {
        return expr->this.pair.cdr;
    }
    if(is_form("if",expr) == 0) {
        if(sfs_eval(cdr(car(expr))) == TRUE){
            expr = cdr(cdr(car(expr)));
            goto restart;
        }
        else{
            expr = cdr(cdr(cdr(car(expr))));
            goto restart;
        }
    }
    if(is_form("define", expr) == 0){
        
    }
    if(is_form("set!", expr) == 0){
        
    }
    if(is_form("or", expr) == 0){
        
    }
    if(is_form("and", expr) == 0){
        
    }
}


 int is_form (char *name, object expr) { /* detecter si c'est une forme oui==1, 0 sinon */
    if ((expr->type == SFS_PAIR) && (expr->this.pair.car->type == SFS_SYMBOL) && (0 == strcmp(name, expr->this.pair.car->this.string))){
        return 1;
    }
    else{
        return 0;
    }
}
