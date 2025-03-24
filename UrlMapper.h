//
// Created by Melanie on 12/11/2023.
//

#include <string>
#include <list>
#include <functional>
#include "ApiHttpRequest.h"
#include "ApiHttpResponse.h"

class Url
{
public:
    Url(std::string method, std::string url, std::function<void(const ApiHttpRequest& request, ApiHttpResponse& response)> handler);
    std::string method();
    std::string url();
    void call(const ApiHttpRequest &request, ApiHttpResponse& response);

private:
    std::string m_method;
    std::string m_url;
    std::function<void(const ApiHttpRequest& request, ApiHttpResponse& response)> m_handler;
};

#ifndef PICOW_WLAN_SETUP_WEBINTERFACE_URLMAPPER_H
#define PICOW_WLAN_SETUP_WEBINTERFACE_URLMAPPER_H


class UrlMapper
{
public:
    UrlMapper();
    static void AddMapping(std::string method, std::string url, std::function<void(const ApiHttpRequest& request, ApiHttpResponse& response)> handler);
    static void Map(const ApiHttpRequest& request, ApiHttpResponse& response);
private:
    static std::list<Url> m_mapping;
};


#endif //PICOW_WLAN_SETUP_WEBINTERFACE_URLMAPPER_H
