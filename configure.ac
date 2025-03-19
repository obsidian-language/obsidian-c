AC_INIT([ObsidianCompiler], [1.0], [https://github.com/obsidian-language/obsidian/issues])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
: ${RELEASE=NO}

AC_PROG_CC

CFLAGS="-std=c99 -O2 -Os -Wall -Wextra -Wshadow -Wundef -Wwrite-strings -Wredundant-decls -Wdisabled-optimization -Wdouble-promotion -Wmissing-declarations -Wconversion -Wstrict-overflow=2 -Wfatal-errors -fno-builtin-memcpy -pedantic -fstack-protector-all"
LDFLAGS="-flto -fPIC"

case `$CC --version` in
  *"clang"*)
    CFLAGS="$CFLAGS"
    ;;
  *"gcc"*)
    CFLAGS="$CFLAGS -Wduplicated-cond -Wduplicated-branches"
    ;;
esac

AC_SUBST([CFLAGS])

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
