#include <iostream>
#include <new> // bad_alloc

int main() {
    try {
        // 尝试分配一块极大的内存，触发 bad_alloc
        int* p = new int[1000000000000LL]; // 约 400GB，几乎必然失败
    } catch (const std::bad_alloc& e) {
        std::cout << "捕获到异常: " << e.what() << std::endl;
    }
    return 0;
}
