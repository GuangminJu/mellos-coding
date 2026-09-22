#include <iostream>
#include <memory>
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

struct Resource
{
    explicit Resource(std::string InName)
        : Name(std::move(InName))
    {
        std::cout << "Create Resource: " << Name << '\n';
    }

    ~Resource()
    {
        std::cout << "Destroy Resource: " << Name << '\n';
    }

    std::string Name;
};

class Object
{
public:
    bool Reload(NonEmptyString Name)
    {
        // --------------------------------
        // 1. Verify
        // --------------------------------
        if (!CanLoad(Name))
            return false;

        // --------------------------------
        // 2. Prepare
        // --------------------------------
        auto NewResource =
            std::make_unique<Resource>(
                std::string(Name.Get())
            );

        // --------------------------------
        // 3. Commit
        // --------------------------------
        ResourcePtr.swap(NewResource);
        return true;
    }


    void Print() const
    {
        if (ResourcePtr)
        {
            std::cout
                << "Current Resource: "
                << ResourcePtr->Name
                << '\n';
        }
        else
        {
            std::cout << "No Resource\n";
        }
    }

private:

    bool CanLoad(NonEmptyString Name) const
    {
        // 这里可以进行运行时检查
        // 比如文件是否存在、资源是否合法等
        return Name.Get() != "Invalid";
    }

private:

    std::unique_ptr<Resource> ResourcePtr;
};

int main(int argc, char* argv[])
{
    Object Obj;

    Obj.Reload("Resource_A");
    Obj.Print();

    Obj.Reload("Resource_B");
    Obj.Print();

    // -----------------------------
    // 编译失败
    // -----------------------------
    // Obj.Reload("");
    // -----------------------------
    // Verify 失败
    // 原来的 Resource_B 不受影响
    // -----------------------------

    Obj.Reload("Invalid");
    Obj.Print();
    
    return 0;
}