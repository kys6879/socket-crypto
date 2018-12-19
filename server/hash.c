#include <stdio.h>
#include <string.h>
#include "KISA_SHA256.h"

int hash_sha256(unsigned char r_msg[30] , unsigned char encrypt[32]) {
	SHA256_Encrpyt(r_msg, strlen((char *)r_msg), encrypt);
	return 1;
}