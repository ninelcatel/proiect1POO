#include <iostream>
union T{
    int a1;
    float a2;
};
struct S{
    int a1;
    int a2;
};

int main(){
    std::cout<<sizeof(T)<<" "<<sizeof(S)<<std::endl;   
    return 0;
}
