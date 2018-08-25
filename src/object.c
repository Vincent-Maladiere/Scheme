

/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"

object cons( object car, object cdr ) {
    object t = make_object(SFS_PAIR);
    
    t->this.pair.car = car;
    t->this.pair.cdr = cdr;
    
    return t;
}

object make_object( uint type ) {
    
    object t = sfs_malloc( sizeof( *t ) );
    
    t->type = type;
    
    return t;
}

object make_nil( void ) {
    
    object t = make_object( SFS_NIL );
    
    t->this.special = t;
    
    return t;
}

object car( object sexpr ){
    return sexpr->this.pair.car;
}

object cdr( object sexpr ){
    return sexpr->this.pair.cdr;
}
