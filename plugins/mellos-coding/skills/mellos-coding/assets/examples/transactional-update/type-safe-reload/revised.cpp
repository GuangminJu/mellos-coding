#include <iostream>
#include <optional>
#include <string>
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

private:
    std::string_view Value;
};

class Resource
{
public:
    // Verify + Prepare：失败返回空，成功时在局部完整构造，不触碰任何持有者
    [[nodiscard]] static std::optional<Resource> Load(NonEmptyString Name)
    {
        if (Name.Get() == "Invalid")
            return std::nullopt;
        return Resource(std::string(Name.Get()));
    }

    std::string_view GetName() const noexcept { return Name; }

private:
    explicit Resource(std::string InName) : Name(std::move(InName)) {}

    std::string Name;
};

class Object
{
public:
    explicit Object(Resource Initial) noexcept : Current(std::move(Initial)) {}

    // Commit：参数类型证明 Verify 与 Prepare 已完成
    void Reload(Resource Next) noexcept { std::swap(Current, Next); }

    void Print() const { std::cout << "Current Resource: " << Current.GetName() << '\n'; }

private:
    Resource Current;
};

int main()
{
    std::optional<Resource> Initial = Resource::Load("Resource_A");
    if (!Initial)
        return 1;

    Object Obj{std::move(*Initial)};
    Obj.Print();

    if (std::optional<Resource> Next = Resource::Load("Resource_B"))
        Obj.Reload(std::move(*Next));
    Obj.Print();

    // 编译失败：Resource::Load("");
    if (std::optional<Resource> Next = Resource::Load("Invalid"))
        Obj.Reload(std::move(*Next));
    Obj.Print();
}
