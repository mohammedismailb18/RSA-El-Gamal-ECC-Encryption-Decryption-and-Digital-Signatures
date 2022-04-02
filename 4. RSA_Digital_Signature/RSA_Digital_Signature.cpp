#include<iostream>
#include<NTL/ZZ.h>
#include "sha1.hpp"
#include <string>
using namespace NTL;
using std::string;
using std::cout;
using std::endl;

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

ZZ convert_decimal_to_ZZ(string num){
    ZZ result = ZZ(0);
    for(int i = 0; i < num.length(); i++){
        result = result*10 + num[i] - '0';
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

ZZ sign(string message, ZZ private_key, ZZ n){
    cout<<"\n-------------- sign ---------------\n";
    ZZ hash = generate_hash(message);
    cout<<"\nhash of message = "<<hash<<endl;
    ZZ signature = PowerMod(hash, private_key, n);
    cout<<"\nsignature = "<<signature<<endl;
    return signature;
}

void verify_signature(string message, ZZ public_key, ZZ signature, ZZ n){
    cout<<"\n-----------------verify signature-------------\n";
    ZZ hash = generate_hash(message);
    cout<<"\nhash = "<<hash<<endl;
    ZZ hash_dash = PowerMod(signature, public_key, n);
    cout<<"\nhash_dash = signature^public_key (mod n) = "<<hash_dash<<endl;
    if(hash == hash_dash)
        std::cout<<"\nsignature is valid\n";
    else
        std::cout<<"\nsignature is not valid\n";
}

int main(){
    ZZ p, q, n, phi_of_n, public_key, private_key;
    std::string message;
    int no_of_bits = 512;

    // generating p and q prime numbers
    p = GenPrime_ZZ(no_of_bits, 80);
    q = GenPrime_ZZ(no_of_bits, 80);
    n = p * q;
    phi_of_n = (p-1)*(q-1);

    std::cout<<"\np = "<<p<<"\n";
    std::cout<<"\nq = "<<q<<"\n";
    std::cout<<"\nn = "<<n<<"\n";
    std::cout<<"\nphi of n = "<<phi_of_n<<"\n";

    ZZ i = (ZZ)1;
    long bits_of_n = 0;
	for( ; i <= n; i *= 10) { 
        bits_of_n++; 
    }

    //Generating public key and private key.
    public_key = GenPrime_ZZ(bits_of_n/2, 80);
	private_key = InvMod(public_key, phi_of_n);

    std::cout<<"\npublic key = "<<public_key<<"\n";
    std::cout<<"\nprivate key = "<<private_key<<"\n";
    std::cout<<"\nprivate key * public key (mod phi_of_n)= "<<MulMod(public_key, private_key, phi_of_n)<<"\n";

    std::cout<<"\nEnter Message to decrypt : ";
    std::cin>>message;

    //Generating signature for the message
    ZZ signature = sign(message, private_key, n);
    
    // Verifying signature
    verify_signature(message, public_key, signature, n);

    return 0; 
}
