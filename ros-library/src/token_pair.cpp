#include "ros-library/token_pair.h"

#include <sstream>

#include "ros-library/api.h"

#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <nlohmann/json.hpp>

namespace API {
    TokenPair::TokenPair(const std::string& access, const std::string& refresh)
        : accessToken(access), refreshToken(refresh)
    {}

    bool TokenPair::refresh() {
        try {
            // Form a token refresh request
            cURLpp::Easy login_request;
            login_request.setOpt(cURLpp::options::Url(TOKEN_REFRESH_URL));

            // Request body
            const nlohmann::json body = {
                {"refresh", this->getRefresh()},
            };

            // Informing that we are using JSON
            login_request.setOpt(cURLpp::options::HttpHeader({"Content-Type: application/json"}));
            // Adding the body and its size to request
            login_request.setOpt(curlpp::options::PostFields(body.dump()));
            login_request.setOpt(curlpp::options::PostFieldSize(static_cast<long>(body.dump().length())));

            // Performing the request
            login_request.perform();

            // Retrieving the response and parsing it as JSON
            std::ostringstream responseStream;
            responseStream << login_request;

            // Parsing the response
            const nlohmann::json response = nlohmann::json::parse(responseStream.str());

            // Update access token
            if (response.contains("access")) {
                this->setAccess(response.at("access").get<std::string>());
                return true;
            }

            // Fail
            return false;
        } catch (cURLpp::RuntimeError&) {
            return false;
        } catch (cURLpp::LogicError&) {
            return false;
        }
    }

    std::string TokenPair::getAccess() const {
        std::lock_guard lock(this->mutex);
        return this->accessToken;
    }

    void TokenPair::setAccess(const std::string& access) {
        std::lock_guard lock(this->mutex);
        this->accessToken = access;
    }

    std::string TokenPair::getRefresh() const {
        std::lock_guard lock(this->mutex);
        return this->refreshToken;
    }

    void TokenPair::setRefresh(const std::string& refresh) {
        std::lock_guard lock(this->mutex);
        this->refreshToken = refresh;
    }

} // API