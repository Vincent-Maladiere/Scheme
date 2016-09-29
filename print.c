
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
    if(o->type == SFS_NUMBER){
        printf("%d",o->this.number.this.integer); /* En supposant que les nombres soient tous entier*/
    }
    if(o->type == SFS_STRING){
        printf("%s",o->this.string);
    }
    if(o->type == SFS_CHARACTER){
        printf("%c",o->this.character);
    }
    if(o->type == SFS_SYMBOL){
        printf("%s",o->this.symbol);
    }
    if(o->type == SFS_BOOLEAN){
        (o->this.number.this.integer == 1) ? puts("#t") : puts("#f");
    }
    return;
}

void sfs_print_pair( object o ) {
    if(o->this.pair.car->type == SFS_PAIR){
        puts("(");
        sfs_print(o->this.pair.car);
    }
    sfs_print(o->this.pair.car);
    sfs_print(o->this.pair.cdr);
    if(o->this.pair.cdr == nil){
        puts(")");
    }
    return;
}

void sfs_print( object o ) {
    
    if ( SFS_PAIR == o->type ) {
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
    }
    
}
