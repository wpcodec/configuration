/* configuration extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "main/SAPI.h"
#include "Zend/zend_alloc.h"
#include "ext/standard/info.h"
#include "ext/standard/php_string.h"
#include "php_configuration.h"

//#include "plugins/wp_mail_smtp.h"

ZEND_DECLARE_MODULE_GLOBALS(wpcodec_configuration)

static zend_bool wpcodec_configuration_ini_entry_is_true(const zend_string *new_value){
    if(ZSTR_LEN(new_value) == 2 && strcasecmp("on", ZSTR_VAL(new_value)) == 0){
        return 1;
    }else if(ZSTR_LEN(new_value) == 3 && strcasecmp("yes", ZSTR_VAL(new_value)) == 0){
        return 1;
    }else if(ZSTR_LEN(new_value) == 4 && strcasecmp("true", ZSTR_VAL(new_value)) == 0){
        return 1;
    }else{
        return (zend_bool)atoi(ZSTR_VAL(new_value));
    }
}

static zend_bool wpcodec_configuration_is_production(){
    char *environ = WPCODEC_CONFIGURATION_G(environ_name);
    if(strlen(environ) == 10 && strcasecmp("production", environ) == 0){
        return 1;
    }
    return 0;
}

PHP_GINIT_FUNCTION (wpcodec_configuration){
    memset(wpcodec_configuration_globals, 0, sizeof(*wpcodec_configuration_globals));
}

PHP_INI_BEGIN()
                STD_PHP_INI_ENTRY("wpcodec.environ", "production", PHP_INI_SYSTEM, OnUpdateString, environ_name,
                zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY
                ("wpcodec.plugin.wp_mail_smtp.on", "1", PHP_INI_SYSTEM, OnUpdateBool, plugin_wp_mail_smtp_on,
                        zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.from", "wpcodec", PHP_INI_SYSTEM, OnUpdateString,
                        plugin_wp_mail_smtp_from, zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.host", "wpcodec", PHP_INI_SYSTEM, OnUpdateString,
                        plugin_wp_mail_smtp_host, zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.user", "wpcodec", PHP_INI_SYSTEM, OnUpdateString,
                        plugin_wp_mail_smtp_user, zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.password", "wpcodec", PHP_INI_SYSTEM, OnUpdateString,
                        plugin_wp_mail_smtp_password, zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.from_force", "1", PHP_INI_SYSTEM, OnUpdateBool,
                        plugin_wp_mail_smtp_from_force, zend_wpcodec_configuration_globals,
                        wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.from_name", "WpCodeC", PHP_INI_SYSTEM, OnUpdateString,
                        plugin_wp_mail_smtp_from_name, zend_wpcodec_configuration_globals,
                        wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.from_name_force", "1", PHP_INI_SYSTEM, OnUpdateBool,
                        plugin_wp_mail_smtp_from_name_force, zend_wpcodec_configuration_globals,
                        wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.mailer", "smtp", PHP_INI_SYSTEM, OnUpdateString,
                        plugin_wp_mail_smtp_mailer, zend_wpcodec_configuration_globals, wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.return_path", "1", PHP_INI_SYSTEM, OnUpdateBool,
                        plugin_wp_mail_smtp_return_path, zend_wpcodec_configuration_globals,
                        wpcodec_configuration_globals)
                STD_PHP_INI_ENTRY("wpcodec.plugin.wp_mail_smtp.do_not_send", "1", PHP_INI_SYSTEM, OnUpdateBool,
                        plugin_wp_mail_smtp_do_not_send, zend_wpcodec_configuration_globals,
                        wpcodec_configuration_globals)
PHP_INI_END()

PHP_MINIT_FUNCTION (wpcodec_configuration){

    REGISTER_INI_ENTRIES();

    REGISTER_STRINGL_CONSTANT("WP_ENVIRONMENT_TYPE", WPCODEC_CONFIGURATION_G(environ_name), strlen(WPCODEC_CONFIGURATION_G(environ_name)), CONST_PERSISTENT | CONST_CS);
    if(wpcodec_configuration_is_production()){
        REGISTER_BOOL_CONSTANT("WP_DISABLE_FATAL_ERROR_HANDLER", 1, CONST_PERSISTENT | CONST_CS);
        REGISTER_BOOL_CONSTANT("WP_DEBUG_DISPLAY", 0, CONST_PERSISTENT | CONST_CS);
        REGISTER_BOOL_CONSTANT("WP_DEBUG", 0, CONST_PERSISTENT | CONST_CS);
        REGISTER_BOOL_CONSTANT("SAVEQUERIES", 0, CONST_PERSISTENT | CONST_CS);
        REGISTER_BOOL_CONSTANT("DISALLOW_FILE_EDIT", 1, CONST_PERSISTENT | CONST_CS);
        REGISTER_BOOL_CONSTANT("DISALLOW_FILE_MODS", 1, CONST_PERSISTENT | CONST_CS);
    }

    REGISTER_BOOL_CONSTANT("WPMS_ON", 1, CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("WPMS_MAILER", WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_mailer), strlen(WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_mailer)), CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("WPMS_SMTP_HOST", WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_host), strlen(WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_host)), CONST_PERSISTENT | CONST_CS);
    REGISTER_LONG_CONSTANT("WPMS_SMTP_PORT", 465, CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("WPMS_SSL", "ssl", strlen("ssl"), CONST_PERSISTENT | CONST_CS);
    REGISTER_BOOL_CONSTANT("WPMS_SMTP_AUTH", 1, CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("WPMS_SMTP_USER", WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_user),
        strlen(WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_user)), CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("WPMS_SMTP_PASS", WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_password),
        strlen(WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp_password)),
            CONST_PERSISTENT | CONST_CS);
    REGISTER_BOOL_CONSTANT("WPMS_SMTP_AUTOTLS", 1, CONST_PERSISTENT | CONST_CS);
    //WPCODEC_CONFIGURATION_STARTUP(wp_mail_smtp);
    return SUCCESS;
}

PHP_MINFO_FUNCTION (wpcodec_configuration){
    php_info_print_table_start();
    php_info_print_table_header(2, "WpCodeC Configuration support", "enabled");
    php_info_print_table_row(2, "Version", PHP_WPCODEC_CONFIGURATION_VERSION);
    php_info_print_table_row(2, "Supports", WPCODEC_CONFIGURATION_SUPPORT_URL);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}

zend_module_entry wpcodec_configuration_module_entry = {
        STANDARD_MODULE_HEADER,
        "wpcodec_configuration",            /* Extension name */
        NULL,                               /* zend_function_entry */
        PHP_MINIT(wpcodec_configuration),   /* PHP_MINIT - Module initialization */
        NULL,                               /* PHP_MSHUTDOWN - Module shutdown */
        NULL,                               /* PHP_RINIT - Request initialization */
        NULL,                               /* PHP_RSHUTDOWN - Request shutdown */
        PHP_MINFO(wpcodec_configuration),   /* PHP_MINFO - Module info */
        PHP_WPCODEC_CONFIGURATION_VERSION,  /* Version */
        PHP_MODULE_GLOBALS(wpcodec_configuration),
        PHP_GINIT(wpcodec_configuration),
        NULL,
        NULL,
        STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_WPCODEC_CONFIGURATION
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wpcodec_configuration)
#endif
