

/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "primitive.h"
#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

object sfs_eval( object expr ) {
    char str1[256] = {'n','e','w','l','i','n','e'};
    char str2[256] = {'s','p','a','c','e'};
    char str3[256] = {'+','i','n','f'};
    char str4[256] = {'-','i','n','f'};
    
    restart :
    
    if((expr->type==SFS_NUMBER || expr->type == SFS_INFINI || expr->type == SFS_NIL || expr->type==SFS_STRING || expr->type==SFS_BOOLEAN  || expr->type==SFS_CHARACTER || (strcmp(expr->this.symbol,str3) == 0) || (strcmp(expr->this.symbol,str4) == 0))){
        return expr;  /* pas d'eval puisqu'autoevaluant */
    }
    if(expr->type == SFS_SYMBOL){
        object prim_safe = list_prim->this.pair.cdr; /* attention 'cdr' et pas 'car' pour list_prim, contrairement à env */
        while(prim_safe->this.pair.car != NULL){
            if(strcmp(prim_safe->this.pair.car->this.pair.car->this.symbol, expr->this.symbol) == 0){
                object result = make_object(SFS_SYMBOL);
                strcpy(result->this.symbol,expr->this.symbol);
                return result;
            }
            prim_safe = prim_safe->this.pair.cdr;
        }
        object cherchemaggle = make_object(SFS_PAIR);
        cherchemaggle = env->this.pair.car;
        if(cherchemaggle == NULL){
            ERROR_MSG("\n\nUndefined parameter\n");
        }
        while(strcmp(cherchemaggle->this.pair.car->this.pair.car->this.symbol, expr->this.symbol) != 0){ /* PB MAGGLE */
            cherchemaggle = cherchemaggle->this.pair.cdr;
            if(cherchemaggle == NULL){
                ERROR_MSG("\n\nUndefined parameter\n");
            }

        }
        object result = make_object(cherchemaggle->this.pair.car->this.pair.cdr->type);
        if(SFS_NUMBER == cherchemaggle->this.pair.car->this.pair.cdr->type){
            result->this.number.this.integer = cherchemaggle->this.pair.car->this.pair.cdr->this.number.this.integer;
            return result;
        }
        if(SFS_STRING == cherchemaggle->this.pair.car->this.pair.cdr->type){
            strcpy(result->this.string, cherchemaggle->this.pair.car->this.pair.cdr->this.string);
            return result;
        }
        if(SFS_CHARACTER == cherchemaggle->this.pair.car->this.pair.cdr->type){
            
            if((strcmp(cherchemaggle->this.pair.car->this.pair.cdr->this.symbol,str1))||(strcmp(cherchemaggle->this.pair.car->this.pair.cdr->this.symbol,str2))){
                strcpy(result->this.symbol,cherchemaggle->this.pair.car->this.pair.cdr->this.symbol);
            }
            else{
                result->this.character = cherchemaggle->this.pair.car->this.pair.cdr->this.character;
            }
            return result;
        }
        if(SFS_BOOLEAN == cherchemaggle->this.pair.car->this.pair.cdr->type){
            result->this.number.this.integer = cherchemaggle->this.pair.car->this.pair.cdr->this.number.this.integer;
            return result;
        }
    }
    if(is_form("quote",expr) == 1) {
        return expr->this.pair.cdr->this.pair.car;
    }
    if(is_form("if",expr) == 1) {
        if(sfs_eval(expr->this.pair.cdr->this.pair.car)->this.number.this.integer == 1){
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
        else{
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
    }
    if(is_form("define", expr) == 1){
        if(expr->this.pair.cdr->this.pair.car->type == SFS_SYMBOL){
            object safe_env = make_object(SFS_PAIR);
            safe_env->this.pair.car = cons(expr->this.pair.cdr->this.pair.car, sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car));
            safe_env->this.pair.cdr = env->this.pair.car;
            env->this.pair.car = safe_env;
            expr = expr->this.pair.cdr->this.pair.car; /* Permet d'afficher la variable définie avec sfs_print */
            return expr;
        }
        else{
            ERROR_MSG("\n\nDefine impossible\n");
        }
    }
    if(is_form("set!", expr) == 1){
        object safe_env = make_object(SFS_PAIR);
        safe_env = env->this.pair.car; /* On ne perd pas la tête de liste ! On envoit une copie */
        if(safe_env == NULL){
            ERROR_MSG("\n\nYou can't set an undefined parameter\n");
        }
        while(strcmp(safe_env->this.pair.car->this.pair.car->this.symbol, expr->this.pair.cdr->this.pair.car->this.symbol) != 0){
            safe_env = safe_env->this.pair.cdr;
            if(safe_env == NULL){
                ERROR_MSG("\n\nYou can't set an undefined parameter\n");
            }
        }

        safe_env->this.pair.car->this.pair.cdr = sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car);
        expr = expr->this.pair.cdr->this.pair.car;
        return expr;
    }
    
    if(is_form("or", expr) == 1){
        if((sfs_eval(expr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0)&&(sfs_eval(expr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01')){
            if((sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0) && (sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01')) {
                expr->type = SFS_BOOLEAN;
                expr->this.number.this.integer = 0;
                return expr;
            }
            else{
                expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
                goto restart;
            }
        }
        else{
            expr = expr->this.pair.cdr->this.pair.car;
            goto restart;
        }
    }
    
    if(is_form("and", expr) == 1){
        if(((sfs_eval(expr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0) &&(sfs_eval(expr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01')) || ((sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0) && (sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01'))) {
            expr->type = SFS_BOOLEAN;
            expr->this.number.this.integer = 0;
            return expr;
        }
        else {
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
    }
    
    if(is_form("begin", expr) == 1){
        object resultat = NULL;
        expr = expr->this.pair.cdr;
        while (expr->type != SFS_NIL){
            resultat =  sfs_eval(expr->this.pair.car);
            expr = expr->this.pair.cdr;
        }
        return resultat;
    }

  
    
    
    
    else{
        object prim_safe = list_prim->this.pair.cdr;
        object env_safe = env->this.pair.car;
        while(env_safe != NULL){
            if(is_form(env_safe->this.pair.car->this.pair.car->this.symbol,expr) == 1){
                strcpy(expr->this.pair.car->this.symbol,env_safe->this.pair.car->this.pair.cdr->this.symbol);
            }
            env_safe = env_safe->this.pair.cdr;
        }
        while(prim_safe->this.pair.car != NULL){
            if(is_form(prim_safe->this.pair.car->this.pair.car->this.symbol, expr) == 1){
                object ArbreAEvaluer = make_object(SFS_PAIR);
                object ArbreAEvaluer_safe = ArbreAEvaluer;
                object expr_safe = expr->this.pair.cdr;
                while(expr_safe != nil){
                    ArbreAEvaluer_safe->this.pair.car = ((is_form("symbol?",expr))||(is_form("symbol->string",expr))||(is_form("pair?",expr))) ? expr_safe->this.pair.car : sfs_eval(expr_safe->this.pair.car);
                    expr_safe = expr_safe->this.pair.cdr;
                    ArbreAEvaluer_safe->this.pair.cdr = make_object(SFS_PAIR);
                    ArbreAEvaluer_safe = ArbreAEvaluer_safe->this.pair.cdr;
                }
                object objetPrimitive = prim_safe->this.pair.car->this.pair.cdr;
                object resultat = objetPrimitive->this.primitive.fonction(ArbreAEvaluer);
                return resultat;
            }
            prim_safe = prim_safe->this.pair.cdr;
        }
        ERROR_MSG("\n\nJe crains que cette fonction n'existe point \n");
    }
    
    return expr;
}

/* object cdr(object o) {
    if(o->type != PAIR) {
        ERROR_MSG("erreur grave pas de cdr");
    }
    return o->this.pair.cdr;
}

object cddr(object o) {
    return cdr(cdr(o));
}

*/


 int is_form (char *name, object expr) {  /* detecter si c'est une forme oui==1, 0 sinon */
     if ((expr->type == SFS_PAIR) && (expr->this.pair.car->type == SFS_SYMBOL) && (0 == strcmp(name, expr->this.pair.car->this.string))){
        return 1;
    }
    else{
        return 0;
    }
}

