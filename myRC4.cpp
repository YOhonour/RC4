// myRC4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
typedef unsigned char u8;
typedef unsigned int u32;
#define mod %
#define swap(a,b) a=a+b;b=a-b;a=a-b;
u8 S[256];
u8 T[256];
//初始化S、T密钥种子
void rc4Init(u8 *rowKey,u32 length) {
	//装载S、T
	for (u32 i = 0; i < sizeof(S); i++) {
		S[i] = i;
		T[i] = rowKey[i % length];
	}
	u32 i, j;
	u8 temp;
	j = 0;
	//随机化S、T
	for (i = 0; i < 256; i++) {
		j = (j + S[i] + T[i]) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}
}
//加密 第一个参数为数据序列，第二个参数为数据长度(字节数)
void encode(u8 *data,u32 datalength) {
	int i, j,t,k,r=0;
	i = 0;
	j = 0;
	while (datalength--) {//每一个数据生成一个密钥
		i = (i + 1) mod 256;
		j = (j + S[i]) mod 256;
		swap(S[i], S[j]);
		t = (S[i] + S[j]) mod 256;
		k = S[t]; //这里的K就是当前生成的一个秘钥流中的一位
		//可以直接在这里进行加密，当然也可以将密钥流保存在数组中，最后进行异或 
		data[r] = data[r] ^ k; //进行加密 
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
int get_file_size(FILE* file_handle) {
	//获取当前读取文件的位置 进行保存
	unsigned int current_read_position = ftell(file_handle);
	int file_size;
	fseek(file_handle, 0, SEEK_END);
	//获取文件的大小
	file_size = ftell(file_handle);
	//恢复文件原来读取的位置
	fseek(file_handle, current_read_position, SEEK_SET);
	return file_size;
}
void encodeFile(char* soursePath, char* keyPath, char* desPath) {
	
	FILE* sourse, * KEY, * DES;
	if ((sourse = fopen(soursePath, "rb+")) == NULL ||
		(KEY = fopen(keyPath, "rb+")) == NULL ||
		(DES = fopen(desPath, "wb+")) == NULL)
	{
		printf("FILE OPEN ERROR");
		exit(0);
	}
	int keyLength = get_file_size(KEY);
	int sourseLength = get_file_size(sourse);
	printf("源文件大小：%d字节\n", sourseLength);
	u8*sourseBuffer = (u8*)malloc(sourseLength);
	u8 *keyBuffer = (u8*)malloc(keyLength);

	fread(keyBuffer, sizeof(char), keyLength, KEY);
	fread(sourseBuffer, sizeof(char), sourseLength, sourse);
	
	rc4Init(keyBuffer, keyLength);
	encode(sourseBuffer, sourseLength);

	fwrite(sourseBuffer, sizeof(char), sourseLength, DES);
	fclose(KEY);
	fclose(sourse);
	fclose(DES);
	free(sourseBuffer);
	free(keyBuffer);

}

int main()
{
	//char soursePath[] = "C:\\Users\\Lenovo\\source\\repos\\myRC4\\myRC4\\data\\sourse.txt";
	char soursePath[] = "C:\\Users\\Lenovo\\source\\repos\\myRC4\\myRC4\\data\\1.png";
	char keyPath[] = "C:\\Users\\Lenovo\\source\\repos\\myRC4\\myRC4\\data\\key.txt";
	char encryptted[] = "C:\\Users\\Lenovo\\source\\repos\\myRC4\\myRC4\\data\\encryptted.png";
	char myresult[] = "C:\\Users\\Lenovo\\source\\repos\\myRC4\\myRC4\\data\\decryptted.png";
	printf("开始第一次文件加密\n");
	encodeFile(soursePath, keyPath, encryptted);
	printf("开始第二次文件加密\n");
	encodeFile(encryptted, keyPath, myresult);

	/*u8 rowKey[] = "ffffff";
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
	ptintfString(M, sizeof(M));*/
	
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
