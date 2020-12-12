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

	BIGNUM *p = BN_new();
	BIGNUM *q = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *p_minus = BN_new();
	BIGNUM *q_minus = BN_new();
	BIGNUM *f_of_fi = BN_new();
	BIGNUM *one = BN_new();

	// initialize p, q, e from PDF file

	BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
	BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
	BN_hex2bn(&e, "0D88C3");
	BN_dec2bn(&one, "1");

	// p-1
	BN_sub(p_minus, p , one);

	// q-1
	BN_sub(q_minus, q , one);

	// (p-1)*(q-1)
	BN_mul(f_of_fi, p_minus, q_minus, ctx);

	//d = e.modInverse(p_1.multiply(q_1))
	BN_mod_inverse(d, e, f_of_fi, ctx);

	printBN("d = ", d);
	return 0;

}

