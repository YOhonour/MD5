// myMD5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTATELEFT(num, n) (((num) << (n)) | ((num) >> (32-(n))))
#define FF(a1, b1, c1, d1, x, s, ac) { \
  (a1) += F ((b1), (c1), (d1)) + (x) + ac; \
  (a1) = ROTATELEFT((a1), (s)); \
  (a1) += (b1); \
}
#define GG(a1, b1, c1, d1, x, s, ac) { \
  (a1) += G ((b1), (c1), (d1)) + (x) + ac; \
  (a1) = ROTATELEFT((a1), (s)); \
  (a1) += (b1); \
}
#define HH(a1, b1, c1, d1, x, s, ac) { \
  (a1) += H ((b1), (c1), (d1)) + (x) + ac; \
  (a1) = ROTATELEFT((a1), (s)); \
  (a1) += (b1); \
}
#define II(a1, b1, c1, d1, x, s, ac) { \
  (a1) += I ((b1), (c1), (d1)) + (x) + ac; \
  (a1) = ROTATELEFT((a1), (s)); \
  (a1) += (b1); \
}



u8 data[64];//一次处理512bit
u64 length;//填充后的字节数
u64 L;//填充后可分为L组512bit(64byte)
//u32 a = 0x01234567,b=0x89ABCDEF,c=0xFEDCBA98,d=0x76543210 ;
u32 state[4] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };

/*
填充函数，
*/
void fill(u8 *sourse,u64 len) {
    u64 n = (len*8 + 64) % 512;//mod 512
    /*需要填充后的数据加上64位长度为512字节*/
    u64 need = (512 - n) % 512;//需要填充的bit数
    length = len + 8 + need / 8;
    memset(data,0,length);
    memcpy(data, sourse, len);
    data[len] = 0x80;
    u64* ptr = (u64*)data;
    ptr[length / 8 - 1] = len*8;
    L = length / 64;
}
void H_MD5(u32 M[16]) {
    u32 a = state[0];
    u32 b = state[1];
    u32 c = state[2];
    u32 d = state[3];
    //第一轮循环计算
    FF(a, b, c, d, M[0], 7, 0xd76aa478);
    FF(d, a, b, c, M[1], 12, 0xe8c7b756);
    FF(c, d, a, b, M[2], 17, 0x242070db);
    FF(b, c, d, a, M[3], 22, 0xc1bdceee);
    FF(a, b, c, d, M[4], 7, 0xf57c0faf);
    FF(d, a, b, c, M[5], 12, 0x4787c62a);
    FF(c, d, a, b, M[6], 17, 0xa8304613);
    FF(b, c, d, a, M[7], 22, 0xfd469501);
    FF(a, b, c, d, M[8], 7, 0x698098d8);
    FF(d, a, b, c, M[9], 12, 0x8b44f7af);
    FF(c, d, a, b, M[10], 17, 0xffff5bb1);
    FF(b, c, d, a, M[11], 22, 0x895cd7be);
    FF(a, b, c, d, M[12], 7, 0x6b901122);
    FF(d, a, b, c, M[13], 12, 0xfd987193);
    FF(c, d, a, b, M[14], 17, 0xa679438e);
    FF(b, c, d, a, M[15], 22, 0x49b40821);
    //第二轮循环计算
    GG(a, b, c, d, M[1], 5, 0xf61e2562);
    GG(d, a, b, c, M[6], 9, 0xc040b340);
    GG(c, d, a, b, M[11], 14, 0x265e5a51);
    GG(b, c, d, a, M[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, M[5], 5, 0xd62f105d);
    GG(d, a, b, c, M[10], 9, 0x02441453);
    GG(c, d, a, b, M[15], 14, 0xd8a1e681);
    GG(b, c, d, a, M[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, M[9], 5, 0x21e1cde6);
    GG(d, a, b, c, M[14], 9, 0xc33707d6);
    GG(c, d, a, b, M[3], 14, 0xf4d50d87);
    GG(b, c, d, a, M[8], 20, 0x455a14ed);
    GG(a, b, c, d, M[13], 5, 0xa9e3e905);
    GG(d, a, b, c, M[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, M[7], 14, 0x676f02d9);
    GG(b, c, d, a, M[12], 20, 0x8d2a4c8a);
    //第三轮循环计算
    HH(a, b, c, d, M[5], 4, 0xfffa3942);
    HH(d, a, b, c, M[8], 11, 0x8771f681);
    HH(c, d, a, b, M[11], 16, 0x6d9d6122);
    HH(b, c, d, a, M[14], 23, 0xfde5380c);
    HH(a, b, c, d, M[1], 4, 0xa4beea44);
    HH(d, a, b, c, M[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, M[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, M[10], 23, 0xbebfbc70);
    HH(a, b, c, d, M[13], 4, 0x289b7ec6);
    HH(d, a, b, c, M[0], 11, 0xeaa127fa);
    HH(c, d, a, b, M[3], 16, 0xd4ef3085);
    HH(b, c, d, a, M[6], 23, 0x04881d05);
    HH(a, b, c, d, M[9], 4, 0xd9d4d039);
    HH(d, a, b, c, M[12], 11, 0xe6db99e5);
    HH(c, d, a, b, M[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, M[2], 23, 0xc4ac5665);
    //第四轮循环计算
    II(a, b, c, d, M[0], 6, 0xf4292244);
    II(d, a, b, c, M[7], 10, 0x432aff97);
    II(c, d, a, b, M[14], 15, 0xab9423a7);
    II(b, c, d, a, M[5], 21, 0xfc93a039);
    II(a, b, c, d, M[12], 6, 0x655b59c3);
    II(d, a, b, c, M[3], 10, 0x8f0ccc92);
    II(c, d, a, b, M[10], 15, 0xffeff47d);
    II(b, c, d, a, M[1], 21, 0x85845dd1);
    II(a, b, c, d, M[8], 6, 0x6fa87e4f);
    II(d, a, b, c, M[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, M[6], 15, 0xa3014314);
    II(b, c, d, a, M[13], 21, 0x4e0811a1);
    II(a, b, c, d, M[4], 6, 0xf7537e82);
    II(d, a, b, c, M[11], 10, 0xbd3af235);
    II(c, d, a, b, M[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, M[9], 21, 0xeb86d391);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
u8 HEX_NUMBERS[16] = {
  '0', '1', '2', '3',
  '4', '5', '6', '7',
  '8', '9', 'a', 'b',
  'c', 'd', 'e', 'f'
};
void printfState() {
    for (size_t i = 0; i < 16; i++)
    {
        printf("%c", HEX_NUMBERS[((((u8*)state)[i]) >> 4) & 0x0f]);
        printf("%c", HEX_NUMBERS[((((u8*)state)[i])) & 0x0f]);
    }
    printf("\n");
}
void myMD5(u8* input, u64 length, u8* output) {
    fill(input, length);
    printfState();

    u64* ptr = (u64*)data;
    for (size_t i = 0; i < L; i++)
    {
        H_MD5((u32*)(data+i*64));
    }
    
    memcpy(output, (u8*)state, 64);
    printfState();
}
//#include"MD5.h"
int main()
{
    
    
    u8 list[] = "abcde", out[1024] = {0};
    u64* ptr = (u64*)data;
    u64* ptr2 = (u64*)list;
    myMD5(list, sizeof(list) -1, out);
    printfState();

    /*char ss[8] = { 0 };
    memcpy(ss, &i, sizeof(i));
    char block[LEN];
    for (size_t i = 0; i < dataSize; i++)
    {
        block[1] = list[i];
    }
    for (size_t i = dataSize; i < LEN - 1; i++)
    {
        block[1] = list[i];
    }*/
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
