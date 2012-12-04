/* gtkmain.c
 *
 * $Id$
 *
 * Copyright 1990, 1991, 1992, 1993, 1994, 1995, Oliver Laumann, Berlin
 * Copyright 2002, 2003 Sam Hocevar <sam@hocevar.net>, Paris
 *
 * This software was derived from Elk 1.2, which was Copyright 1987, 1988,
 * 1989, Nixdorf Computer AG and TELES GmbH, Berlin (Elk 1.2 has been written
 * by Oliver Laumann for TELES Telematic Services, Berlin, in a joint project
 * between TELES and Nixdorf Microprocessor Engineering, Berlin).
 *
 * Oliver Laumann, TELES GmbH, Nixdorf Computer AG and Sam Hocevar, as co-
 * owners or individual owners of copyright in this software, grant to any
 * person or company a worldwide, royalty free, license to
 *
 *    i) copy this software,
 *   ii) prepare derivative works based on this software,
 *  iii) distribute copies of this software or derivative works,
 *   iv) perform this software, or
 *    v) display this software,
 *
 * provided that this notice is not removed and that neither Oliver Laumann
 * nor Teles nor Nixdorf are deemed to have made any representations as to
 * the suitability of this software for any purpose nor are held responsible
 * for any defects of this software.
 *
 * THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

#include "gtk.h"
#include "intern.h"

static Object P_Gtk_Init (Object args) {
    int argc;
    char **argv;
    int i;

    Check_List (args);
    argc = Fast_Length (args) + 1;
    argv = (char **)Safe_Malloc (sizeof (char *) * argc);
    argv[0] = appname ? appname : "elk";
    for (i = 1; i < argc; i++) {
        Object arg = Car (args);
        Check_Type (arg, T_String);
        argv[i] = Get_String (arg);
        args = Cdr (args);
    }
    gtk_init (&argc, &argv);
    free (argv);
    return Void;
}

static Object P_Gtk_Main () {
    gtk_main ();
    return Void;
}

static Object P_Gtk_Main_Quit () {
    gtk_main_quit ();
    return Void;
}

void elk_init_gtk_gtkmain () {
    Define_Primitive (P_Gtk_Init, "gtk-init", 1, 1, EVAL);
    Define_Primitive (P_Gtk_Main, "gtk-main", 0, 0, EVAL);
    Define_Primitive (P_Gtk_Main_Quit, "gtk-main-quit", 0, 0, EVAL);
}
