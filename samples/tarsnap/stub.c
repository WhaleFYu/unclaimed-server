#include <stdint.h>
#include <stddef.h>
#include <string.h>
/* 确定性伪随机，代替 HMAC：只为让参数生成路径跑起来 */
int crypto_hash_data(int key, const uint8_t * msg, size_t len, uint8_t * hbuf) {
    uint32_t s = 2166136261u ^ (uint32_t)key;
    for (size_t i = 0; i < len; i++) s = (s ^ msg[i]) * 16777619u;
    for (int i = 0; i < 32; i++) { s = s * 1103515245u + 12345u; hbuf[i] = (uint8_t)(s >> 16); }
    return 0;
}
