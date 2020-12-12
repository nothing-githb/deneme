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

	// First we must convert strings to hex.
	// python -c 'print("I owe you $2000.".encode("hex"))'
	// 49206f776520796f752024323030302e
	// python -c 'print("I owe you $3000.".encode("hex"))'
	// 49206f776520796f752024333030302e

	BN_CTX *ctx = BN_CTX_new();

	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *n = BN_new();
	BIGNUM *m = BN_new();
	BIGNUM *m2= BN_new();
	BIGNUM *c = BN_new();
	BIGNUM *m_dec = BN_new();

	// initialize e, m, n from PDF file (Task 2)
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&m, "49206f776520796f752024323030302e");
	BN_hex2bn(&m2, "49206f776520796f752024333030302e");
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	

	// Encryption m^e mod n , Compute c = m^e mod n
	BN_mod_exp(c, m, e, n, ctx);

	printBN("Signed Message (I owe you $2000.) = ", c);

	// Encryption m^e mod n , Compute c = m^e mod n
	BN_mod_exp(c, m2, e, n, ctx);

	printBN("Signed Message (I owe you $3000.) = ", c);

	
	return 0;

}

