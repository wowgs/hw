package GIFReader

import java.awt.{Color, Dimension, Graphics2D}
import java.nio.file.{Files, Paths}

import scala.swing.{MainFrame, Panel, SimpleSwingApplication}

class DataPanel(data: Array[Array[Color]]) extends Panel {
  override def paintComponent(g: Graphics2D) {
    val width = data.length
    val height = data.map(_.length).max
    val dx = g.getClipBounds.width.toFloat / width
    val dy = g.getClipBounds.height.toFloat / height
    for {
      x <- data.indices
      y <- data(x).indices
      x1 = (x * dx).toInt
      y1 = (y * dy).toInt
      x2 = ((x + 1) * dx).toInt
      y2 = ((y + 1) * dy).toInt
    } {
      data(x)(y) match {
        case c: Color => g.setColor(c)
        case _ => g.setColor(Color.WHITE)
      }
      g.fillRect(x1, y1, x2 - x1, y2 - y1)
    }
  }
}

object Timer {
  def apply(interval: Int, repeats: Boolean = true)(op: => Unit) {
    val timeOut = new javax.swing.AbstractAction() {
      def actionPerformed(e: java.awt.event.ActionEvent) = op
    }
    val t = new javax.swing.Timer(interval, timeOut)
    t.setRepeats(repeats)
    t.start()
  }
}

object Draw extends SimpleSwingApplication {

  val gif: gif_file = decoder("file.gif")
  val scale = 30
  val back = Array.fill(gif.header.width, gif.header.height)(color(gif.global_color_table(gif.header.background_color)))
  val frames = get_frames(gif.images, gif.image_descriptors, Nil).toArray
  val mod = frames.length
  var num = 0

  def decoder(path: String): gif_file = {
    val headerCodec = (uint16L :: uint16L :: bool :: uintL(3) :: bool :: uintL(3) :: uint8L :: uint8L).as[gif_header]
    val imageCodec = (uint16L :: uint16L :: uint16L :: uint16L :: bool :: bool :: bool :: uint2L :: uintL(3)).as[image]
    val animationCodec = (uintL(3) :: bool :: bool :: uint16L :: uint8L).as[animation]
    def create_color_table(table: Array[Int], size: Int, vector: BitVector): Array[Int] = {
      if (size == 0) {
        table
      }
      else {
        val red = vector.take(8).toInt(false, LittleEndian)
        val green = vector.drop(8).take(8).toInt(false, LittleEndian)
        val blue = vector.drop(16).take(8).toInt(false, LittleEndian)
        val new_color = red * 1000000 + green * 1000 + blue //color in format RRRGGGBBB
        create_color_table(table :+ new_color, size - 1, vector.drop(24))
      }
    }

    def drop_away(vector: BitVector): BitVector = {
      val size = vector.take(8).toInt(false, LittleEndian)
      val new_vector = vector.drop(8)
      if (size == 0) {
        new_vector
      }
      else {
        drop_away(new_vector.drop(8 * size))
      }
    }

    def Get_IM(vec: BitVector, acc: BitVector): BitVector = {
      def bits_rev(in_bl: BitVector, ou_bl: BitVector): BitVector = {
        if (in_bl.isEmpty) {
          ou_bl
        }
        else {
          bits_rev(in_bl.drop(8), ou_bl ++ in_bl.take(8).reverseBitOrder)
        }
      }
      val size = vec.take(8).toInt(false, LittleEndian)
      val vec = vec.drop(8)
      if (size == 0) {
        acc
      }
      else {
        val block = vec.take(size * 8)
        Get_IM(vec.drop(size * 8), acc ++ bits_rev(block, BitVector(Nil)))
      }
    }

    def case_desc(vec: BitVector, giffile: gif_file): gif_file = {
      val exten = vec.take(8).toInt(false, LittleEndian)
      if (exten == 44) {
        val new_im_desc = imageCodec.decode(vec.drop(8)).require.value
        var new_LCT: Array[Int] = Array[Int]()
        var new_vec = vec.drop(8).drop(9 * 8)
        if (new_im_desc.LCT_flag) {
          new_LCT = create_color_table(new_LCT, Math.pow(2, new_im_desc.LCT_size + 1).toInt, vec)
          new_vec = new_vec.drop(Math.pow(2, new_im_desc.LCT_size + 1).toInt * 3 * 8)
        }
        val root = new_vec.take(8).toInt(false, LittleEndian)
        new_vec = new_vec.drop(8)
        val image_vec = Get_IM(new_vec, BitVector(Nil))
        var CT: Array[Int] = Array[Int]()
        if (new_im_desc.LCT_flag) {
          CT = new_LCT
        }
        else {
          CT = giffile.global_color_table
        }
        val new_image = LZW(root + 1, image_vec, CT.toList ::: List(1000000000, 2000000000))
        val new_gif = new gif_file(giffile.header, giffile.global_color_table, new_im_desc ::
          giffile.image_descriptors, new_image :: giffile.images,
          giffile.animations)
        new_vec = drop_away(new_vec)
        case_desc(new_vec, new_gif)
      }
      else if (exten == 59) {
        val gif_out = new gif_file(giffile.header, giffile.global_color_table, giffile.image_descriptors.reverse,
          giffile.images.reverse, giffile.animations.reverse)
        gif_out
      }
      else if (exten == 33) {
        val label = vec.drop(8).take(8).toInt(false, LittleEndian)
        if (label == 249) {
          val new_anim = animationCodec.decode(vec.drop(27)).require.value
          val new_gif = new gif_file(giffile.header, giffile.global_color_table, giffile.image_descriptors,
            giffile.images, new_anim :: giffile.animations)
          case_desc(vec.drop(16).drop(6 * 8), new_gif)
        }
        else if (label == 254) {
          val new_vec = drop_away(vec.drop(16))
          case_desc(new_vec, giffile)
        }
        else if (label == 1) {
          val new_vec = drop_away(vec.drop(16).drop(13 * 8))
          case_desc(new_vec, giffile)
        }
        else if (label == 255) {
          val new_vec = drop_away(vec.drop(16))
          case_desc(new_vec, giffile)
        }
        else {
          throw new NoSuchElementException()
        }
      }
      else {
        throw new NoSuchElementException()
      }
    }
    val byte_ar = Files.readAllBytes(Paths.get(path))
    var bitVector = BitVector(byte_ar).drop(48)
    val decoded_header = headerCodec.decode(bitVector).require.value
    bitVector = bitVector.drop(7 * 8)
    var GCT: Array[Int] = Array[Int](0)
    if (decoded_header.GCT_flag) {
      GCT = create_color_table(Array[Int](), Math.pow(2, decoded_header.GCT_size + 1).toInt, bitVector)
      bitVector = bitVector.drop(Math.pow(2, decoded_header.GCT_size + 1).toInt * 3 * 8)
    }
    val file = new gif_file(decoded_header, GCT, Nil, Nil, Nil)
    case_desc(bitVector, file)
  }

  def LZW(min_root: Int, input: BitVector, CT: List[Int]): Array[Int] = {
    def LoAr(ar: List[Int], acc: List[Array[Int]]): List[Array[Int]] = {
      if (ar.isEmpty) {
        acc.reverse
      }
      else {
        LoAr(ar.tail, Array(ar.head) :: acc)
      }
    }
    def iter(size_of_elem: Int, pref: Array[Int], in: BitVector, table: List[Array[Int]], out: Array[Int],
             last_elem: Int): Array[Int] = {
      val elem = in.take(size_of_elem).reverseBitOrder.toInt(false, LittleEndian)
      if (elem == last_elem) {
        out
      }
      else if (elem < table.length) {
        val New_t = table ::: List(pref :+ table(elem)(0))
        val New_o = out ++ table(elem)
        iter(1 + (Math.log(New_t.length) / Math.log(2)).toInt, table(elem), in.drop(size_of_elem),
          New_t, New_o, last_elem)
      }
      else {
        val New_t = table ::: List(pref :+ pref(0))
        val New_o = out ++ (pref :+ pref(0))
        iter(1 + (Math.log(New_t.length) / Math.log(2)).toInt, pref :+ pref(0), in.drop(size_of_elem),
          New_t, New_o, last_elem)
      }
    }
    val clear_elem = input.take(min_root).reverseBitOrder.toInt(false, LittleEndian)
    val first_elem = input.drop(min_root).take(min_root).reverseBitOrder.toInt(false, LittleEndian)
    iter(min_root, Array(CT(first_elem)), input.drop(2 * min_root), LoAr(CT, Nil),
      Array(CT(first_elem)), clear_elem + 1)
  }

  def color(col: Int): Color = {
    new Color(col / 1000000, (col / 1000) % 1000, col % 1000)
  }

  def get_frames(ims: List[Array[Int]], dscs: List[image], acc: List[Array[Array[Color]]]): List[Array[Array[Color]]] = {
    def frame(back: Array[Array[Color]], im: Array[Int], w: Int, h: Int, desc: image): Array[Array[Color]] = {
      val new_frame = back
      var i = 0
      for {
        x <- 0 until w
        y <- 0 until h
      } {
        if (x >= desc.LP && y >= desc.TP) {
          new_frame(x)(y) = color(im(i))
          i = i + 1
        }
      }
      new_frame
    }
    if (ims.isEmpty) {
      acc
    }
    else {
      get_frames(ims.tail, dscs.tail, acc :+ frame(Array.fill(gif.header.width,
        gif.header.height)(color(gif.global_color_table(gif.header.background_color))), ims.head,
        gif.header.width, gif.header.height, dscs.head))
    }
  }

  def top = new MainFrame {
    def tick() = {
      val disp_method = gif.animations(num % mod).disposal_method
      if (disp_method == 2) {
        contents = new DataPanel(back) {
          preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
        }
      }
      else if (disp_method == 3) {
        contents = new DataPanel(frames((num - 1) % mod)) {
          preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
        }
      }
      num += 1
      contents = new DataPanel(frames((num - 1) % mod)) {
        preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
      }
    }

    Timer(gif.animations(num % mod).delay) {
      tick()
    }
  }

  case class gif_header(width: Int, height: Int, GCT_flag: Boolean, color_resolution: Int, SF_flag: Boolean,
                        GCT_size: Int, background_color: Int, ratio: Int)

  case class image(LP: Int, TP: Int, width: Int, height: Int, LCT_flag: Boolean, interlace_flag: Boolean,
                   sort_flag: Boolean, reserved_bits: Int, LCT_size: Int)

  case class animation(disposal_method: Int, UI_flag: Boolean, TC_flag: Boolean, delay: Int, transparent_color: Int)

  case class gif_file(header: gif_header, global_color_table: Array[Int], image_descriptors: List[image],
                      images: List[Array[Int]], animations: List[animation])
}