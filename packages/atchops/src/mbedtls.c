#include "atchops/mbedtls.h"
#include "atchops/sha.h"

const mbedtls_md_type_t atchops_mbedtls_md_map[] = {
    [ATCHOPS_MD_NONE] = MBEDTLS_MD_NONE,           [ATCHOPS_MD_MD5] = MBEDTLS_MD_MD5,
    [ATCHOPS_MD_RIPEMD160] = MBEDTLS_MD_RIPEMD160, [ATCHOPS_MD_SHA1] = MBEDTLS_MD_SHA1,
    [ATCHOPS_MD_SHA224] = MBEDTLS_MD_SHA224,       [ATCHOPS_MD_SHA256] = MBEDTLS_MD_SHA256,
    [ATCHOPS_MD_SHA384] = MBEDTLS_MD_SHA384,       [ATCHOPS_MD_SHA512] = MBEDTLS_MD_SHA512,
    [ATCHOPS_MD_SHA3_224] = MBEDTLS_MD_SHA3_224,   [ATCHOPS_MD_SHA3_256] = MBEDTLS_MD_SHA3_256,
    [ATCHOPS_MD_SHA3_384] = MBEDTLS_MD_SHA3_384,   [ATCHOPS_MD_SHA3_512] = MBEDTLS_MD_SHA3_512,
};