

object One extends App {



  def my_filter[A](ar: List[A], func: A => Boolean): List[A] = {
    if (ar.isEmpty) Nil
    else {
      if (func(ar.head)) ar.head :: my_filter(ar.tail, func)
      else my_filter(ar.tail, func)
    }
  }
}

object Two extends App{
  def filt(ar: List[Int]): List[Int] = {
    if (ar.isEmpty) Nil
    else {
      if (ar.head > 0) ar.head :: filt(ar.tail)
      else filt(ar.tail)
    }
  }
}

object Three extends App{
  def my_reduce[A](func: (A, A) => A)(ar: List[A]): A = {
    if (ar.tail.isEmpty) ar.head
    else {
      func(ar.head, my_reduce(func)(ar.tail))
    }
  }

  def my_sum = my_reduce[Int](_ + _) _

  def sum2_tail(ar: List[Int], acc: Int = 0): Int = {
    if (ar.isEmpty) acc
    else sum2_tail(ar.tail, acc + ar.head)
  }
}

object Four extends App{

  def my_length(ar: List[Any], acc: Int = 0): Int = {
    if (ar.isEmpty) acc
    else my_length(ar.tail, acc + 1)
  }
}

object Five extends App {
  def add_to_end(ar: List[Any], x: Any): List[Any] = {
    if (ar.isEmpty) x :: Nil
    else ar.head :: add_to_end(ar.tail, x)
  }
}

object Six {

  def my_reverse(ar: List[Any], res: List[Any] = Nil): List[Any] = {
    if (ar.isEmpty) res
    else my_reverse(ar.tail, ar.head :: res)
  }
}

object Maths extends App {

  import scala.math

  def diskr(ar: Array[Double]): Double = {
    ar(1) * ar(1) - 4 * ar(0) * ar(2)
  }

  def kv_kor(ar: Array[Double]): List[Double] = {
    List((-ar(1) - math.sqrt(diskr(ar))) / 2 / ar(0), (-ar(1) + math.sqrt(diskr(ar))) / 2 / ar(0))
  }

  def sign(x: Double): Int =
    if (x < 0) -1 else if (x > 0) 1 else 0

  def matan(ar: Array[Double]): List[Double] = {
    if (ar.length == 3) {
      if (diskr(ar) > 0) kv_kor(ar)
      else if (diskr(ar) == 0) kv_kor(ar).head :: Nil
      else Nil
    }
    else if (ar.length == 4) {
      if (ar(0) == 0) {
        matan(ar.drop(1))
      }
      else if (ar(0) == 1) {
        val a: Double = ar(1)
        val b: Double = ar(2)
        val c: Double = ar(3)
        val q: Double = (a * a - 3 * b) / 9
        val r: Double = (2 * a * a * a - 9 * a * b + 27 * c) / 54
        val r_2_min_q_3: Double = r * r - q * q * q

        if (r_2_min_q_3 < 0) {
          val t: Double = math.acos(r / math.sqrt(q * q * q)) / 3
          val _2_pi_3: Double = 2 * math.Pi / 3

          List(2 * math.sqrt(q) * math.cos(t) - a / 3,
            2 * math.sqrt(q) * math.cos(t + _2_pi_3) - a / 3,
            2 * math.sqrt(q) * math.cos(t - _2_pi_3) - a / 3)
        }
        else {
          val A: Double = sign(r) *
            math.pow(math.abs(r) +
              math.sqrt(r_2_min_q_3), 1 / 3)
          val B: Double = if (A == 0) 0 else q / A

          val x1 = (A + B) - a / 3
          if (A == B && A != 0)
            List(x1, -A - a / 3)
          else
            List(x1)
        }
      }
      else {
        matan(ar.map(_ / ar(0)))
      }
    }
    else {
      println("No support")
      Nil
    }
  }

}
object CountingMoney extends App {

  def countChange(money: Int, coins: List[Int]): Int = {
    if (money == 0) 1
    else if (money < 0 || coins.isEmpty) 0
    else countChange(money, coins.tail) + countChange(money - coins.head, coins)
  }

}

object Balance extends App {

  def check_char(tmp: Char): Int = {
    if (tmp == '(') 1
    else if (tmp == ')') -1
    else 0
  }

  def balance_check(ar: List[Char], d: Int = 0): Boolean = {
    if (d < 0) false
    else {
      if (ar.isEmpty) {
        if (d == 0) true
        else false
      }
      else balance_check(ar.tail, d + check_char(ar.head))
    }
  }

}

object Triangle extends App {

  import BigInt._

  def bad_triangle(x: Int, y: Int): Int = {
    if (y == 0 || y == x) 1
    else bad_triangle(x - 1, y - 1) + bad_triangle(x - 1, y)
  }

  def fact(x: BigInt, y : BigInt = 1): BigInt = {
    if (x == 0) 1
    else if (x == y + 1) y + 1
    else x * fact(x - 1, y)
  }

  def better_triangle(x: BigInt, y: BigInt): BigInt = {
    fact(x, y) / fact(x - y)
  }

  println(better_triangle(10, 4))
}

