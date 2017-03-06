#include <iostream>
#include <vector>
#include <algorithm>

// checking which group statisfy the criteria
void checking_criteria(const std::vector<int>& v, std::vector<int>& list, const int criteria)
{
    int group_index = 0;
    while( std::count(v.begin(), v.end(), group_index) != 0)
    {
        // std::cout << std::count(v.begin(), v.end(), group_index) << std::endl;

        if( std::count (v.begin(), v.end(), group_index) <= criteria )
        {
            // std::cout << "The group n°"<< group_index << " does not satisfy the criteria." << std::endl;
            list.push_back(group_index);
        }
        ++group_index;
    }

};

void erase_bad_elts(std::vector<int>& v, std::vector<int>& list)
{
    int index = 0;

    int start = 0;
    int end = 0;

    for(auto& p : v)
    {
        std::cout << "current elt: " << p << std::endl;

        if( p == list.at(index) )
        {
            ++end;
        }
        else
        {
            // v.erase(v.begin()+start); 
            ++end;
            start = end;
            ++index;
        }

        std::cout << "current index: " << index << std::endl;
        std::cout << "start: " << start << std::endl;
        std::cout << "end: " << end << std::endl;
        std::cout << std::endl;

    }
}


int main()
{
    //WARNING only working with contiguous variables values because of the while() in checking_criteria()
    std::vector<int> v {0,0,0,0,0,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,5,6};

    std::cout << "v.size(): " << v.size() << std::endl;
    std::cout << "v = {"; for(auto& p : v)    std::cout << p << ","; std::cout << "\b};" << std::endl;  //dispay vector

    //using std
    // checking which group statisfy the criteria
    int criteria = 5;
    std::vector<int> groups_to_erase (0);
    checking_criteria(v, groups_to_erase, criteria);
    std::cout << "groups_to_erase = {"; for(auto& p : groups_to_erase)    std::cout << p << ","; std::cout << "\b};" << std::endl;  //dispay vector

    //erase elements belong the the list
    erase_bad_elts(v, groups_to_erase);




    std::cout << "v.size(): " << v.size() << std::endl;
    std::cout << "v = {"; for(auto& p : v)    std::cout << p << ","; std::cout << "\b};" << std::endl;  //dispay vector

    return 0;
}
