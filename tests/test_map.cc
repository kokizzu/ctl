#include "test.h"
#include "digi.hh"

static inline void
int_digi_free(int* a, digi* b)
{
    (void) a;
    digi_free(b);
}

static inline void
int_digi_copy(int* a, int* b, digi* c, digi* d)
{
    *a = *b;
    *c = digi_copy(d);
}

#define USE_INTERNAL_VERIFY
#define T int
#define U digi
#include <map.h>

#include <map>
#include <algorithm>

static inline int
int_compare(int* a, int* b)
{
    return (*a == *b) ? 0 : (*a < *b) ? -1 : 1;
}

#define CHECK(_x, _y) {                                      \
    std::map<int, DIGI>::iterator _iter = _y.begin();        \
    foreach(map_int_digi, &_x, _it, {                        \
        assert(_it.node->first == _iter->first);             \
        _iter++;                                             \
    });                                                      \
    map_int_digi_it _it = map_int_digi_it_each(&_x);         \
    for(auto& _d : _y) {                                     \
        assert(*_it.node->second.value == *_d.second.value); \
        _it.step(&_it);                                      \
    }                                                        \
}

int
main(void)
{
#ifdef SRAND
    srand(time(NULL));
#endif
    const size_t loops = TEST_RAND(TEST_MAX_LOOPS);
    for(size_t loop = 0; loop < loops; loop++)
    {
        size_t iters = TEST_RAND(TEST_MAX_SIZE);
        map_int_digi a = map_int_digi_create(int_compare);
        std::map<int, DIGI> b;
        for(size_t inserts = 0; inserts < iters; inserts++)
        {
            const int va = TEST_RAND(TEST_MAX_SIZE);
            const int vb = TEST_RAND(TEST_MAX_SIZE);
            map_int_digi_insert(&a, va, digi_init(vb));
            b.insert(std::pair<int, DIGI> { va, DIGI{vb} });
        }
        enum
        {
            TEST_INSERT,
            TEST_ERASE,
            TEST_TOTAL,
        };
        int which = TEST_RAND(TEST_TOTAL);
        switch(which)
        {
            case TEST_INSERT:
            {
                const int va = TEST_RAND(TEST_MAX_SIZE);
                const int vb = TEST_RAND(TEST_MAX_SIZE);
                map_int_digi_insert(&a, va, digi_init(vb));
                b.insert(std::pair<int, DIGI> { va, DIGI{vb} });
                CHECK(a, b);
                break;
            }
            case TEST_ERASE:
            {
                if(a.size > 0)
                {
                    const int key = TEST_RAND(TEST_MAX_SIZE);
                    map_int_digi_erase(&a, key);
                    b.erase(key);
                    CHECK(a, b);
                }
                break;
            }
        }
        CHECK(a, b);
        map_int_digi_free(&a);
    }
    TEST_PASS(__FILE__);
}