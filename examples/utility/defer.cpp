#include <mtl/utility.h>

static mutex<int> mutex_obj;

void increment_mutex_val()
{
    mutex_obj.lock();
    auto _ = mtl::defer([&] { mutex_obj.unlock(); })

    return mutex_obj.with_lock([](int &val) { return ++val; });
}
