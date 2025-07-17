#ifndef SHA256_HPP
#define SHA256_HPP

#include <string>
#include <openssl/evp.h>

namespace vcs_core {

std::string sha256(const std::string& input);

} // namespace vcs_core

#endif // SHA256_HPP