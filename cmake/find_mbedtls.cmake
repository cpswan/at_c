# This installs the targets mbedtls mbedx509 mbedcrypto everest p256m

# Configurable variables
option(ENABLE_TESTING "Enable MbedTLS tests" OFF)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE OPT_IN) # only try find_package if FIND_PACKAGE_ARGS is set

message(STATUS "[MbedTLS] fetching package...")
include(FetchContent)
fetchcontent_declare(
  MbedTLS
  URL https://github.com/Mbed-TLS/mbedtls/archive/refs/tags/v3.6.1.zip
  URL_HASH
    SHA256=bca632585454dac63de0c425d251671594c7f2b3c86a56fc3bade51b70d160e9 # hash for v3.6.1 .zip release source code
  # FIND_PACKAGE_ARGS QUIET CONFIG
)
fetchcontent_makeavailable(MbedTLS)
install(
  TARGETS mbedtls mbedx509 mbedcrypto everest p256m
)
