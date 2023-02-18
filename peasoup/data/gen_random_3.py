import random
import string

print 10
words = ["pea soup", "pancakes"]
for place in xrange(10):
    print 10
    for _ in xrange(11):
        base = random.choice(words)
        i1, i2 = sorted(random.sample(range(8), 2))
        if (i1 == 0 and i2 == 3) \
                or (i1 == 3 and i2 == 7):
            i2 = 4
        print base[:i1] + base[i2] + base[i1+1:i2] + base[i1] + base[i2+1:]
