# This installs the targets mbedtls mbedx509 mbedcrypto everest p256m

# Configurable variables
option(ENABLE_TESTING "Enable MbedTLS tests" OFF)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE OPT_IN) # only try find_package if FIND_PACKAGE_ARGS is set

message(STATUS "[MbedTLS] fetching package...")
include(FetchContent)
fetchcontent_declare(
  MbedTLS
  URL https://github.com/Mbed-TLS/mbedtls/archive/refs/tags/v3.5.2.zip
  URL_HASH
    SHA256=55c1525e7d5de18b84a1d1e5540950b4a3bac70e02889cf309919b2877cba63b # hash for v3.5.2 .zip release source code
  # FIND_PACKAGE_ARGS QUIET CONFIG
)
fetchcontent_makeavailable(MbedTLS)
install(
  TARGETS mbedtls mbedx509 mbedcrypto everest p256m
)
