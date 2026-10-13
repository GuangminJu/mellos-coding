#pragma once

#include <utility>
#include <vector>

namespace mellos::example
{
struct Light
{
    unsigned Lumens;
};

class Scene
{
public:
    explicit Scene(std::vector<Light> InLights) : Lights(std::move(InLights)) {}

    Scene(Scene&&) = default;
    Scene& operator=(Scene&&) = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    [[nodiscard]] const std::vector<Light>& GetLights() const { return Lights; }

private:
    std::vector<Light> Lights;
};

struct Lightmap
{
    unsigned Lumens;
};
} // namespace mellos::example
