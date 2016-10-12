//
//  print.c
//  Scheme
//
//  Created by Vincent Maladiere on 05/10/16.
//  Copyright © 2016 Vincent Maladiere. All rights reserved.
//

#include <stdio.h>
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
        (o->this.number.this.integer == 0) ? printf("#f") : printf("#t");
    }
    
    return;
}

void sfs_print_pair_save( object o ) {
    if(o->this.pair.car->type == SFS_PAIR){
        printf("(");
        sfs_print(o->this.pair.car);
    }
    else{
        sfs_print(o->this.pair.car);
        if(o->this.pair.cdr != nil){ /*si ce n'est pas le dernière atome, espace entre les atomes*/
            printf(" ");
        }
        if(o->this.pair.cdr == nil){
            printf(")");
        }
        else{
            sfs_print(o->this.pair.cdr);
        }
        
    }
    return;
}


void sfs_print_pair_save_old( object o ) {
    
    if (o) {
        printf("(");
        sfs_print(o->this.pair.car);
        printf(" ");
        sfs_print_pair(o->this.pair.cdr);
        printf(")");
    }
    else WARNING_MSG("On ne devrait pas etre la");
    return;
}


void sfs_print_pair( object o ) {

    printf("(");
    while(o != nil)
    {
        sfs_print(o->this.pair.car);
        o = o->this.pair.cdr;
        if(o != nil){
            printf(" ");
        }
    }
    printf(")");
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
