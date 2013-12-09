/*
 *  Copyright (c) 2013 Danny Wood <danwood76@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  libhashab.so that is generated from this file does NOT actually do
 *  any hash computation it merely accesses the libhashab32_wrapper to
 *  allow loading of the 32-bit libhashab.so transparently
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

int calcHashAB(unsigned char HashAB[57], unsigned char Sha1[20], unsigned char UUID[20], unsigned char Random[23]) {
    void *lib_handle;
    char *error;
    unsigned char a, i;
    FILE *fp;

    char CmdLine[256];
    char HashOutput[256];
    unsigned char TempVar[3];

    /* Clear our memmory down */
    memset(HashAB, 0, 57);

    /* The command header */
    sprintf(CmdLine, "linux32 /usr/lib/x86_64-linux-gnu/libgpod/libhashab32_wrapper \"");

    /* Print the Sha1 Data */
    for(a = 0; a < 20; a++) {
        sprintf(CmdLine, "%s%02X", CmdLine, Sha1[a]);
    }

    /* Print a gap between the CMD line */
    sprintf(CmdLine, "%s\" \"", CmdLine);

    /* Print the UUID */
    for(a = 0; a < 20; a++) {
        sprintf(CmdLine, "%s%02X", CmdLine, UUID[a]);
    }

    /* Print a gap between the CMD line */
    sprintf(CmdLine, "%s\" \"", CmdLine);

    /* Print the UUID */
    for(a = 0; a < 23; a++) {
        sprintf(CmdLine, "%s%02X", CmdLine, Random[a]);
    }

    /* Finish the command line */
    sprintf(CmdLine, "%s\"", CmdLine);

    /* Open the command for reading */
    fp = popen(CmdLine, "r");

    /* Clear the input char counter to 0 */
    i = 0;

    /* Read in the hash from the stdout */
    do {
        HashOutput[i++] = fgetc(fp);
    } /* While the output is not EOF */
    while(HashOutput[i-1] != -1);

    /* For all chars read in */
    for(a = 0; a < (i-1); a+=2) {
        /* Store the hex values in the temp variable */
        TempVar[0] = HashOutput[a];
        TempVar[1] = HashOutput[a+1];
        TempVar[2] = 0;

        /* Convert the hex value to the HashAB byte */
        HashAB[a/2] = strtoul(TempVar, NULL, 16);
    }

    /* Return success */
    return 0;
}

void get_random_bytes_from_hashAB(unsigned char *Hash, unsigned char *RandomBytes) {
    /* Copy bytes accross from their various offsets */
    RandomBytes[0]  = Hash[23];
    RandomBytes[1]  = Hash[13];
    RandomBytes[2]  = Hash[29];
    RandomBytes[3]  = Hash[12];
    RandomBytes[4]  = Hash[37];
    RandomBytes[5]  = Hash[8];
    RandomBytes[6]  = Hash[4];
    RandomBytes[7]  = Hash[6];
    RandomBytes[8]  = Hash[10];
    RandomBytes[9]  = Hash[41];
    RandomBytes[10] = Hash[53];
    RandomBytes[11] = Hash[27];
    RandomBytes[12] = Hash[5];
    RandomBytes[13] = Hash[43];
    RandomBytes[14] = Hash[28];
    RandomBytes[15] = Hash[45];
    RandomBytes[16] = Hash[16];
    RandomBytes[17] = Hash[46];
    RandomBytes[18] = Hash[34];
    RandomBytes[19] = Hash[9];
    RandomBytes[20] = Hash[19];
    RandomBytes[21] = Hash[2];
    RandomBytes[22] = Hash[56];
}

