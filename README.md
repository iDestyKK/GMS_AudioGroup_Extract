# GameMaker: Studio "audiogroup" extractor

## About
This will extract the file contents from files like "audiogroup1.dat", etc.
It turns out that these are package files that just store the audio files along
with their size.

The number of tracks is found as a 4 byte integer at 0x10.
The first file's size address can be found by reading a 4 byte integer at 0x14.
The file size is stored as a 4 byte integer.
The bytes after that are the contents of the file.
After that, the next size and file is read.
The address of the size must be a multiple of 4.

...It's really that simple.

**Edit (2024/12/06):** [@sparr](https://github.com/sparr) noticed
in [#1](https://github.com/iDestyKK/GMS_AudioGroup_Extract/issues/1) that
all file offsets are stored in the header. This is a more stable way to grab
the file bytes and extract them. So I have updated the tool to do such. Thanks
for that!

## Compilation
This program was written in GNU89 C. Just use the makefile if you have GCC.
Otherwise, good luck.

If you are on Windows, I have provided an EXE in the **Releases** tab. Just for
your convenience.

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

The number of zeros in the filename are determined by the number of tracks in
the file. It will only use as many as necessary.
