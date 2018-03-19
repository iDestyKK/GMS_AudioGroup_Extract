# GameMaker: Studio "audiogroup" extractor

## About
Probably never going to touch this code ever again, but this will extract the file contents from files like "audiogroup1.dat", etc. It turns out that these are package files that just store the audio files along with their size.

The first file's size is located at 0x98, and is a 4 byte integer. The bytes after that are the contents of the file. After that, the next size and file is read. The address of the size must be a multiple of 4.

...It's really that simple.

## Compilation
This program was written in GNU89 C. Just use the makefile if you have GCC. Otherwise, good luck.

## Synopsis
```
./extract file
```

It will generate files in the following way:
```
extract000.ogg
extract001.ogg
extract002.ogg
...
```
