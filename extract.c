/*
 * Game Maker Studio Audio Group Extractor
 *
 * Description:
 *     Extracts file from files such as "audiogroup1.dat", etc which merely
 *     are package files that hold files in it.
 *
 *     This was only tested on two "audiogroup1.dat" files. Will improve if
 *     this glitches out on other files.
 *
 * Synopsis:
 *     ./extract file
 *
 * Compilation:
 *     gcc --std=gnu89 -o extract extract.c
 *
 * Author:
 *     Clara Nguyen (@iDestyKK)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void file_extract(char *buf, size_t pos, char *fname) {
	FILE *fp;
	uint32_t p, s;

	p = pos + 4;                 // Offset of file
	s = *(uint32_t *) &buf[pos]; // Size of file

	printf("File at 0x%08x (Size %u)...", p, s);

	// Dump
	fp = fopen(fname, "wb");
	fwrite(&buf[p], sizeof(char), s, fp);
	fclose(fp);

	printf(" Extracted!\n");
}

main(int argc, char** argv) {
	//Check arguments
	if (argc != 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	char   *buf, fname[32];
	FILE   *fp;
	size_t fsz, i, trk_num, ffloc, pos, num_zero, ztmp;

	fp = fopen(argv[1], "rb");

	//Get size of the file
	fseek(fp, 0, SEEK_END);
	fsz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//Read the entire file into a buffer. We'll be doing this all in memory.
	buf = malloc(fsz * sizeof(char));
	fread(buf, sizeof(char), fsz, fp);
	fclose(fp);

	// Track number information
	trk_num = *(int*)&buf[0x10];

	// Number of 0's in file name
	for (ztmp = trk_num, num_zero = 1; ztmp >= 10; ztmp /= 10, num_zero++);

	// Skip to each file and extract
	for (i = 0, pos = 0x14; i < trk_num; i++, pos += 4) {
		sprintf(fname, "extract%0*d.ogg", num_zero, i);

		file_extract(buf, *(uint32_t *) &buf[pos], fname);
	}

	//Have a nice day.
	free(buf);
	exit(0);
}
