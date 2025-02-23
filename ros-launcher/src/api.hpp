#ifndef API_SETTINGS_HPP
#define API_SETTINGS_HPP

#include <string>

namespace API {
    // Base URL for API access
    const std::string API_BASE_URL = "3.78.71.239:8000/api/auth/";

    // URL for token obtain (login)
    const std::string TOKEN_OBTAIN_URL = API_BASE_URL + "token/get/";

    // URL for token refresh
    const std::string TOKEN_REFRESH_URL = API_BASE_URL + "token/refresh/";

    struct TokenPair {
        std::string access;
        std::string refresh;
    };
}

#endif //API_SETTINGS_HPP
