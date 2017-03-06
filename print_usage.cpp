#include <iostream>
#include <string>
#include <vector>

void prout(const std::string s){ std::cout << s << "\t"; }

void print_usage(auto ... good_args)
{
    std::cout << "Welcome to the show !!!" << std::endl;
    std::cout << "It seems that you're new so let me explain you the rules:" << std::endl;
    std::cout << "To execute the program, please enter different files in the order below:" << std::endl;
    // std::initializer_list<int>{ (static_cast<void>( prout(good_args) ), 0)... };
    std::initializer_list<int>{ (static_cast<void>( std::cout << good_args << "\t" ), 0)... };
    std::cout << "\nSee you!" << std::endl;
}

/*
 * @Brief
*/
int main(int argc, char* argv[])
{   
    if(argc != 4 )
    {
        print_usage("MACHIN", "CACA", "BITE", "LALALA", "Jean-LOUIS");
        return -1;
    }

    std::cout << "CA MARCHE" << std::endl;
}

// int main(int argc, char* argv[])
// {
//     std::vector<std::string> strs;
//     for(int i = 0 ; i < argc ; ++i)
//         strs.push_back(argv[i]);

//     if ( strs.size() != 3 )
//     {
//       std::cout << "  usage: ./exe opt parametres" << std::endl;
//       return 0;
//     }
//     // if(strs[1]=="opt")
//         // run_opt(strs[2]);
// }