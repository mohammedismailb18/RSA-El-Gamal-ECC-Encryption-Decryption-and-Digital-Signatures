# RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures
Assignment done as part of Introduction to Information Security Course (CS4062D). All programs are written in C++ using NTL library.

## RSA Encryption and Decryption
1. Choose two primes p and q of no of bits l. Let n = p * q
2. Let the public key, e ∈ Z be positive such that gcd(e, Φ(n)) = 1.
3. Then the private key, d ∈ Z such that de ≡ 1 (mod(Φ(n))).
4. For every message m < n, we can encrypt the message m using, c = m^e(mod n).
5. c can be decrypted by using the public key, m = c^d(mod n).

**Output for 512 bits**

![512 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/1.%20RSA_Encryption_Decryption/output_512bits.jpg)

**Output for 1024 bits**

![1024 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/1.%20RSA_Encryption_Decryption/output_1024bits.jpg)

## El-Gamal Encryption and Decryption

### DL Domain Parameter Generation
1. Select a t bit prime p and l bit prime q such that q divides p-1.
2. Select generator g of order q:
2.1 Select an arbitrary h ∈ [1, p-1] and calculate g = h^((p-1)/q)
2.2 if g = 1, then go to step 2.1

### DL Key Pair Generation
INPUT : DL domain parameters (p, q, g)
1. Select x ∈ [1, q-1].
2. calculate y = g^x (mod p).
3. return (y, x)

**Output for 512 bits**

![512 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/2.%20El_Gamal_Encryption_Decryption/output_512bits.jpg)

**Output for 1024 bits**

![1024 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/2.%20El_Gamal_Encryption_Decryption/output_1024bits.jpg)

