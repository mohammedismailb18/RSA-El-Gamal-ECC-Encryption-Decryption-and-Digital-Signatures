#include<iostream>
#include<NTL/ZZ.h>
#include<NTL/vector.h>
#include "sha1.hpp"
using namespace NTL;
using namespace std;

typedef struct point{
    ZZ x;
    ZZ y;
}Point;

// NIST parameters for 192 bit
ZZ p = power(ZZ(2), long(192)) - power(ZZ(2), long(64)) - 1;    //feild parameter
ZZ a = ZZ(-3);  // elliptic cuve parameter
ZZ b = conv<ZZ>("2455155546008943817740293915197451784769108058161191238065"); // elliptic curve parameter
ZZ n = conv<ZZ>("6277101735386680763835789423176059013767194773182842284081"); // order of elliptic curve
ZZ Px = conv<ZZ>("602046282375688656758213480587526111916698976636884684818"); // x cordinate of base point
ZZ Py = conv<ZZ>("174050332293622031404857552280219410364023488927386650641"); // y cordinate of base point

Point point_doubling(Point P){
    ZZ x1 = P.x, y1 = P.y;
    if(y1 == 0){
        std::cout<<"Point doubling error";
        return {ZZ(0), ZZ(0)};
    }
    ZZ m = ((3*x1*x1 + a) * InvMod((2*y1) % p, p)) % p;
    ZZ x3 = (m*m - 2*x1) % p;
    ZZ y3 = (m*(x1 - x3) - y1) % p;
    return {x3, y3};
}

Point point_addition(Point P, Point Q){
    ZZ x1 = P.x, y1 = P.y, x2 = Q.x, y2 = Q.y;
    if(y1 == y2 or y1 == -y2){
        std::cout<<"\nPoint Addition invalid operation";
        return {ZZ(0), ZZ(0)};
    }
    ZZ m = (((y2 - y1) % p) * InvMod((x2 - x1) % p, p)) % p;
    ZZ x3 = ((m*m) % p - (x1 + x2) % p) % p;
    ZZ y3 = ((m*(x1 - x3)) % p - y1) % p;
    return {x3, y3};
}

Point scalar_multiply(ZZ k, Point P){
    // std::cout<<"\n k = "<<k<<"\n P.x = "<<P.x<<"\n P.y = "<<P.y<<"\n";
    Point P1 = P, P2;
    bool p2_initialized = false;
    while(k != ZZ(0)){
        if(operator&(k, ZZ(1)) > ZZ(0)){
            if(!p2_initialized){
                p2_initialized = true;
                P2 = P1;
            }
            else{
                P2 = point_addition(P1, P2);
            }
        }
        P1 = point_doubling(P1);
        k = RightShift(k, long(1));
    }
    return P2;
}


ZZ ecc_y_val(ZZ x){
    return (power(x, long(3)) + a*x + b) % p;
}

ZZ choose_random_integer(ZZ num){
    ZZ private_key = RandomBnd(num);
    while(private_key == ZZ(0))
        private_key = RandomBnd(num);
    return private_key;
}

Point generate_public_key(ZZ private_key){
    return scalar_multiply(private_key, {Px, Py});
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

Vec<ZZ> sign(string message, ZZ private_key){
    ZZ r, s, k;
    ZZ hash = generate_hash(message);
    do{
        r = ZZ(0);
        
        do{  
            //select random k from [1, n-1]
            k = choose_random_integer(n);
            // compute k*BasePoint
            Point kP = scalar_multiply(k, {Px, Py});
            //r = kP.x mod n
            r = kP.x % n;
        }while(r == ZZ(0));

        s = (InvMod(k, n)*((hash + (private_key*r) % n) % n)) % n;
    }while(s == ZZ(0));
    
    cout<<"\nSignature, r = "<<r<<endl;
    cout<<"\nSignature, s = "<<s<<endl;

    Vec<ZZ> signature;
    signature.append(r);
    signature.append(s);
    return signature;
}

void verify_signature(Vec<ZZ> signature, string message, Point public_key){
    ZZ r = signature[0], s = signature[1];
    if(r < 1 or r > n-1 or s < 1 or s > n-1){
        cout<<"\nSignature is invalid\n";
        return;
    }
    ZZ hash = generate_hash(message);
    ZZ w = InvMod(s, n);
    ZZ u1 = (hash*w) % n;
    ZZ u2 = (r*w) % n;
    Point u1_mul_P = scalar_multiply(u1, {Px, Py});
    Point u2_mul_Public_key = scalar_multiply(u2, public_key);
    Point X = point_addition(u1_mul_P, u2_mul_Public_key);
    ZZ v = X.x % n;
    if(v == r)
        cout<<"\nSignature is valid\n";
    else
        cout<<"\nSignature is invalid\n";
}

int main(){
    string message;
    std::cout<<"\nEnter message to encrypt using ECC : ";
    std::cin>>message;
    
    //Generating private and public keys
    ZZ private_key = choose_random_integer(n);
    std::cout<<"\nprivate key : "<<private_key<<"\n";

    Point public_key = generate_public_key(private_key);
    std::cout<<"\npublic key : "<<"x = "<<public_key.x<<" , "<<"y = "<<public_key.y<<"\n";

    Vec<ZZ> signature = sign(message, private_key);

    verify_signature(signature, message, public_key);

    return 0;
}
