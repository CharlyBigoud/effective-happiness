#include <iostream>
#include <string>

////////// definition d'une fonction dont le nombre d'arguments peut varier selon l'utilisateur

/////////////////////////////////////Solution classique/////////////////////////////////////////
// void draw_(auto ... a, auto b) //Il faut au moins 1 elt
// {
// 	draw_(b);
// 	draw_(a ...)
// }

// void draw(P2D){} //Le corps de draw_

// void draw_(){} //Lorsque la fonction draw_ n'a plus d'argument

// void mdraw(auto ... a) //Fonctionne pour tous les cas
// {
// 	draw_(a ...);
// }

/////////////////////////////////////Solution metaprogrammation/////////////////////////////////////////
struct P2D { int value;};

void draw(P2D p){std::cout << " p : " << p.value << std::endl;}

void meta_draw(auto ... a) { std::initializer_list<int>{(static_cast<void>(draw(a)),0)...}; }

int main()
{
  meta_draw(P2D{1},P2D{2},P2D{3});
}

////////////////////////TEST


void LIBV_CHARLIB_EXPORT meta_draw2D(const LytroCamera&, const int, auto ... a);

void draw2D(const LytroCamera& camera, const int SCALE_FACTOR, const AlignedVector<AlignedVector<Eigen::Vector2d>>& p2d)
{
	drawPoint(camera, camera.lens[i*camera.width+j], p2d[i*camera.width+j].at(p),SCALE_FACTOR,i,j);
}