#include <iostream>
#include <array>
#include <vector>

using P3D = std::array<double,3>;


struct Pose{
 
};

// voici ma structure chessboard :
struct ChessBoard
{
  size_t h = 6;
  size_t w = 8;
  double square = 0.03;

  Pose pose;

  size_t width() const;
  size_t height() const;
  size_t nb_corners() const { return 10; }

  // point objet passé dans le repère monde
  P3D world_coordinate(size_t i) const { return P3D{i,i,i}; }
  P3D object_coordinate(size_t i) const { return P3D{-i,-i,i}; }


};

// je veux pouvoir écrire:
// ChessBoard chessboard;
// p est un P3D dans le repère monde pouvant être obtenu avec chessboard.world_coordinate(k) avec k le k-ième élément du chessboard
// for(P3D p : chessboard)  
// {
// quelque chose avec p
//   project(p,...)
// }


struct MaStruct
{
	std::vector<int> a {1,2,3,4,5};
	MaStruct()
	{
		a = {1,2,3,4,5};
	}
//	P3D maFonction(int k){return P3D();};

	//necessary elts to iterate
	// MaStruct begin(){return MaStruct();};
	// MaStruct end(){return MaStruct();};
	// bool operator!=(const MaStruct s){return true;};
	// void operator++(){};
	// MaStruct operator*(){ return MaStruct();};

	// P3D begin(){return P3D();};
	// P3D end(){return P3D();};
	// bool operator!=(P3D p) const {return true;};
	// P3D operator++(int i) {return P3D();};
	// P3D operator*(P3D p){return P3D();};
};

auto begin(const MaStruct& m) { return m.a.begin(); }
auto end(const MaStruct& m) { return m.a.end(); }


struct ChessBoardIterator
{
	const ChessBoard& chessboard;
	int current;
	bool operator!=(const ChessBoardIterator& t) const { return t.current != current; }	
	void operator++(){ current++;}
	P3D operator*() const {return chessboard.world_coordinate(current);}
};


ChessBoardIterator begin(const ChessBoard& m) { return ChessBoardIterator{m,0}; }
ChessBoardIterator end(const ChessBoard& m) { return ChessBoardIterator{m,m.nb_corners()}; }

struct ObjectChessBoard
{
	const ChessBoard& m;
};

struct WChessBoardIterator
{
	const ChessBoard& chessboard;
	int current;
	bool operator!=(const WChessBoardIterator& t) const { return t.current != current; }	
	void operator++(){ current++;}
	P3D operator*() const {return chessboard.object_coordinate(current);}
};


WChessBoardIterator begin(const ObjectChessBoard& m) { return WChessBoardIterator{m.m,0}; }
WChessBoardIterator end(const ObjectChessBoard& m) { return WChessBoardIterator{m.m,m.m.nb_corners()}; }

int main()
{
	std::cout << "Datta me pose un problème !" << std::endl;

	ChessBoard chessboard;
	for(P3D p : chessboard)
		std::cout << p[0] << "," << p[1] << std::endl;

	for(P3D p : ObjectChessBoard{chessboard})
		std::cout << p[0] << "," << p[1] << std::endl;

	MaStruct s;
	// for(MaStruct p : s)
	for(int p : s)
	{
		std::cout << p << " ";
		// project(p,...);
	}
	std::cout << std::endl;

	return 0;
}