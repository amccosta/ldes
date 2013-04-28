NF==4 {
  a=$0
  getline
  b=$0
  getline
  c=$0
  getline
  d=$0
  printf "%s %s %s %s\n",a,b,c,d
  next
}
/Command / {
  getline
  getline
  next
}
