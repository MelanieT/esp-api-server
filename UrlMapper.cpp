//
// Created by Melanie on 12/11/2023.
//

#include "UrlMapper.h"
#include "HttpStatus.h"

#include <utility>
#include <functional>

Url::Url(std::string method, std::string url, std::function<void(const ApiHttpRequest& request, ApiHttpResponse& response)> handler)
{
    m_method = std::move(method);
    m_url = std::move(url);
    m_handler = std::move(handler);
}

std::string Url::method()
{
    return m_method;
}

std::string Url::url()
{
    return m_url;
}

void Url::call(const ApiHttpRequest &request, ApiHttpResponse &response)
{
    (m_handler)(request, response);
}

UrlMapper::UrlMapper()
= default;

std::list<Url> UrlMapper::m_mapping;

void UrlMapper::AddMapping(std::string method, std::string url,
                           std::function<void(const ApiHttpRequest &, ApiHttpResponse &)> handler)
{
    auto map = Url(std::move(method), std::move(url), std::move(handler));
    m_mapping.emplace_back(map);
}

void UrlMapper::Map(const ApiHttpRequest& request, ApiHttpResponse& response)
{
    for (Url mapping : m_mapping)
    {
        if (request.method() == mapping.method() && request.url() == mapping.url())
        {
            mapping.call(request, response);
            return;
        }
    }
    response.setStatusCode(HttpStatus::Code::NotFound);
}


