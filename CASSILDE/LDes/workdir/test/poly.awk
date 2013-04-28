function crossp(a1, a2, a3, b1, b2, b3) {
  xcp = a2 * b3 - a3 * b2
  ycp = a3 * b1 - a1 * b3
  zcp = a1 * b2 - a2 * b1
  return sqrt(xcp * xcp + ycp * ycp + zcp * zcp)
}
BEGIN {
  print "5 1 1 0 0 0 1 1 1 -"
  getline
  getline
  nvert=$1
  for (i=0; i<nvert; i++) {
    getline
    vx[i]=$1
    vy[i]=$2
    vz[i]=$3
  }
  getline
  npoly=$1
  for (i=0; i<npoly;i++) {
    getline
    n=$1
    if (n>2) {
      for (j=0; j<n; j++) {
        k=2+j
        lv[j]=$k
      }
      tx=vx[lv[1]]
      ty=vy[lv[1]]
      tz=vz[lv[1]]
      dx1=vx[lv[0]]-tx
      dy1=vy[lv[0]]-ty
      dz1=vz[lv[0]]-tz
      dx2=vx[lv[2]]-tx
      dy2=vy[lv[2]]-ty
      dz2=vz[lv[2]]-tz
      crossp(dx2,dy2,dz2,dx1,dy1,dz1)
      cosa=xcp*tx+ycp*ty+zcp*tz
      printf "%d",n
      if (cosa>0) {
        for (j=0; j<n; j++) {
          printf " %d",lv[j]+1
        }
      }
      if (cosa<0) {
        for (j=n-1; j>=0; j--) {
          printf " %d",lv[j]+1
        }
      }
      printf "\n"
    }
  }
  print ""
  for (i=0; i<nvert; i++) {
    printf "%g %g %g\n",vx[i],vy[i],vz[i]
  }
  print ""
  print ""
}
