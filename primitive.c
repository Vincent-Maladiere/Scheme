object plus (object A, object B)
// si le type de A et B sont bien des integer, on puet les aditionner, sinon: erreur
{
    if ((A->this->type == SFS_NUMBER) || (B->type->type == SFS_NUMBER)) {
        object res = make_object(0);
        res= (A->this.number.this.integer) + (B->this.number.this.integer);
        return res;
        }
    else {
    return ERROR_MSG("\n plus impossible\n"); }
}

