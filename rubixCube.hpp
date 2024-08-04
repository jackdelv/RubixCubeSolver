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

    Face & queryFace(RubixFace face);

    private:
    Face up;
    Face down;
    Face front;
    Face back;
    Face left;
    Face right;
};

using Edge = std::pair<RubixFace,RubixFace>;
using Corner = std::vector<RubixFace>;

class RubixCubeSolver
{
    public:
    RubixCubeSolver();
    
    RubixCube solveCube(RubixCube & _mixedCube);

    //Functions for solving subsections of the cube
    void solveCross();
    void solveTopCorners();
    void solveMiddleLayer();
    void solveBottomCross();
    void solveBottomFace();
    void solveThirdLayer();

    // Algoriths for manipulating specific pieces
    void topCornerTopUp(RubixFace face, bool reverse=false);
    void topCornerTopDown(RubixFace face);
    void middleEdge(RubixFace face, bool reverse=false);
    void bottomCross(RubixFace face);
    void bottomCorners(RubixFace face);
    void bottomSides(RubixFace face, bool reverse=false);
    void bottomSideCenters(RubixFace face, bool reverse=false);
    void rotateWhiteCornerOnBottom(Corner & corner);
    void rotateMiddleEdgeOnBottom(Edge & edge);

    // Solve status checking functions
    bool checkLayer(int row);
    bool isCrossSolved();
    bool isTopCornersSolved();
    bool isUpSolved();
    bool isFirstLayerSolved();
    bool isSecondLayerSolved();
    bool isBottomCrossSolved();
    bool isBottomSolved();
    bool isthirdLayerSolved();
    bool isSolved();

    // Functions for locating pieces on the cube
    Edge findWhiteEdge();
    Edge findMiddleEdge();
    Corner findWhiteCorner();
    RubixFace findBottomCrossFace();

    private:
    RubixCubeSolver & rotateCW(RubixFace face);
    RubixCubeSolver & rotateCCW(RubixFace face);

    private:
    int moves = 0;

    RubixCube solvedCube;
    RubixCube mixedCube;
};
