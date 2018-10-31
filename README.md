# GC Pointer
A small smart pointer implementation.

This originally was designed to be a simple approach to garbage colleciton in C++, but as I got finished 
with it, I realized this was pretty much just a smart pointer. 

This library was designed to provide "garbage collection" (i.e. smart pointers) with minimal syntax
modification. In this case, `new` is replaced by the template function `gnew`, which functions about the 
same as new, for both array/pointer and object types. 

### Usage
This works best in C++11 or greater, and also might not work in anything less than that. Essentially, it's
most friendly with post-C++11 `auto` syntax.  A bit like the STL iterators in that sense. Additionally, it 
has an implicit cast operator that allows it to be cast to a plain pointer of its type, although reference 
counting is lost in this case. Not brilliant, but not much you can do without majorly affecting C++ syntax 
or a lot more work. Basically, just don't use the pointer returned from the cast for anything that moves it 
to a different, higher-level scope.

### Future Work
I'm going to try to make something that far more closely resembles an actual garbage collector, but that 
seems incompatible with the design of this project, so that will be an entirely separate project.

I'm actually going to try to use this library in my C++ projects, so this will get updated when I discover 
any features that would be useful and I'll patch it if/when I find any issues. Basically, when I find any 
bugs or POLA violations, I'll fix it here, just in case anybody actually cares.
