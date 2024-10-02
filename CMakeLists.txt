cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

# 指定目标系统类型
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# 指定交叉编译的编译器
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# 设置交叉编译工具链的根目录
set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)

project(HttpsGetTest)

# 设置 curl 安装路径
set(CURL_ROOT_DIR /home/chi/curl)
set(CURL_LIBRARY /home/chi/curl/lib)
set(CURL_INCLUDE_DIR /home/chi/curl/include)
set(ZLIB_ROOT_DIR /home/chi/zlib)
set(ZLIB_LIBRARY /home/chi/zlib/lib)
set(ZLIB_INCLUDE_DIR /home/chi/zlib/include)
set(OPENSSL_ROOT_DIR /home/chi/openssl)
# 查找 curl
find_package(CURL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)


include_directories(${CURL_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})

# 添加源代码
add_executable(HttpsGetTest test.cpp)
target_link_libraries(HttpsGetTest 
${CURL_LIBRARIES}/libcurl.a 
${ZLIB_LIBRARIES}/libz.a 
${OPENSSL_LIBRARIES} 
pthread
)