#include <iostream>
#include <optional>
#include <set>
#include <string_view>
#include <utility>

class NonEmptyString
{
public:
    template <std::size_t N>
    consteval NonEmptyString(const char (&Str)[N])
        : Value(Str, N - 1)
    {
        static_assert(N > 1, "NonEmptyString cannot be empty.");
    }

    std::string_view Get() const noexcept
    {
        return Value;
    }

    bool operator<(NonEmptyString Other) const noexcept { return Value < Other.Value; }

private:
    std::string_view Value;
};

// Stands in for real storage: which resources exist is decided outside the program.
class Storage
{
public:
    explicit Storage(std::set<NonEmptyString> InAvailable) : Available(std::move(InAvailable)) {}

    [[nodiscard]] bool Contains(NonEmptyString Name) const { return Available.count(Name) > 0; }

private:
    std::set<NonEmptyString> Available;
};

class Resource
{
public:
    [[nodiscard]] static std::optional<Resource> Load(const Storage& Disk, NonEmptyString Name)
    {
        if (!Disk.Contains(Name))
            return std::nullopt;
        return Resource(Name);
    }

    NonEmptyString GetName() const noexcept { return Name; }

private:
    explicit Resource(NonEmptyString InName) : Name(InName) {}

    NonEmptyString Name;
};

class Object
{
public:
    explicit Object(Resource Initial) noexcept : Current(std::move(Initial)) {}

    void Reload(Resource Next) noexcept { std::swap(Current, Next); }

    void Print() const { std::cout << "Current Resource: " << Current.GetName().Get() << '\n'; }

private:
    Resource Current;
};

int main()
{
    const Storage Disk{{"Resource_A", "Resource_B"}};

    std::optional<Resource> Initial = Resource::Load(Disk, "Resource_A");
    if (!Initial)
        return 1;

    Object Obj{std::move(*Initial)};
    Obj.Print();

    if (std::optional<Resource> Next = Resource::Load(Disk, "Resource_B"))
        Obj.Reload(std::move(*Next));
    Obj.Print();

    // Compile error: Resource::Load(Disk, "");
    if (std::optional<Resource> Next = Resource::Load(Disk, "Missing"))
        Obj.Reload(std::move(*Next));
    Obj.Print();
}
