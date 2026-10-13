#include "ConfigReader.h"

#include <ostream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

using namespace mellos::example;

constexpr bool ValidTextBecomesTypedValues()
{
    const std::variant<Config, ConfigReader::Error> Parsed = ConfigReader::Parse("host=a\nport=1\ntoken=t\n");
    const Config* Settings = std::get_if<Config>(&Parsed);
    return Settings && Settings->Host.Get() == "a" && Settings->Listen.Get() == 1 && Settings->Admin.Matches("t");
}

constexpr bool FailsWith(std::string_view Text, ConfigReader::Error Expected)
{
    const std::variant<Config, ConfigReader::Error> Parsed = ConfigReader::Parse(Text);
    const ConfigReader::Error* Problem = std::get_if<ConfigReader::Error>(&Parsed);
    return Problem && *Problem == Expected;
}

template <class T, class = void>
struct HasTextForm : std::false_type {};

template <class T>
struct HasTextForm<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>> : std::true_type {};

static_assert(ValidTextBecomesTypedValues(), "Valid text becomes typed values in one pass");
static_assert(FailsWith("host=a\nport=1", ConfigReader::Error::BadToken), "A missing key is reported by name");
static_assert(FailsWith("host=a\nport=0\ntoken=t", ConfigReader::Error::BadPort), "Port 0 is rejected at the boundary");
static_assert(FailsWith("host=a\nport=65536\ntoken=t", ConfigReader::Error::BadPort), "Port above 65535 is rejected");
static_assert(FailsWith("host=a\nport=1\ntoken=t\ncolour=red", ConfigReader::Error::UnknownKey), "Unknown keys are rejected");
static_assert(FailsWith("host", ConfigReader::Error::MalformedLine), "A line without = is rejected");
static_assert(!HasTextForm<Token>::value, "A secret has no text form, so it cannot be logged");
static_assert(!std::is_default_constructible_v<Port> && !std::is_default_constructible_v<Token>,
              "Only parsing creates a typed value");
