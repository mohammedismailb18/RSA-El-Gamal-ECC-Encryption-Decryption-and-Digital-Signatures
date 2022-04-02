# RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures
Assignment done as part of Introduction to Information Security Course (CS4062D). All programs are written in C++ using NTL library.

## 1. RSA Encryption and Decryption
1. Choose two primes p and q of no of bits l. Let n = p * q
2. Let the public key, e ∈ Z be positive such that gcd(e, Φ(n)) = 1.
3. Then the private key, d ∈ Z such that de ≡ 1 (mod(Φ(n))).
4. For every message m < n, we can encrypt the message m using, c = m<sup>e</sup>(mod n).
5. c can be decrypted by using the private key, m = c<sup>d</sup>(mod n).

**Output for 512 bits**

![512 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/1.%20RSA_Encryption_Decryption/output_512bits.jpg)

**Output for 1024 bits**

![1024 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/1.%20RSA_Encryption_Decryption/output_1024bits.jpg)

## 2. El-Gamal Encryption and Decryption

### 2.1 DL Domain Parameter Generation
**INPUT** : Security parameter l and t <br>
**OUTPUT** : DL domain parameters (p, q, g)
1. Select a t bit prime p and l bit prime q such that q divides p-1.
2. Select an arbitrary h ∈ [1, p-1] and calculate generator g = h<sup>(p-1)/q</sup>
3. if g = 1, then go to step 2

### 2.2 DL Key Pair Generation
**INPUT** : DL domain parameters (p, q, g) <br>
**OUTPUT** : public key **y** and private key **x**
1. Select x ∈ [1, q-1].
2. calculate y = g<sup>x</sup> (mod p).
3. return (y, x)

### 2.3 El-Gamal Encryption
**INPUT** : DL domain parameters (p, q, g), public key y, plain text m ∈ [0, p-1]. <br>
**OUTPUT** : CipherText (c1, c2)
1. Choose k randomly from [1, q-1].
2. c1 = g<sup>k</sup> (mod p).
3. c2 = m * y<sup>k</sup> (mod p)
4. return (c1, c2)

### 2.4 El-Gamal Decryption
**INPUT** : DL domain parameters (p, q, g), private key x, cipher text (c1, c2). <br>
**OUTPUT** : plaintext m
1. compute m = c2 * c1<sup>-x</sup> (mod p)
2. return m

**Output for 512 bits**

![512 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/2.%20El_Gamal_Encryption_Decryption/output_512bits.jpg)

**Output for 1024 bits**

![1024 bits output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/2.%20El_Gamal_Encryption_Decryption/output_1024bits.jpg)

## 3. ECC Encryption and Decryption

### 3.1 ECC NIST parameters for 192 bits
1. Feild, p = 2<sup>192</sup> −2<sup>64</sup> −1
2. a = −3 (where a is in y<sup>2</sup> = x<sup>3</sup> + ax + b)
3. b = 0x 64210519 E59C80E7 0FA7E9AB 72243049 FEB8DEEC C146B9B1 (where b is in y<sup>2</sup> = x<sup>3</sup> + ax + b)
4. n = 0x FFFFFFFF FFFFFFFF FFFFFFFF 99DEF836 146BC9B1 B4D22831 (order of E<sub>(a, b)</sub>(F<sub>p</sub>))
5. x = 0x 188DA80E B03090F6 7CBF20EB 43A18800 F4FF0AFD 82FF1012 (x cordinate of base point)
6. y = 0x 07192B95 FFC8DA78 631011ED 6B24CDD5 73F977A1 1E794811 (y cordinate of base point)

### 3.2 Elliptic Curve Key Pair Generation
**INPUT**: Elliptic curve domain parameters (p, E, P,n). <br>
**OUTPUT**: Public key Q and private key d
1. Select d ∈<sub>R</sub> [1,n −1].
2. Compute Q = d.P.
3. Return(Q,d).

### 3.3 ElGamal Elliptic Curve Encryption
**INPUT**: Elliptic curve domain parameters (p, E, P,n), public key Q, plaintext m. <br>
**OUTPUT**: Ciphertext (C1,C2).
1. Represent the message m as a point M in E(Fp).
2. Select k ∈<sub>R</sub> [1,n −1].
3. Compute C1 = k.P.
4. Compute C2 = M +k.Q.
5. Return(C1,C2).

### 3.4 ElGamal Elliptic Curve Decryption
**INPUT:** Domain parameters (p, E, P,n), private key d, ciphertext (C1,C2). <br>
**OUTPUT:** Plaintext m.
1. Compute M = C2 −d.C1, and extract m from M.
2. Return(m).

**Output**

![output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/3.%20ECC_Encryption_Decryption/Screenshot%202022-04-01%20085240.jpg)

## 4. RSA Digital Signature
### 4.1 RSA Sign
**INPUT:** (message (msg), private key (d), n) <br>
**OUTPUT:** Signature (s) <br>
Signing a message msg with the private key exponent d: <br>
1. Calculate the message hash: h = hash(msg)
2. Encrypt h to calculate the signature : s = h<sup>d</sup>(modn)

The hash h should be in the range [0...n). The obtained signature s is an integer in the range [0...n).

### 4.2 RSA Verify Signature
**INPUT:** (Signature (s), message (msg), public key (e), n) <br>
**OUTPUT:** prints valid sign or not <br>
Verifying a signature s for the message msg with the public key e:
1. Calculate the message hash: h = hash(msg)
2. Decrypt the signature: h′ = s<sup>e</sup>(modn)
3. if h == h′, then signature is valid else signature is invalid.

**Output**

![output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/4.%20RSA_Digital_Signature/output.jpg)


## 5. ElGamal Digital Signature
### 5.1 Sign
**INPUT:** (message (m), private key (x), p) <br>
**OUTPUT:** (r, s)
1. Choose an integer k randomly from {2,....,p-2} with k relatively prime to p-1.
2. Compute r = g<sup>k</sup> (mod p).
3. Compute s = (H(m) - x.r).k<sup>-1</sup> (mod p-1).
4. if s == 0, then go to step 1.

### 5.2 Verify Signature
**INPUT:** (r, s, message (m), public key (y), p) <br>
**OUTPUT:** prints valid sign or not <br>
1. Verify that 0<r<p and 0<s<p-1.
2. The signature is valid if and only if g<sup>H(m)</sup> = y<sup>r</sup>.r<sup>s</sup> (mod p).

**Output**

![output](https://github.com/mohammedismailb18/RSA-El-Gamal-ECC-Encryption-Decryption-and-Digital-Signatures/blob/main/5.%20ElGamal_Digital_Signature/output.jpg)
