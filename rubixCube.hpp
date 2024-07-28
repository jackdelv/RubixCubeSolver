#include <vector>

// RubixColor and RubixFace are ordered to match color to face.
enum RubixColor
{
    WHITE,
    YELLOW,
    RED,
    ORANGE,
    BLUE,
    GREEN
};

enum RubixFace
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

class Face
{
    friend class RubixCube;
    public:
    Face(RubixColor c);

    RubixColor sticker(int row, int column) const;
    Face & rotateCW();
    Face & rotateCCW();

    bool operator==(const Face &other);
    unsigned equivalence(const Face &other);
    void reset();

    private:
    std::vector<std::vector<RubixColor> > stickers; // 3x3 matrix holding color locations on the face
};

// Rubix cube Class for containing the color locations and manipulating the cube
class RubixCube
{
    public:
    RubixCube();
    RubixCube(int moves);

    void print(int spacing = 0);
    bool equivalent(RubixCube &other);
    unsigned equivalence(RubixCube &other);
    RubixCube & reset() { up.reset(); down.reset(); front.reset(); back.reset(); left.reset(); right.reset(); return *this; };

    RubixCube & rotateCW(RubixFace face);
    RubixCube & rotateCCW(RubixFace face);

    private:
    Face up;
    Face down;
    Face front;
    Face back;
    Face left;
    Face right;
};

class RubixCubeSolver
{
    public:
    RubixCubeSolver();

    void solveCube(RubixCube & _mixed);

    private:
};
