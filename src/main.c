#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <openssl/md5.h>

#define DIFF 4

#define NUM_CORES sysconf(_SC_NPROCESSORS_ONLN)
#define NUM_THREADS NUM_CORES
#define CHUNK_SIZE UINT64_MAX/NUM_THREADS

void *mine(void *args) {
    int diff;
    unsigned n = *(unsigned *)args;
    unsigned char digest[MD5_DIGEST_LENGTH];

    for (unsigned i = 0; i < CHUNK_SIZE; i++) {
        uint64_t nonce = (n*CHUNK_SIZE) + i;

        MD5((unsigned char*)&nonce, sizeof(nonce), (unsigned char*)&digest);    

        diff = DIFF;
        do {
            if (digest[diff-1] != 0x00)
                break;
        } while (diff--);

        if (diff == -1)
            break;
    }

    // print hash
    if (diff == -1) {
        char mdString[49];
        for(int i = 0; i < 16; i++)
             sprintf(&mdString[i*3], "%02x ", (unsigned int)digest[i]);
        printf("md5 digest: %s\n", mdString);
        exit(0);
    }
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (unsigned i = 0; i < NUM_THREADS; i++) {
        unsigned *n = malloc(sizeof(unsigned));
        *n = i;
        pthread_create(&threads[i], NULL, mine, n);
    }

    for (unsigned i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
