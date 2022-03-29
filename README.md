# RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures
Assignment done as part of Introduction to Information Security Course (CS4062D). All programs are written in C++ using NTL library.

## RSA
1. Choose two primes p and q of no of bits l. Let n = p * q
2. Let the public key, e ∈ Z be positive such that gcd(e, Φ(n)) = 1.
3. Then the private key, d ∈ Z such that de ≡ 1 (mod(Φ(n))).
4. For every message m < n, we can encrypt the message m using, c = m^e(mod n).
5. c can be decrypted by using the public key, m = c^d(mod n).

**Output for 512 bits**
<img src = "https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-DigitalSignatures/blob/main/1.%20RSA_Encryption_Decryption/output_512bits.jpg">
