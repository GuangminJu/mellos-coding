#pragma once

#include "Lightmap.h"

#include <future>

namespace mellos::example
{
class Baker
{
public:
    Baker() = delete;

    [[nodiscard]] static Lightmap Bake(Scene Source);
    [[nodiscard]] static std::future<Lightmap> BakeOnWorkerThread(Scene Source);
};
} // namespace mellos::example
