#ifndef GCPOINTER_H
#define GCPOINTER_H

template <typename T>
struct gcpointer {
    T* data;
    int* refcount;

    T& operator *() {
        return *data;
    }

    T* operator->() {
        return data;
    }

    gcpointer() {
        data = nullptr;
        refcount = new int(0);
    }

    gcpointer(const T& val) {
        data = &val;
        refcount = new int(1);
    }

    gcpointer(const gcpointer<T>&& p) {
        data = p.data;
        refcount = p.refcount;
    }

    gcpointer(gcpointer<T>& p) {
        *(p.refcount) += 1;
        data = p.data;
        refcount = p.refcount;
    }

    gcpointer<T>& operator=(gcpointer<T>& p) {
        *(p.refcount) += 1;
        data = p.data;
        refcount = p.refcount;
    }

    ~gcpointer() {
        *refcount -= 1;
        if(*refcount <= 0) {
            delete data;
            delete refcount;
        }
    }

    // implicit cast operator that yields data, so you can cast the gcpointer, for whatever reason
    operator T*() {
        return data;
    }
};


// specialize further in the future to behave more like a slice than an array
template <typename T, size_t N>
struct gcpointer<T[N]> {
    T* data;
    int* refcount;

    gcpointer() {
        data = nullptr;
        refcount = new int(0);
    }

    gcpointer(T val[N]) {
        data = val;
        refcount = new int(1);
    }

    gcpointer(const gcpointer<T>&& p) {
        data = p.data;
        refcount = p.refcount;
    }

    gcpointer(gcpointer<T>& p) {
        *(p.refcount) += 1;
        data = p.data;
        refcount = p.refcount;
    }

    gcpointer<T>& operator=(gcpointer<T>& p) {
        *(p.refcount) += 1;
        data = p.data;
        refcount = p.refcount;
    }

    ~gcpointer() {
        *refcount -= 1;
        if(*refcount <= 0) {
            delete[] data;
            delete refcount;
        }
    }

    T& operator *() {
        return *data;
    }

    T* operator->() {
        return data;
    }

    T& operator[](int i) {
        return data[i];
    }

    T* operator+(int i) {
        return data + i;
    }

    // implicit cast operator that yields data, so you can cast the gcpointer, for whatever reason
    operator T*() {
        return data;
    }
};


template <typename T, class... Args>
gcpointer<T> gnew(Args&&... args) {
    gcpointer<T> p;
    p.data = new T(args...);
    *(p.refcount) = 1;
    return p;
}

#endif
