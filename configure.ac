AC_INIT([ObsidianCompiler], [1.0], [https://github.com/obsidian-language/obsidian/issues])
AC_CONFIG_MACRO_DIRS([m4])
: ${RELEASE=NO}

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC

CFLAGS="-std=c99 -O2 -Wall -Wextra -Wshadow -Wundef -Wwrite-strings -Wredundant-decls -Wdisabled-optimization -Wdouble-promotion -Wmissing-declarations -Wconversion -Wstrict-overflow=2 -Wfatal-errors"
AC_SUBST([CFLAGS])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
