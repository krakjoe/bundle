all: link-php-objects index-php-objects $(all_targets)
	@echo
	@echo "Build complete."
	@echo "Don't forget to run 'make test'."
	@echo

generate-php-objects:
	@echo "Generating PHP objects in $(PHP_DIR)"
	@for f in `ls $(PHP_DIR)/*.php`; do \
		objcopy --input binary --output elf64-x86-64 --binary-architecture i386 $$f $$f.o; \
	done;

link-php-objects: generate-php-objects
	@echo "Linking PHP objects in $(PHP_DIR)"
	@for f in `ls $(PHP_DIR)/*.php`; do \
		ar rcs $(PHP_DIR)/lib$(PHP_LIB).a $$f.o; \
	done;

index-php-objects: link-php-objects
	@echo "Indexing PHP objects in $(PHP_DIR)"
	@echo "#ifndef HAVE_PHP_$(PHP_LIB)_H" 																	> $(PHP_DIR)/$(PHP_LIB).h
	@echo "#define HAVE_PHP_$(PHP_LIB)_H" 																	>> $(PHP_DIR)/$(PHP_LIB).h
	@echo "/* I AM GENERATED | DO NOT EDIT | I AM GENERATED */"												>> $(PHP_DIR)/$(PHP_LIB).h
	@for f in `ls $(PHP_DIR)/*.php`; do \
		name=`echo $$f | sed 's/[^a-z]/_/g'`; \
		echo "extern char _binary_"$$name"_start;" 															>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "static inline char* php_index_$(PHP_LIB)_"$$name"() {" 										>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "	return (char*) &_binary_"$$name"_start;"													>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "}"																							>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "extern char _binary_"$$name"_end;" 															>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "static inline char* php_index_$(PHP_LIB)_"$$name"_end() {" 									>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "	return (char*) &_binary_"$$name"_end;"														>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "}"																							>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "static inline size_t php_index_$(PHP_LIB)_"$$name"_size() {" 									>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "	return (size_t) (php_index_$(PHP_LIB)_"$$name"_end() - php_index_$(PHP_LIB)_"$$name"());"	>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "}"																							>> $(PHP_DIR)/$(PHP_LIB).h; \
	done;
	@echo "static inline php_$(PHP_LIB)_init(HashTable *ht) {"												>> $(PHP_DIR)/$(PHP_LIB).h
	@echo "	zval val;"																						>> $(PHP_DIR)/$(PHP_LIB).h
	@for f in `ls $(PHP_DIR)/*.php`; do \
		name=`echo $$f | sed 's/[^a-z]/_/g'`; \
		echo "	ZVAL_NEW_STR(&val, zend_string_init(\
					php_index_$(PHP_LIB)_"$$name"(), \
						php_index_$(PHP_LIB)_"$$name"_size(), 0));"											>> $(PHP_DIR)/$(PHP_LIB).h; \
		echo "	zend_hash_str_add(ht, \""$$f"\", sizeof(\""$$f"\")-1, &val);"								>> $(PHP_DIR)/$(PHP_LIB).h; \
	done;
	@echo "}"																								>> $(PHP_DIR)/$(PHP_LIB).h
	@echo "#endif"																							>> $(PHP_DIR)/$(PHP_LIB).h
