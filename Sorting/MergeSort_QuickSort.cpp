#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>

std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    //std::cout<<"enter";
    std::vector<int> sorted;
    auto it_left = left.begin(), it_right = right.begin();
    while(it_left != left.end() && it_right != right.end())
    {
        if(*it_left < *it_right)
        {
            sorted.push_back(*it_left);
            it_left++;
        }
        else
        {
            sorted.push_back(*it_right);
            it_right++;
        }
    }
    while(it_left != left.end())
    {
        sorted.push_back(*it_left);
        it_left++;
    }
    while(it_right != right.end())
    {
        sorted.push_back(*it_right);
        it_right++;
    }
    return sorted;
}

void merge_sort(std::vector<int>& v1)
{
    if(v1.size() == 1)
        return;
    auto it = v1.begin();
    auto mid = v1.begin() + v1.size() / 2;
    std::vector<int> l,r;
    while(it != mid)
    {
        l.push_back(*it);
        it++;
    }
    while(it != v1.end())
    {
        r.push_back(*it);
        it++;
    }
    merge_sort(l);
    merge_sort(r);
    v1 = merge(l,r);
    return;
}

std::vector<int>::iterator partition(std::vector<int>& v, std::vector<int>::iterator low, std::vector<int>::iterator high)
{
    auto i = low;
    while(low <= high)
    {
        if(*low <= *high)
        {
            int temp = *low;
            *low = *i;
            *i = temp;
            i++;
        }
        low++;
    }
    return i - 1;
}

void quick_sort(std::vector<int>& v1, std::vector<int>::iterator low, std::vector<int>::iterator high)
{
    if(low < high)
    {
        std::vector<int>::iterator pivot = partition(v1,low,high);
        quick_sort(v1, low, pivot - 1);
        quick_sort(v1, pivot + 1, high);
    }
}

int main(int argc, char const *argv[])
{
    std::ifstream cin1(argv[1]);
    std::istream_iterator<std::string> itr(cin1);
    std::istream_iterator<std::string> eos;
    std::vector<int> v1;

    std::ofstream out1,out2;
    out1.open("merge_sort.out");
    out2.open("quick_sort.out");
    while(itr != eos)
    {
        v1.push_back(stoi(*itr));
        itr++;
    }
    std::vector<int> v2(v1);

    merge_sort(v1);
    for(auto it = v1.begin(); it != v1.end(); it++)
        out1<<*it<<std::endl;

    quick_sort(v2, v2.begin(), v2.end() - 1);
    for(auto it = v2.begin(); it != v2.end(); it++)
        out2<<*it<<std::endl;

    return 0;
}
