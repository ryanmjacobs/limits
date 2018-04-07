#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/md5.h>

#define DIFF 5

int main(void) {
    unsigned char digest[MD5_DIGEST_LENGTH];

    for (uint64_t nonce = 0; nonce < UINT64_MAX; nonce++) {
        MD5((unsigned char*)&nonce, sizeof(nonce), (unsigned char*)&digest);    

        int diff = DIFF;
        do {
            if (digest[diff-1] != 0x00)
                break;
        } while (diff--);

        if (diff == -1)
            break;
    }
     
     // print hash
     char mdString[49];
     for(int i = 0; i < 16; i++)
          sprintf(&mdString[i*3], "%02x ", (unsigned int)digest[i]);
     printf("md5 digest: %s\n", mdString);

    return 0;
}
