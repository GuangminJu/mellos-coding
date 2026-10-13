#include "Units.h"

namespace mellos::example
{
class Mover
{
public:
    Mover(Position Start, Position InTarget, Speed InRate) : Here(Start), Target(InTarget), Rate(InRate) {}
    Mover(const Mover&) = delete;

    void Update(Millis Dt)
    {
        const int Reach = Rate.Over(Dt);
        const int Gap = Here.DistanceTo(Target);
        if (Gap > Reach)
            Here = Here.MovedBy(Reach);
        else if (Gap < -Reach)
            Here = Here.MovedBy(-Reach);
        else
            Here = Target;
    }

    [[nodiscard]] bool HasArrived() const { return Here == Target; }
    [[nodiscard]] Position GetPosition() const { return Here; }

private:
    Position Here;
    Position Target;
    Speed Rate;
};

// Compile error: Position Preview(const Mover& Unit) { Mover Copy = Unit; Copy.Update(Millis(3000)); return Copy.GetPosition(); }
} // namespace mellos::example
