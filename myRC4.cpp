// myRC4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
typedef unsigned char u8;
typedef unsigned int u32;
#define mod %
#define swap(a,b) a=a+b;b=a-b;a=a-b;
u8 S[256];
u8 T[256];
void rc4Init(u8 *rowKey,u32 length) {
	for (u32 i = 0; i < sizeof(S); i++) {
		S[i] = i;
		T[i] = rowKey[i % length];
	}
	u32 i, j;
	u8 temp;
	j = 0;
	for (i = 0; i < 256; i++) {
		j = (j + S[i] + T[i]) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}
}
void encode(u8 *data,u32 datalength) {
	int i, j,t,k,r=0;
	i = 0;
	j = 0;
	while (datalength--) {//相当于执行1024次，这样生成的秘钥流也是1024个字节
		i = (i + 1) mod 256;
		j = (j + S[i]) mod 256;
		swap(S[i], S[j]);
		t = (S[i] + S[j]) mod 256;
		k = S[t]; //这里的K就是当前生成的一个秘钥流中的一位
			//可以直接在这里进行加密，当然也可以将密钥流保存在数组中，最后进行异或就ok
		data[r] = data[r] ^ k; //进行加密，"^"是异或运算符	
		r++;
	}
}
void ptintfString(u8 *ptr,u32 length) {
	for (size_t i = 0; i < length; i++)
	{
		printf("%c", ptr[i]);
	}
	printf("\n");
 }
int main()
{
	u8 rowKey[] = "ffffff";
	u8 M[] = "123456789",C[10];
	printf("使用的密钥为：%s\n", rowKey);

	rc4Init(rowKey,sizeof(rowKey));
	
	printf("原文为：");
	ptintfString(M, sizeof(M));
	encode(M, sizeof(M));
	printf("密文为：");
	ptintfString(M, sizeof(M));
	rc4Init(rowKey, sizeof(rowKey));
	encode(M, sizeof(M));
	printf("解密后：");
	ptintfString(M, sizeof(M));
	
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
