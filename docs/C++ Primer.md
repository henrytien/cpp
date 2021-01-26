# C++ Primer







**Chapter 12. Dynamic Memory**

> The fact that the shared_ptr class automatically frees dynamic objects when they are no longer needed makes it fairly easy to use dynamic memory. For example, we might have a function that returns a shared_ptr to a dynamically allocated object of a type named Foo that can be initialized by an argument of type T:

```c++
// factory returns a shared_ptr pointing to a dynamically allocated object 
shared_ptr<Foo> factory(T arg)
{
 // process arg as appropriate

// shared_ptr will take care of deleting this memory
  return make_shared<Foo>(arg);

}

void use_factory(T arg)
{
  shared_ptr<Foo> p = factory(arg);
  // use p
} // p goes out of scope; the memory to which p points is automatically freed.
```



Programs tend to use dynamic memory for one of three purposes: 

**1.** They don’t know how many objects they’ll need

**2.** They don’t know the precise type of the objects they need 

**3.** They want to share data between several objects

