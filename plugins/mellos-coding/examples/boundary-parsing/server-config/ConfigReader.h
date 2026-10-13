#pragma once

#include "Config.h"

#include <cstddef>
#include <optional>
#include <string_view>
#include <variant>

namespace mellos::example
{
class ConfigReader
{
public:
    enum class Error
    {
        MalformedLine,
        UnknownKey,
        BadHost,
        BadPort,
        BadToken,
    };

    ConfigReader() = delete;

    [[nodiscard]] static constexpr std::variant<Config, Error> Parse(std::string_view Text)
    {
        std::optional<Address> Host;
        std::optional<Port> Listen;
        std::optional<Token> Admin;

        while (!Text.empty())
        {
            const std::string_view Line = Text.substr(0, Text.find('\n'));
            Text.remove_prefix(Line.size() == Text.size() ? Line.size() : Line.size() + 1);

            const std::size_t Equals = Line.find('=');
            if (Equals == std::string_view::npos)
                return Error::MalformedLine;
            const std::string_view Key = Line.substr(0, Equals);
            const std::string_view Value = Line.substr(Equals + 1);

            if (Key == "host")
            {
                Host = Address::Parse(Value);
                if (!Host)
                    return Error::BadHost;
            }
            else if (Key == "port")
            {
                Listen = Port::Parse(Value);
                if (!Listen)
                    return Error::BadPort;
            }
            else if (Key == "token")
            {
                Admin = Token::Parse(Value);
                if (!Admin)
                    return Error::BadToken;
            }
            else
                return Error::UnknownKey;
        }

        if (!Host)
            return Error::BadHost;
        if (!Listen)
            return Error::BadPort;
        if (!Admin)
            return Error::BadToken;
        return Config{*Host, *Listen, *Admin};
    }
};
} // namespace mellos::example
