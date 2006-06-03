/* Copyright (c) 1999, 2000, 2002, 2003, 2004, 2005, 2006 John E. Davis
 * This file is part of JED editor library source.
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */
#include "config.h"
#include "jed-feat.h"

#include <stdio.h>
#include <string.h>
#include <slang.h>

#include "buffer.h"
#include "version.h"

int Jed_Version_Number = JED_VERSION;
char *Jed_Version_String = JED_VERSION_STR;

#ifdef USE_GPM_MOUSE
# define USE_GPM_MOUSE 1
#else
# define USE_GPM_MOUSE 0
#endif

typedef struct 
{
   char *name;
   int value;
}
Compile_Option_Type;

static Compile_Option_Type Compile_Options [] =
{
   {"LINE_ATTRIBUTES",		JED_HAS_LINE_ATTRIBUTES},
   {"BUFFER_LOCAL_VARS",	JED_HAS_BUFFER_LOCAL_VARS},
   {"SAVE_NARROW",		JED_HAS_SAVE_NARROW},
   {"TTY_MENUS",		JED_HAS_TTY_MENUS},
   {"EMACS_LOCKING",		JED_HAS_EMACS_LOCKING},
   {"MULTICLICK",		JED_HAS_MULTICLICK},
   {"SUBPROCESSES",		JED_HAS_SUBPROCESSES},
   {"DFA_SYNTAX",		JED_HAS_DFA_SYNTAX},
   {"ABBREVS",			JED_HAS_ABBREVS},
   {"COLOR_COLUMNS",		JED_HAS_COLOR_COLUMNS},
   {"LINE_MARKS",		JED_HAS_LINE_MARKS},
   {"GPM_MOUSE",		USE_GPM_MOUSE},
   {"IMPORT",			JED_HAS_IMPORT},
   {NULL, 0}
};

static void show_features (FILE *fp)
{
   Compile_Option_Type *opt;
   unsigned int len;

   fprintf (fp, "\njed compile-time options:\n");
   
   opt = Compile_Options;
   len = 0;
   while (opt->name != NULL)
     {
	unsigned int dlen = strlen (opt->name) + 3;

	len += dlen;
	if (len >= 80)
	  {
	     fputc ('\n', fp);
	     len = dlen;
	  }
	fprintf (fp, " %c%s", (opt->value ? '+' : '-'), opt->name);
	opt++;
     }
   fputc ('\n', fp);
}

void jed_show_version (FILE *fp)
{
   char *os;
#ifdef VMS
   os = "VMS";
#else
# ifdef __os2__
   os = "OS/2";
# else
#  ifdef __WIN32__
   os = "win32";
#  else
#   ifdef __MSDOS__
   os = "MSDOS";
#   else
#    ifdef REAL_UNIX_SYSTEM
   os = "Unix";
#    else
   os = "unknown";
#    endif
#   endif
#  endif
# endif
#endif
   
   fprintf (fp, "jed version: %s/%s\n", Jed_Version_String, os);

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
   fprintf (fp, " Compiled with GNU C %d.%d", __GNUC__, __GNUC_MINOR__);
# if defined(__DJGPP) && defined(__DJGPP_MINOR)
   fprintf (fp, " (DJGPP v%d.%d)", __DJGPP, __DJGPP_MINOR);
# endif 
# ifdef __MINGW32__
   fprintf (fp, " (MINGW32 v%g)",
#  ifdef __MINGW32_VERSION
	    __MINGW32_VERSION
#  else
	    __MINGW32__
#  endif
	    );
# endif
   fprintf (fp, "\n");
#endif				       /* __GNUC__ */

   fprintf (fp, "S-Lang version: %s\n", SLang_Version_String);
   if (SLang_Version != SLANG_VERSION)
     fprintf (fp, "*** Compiled against S-Lang %d but linked to %d\n",
			SLANG_VERSION, SLang_Version);
   
   show_features (fp);
}