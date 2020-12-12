#include <stdio.h>
#include <openssl/bn.h>


// d * e == 1 modulo (p-1)(q-1)

void printBN(char *msg, BIGNUM * a)
{
	/* Use BN_bn2hex(a) for hex string
	* Use BN_bn2dec(a) for decimal string */
	char * number_str = BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}

int main(){

	BN_CTX *ctx = BN_CTX_new();

	// First we must convert strings to hex.
	// python -c 'print("Launch a missile.".encode("hex"))'
	// 4c61756e63682061206d697373696c652e

	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *n = BN_new();
	BIGNUM *m = BN_new();
	BIGNUM *s = BN_new();
	BIGNUM *m_dec = BN_new();
	BIGNUM *m_dec2 = BN_new();

	// initialize c, n, e from PDF file
	BN_hex2bn(&m, "4c61756e63682061206d697373696c652e");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");

	BN_hex2bn(&s, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");
	
	printBN("Message = ", m);

	// Decryption s^e mod n , Compute m_dec = s^e mod n
	BN_mod_exp(m_dec, s, e, n, ctx);

	printBN("Decrypted Sign = ", m_dec);

	BN_hex2bn(&s, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F");

	// Decryption s^e mod n , Compute m_dec2 = s^e mod n
	BN_mod_exp(m_dec2, s, e, n, ctx);

	printBN("Decrypted Sign (Corrupted)= ", m_dec2);

	
	return 0;

}

