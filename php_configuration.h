/* wpcodec configuration extension for PHP */

#ifndef PHP_WPCODEC_CONFIGURATION_H
#define PHP_WPCODEC_CONFIGURATION_H

extern zend_module_entry wpcodec_configuration_module_entry;
#define phpext_wpcodec_configuration_ptr &wpcodec_configuration_module_entry

#define PHP_WPCODEC_CONFIGURATION_VERSION "0.1.0"
#define WPCODEC_CONFIGURATION_SUPPORT_URL "https://www.github.com/wpcodec/configuration"

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define WPCODEC_CONFIGURATION_G(v) TSRMG(wpcodec_configuration_globals_id, zend_wpcodec_configuration_globals *, v)
#else
#define WPCODEC_CONFIGURATION_G(v) (wpcodec_configuration_globals.v)
#endif

#define WPCODEC_CONFIGURATION_STARTUP_FUNCTION(plugin) ZEND_MINIT_FUNCTION(wpcodec_configuration_##plugin)
#define WPCODEC_CONFIGURATION_STARTUP(plugin) ZEND_MODULE_STARTUP_N(wpcodec_configuration_##plugin)(INIT_FUNC_ARGS_PASSTHRU)

#define WPCODEC_CONFIGURATION_VAR_FLAGS(v) ((v).u2.next)
#define WPCODEC_CONFIGURATION_FLAGS() (WPCODEC_CONFIGURATION_VAR_FLAGS(WPCODEC_CONFIGURATION_G(app)))

#define WPCODEC_CONFIGURATION_PRODUCTION (1<<0)
#define WPCODEC_CONFIGURATION_DEVELOPMENT (1<<1)
#define WPCODEC_CONFIGURATION_DEBUG (1<<2)

ZEND_BEGIN_MODULE_GLOBALS(wpcodec_configuration)
    zval app;
    char *environ_name;
    char *plugin_wp_mail_smtp_on;
    char *plugin_wp_mail_smtp_host;
    char *plugin_wp_mail_smtp_user;
    char *plugin_wp_mail_smtp_password;
    char *plugin_wp_mail_smtp_from;
    char *plugin_wp_mail_smtp_from_force;
    char *plugin_wp_mail_smtp_from_name;
    char *plugin_wp_mail_smtp_from_name_force;
    char *plugin_wp_mail_smtp_mailer;
    char *plugin_wp_mail_smtp_return_path;
    char *plugin_wp_mail_smtp_do_not_send;
ZEND_END_MODULE_GLOBALS(wpcodec_configuration)

PHP_MINIT_FUNCTION(wpcodec_configuration);

PHP_MINFO_FUNCTION(wpcodec_configuration);

extern ZEND_DECLARE_MODULE_GLOBALS(wpcodec_configuration)

static zend_bool wpcodec_configuration_is_production();

static zend_bool wpcodec_configuration_ini_entry_is_true(const zend_string *new_value);

#if defined(ZTS) && defined(COMPILE_DL_WPCODEC_CONFIGURATION)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif    /* PHP_CONFIGURATION_H */
