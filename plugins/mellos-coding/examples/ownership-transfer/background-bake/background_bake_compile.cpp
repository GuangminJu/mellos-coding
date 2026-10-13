#include "Baker.h"

#include <future>
#include <type_traits>
#include <utility>

using namespace mellos::example;

static_assert(!std::is_copy_constructible_v<Scene> && std::is_move_constructible_v<Scene>,
              "A scene has one owner at a time, so two threads can never share it");
static_assert(std::is_same_v<decltype(Baker::BakeOnWorkerThread(std::declval<Scene>())), std::future<Lightmap>>,
              "The worker hands back a value, never a reference into its own state");
static_assert(!std::is_copy_constructible_v<std::future<Lightmap>>, "A pending result is collected exactly once");
