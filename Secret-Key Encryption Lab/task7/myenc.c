// Initialize the libraries
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <string.h>
#include <stdio.h>
#include <string.h>


// Initialize the plain text.
unsigned char *plain_text = "This is a top secret.";

// Initialize the cipher text.
unsigned char cipher_text[] = {0x76,0x4a,0xa2,0x6b,0x55,0xa4,0xda,0x65,0x4d,0xf6,0xb1,0x9e,0x4b,0xce,0x00,0xf4,0xed,0x05,0xe0,0x93,0x46,0xfb,0x0e,0x76,0x25,0x83,0xcb,0x7d,0xa2,0xac,0x93,0xa2};

// Initialize the methods
int isSame(unsigned char *cipher, int cipher_len, unsigned char *buff, int buff_len);
int isKey(unsigned char *key);

int main(void) {

	unsigned char key[16];	// Initialize the key
	FILE *txt = fopen("words.txt", "r");	// Reads words.txt

	while(fgets(key, 16, txt) != 0){	// Read file line by line

		key[strlen(key)-1]='\0';	// Remove the new line symbol
		int key_len = strlen(key);	// Get length of key

		if(key_len < 16){	// Complete the key size with the # character to 16.
			int len = key_len;
			while(len < 16){
				key[len] = 0x23;
				len++;
			}
		}

		int t = isKey(key);	// Control the the key is true
		if(t == 1){
			printf("Key found: %s \n", key);
			break;
		}
	}
	fclose(txt);
	return(0);
}

int isKey(unsigned char *key){ // Control the Key

	int out_size = 1024 +EVP_MAX_BLOCK_LENGTH;
	unsigned char out[out_size];
	int out_len = 0;
	int plain_text_len = strlen(plain_text);
	int buff_out_len;

	EVP_CIPHER_CTX ctx;

	// Initialize the initial vector
	unsigned char iv[] = {0xaa,0xbb, 0xcc, 0xdd,0xee, 0xff, 0x00, 0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11};

	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), 0, 0, 0, 1);

	// Control key and iv lengths
	OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
	OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);

	EVP_CipherInit_ex(&ctx, 0, 0, key, iv, 1);
	EVP_CipherUpdate(&ctx, out, &buff_out_len, plain_text, plain_text_len);

	out_len = buff_out_len;
	EVP_CipherFinal_ex(&ctx, out + buff_out_len, &buff_out_len);
	out_len += buff_out_len;
	EVP_CIPHER_CTX_cleanup(&ctx);

	int compare = isSame(cipher_text, sizeof(cipher_text), out, out_len);
	return compare;

}

// Control byte by byte for original cipher text with different keys.
int isSame(unsigned char *cipher, int cipher_len, unsigned char *buff, int buff_len){
	// Base condition
	if(cipher_len <= 0 || buff_len <= 0 || cipher_len != buff_len) return 0;
	// 
	for(int i =0;i < cipher_len; i++)
		if(cipher[i] != buff[i])
			return 0;
			
	return 1;
}