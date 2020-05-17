#ifndef DRAUTOMATON_SRC_IRULE_*
#define DRAUTOMATON_SRC_IRULE_*

/* Interface for rules --- not to be included in any code! */
class IRule
{
public:
  using State = T;  // Where T is a type with operator int();

  // Compute the state of the cell at the coords `(x, y)` of `space` in
  // the next generation.
  T transition(int x, int y, const Space<T>& space);

  // Return the state obtained by incrementing the state of `t` by one.
  T increment(const T& t);
};

#endif /* DRAUTOMATON_SRC_IRULE_* */
