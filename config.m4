PHP_ARG_ENABLE([wpcodec_configuration],
  [whether to enable wpcodec_configuration support],
  [AS_HELP_STRING([--enable-wpcodec_configuration],
    [Enable wpcodec_configuration support])],
  [no])

if test "$PHP_WPCODEC_CONFIGURATION" != "no"; then

  AC_DEFINE(HAVE_WPCODEC_CONFIGURATION, 1, [ Have wpcodec_configuration support ])

  PHP_NEW_EXTENSION(wpcodec_configuration,
  configuration.c,
  $ext_shared)
  PHP_ADD_BUILD_DIR([$ext_builddir/plugins])
fi
