NF==3 {
  printf "2 1 1 %g %g %g 0.001 0.001 0.001\n",$1,$2,$3
  next
}
END {
  print ""
  print ""
}
