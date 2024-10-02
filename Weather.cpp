#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION
#define CHUNK 65535

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "zlib.h"



const std::string KEY{ "-------------------------" };
const std::string LOCATION{ "------------" };
const std::string GeneralURL{ "https://devapi.qweather.com/v7/weather/now?" };
const std::string url { GeneralURL + "location=" + LOCATION + "&key=" + KEY };


 /* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */

/* 回调函数，用于接收 CURL 响应数据 */
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)userp;
    buffer->insert(buffer->end(), (unsigned char*)contents, (unsigned char*)contents + totalSize);
    return totalSize;
}

/* 使用 zlib 解压缩数据 */
std::string decompress(const std::vector<unsigned char>& compressed_data) {
    std::string decompressed_data;
    z_stream strm = {0};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = compressed_data.size();
    strm.next_in = (Bytef*)compressed_data.data();

    // 初始化解压缩
    if (inflateInit2(&strm, 16 + MAX_WBITS) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib for decompression.");
    }

    char buffer[CHUNK];
    int ret;
    do {
        strm.avail_out = CHUNK;
        strm.next_out = reinterpret_cast<unsigned char*>(buffer);
        ret = inflate(&strm, Z_NO_FLUSH);

        if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            inflateEnd(&strm);
            throw std::runtime_error("Decompression failed.");
        }

        decompressed_data.append(buffer, CHUNK - strm.avail_out);
    } while (ret != Z_STREAM_END);

    // 清理
    inflateEnd(&strm);
    return decompressed_data;
}



int main(void)
{
  CURL *curl;
  CURLcode res;
  std::vector<unsigned char> response_data;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    std::cout << url << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who is not using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
 
#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you are connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl refuses to connect. You can skip this
     * check, but it makes the connection insecure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
 
   // 设置回调函数接收数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
 
    /* Perform the request, res gets the return code */
    res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            try {
                // 解压缩接收到的数据
                std::string decompressed_json = decompress(response_data);
                std::cout << "解压后的 JSON 数据:\n" << decompressed_json << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "解压失败: " << e.what() << std::endl;
            }
        }

        /* 清理 */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}