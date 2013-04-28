NF==6 {
  f=1
  sx=$1; ex=$2; dx=$3
  sy=$4; ey=$5; dy=$6
  if (sx>ex || sy>ey || dx<1 || dy<1) f=0
  next
}
END {
  if (f) {
    for (x = sx; x <= ex; x += dx) {
      for (y = sy; y <= ey; y += dy) {
        comm = "./Eval asa0.cf "x" "y
        system(comm)
        getline < "eval.out"
        print x, y, $1
        close("eval.out")
      }
      print ""
    }
  }
}
