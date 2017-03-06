#include <iostream>
#include <boost/thread.hpp>
#include <ctime>

namespace v
{
  inline void tempo(size_t duration)
  {
  #if BOOST_VERSION > 104800
    boost::this_thread::sleep_for(boost::chrono::milliseconds(duration));
  #else
    boost::this_thread::sleep(boost::posix_time::milliseconds(duration));
  #endif
  }
}


struct Helico
{
  struct Detail
  {
    const size_t ms;
    const std::string chaine;
    int etat;
    const int nb_etat;
    Detail(size_t ms_=30,std::string str="-\\|/"):ms(ms_),chaine(str),etat(0),nb_etat(str.size()){}
    void operator()()
    {
      if (chaine.empty()) return;
      etat ++;
      etat = etat % nb_etat;
      std::cout << '\b';
      std::cout << chaine[etat] << std::flush;
      v::tempo(ms);
    }
  };

  boost::thread th;
  Helico():th([&](){Detail _;while(1){_();}}) {}

  void stop()
  {
    th.interrupt();
    th.join();
  }
  ~Helico(){stop();}
};

void usage1()
{
  std::cout << " Press enter to finish " << std::endl;
  {
    Helico _;
    //...
    getchar();
  }
  std::cout << " return " << std::endl;
}

void usage2()
{
  std::cout << " Press enter to finish " << std::endl;
  Helico _;

  //...
  getchar();
  _.stop();
  std::cout << " return " << std::endl;
}

int main()
{
  usage1();
  usage2();
}
