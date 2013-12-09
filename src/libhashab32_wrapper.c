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
 *  libhashab32_wrapper is a small wrapper application around the
 *  libhashab.so library allowing you to access this 32-bit version of
 *  the library from 64-bit libgpod
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

typedef void (*calcHashAB_t)(unsigned char target[57], const unsigned char sha1[20], const unsigned char uuid[20], const unsigned char rnd_bytes[23]);
static calcHashAB_t calc_hashAB = NULL;

int main(int argc, char *argv[]) {
    void *lib_handle;
    char *error;
    unsigned char a, i;
    FILE *fp;

    unsigned char Sha1[20];
    unsigned char UUID[20];
    unsigned char Random[23];
    unsigned char HashAB[57];
    unsigned char TempVar[3];
    
    /* Clear the data arrays to 0 */    
    memset(Sha1, 0, 20);
    memset(UUID, 0, 20);
    memset(Random, 0, 23);
    memset(HashAB, 0, 57);

    /* Try to open the modified shared library */
    lib_handle = dlopen("/usr/lib/x86_64-linux-gnu/libgpod/libhashab32.so", RTLD_LAZY);

    /* If the library failed to open */
    if (!lib_handle) {
        /* Print the error to stderr and return 1 */
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    /* Get the calc_hashAB function pointer */
    calc_hashAB = dlsym(lib_handle, "calcHashAB");

    /* If there was an error */
    if (!calc_hashAB) {
        /* Print the error to stderr and return 1 */
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }


    /* There needs to be 3 arguments */
    if(argc < 4) {
        /* Print the error to stderr and return 1 */
        fprintf(stderr, "Error: Needs 3 arguments\n");
        return 1;
    }

    /* For all of arg1 Sha1 */
    for(a = 0; a < strlen(argv[1]); a+=2) {
        /* Store the hex values in the temp variable */
        TempVar[0] = argv[1][a];
        TempVar[1] = argv[1][a+1];
        TempVar[2] = 0;

        /* Convert the hex value to the UUID byte */
        Sha1[a/2] = strtoul(TempVar, NULL, 16);
    }

    /* For all of arg2 (UUID) */
    for(a = 0; a < strlen(argv[2]); a+=2) {
        /* Store the hex values in the temp variable */
        TempVar[0] = argv[2][a];
        TempVar[1] = argv[2][a+1];
        TempVar[2] = 0;

        /* Convert the hex value to the UUID byte */
        UUID[a/2] = strtoul(TempVar, NULL, 16);
    }

    /* For all of arg3 (Rand data) */
    for(a = 0; a < strlen(argv[3]); a+=2) {
        /* Store the hex values in the temp variable */
        TempVar[0] = argv[3][a];
        TempVar[1] = argv[3][a+1];
        TempVar[2] = 0;

        /* Convert the hex value to the UUID byte */
        Random[a/2] = strtoul(TempVar, NULL, 16);
    }

    /* Generate the hash */
    calc_hashAB(HashAB, Sha1, UUID, Random);

    /* For all hashab bytes */
    for(a = 0; a < 57; a++) {
        /* Print the hex output */
        printf("%02X", HashAB[a]);
    }

    /* Close the library */
    dlclose(lib_handle);

    /* Return success */
    return 0;
}

