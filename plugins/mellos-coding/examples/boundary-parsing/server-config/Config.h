#pragma once

#include "Address.h"
#include "Port.h"
#include "Token.h"

namespace mellos::example
{
struct Config
{
    Address Host;
    Port Listen;
    Token Admin;
};
} // namespace mellos::example
