// stod example
#include <iostream>   // std::cout
#include <string>     // std::string, std::stod

int main ()
{
  std::string orbits ("The 29.53 223.24");
  std::string::size_type sz;     // alias of size_t

  double earth = std::stod (orbits,&sz);
  //double moon = std::stod (orbits.substr(sz));
  double third = std::stod (orbits.substr(sz));
  std::cout << "The "<<third<<" moon completes orbits per Earth year.\n";
  return 0;
}