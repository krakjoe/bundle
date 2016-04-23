# bundle
*An experimental method of bundling PHP code with extensions*

This is WIP ... I have no idea how this will work on windows ...

Use:

 - Open config.m4
  - change ```PHP_DIR``` to relative path to dir with code
  - change ```PHP_LIB``` to the name of your user code library
 - Put php files in ```PHP_DIR```
 - #include {$PHP_DIR}/{$PHP_LIB}.h in your extension

API:

  ```static inline void php_{$PHP_LIB}_init(HashTable *index, HashTable *includes);```

	Shall accept two uninitialized HashTables, and create index of code

  ```static inline void php_{$PHP_LIB}_include(HashTable *index, HashTable *includes, char *path, size_t len, zval *rv);```

	Shall find path in index table, and eval the code if it was not already included

  ```static inline void php_{$PHP_LIB}_shutdown(HashTable *index, HashTable *includes);```

	Shall release resources used by index and include table

yolo, and goodnight ...
 
