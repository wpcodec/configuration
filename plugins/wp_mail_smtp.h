//
// Created by PersiLiao on 2021/3/10.
//

#ifndef PHP_WPCODEC_CONFIGURATION_PLUGIN_WP_MAIL_SMTP_H
#define PHP_WPCODEC_CONFIGURATION_PLUGIN_WP_MAIL_SMTP_H

typedef struct{
    unsigned int on;
    zend_string *from;
    unsigned int from_force;
    zend_string *from_name;
    unsigned int from_name_force;
    zend_string *mailer;
    unsigned int return_path;
    unsigned int do_not_send;
    zend_object std;
} wpcodec_plugin_wp_mail_smtp_object;

#define Z_WPCODEC_PLUGIN_WP_MAIL_SMTP_OBJ(zv)     ((wpcodec_plugin_wp_mail_smtp_object)(Z_OBJ(zv)))
#define Z_WPCODEC_PLUGIN_WP_MAIL_SMTP_OBJ_P(zv)   Z_WPCODEC_PLUGIN_WP_MAIL_SMTP_OBJ(*(zv))

static zend_always_inline wpcodec_plugin_wp_mail_smtp_object *
php_wpcodec_plugin_wp_mail_smtp_fetch_object(zend_object *obj){
    return (wpcodec_plugin_wp_mail_smtp_object *)((char *)(obj) - XtOffsetOf(wpcodec_plugin_wp_mail_smtp_object, std));
}

WPCODEC_CONFIGURATION_STARTUP_FUNCTION(wp_mail_smtp);

#endif
