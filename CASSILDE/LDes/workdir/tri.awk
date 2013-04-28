BEGIN {
  print "5 1 1 0 0 0 1 1 1 -"
  f = 0
}
/^#/ {
  next
}
/^f / && NF==4 {
  print "3", $2, $3, $4
  f = 1
  next
}
NF==3 {
  if (f) {
    f = 0
    print ""
  }
  print
  next
}
END {
  print ""
  print ""
}
