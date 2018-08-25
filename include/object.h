

/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif
    
#include "number.h"
    
    
    typedef struct object_t {
        
        uint type;
        
        union {
            
            num              number;
            char             character;
            string           string;
            string           symbol;
            
            struct pair_t {
                struct object_t *car;
                struct object_t *cdr;
            }                pair;
            
            struct object_t *special;
            struct {
                struct object_t * (*fonction)( struct object_t * );
            } primitive;
            
        } this;
        
    } *object;
    
    
    object make_object( uint type );
    object cons( object car, object cdr );
    object make_nil( void );
    
#define SFS_NUMBER       0
#define SFS_CHARACTER    1
#define SFS_STRING       2
#define SFS_PAIR         3
#define SFS_NIL          4
#define SFS_BOOLEAN      5
#define SFS_SYMBOL       6
#define SFS_PRIMITIVE    7
#define SFS_INFINI       8
    
    extern object nil;
    extern object env; /* environnement */
    extern object list_prim;
#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */