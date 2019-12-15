#ifndef tuple_h_
#define tuple_h_
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <type_traits>

template<class... Ts> struct tuple; //forward reference

// Template specializtion for empty list of template arguments, the base struct of the recursively implemented tuple 
// data structure.
template<> struct tuple<> { 

    tuple()
    {
  	std::cout << "In template<> tuple<>::tuple() constructor, which has NO member tail." << std::endl;
    }
}; 

// Recall that public inheritance is the default for structs.
template<class T, class... Ts> struct tuple<T, Ts...> : tuple<Ts...> { 

    tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t)
    {
        std::cout << "  In constructor for " <<  __PRETTY_FUNCTION__ << " where tail = " << tail << std::endl;
    }

    T tail;
};

// tuple_element forward declaration.
template<std::size_t Index, class _tuple> struct tuple_element;

// recursive data structure tuple_element definition
template <std::size_t Index, class T, class... Rest>  struct tuple_element<Index, tuple<T, Rest...>> : 
     public tuple_element<Index - 1, tuple<Rest...> > {

    tuple_element()
    {
      std::cout << "  In tuple_element<" << Index << ", tuple<T, Rest...>>::tuple(), where there are not type definitions." << std::endl;
    }
};

// partial template specialization for tuple_element<0, tuple<T, Rest...>>.
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
 * get reference to Index element of tuple
 */
template<size_t Index, class... Type> inline 
                       typename tuple_element<Index, tuple<Type...>>::value_type get(tuple<Type...>& _tuple)
{
  std::cout << "In get<" << Index << ">(some_tuple)" << "\n---------" << std::endl;

  // Cast _tuple to the base type of the corresponding tuple_element<Index,  tuple<Type...>> recursive struct type. 
  using base_tuple_type = typename tuple_element<Index, tuple<Type...>>::base_tuple_type;

  return static_cast<base_tuple_type&>(_tuple).tail;
}
#endif
