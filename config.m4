dnl $Id$
dnl config.m4 for extension bundle

PHP_ARG_ENABLE(bundle, whether to enable bundle support,
[  --enable-bundle           Enable bundle support])

if test "$PHP_BUNDLE" != "no"; then
  PHP_NEW_EXTENSION(bundle, bundle.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  PHP_DIR="php"
  PHP_LIB="user"
  PHP_SUBST(PHP_DIR)
  PHP_SUBST(PHP_LIB)
  PHP_ADD_LIBRARY_WITH_PATH($PHP_LIB, $PHP_DIR, BUNDLE_SHARED_LIBADD)
  PHP_SUBST(BUNDLE_SHARED_LIBADD)
  PHP_ADD_MAKEFILE_FRAGMENT
fi
