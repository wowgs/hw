object My_Set extends App {
  type set = Int => Boolean

  def contains(s: set, elem: Int): Boolean = s(elem)

  def singletonSet(elem: Int): set = (_ == elem)

  def union(s: set, t: set): set = (x: Int) => contains(s, x) || contains(t, x)

  def intersect(s: set, t: set): set = (x: Int) => contains(s, x) && contains(t, x)

  def diff(s: set, t: set): set = (x: Int) => contains(s, x) && !contains(t, x)

  def filter(s: set, p: (Int) => Boolean): set = (x: Int) => contains(s, x) && p(x)

  val bound = 1000

  def toString(s: set): String = {
    val xs = for (i <- -bound to bound if contains(s, i)) yield i
    xs.mkString("{", ",", "}")
  }

  def forall(s: set, p: (Int) => Boolean): Boolean = {
    def iter(a: Int): Boolean = {
      if (a > bound) true
      else if (contains(s, a) && !p(a)) false
      else iter(a + 1)
    }
    iter(-bound)
  }

  def exists(s: set, p: (Int) => Boolean): Boolean = {
    def iter(a: Int): Boolean = {
      if (a > bound) false
      else if (contains(s, a) && p(a)) true
      else iter(a + 1)
    }
    iter(-bound)
  }

  def map(s: set, f: (Int) => Int): set = {
    def iter(a: Int): set = {
      if (a > bound) (_ => false)
      else if (contains(s, a)) union(singletonSet(f(a)), iter(a + 1))
      else iter(a + 1)
    }
    iter(-bound)
  }
}