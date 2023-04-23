#include <stdio.h>
#include <stdint.h>

unsigned char RC[10][4] =
{
    {0x01,0x00,0x00,0x00},
    {0x02,0x00,0x00,0x00},
    {0x04,0x00,0x00,0x00},
    {0x08,0x00,0x00,0x00},
    {0x10,0x00,0x00,0x00},
    {0x20,0x00,0x00,0x00},
    {0x40,0x00,0x00,0x00},
    {0x80,0x00,0x00,0x00},
    {0x1b,0x00,0x00,0x00},
    {0x36,0x00,0x00,0x00}
    
};
unsigned char mixMatrix[4][4] = 
{   
    {2,3,1,1},
    {1,2,3,1},
    {1,1,2,3},
    {3,1,1,2}
};

unsigned char subbyte[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

void shiftrow(unsigned char x[4][4])
{
    int t1, t2, t3;

    // Row 1: no change
    // Row 2: shift left by 1
    t1 = x[1][0];
    x[1][0] = x[1][1];
    x[1][1] = x[1][2];
    x[1][2] = x[1][3];
    x[1][3] = t1;

    // Row 3: shift left by 2
    t1 = x[2][0];
    t2 = x[2][1];
    x[2][0] = x[2][2];
    x[2][1] = x[2][3];
    x[2][2] = t1;
    x[2][3] = t2;

    // Row 4: shift left by 3
    t1 = x[3][0];
    t2 = x[3][1];
    t3 = x[3][2];
    x[3][0] = x[3][3];
    x[3][1] = t1;
    x[3][2] = t2;
    x[3][3] = t3;
}
void invShiftRow(unsigned char x[4][4])
{
    int t1, t2, t3;

    // Row 1: no change
    // Row 2: shift right by 1
    t1 = x[1][3];
    x[1][3] = x[1][2];
    x[1][2] = x[1][1];
    x[1][1] = x[1][0];
    x[1][0] = t1;

    // Row 3: shift right by 2
    t1 = x[2][3];
    t2 = x[2][2];
    x[2][3] = x[2][1];
    x[2][2] = x[2][0];
    x[2][1] = t1;
    x[2][0] = t2;

    // Row 4: shift right by 3
    t1 = x[3][3];
    t2 = x[3][2];
    t3 = x[3][1];
    x[3][3] = x[3][0];
    x[3][2] = t1;
    x[3][1] = t2;
    x[3][0] = t3;
}

void rotword(unsigned char x[4])
{
    unsigned char temp = x[0];
    x[0] = x[1];
    x[1] = x[2];
    x[2] = x[3];
    x[3] = temp; 
}
unsigned char getSubByte(unsigned char a) {
    int t1, t2;
    t1 = a & 15;
    t2 = a >> 4;
    return (subbyte[t2][t1]);
}
void KeyExpansion(unsigned char key[4][4], unsigned char roundKey[44][4], unsigned char sbox[16][16]) {
    unsigned char temp[4];
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            roundKey[i][j]=key[i][j];
        }
    }
    
    for(int i=4;i<44;i++) {
        for(int j=0;j<4;j++) {
            temp[j]=roundKey[i-1][j];
        }
        if(i%4==0) 
        {
            rotword(temp);
            for(int j=0; j<4; j++)
            {
                temp[j] = getSubByte(temp[j])^ RC[i/4-1][j];                
            }
        }
        for(int j = 0; j < 4; j++)
        {
            roundKey[i][j] = roundKey[i-4][j] ^ temp[j];
        }
    }
}
unsigned char xs(unsigned char s)
{
    unsigned char t;
    t = s << 1;
    if(s >> 7 == 1)
    {
        t = t ^ 27;
    }
    return t;
}
unsigned char ys(unsigned char t)
{
    unsigned char s;
    if(t >= 128)
    {
        t = t ^ 27;
    }
    s = t >> 1;
    return s;
}

void getKey(int index, unsigned char key[44][4], unsigned char k[4][4]) {
    int l = 0;
     for (int i = index; i < index + 4; i++) {
    for (int j = 0; j < 4; j++) {
       
            k[j][l] = key[i][j];

        }
        l++;
    }
}

void xor(unsigned char pt[4][4], unsigned char k[4][4])
{
  for(int i =0; i < 4; i++)
    {
        for(int j=0; j < 4; j++)
        {
            pt[i][j] = pt[i][j] ^ k[i][j];
        }
    }
}
void xordecrypt(unsigned char ct[4][4], unsigned char k[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            ct[i][j] = ct[i][j] ^ k[i][j];  // XOR the ciphertext with the key
        }
    }
}
unsigned invSub(unsigned char a)
{
    int i, j;
    unsigned char x;
    for(int i =0; i < 16; i++)
    {
        for(int j =0; j < 16; j++)
        {
            if(subbyte[i][j]==a)
            {
                x = i;
                x = (x<<4) | j;
                break;
            }
        }
    }
    return x;
}
void sub(unsigned char stateMatrix[4][4])
{
     for(int i =0; i < 4; i++)
    {
        for(int j=0; j < 4; j++)
        {
            stateMatrix[i][j] = getSubByte(stateMatrix[i][j]);
        }
    }
}
void subInv(unsigned char stateMatrix[4][4])
{
     for(int i =0; i < 4; i++)
    {
        for(int j=0; j < 4; j++)
        {
            stateMatrix[i][j] = invSub(stateMatrix[i][j]);
        }
    }
}
void mixColumn(unsigned char res[4][4], unsigned char stateMatrix[4][4])
{
     for(int i=0;i<4;i++)
    {
      res[i][0]=xs(stateMatrix[i][0])^xs(stateMatrix[(i+1)%4][0])^(stateMatrix[(i+1)%4][0])^(stateMatrix[(i+2)%4][0])^(stateMatrix[(i+3)%4][0]);
       res[i][1]=xs(stateMatrix[i][1])^xs(stateMatrix[(i+1)%4][1])^(stateMatrix[(i+1)%4][1])^(stateMatrix[(i+2)%4][1])^(stateMatrix[(i+3)%4][1]);
        res[i][2]=xs(stateMatrix[i][2])^xs(stateMatrix[(i+1)%4][2])^(stateMatrix[(i+1)%4][2])^(stateMatrix[(i+2)%4][2])^(stateMatrix[(i+3)%4][2]);
         res[i][3]=xs(stateMatrix[i][3])^xs(stateMatrix[(i+1)%4][3])^(stateMatrix[(i+1)%4][3])^(stateMatrix[(i+2)%4][3])^(stateMatrix[(i+3)%4][3]);
    }
   
}
// multiply function for Galois Field (GF(2^8))
unsigned char multiply(unsigned char x, unsigned char y) {
    unsigned char result = 0;
    unsigned char temp;
    while (y) {
        if (y & 1) {
            result ^= x;
        }
        temp = x & 0x80;
        x <<= 1;
        if (temp) {
            x ^= 0x1b; // irreducible polynomial for GF(2^8)
        }
        y >>= 1;
    }
    return result;
}


void invMixColumn(unsigned char res[4][4], unsigned char stateMatrix[4][4])
{
    for(int i=0;i<4;i++)
    {
        res[0][i] = multiply(0x0e, stateMatrix[0][i]) ^ multiply(0x0b, stateMatrix[1][i]) ^ multiply(0x0d, stateMatrix[2][i]) ^ multiply(0x09, stateMatrix[3][i]);
        res[1][i] = multiply(0x09, stateMatrix[0][i]) ^ multiply(0x0e, stateMatrix[1][i]) ^ multiply(0x0b, stateMatrix[2][i]) ^ multiply(0x0d, stateMatrix[3][i]);
        res[2][i] = multiply(0x0d, stateMatrix[0][i]) ^ multiply(0x09, stateMatrix[1][i]) ^ multiply(0x0e, stateMatrix[2][i]) ^ multiply(0x0b, stateMatrix[3][i]);
        res[3][i] = multiply(0x0b, stateMatrix[0][i]) ^ multiply(0x0d, stateMatrix[1][i]) ^ multiply(0x09, stateMatrix[2][i]) ^ multiply(0x0e, stateMatrix[3][i]);
    }
}





int main() {
    printf("%hhx", xs(0x50));
    printf("%hhx", ys(0xa0));
    unsigned char plaintext[16];
    unsigned char key[16];
    unsigned char pt[4][4];
    unsigned char k[4][4];
    unsigned char stateMatrix[4][4];
    unsigned char roundkey[44][4];
    unsigned char res[4][4];
        unsigned char res1[4][4];
    
    printf("Enter plaintext (up to 16 characters): ");
    scanf("%16[^\n]", plaintext); // read up to 16 characters until newline
    getchar(); // consume the newline character left over from previous input
    int target = 0; 
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            pt[j][i] = plaintext[target];
            printf(" ");
            target++;
        }
    }
    printf("\nYour entered plaintext is: \n");
    for(int i =0; i < 16; i++) {
        printf("%hhx", plaintext[i]); // print as 2-digit hex values
    }
    printf("\nEnter key (up to 16 characters): \n");
    scanf("%16[^\n]", key); // read up to 16 characters until newline
    getchar(); // consume the newline character left over from previous input
    
    printf("Your entered key is: \n");
    for(int i =0; i < 16; i++) {
        printf("%hhx", key[i]); // print as 2-digit hex values
    }
    
    int index = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            k[i][j] = key[index];
            index++;
        }
    }      
    KeyExpansion(k,roundkey,subbyte);
    index = 0;
     printf("Key is: \n");
      for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", k[i][j]);
        }
        printf("\n");
    }  

    getKey(0,roundkey,k);
    for(int i=0; i <44; i++)
    {
        for(int j=0; j <4; j++)
        {
            ("%hhx", roundkey[i][j]);
        }
    }
    printf("Key is: \n");
      for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", k[i][j]);
        }
        printf("\n");
    }  
    int d=0;
    for(int i=0; i <10; i++)
    {
     getKey(d,roundkey,k);
     printf("Key after round %d: \n", i);
      for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", k[i][j]);
        }
        printf("\n");
    } 
    xor(pt, k);
    printf("PT after xor %dis: \n", i);
      for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    } 
    sub(pt);
      printf("PT after subbyte %d: \n", i);
     for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    } 
    shiftrow(pt);
       printf("PT after shiftrow %d: \n", i);
      for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    } 
    if(i!=9)
    {
    mixColumn(res,pt);  
       printf("PT after mixColumn:%d \n", i);
      for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    } 
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            pt[i][j]=res[i][j];
            res[i][j]=0;
        }
        printf("\n");
    }
    }
     
    d=d+4;
        
    }
    getKey(40, roundkey, k);
    xor(pt, k);
      printf("Last round key: \n");
       for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", k[i][j]);
        }
        printf("\n");
    } 
    printf("The encrypted message is: \n");
       for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    } 
    xordecrypt(pt,k);
     printf("Dkey: \n");
       for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    }
    d=36;
    for(int i =0;  i <10; i++)
    {
    invShiftRow(pt);
    printf("PT after decrypting shiftrow function: \n");
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    }
    subInv(pt);
    printf("PT after decrypting sub-byte function: \n");
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    }
  
     getKey(d, roundkey, k);
       xor(pt, k);
       if(i!=9)
       {
        invMixColumn(res1,pt);
    printf("PT after decrypting mixColumn: \n");
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", res1[i][j]);
        }
        printf("\n");
    }
     for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            pt[i][j]=res1[i][j];
            res1[i][j]=0;
        }
        printf("\n");
    }
    }
    d = d-4;
}
 getKey(0, roundkey, k);
xordecrypt(pt,k);
xordecrypt(pt,k);
printf("the decrypted text is: \n");
for(int i=0; i < 4; i++)
    {
        for(int j=0; j <4; j++)
        {
            printf("%hhx \t", pt[i][j]);
        }
        printf("\n");
    }
    return 0;
}
