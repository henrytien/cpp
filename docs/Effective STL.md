# Effective STL

## Containers

### Item 1. Choose your containers with care.

> Deque is the only standard STL container whose iterators may be invalidated without also invalidating its pointers and references.

### Item 2. Beware the illusion of container-independent code.

> To write code that will work correctly with vector, deque, and list, you must assume that any operation invalidating iterators, pointers, or references in any of those containers invalidates them in the container you're using.
>
> With map and multimap, you must avoid using operator[], because that member function exists only for map.
>
> Once you've used the STL a little while, you'll realize that typedefs are your friends.

### Item 3. Make copying cheap and correct for objects in containers.

> An easy way to make copying efficient, correct, and immune to the slicing problem is to create containers of pointers instead of containers of objects.

### Item 4. Call empty instead of checking size() against zero.

> You should prefer the construct using empty, and the reason is simple: empty is a constant-time operation for all standard containers, but for some list implementations, size takes linear time.

### Item 5. Prefer range member functions to their single-element counterparts.

> Whenever you have to completely replace the contents of a container, you should think of assignment. If you're just copying one container to another of the same type, operator= is the assignment function of choice.
>
> Range member functions are easier to write, they express your intent more clearly, and they exhibit higher performance.

### Item 6. Be alert for C++'s most vexing parse.

```c++
ifstream dataFile(" ints.dat"); 
istream_iterator<int> dataBegin(dataFile); 
istream_iterator<int> dataEnd;
list<int> data(dataBegin, dataEnd);
```

### Item 7. When using containers of newed pointers, remember to delete the pointers before the container is destroyed.

> To avoid resource leaks when you have containers of pointers that should be deleted, you must either replace the pointers with smart reference-counting pointer objects (such as Boost's shared_ptr) or you must manually delete each pointer in the container before the container is destroyed.

### Item 8. Never create containers of auto_ptrs.

### Item 9. Choose carefully among erasing options.

> We have to make sure we have an iterator to the next element of c before we call erase. The easiest way to do that is to use postfix increment on i when we make the call.
>
> If the container is a standard sequence container, write a loop to walk the container elements, being sure to update your iterator with erase's return value each time von call it.
>
> If the container is a standard associative container, write a loop to walk the container elements, being sure to postincrement your iterator when you pass it to erase.

### Item 10. Be aware of allocator conventions and restrictions.

### Item 11. Understand the legitimate uses of custom allocators.

> Also, construction of the vector in the shared memory is accomplished by "placement new."

### Item 12. Have realistic expectations about the thread safety of STL containers.

```c++
template<typename Container> class Lock {
public:
// skeletal template for classes
// that acquire and release mutexes
// for containers; many details
// have been omitted
Lock(const Containers container) : c(container)
{
	getMutexFor(c);         // acquire mutex in the constructor
}
~Lock() {
	releaseMutexFor(c);			// release it in the destructor
}
private:
	const Container& c;
};


vector<int> v; ...
{
// close block, automatically // releasing the mutex
// create new block; 
Lock<vector<int> > lock(v); // acquire mutex
vector<int>::iterator first5(find(v.begin(), v.end(), 5)); 
	if (first5 != v.end()) {
		*first5 = 0; 
	}
}
```

## vector and string

### Item 13. Prefer vector and string to dynamically allocated arrays.

> If you're dynamically allocating arrays, you're probably taking on more work than you need to. To lighten your load, use vectors or strings instead.

### Item 14. Use reserve to avoid unnecessary reallocations.

> The key to avoiding reallocations, then, is to use reserve to set a container's capacity to a sufficiently large value as soon as possible, ideally right after the container is constructed.
>
> The first is applicable when you know exactly or approximately how many elements will ultimately end up in your container. In that case, as in the vector code above, you simply reserve the appropriate amount of space in advance. The second way is to reserve the maximum space you could ever need. then, once you've added all your data, trim off any excess capacity. 

### Item 15. Be aware of variations in string implementations.

### Item 16. Know how to pass vector and string data to legacy APIs.

### Item 17. Use "the swap trick" to trim excess capacity.

> This is how you trim the excess capacity from your contestants vector:

`vector<Contestant>(contestants).swap(contestants);`

`vector<Contestant>().swap(v); //clear v and minimize its capacity`

### Item 18. Avoid using vector<bool>.

>  What does matter is this: vector<bool> doesn't satisfy the requirements of an STL container; you're best off not using it; and deque<bool> and bitset are alternative data structures that will almost certainly satisfy your need for the capabilities promised by vector<bool>.

## Associative Containers

### Item 19. Understand the difference between equality and equivalence.



### Item 20. Specify comparison types for associative containers of pointers.

```c++
struct StringPtrLess:
	public binary_function<const string*, // see Item 40 for the
												const string*, //reason for this base 
												bool> { //class
	bool operator()(const string *ps1, const string *ps2) const 
	{
		return *ps1 < *ps2; 
	}
};
```




### Item 21. Always have comparison functions return false for equal values.

### Item 22. Avoid in-place key modification in set and multiset.

### Item 23. Consider replacing associative containers with sorted vectors.

> suppose you're working on a system where a Widget is 12 bytes in size, pointers are 4 bytes, and a memory' page holds 4096 (4K) bytes. Ignoring the per-container overhead, you can fit 341 Widgets on a page when they are stored in a vector, but you can fit at most 170 when they are stored in an associative container.



### Item 24. Choose carefully between map::operator[] and map-insert when efficiency is important.

`m.insert(lntWidgetMap::value_type(1,1.50));`

> If you're updating an existing map element, operator[] is preferable, but if you're adding a new element, insert has the edge.

### Item 25. Familiarize yourself with the nonstandard hashed containers.

## Iterators

### Item 26. Prefer iterator to const iterator, reverse_iterator, and const_reverse_iterator.

> All these things conspire to make working with containers easiest, most efficient, and least likely to harbor subtle bugs if you prefer iterators to their const and reverse colleagues.

### Item 27. Use distance and advance to convert a container's const_iterators to iterators.

`advance(i, distance<ConstIter>(i, ci));`

### Item 28. Understand how to use a reverse_iterator's base iterator.

`v.erase(++ri).base());`

### Item 29. Consider istreambuf_iterators for character-by-character input.

> If you need to read the characters in a stream one by one, you don't need the power of formatted input, and you care about how long it takes to read the stream, typing three extra characters per iterator is a small price to pay for what is often a significant increase in performance. For unformatted character- by-character input, you should always consider istreambuf_iterators.
>
> 