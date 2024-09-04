# This installs the targets mbedtls mbedx509 mbedcrypto everest p256m

# Configurable variables
option(ENABLE_TESTING "Enable MbedTLS tests" OFF)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE OPT_IN) # only try find_package if FIND_PACKAGE_ARGS is set

message(STATUS "[MbedTLS] fetching package...")
include(FetchContent)
fetchcontent_declare(
  MbedTLS
  URL https://github.com/Mbed-TLS/mbedtls/archive/refs/tags/v3.6.0.zip
  URL_HASH
    SHA256=749c8a3b240923bcb30408ac93f6bf4d730514b71053605fa690673fd4437273 # hash for v3.6.0 .zip release source code
  # FIND_PACKAGE_ARGS QUIET CONFIG
)
fetchcontent_makeavailable(MbedTLS)
install(
  TARGETS mbedtls mbedx509 mbedcrypto everest p256m
)
