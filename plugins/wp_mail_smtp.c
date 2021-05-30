//
// Created by PersiLiao on 2021/3/10.
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_configuration.h"
#include "wp_mail_smtp.h"

PHP_INI_MH (OnUpdateWpMailSmtpOn){
    if(wpcodec_configuration_ini_entry_is_true(new_value)){
        WPCODEC_CONFIGURATION_VAR_FLAGS(WPCODEC_CONFIGURATION_G(plugin_wp_mail_smtp));
    }
    return SUCCESS;
}

WPCODEC_CONFIGURATION_STARTUP_FUNCTION(wp_mail_smtp){

}