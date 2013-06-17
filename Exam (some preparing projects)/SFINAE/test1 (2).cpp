#include <vector>
#include <iostream>

#include <cstdlib>
#include <cstring>

template <typename It>
struct is_continous {
    static const bool value = false;
};

template <typename T>
struct is_continous<T*> {
    static const bool value = true;
};

template <bool cond>
struct enable_if;

template <>
struct enable_if<true>
{
   typedef void* type;
};

template <typename It, typename outIt>
void mycopy_(It first, It last, outIt out, typename enable_if<is_continous<It>::value>::type = 0) {
    std::cout << "1\n";
    memcpy(&*out, *&first, (last - first) * sizeof *first);
}


template <typename It, typename outIt>
void mycopy_(It first, It last, outIt out, typename enable_if<!is_continous<It>::value>::type = 0) {
     std::cout << "2\n";
     std::copy(first, last, out);
}

//template <typename It, typename outIt>
//void mycopy(It first, It last, outIt out) {
//    mycopy_(first, last, out, typename is_continous<It>::value());
//}

//template <typename It, typename outIt>
//void foo(It first, It last, outIt out) {
//    std::copy(first, last, out);
//}


int main () {
    int a[5];
    int b[5];
    std::vector<int> c(5);

    mycopy_(a + 0, a + 5, b + 0);
    mycopy_(c.begin(), c.end(), b + 0);
}

