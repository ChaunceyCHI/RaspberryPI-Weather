
交叉编译环境：Ubuntu 20.04 (WSL)

## 步骤 1：安装交叉编译工具链
### 1.1 安装交叉编译环境

1. 打开 Microsoft Store 搜索 Ubuntu20.04 LTS 并安装；

2. 打开 WSL Ubuntu 终端，更新并安装必要的工具：
```bash
sudo apt update 
sudo apt upgrade
```

### 1.2 安装交叉编译工具链

在 WSL Ubuntu 中，安装适用于 Raspberry Pi 4B 的交叉编译工具链。

1. 安装 ARM 交叉编译工具链：

```bash
sudo apt-get install g++-aarch64-linux-gnu
```

2. 安装 CMake：

```bash
sudo apt install cmake
```

## 步骤 2：编译 aarch64 的 zlib

### 2.1 从 zlib 的官方网站下载最新版本

```shell
cd 
wget https://zlib.net/zlib-1.3.1.tar.gz
tar -xzvf zlib-1.3.1.tar.gz
cd zlib-1.3.1
```

### 2.2 配置并编译 zlib

为 `aarch64` 进行编译（注意编译为**静态库**）：

```shell
CC=/usr/bin/aarch64-linux-gnu-gcc CXX=/usr/bin/aarch64-linux-gnu-g++ ./configure --static --prefix=~/zlib
make
make install
```

这会将 OpenSSL 安装到 `/home/[用户名]/openssl`。

## 步骤 3：编译 aarch64 的 OpenSSL

### 3.1  从 OpenSSL 的官方网站下载最新版本：

```bash
wget https://www.openssl.org/source/openssl-3.3.2.tar.gz 
tar -xzvf openssl-3.3.2.tar.gz 
cd openssl-3.3.2
```

### 3.2 配置并编译 OpenSSL

为 `aarch64` 进行编译（**注意使用绝对路径**）：

```bash
CC=/usr/bin/aarch64-linux-gnu-gcc CXX=/usr/bin/aarch64-linux-gnu-g++ ./Configure linux-aarch64 --prefix=/home/[用户名]/openssl
make  
make install
```

这会将 OpenSSL 安装到 `/home/[用户名]/openssl`。

## 步骤 4：编译 aarch64 的 libcurl

### 4.1 从 libcurl 的官方网站下载最新版本

```bash
cd 
wget https://curl.se/download/curl-8.10.1.tar.gz
tar -zxvf curl-8.10.1.tar.gz
cd curl-8.10.1
```

### 4.2 配置并编译libcurl

为`aarch64`进行编译:

```bash
./configure --host=aarch64-linux-gnu --prefix=/home/[用户名]/curl --with-zlib=/home/[用户名]/zlib --with-openssl=/home/[用户名]/openssl --without-libpsl --disable-shared 
make
make install
```

这会将 libcurl安装到 `/home/[用户名]/curl。
