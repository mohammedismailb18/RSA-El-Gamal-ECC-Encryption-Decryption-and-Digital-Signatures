#include<iostream>
#include<NTL/ZZ.h>
#include <NTL/vector.h>
using namespace NTL;

ZZ p, q, generator, private_key, public_key;

// ZZ primitive_root(ZZ p){
//     if(p == 2)
//         return (ZZ)1;
//     ZZ p1 = (ZZ)2;
//     ZZ p2 = (p-1)/p1;

//     while(true){
//         ZZ g = RandomBnd(p-1);
//         while(g == ZZ(0) or g == ZZ(1))
//             g = RandomBnd(p-1);
//         if(PowerMod(g, (p-1)/p1, p) != ZZ(1) or PowerMod(g, (p-1)/p2, p) != ZZ(1))
//             return g;
//     }
//     return ZZ(-1);
// }

void generate_keys(long no_of_bits){
    q = GenGermainPrime_ZZ(no_of_bits-1, 80);
    p = 2*q + 1;
    generator = ZZ(1);
    while(generator == ZZ(1)){
        ZZ h = RandomBnd(p);
        while(h == ZZ(0))
            h = RandomBnd(p);
        generator = PowerMod(h, (p-1)/q, p);
    }
    private_key = RandomBnd(q);
    while(private_key == ZZ(0))
        private_key = RandomBnd(q);
    public_key = PowerMod(generator, private_key, p);
    std::cout<<"\np = "<<p<<"\n";
    std::cout<<"\nq = "<<q<<"\n";
    std::cout<<"\ngenerator = "<<generator<<"\n";
    std::cout<<"\nprivate key = "<<private_key<<"\n";
    std::cout<<"\npublic key = "<<public_key<<"\n";
}

Vec<ZZ> encrypt(ZZ message){
    ZZ k = RandomBnd(q);
    while(k == ZZ(0))
        k = RandomBnd(q);
    ZZ c1 = PowerMod(generator, k, p);
    ZZ c2 = (message * PowerMod(public_key, k, p)) % p;
    Vec<ZZ> cipher;
    cipher.append(c1);
    cipher.append(c2);
    return cipher;
}

ZZ decrypt(Vec<ZZ> cipher){
    ZZ c1 = cipher[0];
    ZZ c2 = cipher[1];
    ZZ inverse_of_c1 = InvMod(c1, p);
    ZZ decrypted_message = (c2 * PowerMod(inverse_of_c1, private_key, p)) % p;
    return decrypted_message;
}

int main(){
    long no_of_bits;
    std::cout<<"\nEnter no of bits : ";
    std::cin>>no_of_bits;
    generate_keys(no_of_bits);
    ZZ message;
    std::cout<<"\nmessage = ";
    std::cin>>message;
    std::cout<<"\n";
    Vec<ZZ> cipher = encrypt(message);
    std::cout<<"\nCipher C1 = "<<cipher[0]<<"\n";
    std::cout<<"\nCipher C2 = "<<cipher[1]<<"\n"; 
    ZZ decrypted_message = decrypt(cipher);
    std::cout<<"\nDecrypted message = "<<decrypted_message<<"\n";
    return 0;
}
