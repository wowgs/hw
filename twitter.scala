object twister extends App{
 // package objsets

  //import common._

  /**
    * A class to represent tweets.
    */
  class Tweet(val user: String, val text: String, val retweets: Int) {
    override def toString: String =
      "User: " + user + "\n" +
        "Text: " + text + " [" + retweets + "]"
    def maxi(x : Tweet) : Tweet = {
      if (this.retweets > x.retweets) this
      else x
    }
  }

  /**
    * This represents a set of objects of type `Tweet` in the form of a binary search
    * tree. Every branch in the tree has two children (two `TweetSet`s). There is an
    * invariant which always holds: for every branch `b`, all elements in the left
    * subtree are smaller than the tweet at `b`. The elements in the right subtree are
    * larger.
    *
    * Note that the above structure requires us to be able to compare two tweets (we
    * need to be able to say which of two tweets is larger, or if they are equal). In
    * this implementation, the equality / order of tweets is based on the tweet's text
    * (see `def incl`). Hence, a `TweetSet` could not contain two tweets with the same
    * text from different users.
    *
    *
    * The advantage of representing sets as binary search trees is that the elements
    * of the set can be found quickly. If you want to learn more you can take a look
    * at the Wikipedia page [1], but this is not necessary in order to solve this
    * assignment.
    *
    * [1] http://en.wikipedia.org/wiki/Binary_search_tree
    */
  abstract class TweetSet {

    /**
      * This method takes a predicate and returns a subset of all the elements
      * in the original set for which the predicate is true.
      *
      * Question: Can we implment this method here, or should it remain abstract
      * and be implemented in the subclasses?
      */
    def filter(p: Tweet => Boolean): TweetSet = {
      filterAcc(p, Empty())
    }

    /**
      * This is a helper method for `filter` that propagetes the accumulated tweets.
      */
    def filterAcc(p: Tweet => Boolean, acc: TweetSet): TweetSet

    /**
      * Returns a new `TweetSet` that is the union of `TweetSet`s `this` and `that`.
      *
      * Question: Should we implment this method here, or should it remain abstract
      * and be implemented in the subclasses?
      */
    def union(that: TweetSet): TweetSet

    /**
      * Returns the tweet from this set which has the greatest retweet count.
      *
      * Calling `mostRetweeted` on an empty set should throw an exception of
      * type `java.util.NoSuchElementException`.
      *
      * Question: Should we implment this method here, or should it remain abstract
      * and be implemented in the subclasses?
      */
    def mostRetweeted: Tweet

    /**
      * Returns a list containing all tweets of this set, sorted by retweet count
      * in descending order. In other words, the head of the resulting list should
      * have the highest retweet count.
      *
      * Hint: the method `remove` on TweetSet will be very useful.
      * Question: Should we implment this method here, or should it remain abstract
      * and be implemented in the subclasses?
      */
    def descendingByRetweet: TweetList

    /**
      * The following methods are already implemented
      */

    /**
      * Returns a new `TweetSet` which contains all elements of this set, and the
      * the new element `tweet` in case it does not already exist in this set.
      *
      * If `this.contains(tweet)`, the current set is returned.
      */
    def incl(tweet: Tweet): TweetSet

    /**
      * Returns a new `TweetSet` which excludes `tweet`.
      */
    def remove(tweet: Tweet): TweetSet

    /**
      * Tests if `tweet` exists in this `TweetSet`.
      */
    def contains(tweet: Tweet): Boolean

    /**
      * This method takes a function and applies it to every element in the set.
      */
    def foreach(f: Tweet => Unit): Unit

    /**
      * This method returns most popular tweets containing any of keywords.
      */
    def trending(words: List[String]): TweetList = {
      val anon = (x : Tweet) => words.exists((y : String) => x.text.contains(y))
      filter(anon).descendingByRetweet
    }
  }

  case class Empty() extends TweetSet {
    def filterAcc(p: Tweet => Boolean, acc: TweetSet): TweetSet = acc

    /**
      * The following methods are already implemented
      */

    def contains(tweet: Tweet): Boolean = false

    def incl(tweet: Tweet): TweetSet = new NonEmpty(tweet, new Empty, new Empty)

    def remove(tweet: Tweet): TweetSet = this

    def foreach(f: Tweet => Unit): Unit = ()

    def mostRetweeted : Tweet = throw new java.util.NoSuchElementException("Empty()")

    def descendingByRetweet: TweetList = Nil

    def union(that: TweetSet): TweetSet = that
  }

  class NonEmpty(val elem: Tweet, val left: TweetSet, val right: TweetSet) extends TweetSet {

    def filterAcc(p: Tweet => Boolean, acc: TweetSet): TweetSet = {
      left.filterAcc(p, right.filterAcc(p, if(p(elem)) acc.incl(elem) else acc))
    }


    /**
      * The following methods are already implemented
      */

    def contains(x: Tweet): Boolean =
      if (x.text < elem.text) left.contains(x)
      else if (elem.text < x.text) right.contains(x)
      else true

    def incl(x: Tweet): TweetSet = {
      if (x.text < elem.text) new NonEmpty(elem, left.incl(x), right)
      else if (elem.text < x.text) new NonEmpty(elem, left, right.incl(x))
      else this
    }

    def remove(tw: Tweet): TweetSet =
      if (tw.text < elem.text) new NonEmpty(elem, left.remove(tw), right)
      else if (elem.text < tw.text) new NonEmpty(elem, left, right.remove(tw))
      else left.union(right)

    def foreach(f: Tweet => Unit): Unit = {
      f(elem)
      left.foreach(f)
      right.foreach(f)
    }

    def descendingByRetweet : TweetList = {
      val most = this.mostRetweeted
      Cons(most, remove(most).descendingByRetweet)
    }

    def mostRetweeted : Tweet = {
      val left_max = left match {
        case Empty() => new Tweet("","",-1)
        case NonEmpty(a, b, c) => left.mostRetweeted
      }
      val right_max = right match {
        case Empty() => new Tweet("","",-1)
        case NonEmpty(a, b, c) => right.mostRetweeted
      }
      elem.maxi(left_max.maxi(right_max))
    }

    def union(that: TweetSet): TweetSet = left.union(right.union(that.incl(elem)))
  }

  object NonEmpty {
    def unapply (x : NonEmpty) = Some((x.elem, x.left, x.right))
  }

  trait TweetList {
    def head: Tweet

    def tail: TweetList

    def isEmpty: Boolean

    def foreach(f: Tweet => Unit): Unit =
      if (!isEmpty) {
        f(head)
        tail.foreach(f)
      }
  }

  object Nil extends TweetList {
    def head = throw new java.util.NoSuchElementException("head of EmptyList")

    def tail = throw new java.util.NoSuchElementException("tail of EmptyList")

    def isEmpty = true
  }

  class Cons(val head: Tweet, val tail: TweetList) extends TweetList {
    def isEmpty = false
  }

  object Cons{
    def apply (head: Tweet, tail: TweetList) : Cons= new Cons(head, tail)
  }


  /**
    * val T: TweetSet = new Empty
    * val first: Tweet = new Tweet("first", "abc def", 0)
    * val second: Tweet = new Tweet("second", "a ghi", 91)
    * val third: Tweet = new Tweet("third", "jk", 101)
    * val fourth: Tweet = new Tweet("second", "a ghi", 91) //=second
    * val New: TweetSet = T.incl(first).incl(second).incl(third).incl(fourth)
    * val NewUnion: TweetSet = T.incl(first).union(T.incl(second))
    * println("UNION")
    * NewUnion.foreach(tw => println(tw.toString))
    * println("FILTER: RETWEETS > 10")
    * New.filter(tweet => tweet.retweets > 10).foreach(tw => println(tw.toString))
    * println("TRENDING(ab, j) (3 AND 4 TASKS)")
    * New.trending(List("ab", "j")).foreach(tw => println(tw.toString))
    * */

  /**
    * UNION
    * User: second
    * Text: a ghi [91]
    * User: first
    * Text: abc def [0]
    * FILTER: RETWEETS > 10
    * User: third
    * Text: jk [101]
    * User: second
    * Text: a ghi [91]
    * TRENDING(ab, j) (3 AND 4 TASKS)
    * User: third
    * Text: jk [101]
    * User: first
    * Text: abc def [0]
    * */
}
