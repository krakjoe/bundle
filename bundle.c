/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bundle.h"
#include "php/user.h"

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bundle)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(bundle)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(bundle)
{
	HashTable tmp;
	zval *found;

#if defined(COMPILE_DL_BUNDLE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	
	zend_hash_init(&tmp, 8, NULL, ZVAL_PTR_DTOR, 0);

	/* this is generated, just builds hashtable of code, no compile yet */
	php_user_init(&tmp);

	/* you have your embedded code ... */
	if ((found = zend_hash_str_find(&tmp, ZEND_STRL("php/file.php")))) {
		php_var_dump(found, 0);
	}

	/* remember to cleanup */
	zend_hash_destroy(&tmp);
	
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(bundle)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(bundle)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bundle support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ bundle_functions[]
 *
 * Every user visible function must have an entry in bundle_functions[].
 */
const zend_function_entry bundle_functions[] = {
	PHP_FE_END	/* Must be the last line in bundle_functions[] */
};
/* }}} */

/* {{{ bundle_module_entry
 */
zend_module_entry bundle_module_entry = {
	STANDARD_MODULE_HEADER,
	"bundle",
	bundle_functions,
	PHP_MINIT(bundle),
	PHP_MSHUTDOWN(bundle),
	PHP_RINIT(bundle),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(bundle),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(bundle),
	PHP_BUNDLE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BUNDLE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(bundle)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
