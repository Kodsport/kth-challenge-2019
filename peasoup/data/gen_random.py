import random
import string

print 10
for place in xrange(10):
    print 10
    for _ in xrange(11):
        top = random.choice(string.ascii_lowercase)
        mid = ''.join(random.choice(string.ascii_lowercase + ' ') for _ in range(98))
        end = random.choice(string.ascii_lowercase)
        print top + mid + end
