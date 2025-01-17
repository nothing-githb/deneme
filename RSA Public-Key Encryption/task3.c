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

	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *n = BN_new();
	BIGNUM *m = BN_new();
	BIGNUM *c = BN_new();
	BIGNUM *m_dec = BN_new();

	// Initialize the c, n and d values from PDF
	BN_hex2bn(&c, "8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

	// Decryption c^d mod n , Compute m_dec = c^d mod n
	BN_mod_exp(m_dec, c, d, n, ctx);

	printBN("Decrypted Message = ", m_dec);

	// python -c 'print("50617373776F72642069732064656573".decode("hex"))'
	// Password is dees
	return 0;

}

