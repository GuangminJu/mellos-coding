#include "Baker.h"

#include <future>
#include <iostream>

using namespace mellos::example;

int main()
{
    std::future<Lightmap> Pending = Baker::BakeOnWorkerThread(Scene{{Light{300}, Light{500}}});

    std::cout << "main thread: loading sounds while the bake runs\n";

    const Lightmap Baked = Pending.get();
    std::cout << "worker thread delivered " << Baked.Lumens << " lumens\n";
}
