#pragma once

#include "Config.h"

#include <ostream>
#include <string_view>

namespace mellos::example
{
class Server
{
public:
    enum class Access
    {
        Granted,
        Denied,
    };

    Server(const Config& InSettings, std::ostream& Log) : Settings(InSettings)
    {
        Log << "listening on " << Settings.Host.Get() << ':' << Settings.Listen.Get() << '\n';
    }

    [[nodiscard]] Access Authorize(std::string_view Presented) const
    {
        return Settings.Admin.Matches(Presented) ? Access::Granted : Access::Denied;
    }

private:
    const Config& Settings;
};
} // namespace mellos::example
