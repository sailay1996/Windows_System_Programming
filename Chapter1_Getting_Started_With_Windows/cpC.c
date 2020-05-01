/* Chapter 1. Basic cp file copy program. C library Implementation. */
/* cpC file1 file2: Copy file1 to file2. */

#include <stdio.h>
#include <errno.h>
#define BUF_SIZE 256

int main(int argc, char const *argv[])
{
	FILE *inFile, *outFile;
	char rec[BUF_SIZE];
	size_t bytesIn, bytesOut;
	if (argc != 3) {
		fprintf (stderr, "Usage: cp file1 file2\n");
		return 1;
	}	
	inFile = fopen (argv[1], "rb");  /* Open for reading in binary mode .*/
	if (inFile == NULL) {
		perror (argv[1]);
		return 2;
	}
	outFile = fopen (argv[2], "wb");  /* Open for writing in binary mode. */
	if (outFile == NULL) {
		perror (argv[2]);
		fclose(inFile);
		return 3;
	}
	/* Process the input file a record at a time */
	while	((bytesIn = fread (rec, 1, BUF_SIZE, inFile))	> 0) {
		bytesOut = fwrite (rec, 1, bytesIn, outFile);
		if (bytesOut != bytesIn)
		{
			perror ("Fatal Write error.");
			fclose(inFile); fclose(outFile);
			return 4;
		}
	}
	fclose (inFile);
	fclose (outFile);
	return 0;
}
