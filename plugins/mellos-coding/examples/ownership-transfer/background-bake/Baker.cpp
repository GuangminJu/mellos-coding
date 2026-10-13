#include "Baker.h"

#include <utility>

namespace mellos::example
{
Lightmap Baker::Bake(Scene Source)
{
    unsigned Lumens = 0;
    for (const Light& Each : Source.GetLights())
        Lumens += Each.Lumens;
    return Lightmap{Lumens};
}

std::future<Lightmap> Baker::BakeOnWorkerThread(Scene Source)
{
    return std::async(std::launch::async, &Baker::Bake, std::move(Source));
}
} // namespace mellos::example
