#include "ConfigReader.h"
#include "Server.h"

#include <iostream>
#include <string_view>
#include <variant>

using namespace mellos::example;

// Stands in for the real config file: its values are decided outside the program.
constexpr std::string_view ConfigFile = "host=play.example\nport=7777\ntoken=letmein";

static void Report(ConfigReader::Error Problem, std::ostream& Log)
{
    switch (Problem)
    {
    case ConfigReader::Error::MalformedLine:
        Log << "config: a line is not key=value\n";
        break;
    case ConfigReader::Error::UnknownKey:
        Log << "config: unknown key\n";
        break;
    case ConfigReader::Error::BadHost:
        Log << "config: host is missing or empty\n";
        break;
    case ConfigReader::Error::BadPort:
        Log << "config: port is missing or not 1-65535\n";
        break;
    case ConfigReader::Error::BadToken:
        Log << "config: token is missing or empty\n";
        break;
    }
}

int main()
{
    const std::variant<Config, ConfigReader::Error> Parsed = ConfigReader::Parse(ConfigFile);
    if (const ConfigReader::Error* Problem = std::get_if<ConfigReader::Error>(&Parsed))
    {
        Report(*Problem, std::cerr);
        return 1;
    }
    const Config& Settings = std::get<Config>(Parsed);

    const Server Game{Settings, std::cout};
    std::cout << "guest token denied: " << (Game.Authorize("guest") == Server::Access::Denied) << '\n';
    std::cout << "admin token granted: " << (Game.Authorize("letmein") == Server::Access::Granted) << '\n';
    // Compile error: std::cout << Settings.Admin;
}
