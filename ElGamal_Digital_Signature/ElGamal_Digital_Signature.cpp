#include<iostream>
#include<NTL/ZZ.h>
#include <NTL/vector.h>
#include "sha1.hpp"
using namespace NTL;
using namespace std;

ZZ p, q, generator, private_key, public_key;

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
    private_key = RandomBnd(p);
    while(private_key == ZZ(0) or private_key == p-1)
        private_key = RandomBnd(p);
    public_key = PowerMod(generator, private_key, p);
    std::cout<<"\np = "<<p<<"\n";
    std::cout<<"\nq = "<<q<<"\n";
    std::cout<<"\ngenerator = "<<generator<<"\n";
    std::cout<<"\nprivate key = "<<private_key<<"\n";
    std::cout<<"\npublic key = "<<public_key<<"\n";
}

int decimal_value(char ch){
    switch(ch){
        case '0' : return 0;
        case '1' : return 1;
        case '2' : return 2;
        case '3' : return 3;
        case '4' : return 4;
        case '5' : return 5;
        case '6' : return 6;
        case '7' : return 7;
        case '8' : return 8;
        case '9' : return 9;
        case 'a' : return 10;
        case 'b' : return 11;
        case 'c' : return 12;
        case 'd' : return 13;
        case 'e' : return 14;
        case 'f' : return 15;
    }
    return -1;
}

ZZ convert_hexa_decimal_string_to_ZZ(string num){
    ZZ result = ZZ(0);
    for(int i = 0; i < num.length(); i++){
        result = result*16 + decimal_value(num[i]);
    }
    return result;
}

ZZ generate_hash(string input){
    // SHA1
    SHA1 checksum;
    checksum.update(input);
    const string hash = checksum.final();
    ZZ hash_val = convert_hexa_decimal_string_to_ZZ(hash);
    return hash_val;
}

Vec<ZZ> sign(string message){
    cout<<"\n-------------------- Sign -----------------------\n";
    
    ZZ s = ZZ(0), r, hash = generate_hash(message);
    
    cout<<"\nmessage = "<<message<<endl;
    cout<<"\nhash = "<<hash<<endl;

    while(s == ZZ(0)){  
        // choose random integer from {2,...,p-2} such that gcd(k, p-1) = 1.
        ZZ k = RandomBnd(p-1);
        while(k == ZZ(0) or k == ZZ(1) or GCD(k, p-1) != ZZ(1))
            k = RandomBnd(p-1);

        r = PowerMod(generator, k, p);
    
        //Signature
        s = (((hash - (private_key*r) % (p-1)) % (p-1)) * InvMod(k, p-1)) % (p-1);
    }

    cout<<"\nr = "<<r<<endl;
    cout<<"\ns = "<<s<<endl;

    Vec<ZZ> signature;
    signature.append(r);
    signature.append(s);
    return signature;
}

void verify_signature(Vec<ZZ> signature, string message){
    cout<<"\n---------------------Verify-------------------"<<endl;
    
    ZZ r = signature[0], s = signature[1];

    cout<<"\nr = "<<r<<"\n\ns = "<<s<<endl;

    if(r <= ZZ(0) or r >= p or s <= ZZ(0) or s >= p-1){
        cout<<"\nSignature is not valid\n";
        return;
    }
    
    //verify g^H(m) = (y^r).(r^s) (mod p)
    ZZ hash = generate_hash(message);
    ZZ lhs = PowerMod(generator, hash, p);
    ZZ rhs = (PowerMod(public_key, r, p) * PowerMod(r, s, p)) % p;

    cout<<"\n hash = "<<hash<<endl;
    cout<<"\nLHS = g^H(m) (mod p)= "<<lhs<<endl;
    cout<<"\nRHS = (y^r).(r^s) (mod p) = "<<rhs<<endl;

    if(lhs == rhs)
        cout<<"\nSignature is valid\n";
    else
        cout<<"|nSignature is invalid\n";
}

int main(){
    long no_of_bits = 512;
    generate_keys(no_of_bits);

    string message;
    std::cout<<"\nmessage = ";
    std::cin>>message;

    Vec<ZZ> signature = sign(message);

    verify_signature(signature, message);

    return 0;
}
