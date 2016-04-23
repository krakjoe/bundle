#ifndef HAVE_PHP_user_H
#define HAVE_PHP_user_H
/* I AM GENERATED | DO NOT EDIT | I AM GENERATED */
extern char _binary_php_file_php_start;
static inline char* php_index_user_php_file_php() {
	return (char*) &_binary_php_file_php_start;
}
extern char _binary_php_file_php_end;
static inline char* php_index_user_php_file_php_end() {
	return (char*) &_binary_php_file_php_end;
}
static inline size_t php_index_user_php_file_php_size() {
	return (size_t) (php_index_user_php_file_php_end() - php_index_user_php_file_php());
}
extern char _binary_php_other_php_start;
static inline char* php_index_user_php_other_php() {
	return (char*) &_binary_php_other_php_start;
}
extern char _binary_php_other_php_end;
static inline char* php_index_user_php_other_php_end() {
	return (char*) &_binary_php_other_php_end;
}
static inline size_t php_index_user_php_other_php_size() {
	return (size_t) (php_index_user_php_other_php_end() - php_index_user_php_other_php());
}
static inline php_user_init(HashTable *index, HashTable *includes) {
	zval val;
	zend_hash_init(index, 8, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_init(includes, 8, NULL, NULL, 0);
	ZVAL_NEW_STR(&val, zend_string_init(				php_index_user_php_file_php(), 					php_index_user_php_file_php_size(), 0));
	zend_hash_str_add(index, "php/file.php", sizeof("php/file.php")-1, &val);
	ZVAL_NEW_STR(&val, zend_string_init(				php_index_user_php_other_php(), 					php_index_user_php_other_php_size(), 0));
	zend_hash_str_add(index, "php/other.php", sizeof("php/other.php")-1, &val);
}
static inline void php_user_include(HashTable *index, HashTable *includes, 				char *path, size_t len, zval *retval) {
	zend_string *key = zend_string_init(path, len, 0);
	zval *code = zend_hash_find(index, key);
	if (code && !zend_hash_exists(includes, key)) {
		zend_string *prepared = zend_string_alloc(Z_STRLEN_P(code) + (sizeof(";")-1), 0);

		memcpy(&ZSTR_VAL(prepared)[0], ";", sizeof(";")-1);
		if (Z_STRLEN_P(code) > (sizeof("<?php") -1) && 
			memcmp(Z_STRVAL_P(code), "<?php", sizeof("<?php")-1) == SUCCESS) {
				memcpy(&ZSTR_VAL(prepared)[1], &Z_STRVAL_P(code)[5], 						Z_STRLEN_P(code) - (sizeof("<?php") - 1));
				ZSTR_LEN(prepared) -= (sizeof("<?php") - 1);
				ZSTR_VAL(prepared)[ZSTR_LEN(prepared)] = 0;
		} else {
			memcpy(&ZSTR_VAL(prepared)[1], Z_STRVAL_P(code), Z_STRLEN_P(code));
		}
		zend_eval_stringl(ZSTR_VAL(prepared), ZSTR_LEN(prepared), retval, path);
		zend_hash_add_empty_element(includes, key);
		zend_string_release(prepared);
	}
	zend_string_release(key);
}
static inline void php_user_shutdown(HashTable *index, HashTable *includes) {
	zend_hash_destroy(index);
	zend_hash_destroy(includes);
}
#endif
