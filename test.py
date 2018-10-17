a = "Prince !"
n = 5
tempstrings = []
#for i in range(len(a)):
    #for j in range(n):
    #print(a[i:n+i])

# determine string length
#s_len = len(a)

# number of substring ex.apple n=3 app, ppl, ple
#subnum = s_len - n + 1

# put substring into list
#for i in range(subnum):
    #tempstrings.append(a[i:i + n])

for i in range(len(a) - n + 1):
    tempstrings.append(a[i:n+i])

print(tempstrings)
