#ifndef quick_sort_h
#define quick_sort_h

#include <cassert>
#include "utils.h"
#include "random.h"

template <typename T>
class quick_sort {
public:
    static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>())
    {
        std_random<T>::shuffle(arr, n);
        sort(arr, 0, n - 1, comp);
    }

private:
    static const int CUTOFF = 7;

    static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp)
    {
        if(high <= low)
            return;

        size_t x = partition(arr, low, high, comp);
        sort(arr, low, (x == 0 ? 0 : x - 1), comp);
        sort(arr, x + 1, high, comp);
    }

    static size_t partition(T* arr, size_t low, size_t high, const comparator<T>& comp)
    {
        size_t x = low; 
        size_t y = high + 1;

        while (true)
        {
            while(less(arr[++x], arr[low], comp))
            {
                if(x == high)
                    break;
            }

            while(less(arr[low], arr[--y], comp))
            {
                if(y == low)
                    break;
            }
            
            if(x >= y)
                break;

            exchange(arr, x, y);
        }

        exchange(arr, low, y);
        return y;
    }
};


template <typename T>
class quick_sort_3way {
    static const int CUTOFF = 7;

public:
    static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>())
    {
        std_random<T>::shuffle(arr, n);
        sort(arr, 0, n - 1, comp);
        assert(is_sorted(arr, n, comp));
    }

private:
    static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp)
    {
        if (high <= low)
            return;

        size_t lt = low;
        size_t gt = high;
        size_t i = low + 1;
        T value = arr[low];

        while(i <= gt)
        {
            if (less(arr[i], value, comp))
                exchange(arr, lt++, i++);
            else if (less(value, arr[i], comp))
            {
                exchange(arr, i, gt);
                if (gt != 0)
                    --gt;
            }
            else
                ++i;            
        }

        sort(arr, low, (lt == 0 ? 0 : lt - 1), comp);
        sort(arr, gt + 1, high, comp);
        assert(is_sorted(arr, low, high, comp));
    }
};

#endif