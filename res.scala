abstract class ParagraphElement {
  def length: Int
}

case class Word(word: String) extends ParagraphElement {
  override def toString: String =
    "Word(" + this.word + ")"
  def length = word.length
}

case class Space(width: Int) extends ParagraphElement {
  override def toString: String =
    "Space(" + this.width.toString + ")"
  def length = width
}

abstract class Alignment

case class Left() extends Alignment
case class Right() extends Alignment
case class Middle() extends Alignment

object String_Alignment extends App {
  type Line = List[ParagraphElement]
  type Paragraph = List[Line]

  def make_Paragraph(list: List[String], screen_size: Int): Paragraph = {
    if (Errors(list, screen_size) == 0) {
      def StringAcc(l: List[String], width: Int, avbl_width: Int,  dw: Int, line: Line, acc: Paragraph): Paragraph = {
        if (l.isEmpty)
          line.reverse :: acc
        else if (l.head.length <= avbl_width)
          StringAcc(l.tail, width, avbl_width - l.head.length - 1, 1, line.:::(Spaces(l.head :: Nil, dw)), acc)
        else StringAcc(l, width, width, 0, Nil, line.reverse :: acc)
      }
      StringAcc(list, screen_size, screen_size, 0, Nil, Nil)
    } else {
      val max_length = list.map(_.length).max
      make_Paragraph(list, max_length)
    }
  }

  def Align(l: Paragraph, size: Int, align: Alignment, res: Paragraph): Paragraph = {
    def Align_String(list: Line, width: Int, align_type: Alignment): Line = {
      val border = width / 2
      if (width != 0)
        align_type match {
          case Middle() =>
            if (border != 0) new Space(width - border) :: list ::: List(new Space(border))
            else new Space(width - border) :: list
          case Left() =>
            list :+ new Space(width)
          case Right() =>
            new Space(width) :: list
        }
      else list
    }
    if (l.isEmpty)
      res
    else {
      var b = Align_String(l.head, size - count(l.head, 0), align)
      Align(l.tail, size, align, b :: res)
    }
  }

  def count(list: Line, acc: Int) : Int = {
    if (list.isEmpty)
      acc
    else
      count(list.tail, acc + list.head.length)
  }

  def Errors(string: List[String], size: Int): Int = {
    if (string.isEmpty) 0
    else if (string.head.length > size) {
      println("You have too little screen")
      1
    }
    else
      Errors(string.tail, size)
  }

  def Spaces(words: List[String], spaces_count: Int): Line = {
    if (spaces_count == 1)
      new Word(words.head) :: Space(1) :: Nil
    else
      new Word(words.head) :: Nil
  }
}