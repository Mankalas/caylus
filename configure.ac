# Initialize Autoconf. Specify package's name, version number, and
# bug-report address.
AC_INIT([caylus_ia], [0.1], [mankalas@gmail.com,crucugny@gmail.com])

# Check for a C++ compiler.
AC_PROG_CXX

# Declare config.h as output header.
AC_CONFIG_HEADERS([config.h])

# Auxiliary scripts such as install-sh and depcomp should be in
# build-aux
AC_CONFIG_AUX_DIR([build-aux])

# Initialize Automake. Turn on all Automake warnings and report them
# as errors.
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# A safety check. FILE should be a distributed source file, and this
# makes sure that 'configure' is not run from outer space. E.g.
AC_CONFIG_SRCDIR([src/main.cc])

# Auxiliary scripts such as install-sh and depcomp should be in
# DIRECTORY. E.g. AC CONFIG AUX DIR([build-aux]).
AC_CONFIG_FILES([Makefile src/Makefile])

# Check whether SFML libraries exist and contain trivial functions.
AC_CHECK_LIB([sfml-graphics], [GetValidTextureSize], [sfml-graphics=-lsfml-graphics])

#AC_CHECK_LIB([SDL], [SDL_Init], [SDLLIB=-lSDL])
#AC_CHECK_LIB([SDL_image], [IMG_Load], [SDL_IMAGELIB=-lSDL_image])
# Check for headers and #define HAVE_HEADER_H for each header found.
AC_CHECK_HEADERS([string iostream])

#AC_SUBST([sfml-graphics])
#AC_SUBST([SDLLIB])
#AC_SUBST([SDL_IMAGELIB])

# Actually output all declared files.
AC_OUTPUT
