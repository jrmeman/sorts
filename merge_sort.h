#ifndef merge_sort_h
#define merge_sort_h

template <typename T>
class merge_sort {
public:
    static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>())
    {
        T* aux = new T[n];
        assert(aux != nullptr);

        sort(arr, aux, 0, n - 1, comp);

        delete[] aux;
    }

private:
    static const int CUTOFF = 7;

    static void sort(T* arr, T* aux, size_t low, size_t high, const comparator<T>& comp)
    {
        if(high <= low)
            return;

        size_t mid = low + (high - low) / 2;
        sort(arr, aux, low, mid, comp);
        sort(arr, aux, mid + 1, high, comp);
        merge(arr, aux, low, mid, high, comp);
    }

    static void merge(T* arr, T* aux, size_t low, size_t mid, size_t high, const comparator<T>& comp)
    {
        assert(is_sorted(arr, low, mid, comp));
        assert(is_sorted(arr, mid + 1, high, comp));

        for(size_t i = low; i <= high; i++)
            aux[i] = arr[i];

        size_t x = low;
        size_t y = mid + 1;
        for(size_t i = low; i <= high; i++)
        {
            if(x > mid)
                arr[i] = aux[y++];
            else if(y > high)
                arr[i] = aux[x++];
            else if(less(aux[y], aux[x], comp))
                arr[i] = aux[y++];
            else
                arr[i] = aux[x++];            
        }

        assert(is_sorted(arr, low, high, comp));
    }
};


template <typename T>
class merge_bu_sort {
public:
// merge_bu_sort() = delete;
    static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>())
    {
        T* aux = new T[n];
        for(size_t size = 1; size < n; size *= 2)
        {
            for(size_t low = 0; low < n - size; low += 2 * size)
            {
                merge(arr, aux, low, low + size - 1, std::min(low + 2 * size - 1, n - 1), comp);
            }
        }

        assert(is_sorted(arr, n, comp));
    }

private:
    static void merge(T* arr, T* aux, size_t low, size_t mid, size_t high, const comparator<T>& comp)
    {
        assert(is_sorted(arr, low, mid, comp));
        assert(is_sorted(arr, mid + 1, high, comp));

        for(size_t i = low; i <= high; i++)
            aux[i] = arr[i];

        size_t x = low; 
        size_t y = mid + 1;
        for(size_t i = low; i <= high; i++)
        {
            if(x > mid)
                arr[i] = aux[y++];
            else if(y > high)
                arr[i] = aux[x++];
            else if(less(aux[y], aux[x], comp))
                arr[i] = aux[y++];
            else
                arr[i] = aux[x++];            
        }

        assert(is_sorted(arr, low, high, comp));
    }
};

#endif