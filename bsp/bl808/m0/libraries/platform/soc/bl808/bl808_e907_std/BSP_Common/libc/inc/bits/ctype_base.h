  
namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    // Non-standard typedefs.
    typedef const int* 		__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef char 		mask;
    static const mask upper    	= _U;
    static const mask lower 	= _L;
    static const mask alpha 	= _U | _L;
    static const mask digit 	= _N;
    static const mask xdigit 	= _X | _N;
    static const mask space 	= _S;
    static const mask print 	= _P | _U | _L | _N | _B;
    static const mask graph 	= _P | _U | _L | _N;
    static const mask cntrl 	= _C;
    static const mask punct 	= _P;
    static const mask alnum 	= _U | _L | _N;
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
