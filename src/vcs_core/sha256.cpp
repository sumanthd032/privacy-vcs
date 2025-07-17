#include "vcs_core/sha256.hpp"
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace vcs_core {

std::string sha256(const std::string& input) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (!context) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    if (!EVP_DigestInit_ex(context, EVP_sha256(), nullptr)) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to initialize SHA256");
    }

    if (!EVP_DigestUpdate(context, input.c_str(), input.size())) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to update SHA256");
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;
    if (!EVP_DigestFinal_ex(context, hash, &length)) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to finalize SHA256");
    }

    EVP_MD_CTX_free(context);

    std::stringstream ss;
    for (unsigned int i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

} // namespace vcs_core