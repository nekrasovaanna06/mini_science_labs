#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();
  gmsh::model::add("torus");

  gmsh::option::setNumber("Mesh.MeshSizeFactor", 0.3);

  double R = 0.8;        // радиус тора
  double r = 0.4;        // внешний радиус 
  double r_pol = 0.3;   // внутренний радиус 
  
  
  int tor_out = gmsh::model::occ::addTorus(0, 0, 0, R, r);
  int tor_pol = gmsh::model::occ::addTorus(0, 0, 0, R, r_pol);

  
  std::vector<std::pair<int, int>> Tor; //Здесь будет полый тор          
  std::vector<std::vector<std::pair<int, int>>> Otr;  //Эта штука останется пустой, нужна для работы функции
  
 
  gmsh::model::occ::cut({{3, tor_out}}, {{3, tor_pol}}, Tor, Otr);
  
  
  gmsh::model::occ::synchronize();
  
  
  gmsh::model::mesh::generate(3);
  gmsh::write("torus.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();
  return 0;
}