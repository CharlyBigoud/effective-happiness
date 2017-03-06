#include <iostream>
#include <array>
#include <cmath>

using P3D = std::array<float,3>;
using P2D = std::array<float,2>;

P2D index_to_colRow(const size_t matrix_width, const int index)
{
    // if( matrix_width <= 0 )
        // throw(std::out_of_range( std::cerr << "index_to_colRow: the matrix width has not a good value (" << matrix_width << ")." << std::endl;) );

    P2D indexes;

    indexes[1] = index / matrix_width;
    indexes[0] = index - matrix_width*indexes[1];

    return indexes;
}

struct GridMesh
{
    int width, height;  //the size of the grid
    float edge_size;    //the mean dsitance between each node
    float angle;        //the angle between an horizontal edge and an horizontal line (rad)

    // returns 3D coordinates of a desired node
    P3D node(const int i) const;

    int nodeNbr() const { return width*height; };
};

P3D GridMesh::node(const int i) const
{
    // assert(i <= this->nodeNbr());

    const P2D coords = index_to_colRow(this->width, i);

    P3D p;

    //Orthogonal, Horizontal & Vertical
    p = P3D{
        this->edge_size * ( coords[0] + coords[1] * std::sin(this->angle) )
        , this->edge_size * ( coords[1] + coords[0] * std::sin(this->angle) )
        , 0
    };

    return p;
}

struct NodeGenerator{
    const GridMesh& gm;
    int current;

    bool operator!=(const NodeGenerator& g) const { return g.current != current; }  
    void operator++(){ ++current; }
    P3D operator*() const { return this->gm.node(this->current); }
};

//To iterate through nodes
NodeGenerator begin(const GridMesh& gm){return NodeGenerator{gm, 0}; };
NodeGenerator end(const GridMesh& gm){return NodeGenerator{gm, gm.nodeNbr()}; };

int main()
{   
    GridMesh g{10,10,100,0};
    
    for(auto n : g)
    {
        std::cout << "Node: {" << n[0] << ", " << n[1] << ", "  << n[2] << "}" <<  std::endl;
    }

    return 0;
}