#ifndef tuple_h_
#define tuple_h_
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

// These headers are needed for get_realname() template function.
#include <typeinfo>
#include <type_traits>
#include <cxxabi.h>

template<class... Ts> struct tuple; // Forward reference

// Template specializtion for an empty list of template arguments, which is the base struct of the recursively defined tuple 
// data structure.
template<> struct tuple<> { 

    tuple()
    {
  	  std::cout << "In template<> tuple<>::tuple() constructor, which has NO member tail." << std::endl;
    }
}; 

// Recall that public inheritance is the default for structs.
template<class T, class... Ts> struct tuple<T, Ts...> : tuple<Ts...> { 

    template<class Arg1, class... Args> tuple(Arg1&& arg1, Args&&...args) : tuple<Ts...>(std::forward<Args>(args)...), tail(std::forward<Arg1>(arg1))
    {
        std::cout << "  In constructor for " <<  __PRETTY_FUNCTION__  << std::endl;
    }

    T tail;
};

// Forward declaration of tuple_element forward
template<std::size_t Index, class _tuple> struct tuple_element;

// Recursive data structure tuple_element definition
template <std::size_t Index, class T, class... Rest>  struct tuple_element<Index, tuple<T, Rest...>> : 
     public tuple_element<Index - 1, tuple<Rest...> > {

    tuple_element()
    {
      std::cout << "  In tuple_element<" << Index << ", tuple<T, Rest...>>::tuple(), where there are not type definitions." << std::endl;
    }
};

// Partial template specialization for tuple_element<0, tuple<T, Rest...>>.
template<class T, class... Rest>  struct tuple_element<0, tuple<T, Rest...>>  {

  using value_type = T&;                 // Reference to tail's type.
  using base_tuple_type = tuple<T, Rest...>;  // The type of the tuple instance

  tuple_element()
  {
      std::cout << "In tuple_element<0, T, Rest...>>::tuple(), where there are these two type definitions:" << std::endl;
      std::cout << "\tusing value_type = T&" << std::endl;
      std::cout << "\tusing base_tuple_type = tuple<T, Rest>" << std::endl;
  }
};


/*
 * This method returns the demangled name for a tuple_element<std::size_t, Ts...>'s actual type.
 */

template<std::size_t Index, class T, class... Rest> std::string get_realname( tuple_element<Index, tuple<T, Rest...>>& te  )
{
  const std::type_info  &ti = typeid(te);

  int status;

  char *realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);

  std::string str_name{realname};

  free(realname);

  return str_name;
}

/*
 * get reference to Index element of tuple
 */
template<size_t Index, class... Type> auto get(tuple<Type...>& _tuple) -> typename tuple_element<Index, tuple<Type...>>::value_type
{
  // We will cast _tuple to the base type of the corresponding tuple_element<Index,  tuple<Type...>> recursive struct's base type.
  using base_tuple_type = typename tuple_element<Index, tuple<Type...>>::base_tuple_type;

  std::cout << "In get<" << Index << ">(some_tuple)" << " doing this cast: static_cast<base_tuple_type&>(_tuple).tail\n---------" << std::endl;

  return static_cast<base_tuple_type&>(_tuple).tail;
}
#endif
