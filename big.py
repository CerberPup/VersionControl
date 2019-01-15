f= open("big.txt","w+")
for i in range(10000):
     f.write("This is line %d\r" % (i+1))
f.close() 