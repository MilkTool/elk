#include "kernel.h"

Object V_Autoload_Notifyp;

void Init_Auto (void) {
    Define_Variable (&V_Autoload_Notifyp, "autoload-notify?", False);
}

Object P_Autoload (Object sym, Object files) {
    Object al, ret;
    GC_Node3;

    al = Null;
    Check_Type (sym, T_Symbol);
    Check_Loadarg (files);
    GC_Link3 (al, sym, files);
    al = Alloc_Object (sizeof (struct S_Autoload), T_Autoload, 0);
    AUTOLOAD(al)->files = files;
    AUTOLOAD(al)->env = The_Environment;
    al = Cons (al, Null);
    al = Cons (sym, al);
    ret = P_Define (al);
    GC_Unlink;
    return ret;
}

Object Do_Autoload (Object sym, Object al) {
    Object val, a[1];
    GC_Node;

    if (Var_Is_True (V_Autoload_Notifyp)) {
	a[0] = AUTOLOAD(al)->files;
	Format (Standard_Output_Port, "[Autoloading ~a]~%", 18, 1, a);
    }
    GC_Link (sym);
    (void)General_Load (AUTOLOAD(al)->files, AUTOLOAD(al)->env);
    GC_Unlink;
    val = SYMBOL(sym)->value;
    if (TYPE(val) == T_Autoload)
	Primitive_Error ("autoloading failed to define ~s", sym);
    return val;
}
