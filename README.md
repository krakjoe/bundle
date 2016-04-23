# bundle
*An experimental method of bundling PHP code with extensions*

This is WIP ... I have no idea how this will work on windows ...

Use:

 - Open config.m4
  - change ```PHP_DIR``` to relative path to dir with code
  - change ```PHP_LIB``` to the name of your user code library
 - Put php files in ```PHP_DIR```
 - #include {$PHP_DIR}/{$PHP_LIB}.h in your extension
 - call php_{$PHP_LIB}_init(HashTable *ht);
 - The HashTable passed to init has all the scripts by name, with relative path

yolo, and goodnight ...
 
