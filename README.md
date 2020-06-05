## RC4

```sh
C++实现了RC4加密，实际上使用的是C语言的编程思想。
```

主要分为两个部分`密钥初始化`、`执行加密`，生成密钥后直接与待加密数据按字节异或， 由于[异或运算](https://zh.wikipedia.org/wiki/异或)的[对合性](https://zh.wikipedia.org/wiki/對合)，RC4加密解密使用同一套算法。 

