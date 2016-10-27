#pragma once

#include <regex>
#include <string>
#include <vector>

inline bool searchByRegex(const std::wstring& targets, const std::wstring& regex, std::vector<std::wstring>& results)
{
    if (targets.empty() || regex.empty())
    {
        return false;
    }

    std::wstring s = targets;
    std::wsmatch m;
    std::wregex e(L"Content-Length: {[0-9]+}");

    while (std::regex_search(targets, m, e))
    {
        results.emplace_back(m.str());
        s = m.suffix().str();
    }

    return results.size() > 0;
}

inline unsigned int getContentLength(const std::wstring& mResponseHeader)
{
    if (mResponseHeader.empty())
    {
        return 0;
    }

    std::wstring content_length = L"Content-Length: ";

    auto position = mResponseHeader.find(content_length);
    if (position != std::wstring::npos)
    {
        auto crlf = mResponseHeader.find(0x0a, position);
        if (crlf != std::wstring::npos)
        {
            auto offset = position + content_length.length();

            auto length = mResponseHeader.substr(offset, crlf - offset);
            return std::stoi(length);
        }
    }

    return 0;
}