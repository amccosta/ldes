BEGIN {
  getline
  n=$1
  srand()
  for (i=0; i<n; i++) {
    print 3,rand()*9.5+0.5,rand()*9.5+0.5,rand()*0.5+2
  }
}
