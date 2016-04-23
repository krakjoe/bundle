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
static inline php_user_init(HashTable *ht) {
	zval val;
	ZVAL_NEW_STR(&val, zend_string_init(				php_index_user_php_file_php(), 					php_index_user_php_file_php_size(), 0));
	zend_hash_str_add(ht, "php/file.php", sizeof("php/file.php")-1, &val);
	ZVAL_NEW_STR(&val, zend_string_init(				php_index_user_php_other_php(), 					php_index_user_php_other_php_size(), 0));
	zend_hash_str_add(ht, "php/other.php", sizeof("php/other.php")-1, &val);
}
#endif
