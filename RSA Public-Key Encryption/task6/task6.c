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
	BIGNUM *s = BN_new();
	BIGNUM *c = BN_new();
	BIGNUM *s_dec = BN_new();

	// Get certificates 
	// openssl s_client -connect www.example.org:443 -showcerts
	// Save c0.pem and c1.pem

	// Step1
	// Extract Public Key

	// For modulus (n):
	// openssl x509 -in c1.pem -noout -modulus

	// For modulus (n):
	// Assign the modulus
	BN_hex2bn(&n, "C14BB3654770BCDD4F58DBEC9CEDC366E51F311354AD4A66461F2C0AEC6407E52EDCDCB90A20EDDFE3C4D09E9AA97A1D8288E51156DB1E9F58C251E72C340D2ED292E156CBF1795FB3BB87CA25037B9A52416610604F571349F0E8376783DFE7D34B674C2251A6DF0E9910ED57517426E27DC7CA622E131B7F238825536FC13458008B84FFF8BEA75849227B96ADA2889B15BCA07CDFE951A8D5B0ED37E236B4824B62B5499AECC767D6E33EF5E3D6125E44F1BF71427D58840380B18101FAF9CA32BBB48E278727C52B74D4A8D697DEC364F9CACE53A256BC78178E490329AEFB494FA415B9CEF25C19576D6B79A72BA2272013B5D03D40D321300793EA99F5");

	// Print out all the fields, find the exponent (e):
	// openssl x509 -in c1.pem -text -noout

	// Assign the exponent (e) - 65537
	BN_hex2bn(&e, "10001");

	// openssl x509 -in c0.pem -text -noout
	// cat signature | tr -d ’[:space:]:’
	BN_hex2bn(&s, "a72a10305cb86b7a1bf86638f6e9a00ad5138282f8658957a5b8eb13291d846cecfbe30511d71e315e0ee2c000e56d0648be3d556fbab71135b6eac4cf84f1304cbb339e11172bc9d2194b2cd0ad5f172384e1df17a23ba87f69297c48a6615f263f75e23b5ba336b31ccde30457301ffcc9fa4b8e488058279ca2c7c326dc1702fae66cea81015c928fd3180817707ac2a34b6c3afae3cff6fe7ec956e5a54e1b144fa9989d79b11ec3abb10d1585a946b6e5c258e85afec814286890c6b8c8947fe10f89faa7d60937a162b70027b5bef1b15e452806b35415e6c3c8ac8201ce86e22be17ae4bd4ccb9c5ed062c261bd8b5a62b67630bc460fe34523c0645f");



	// We generated the hash of the certificate body like so:
	// First, extract the body of the certificate
	// openssl asn1parse -i -in c0.pem -strparse 4 -out c0_body.bin -noout
	// Then, compute the hash:
	// sha256sum c0_body.bin
	// This hash will be used for comparison for when we decrypt the signature.


	// Decryption c^e mod n , Compute m_dec = c^e mod n
	BN_mod_exp(s_dec, s, e, n, ctx);

	printBN("Decrypted Sign = ", s_dec);

	// Last 32 bit must be same with this hash

	printf("the pre-computed hash was: ");
	printf("373e90af567edd6dab8b435927ff7cc2db6e8a17337c6eb9aabea0e4907b0eff\n");

	return 0;

}

