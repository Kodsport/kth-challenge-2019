#!/usr/bin/env python3
import re
S = input()

if S.find('meow') > -1:
    print((0))
# 3 consecutive
elif ( re.search(r'eow', S)
        or re.search(r'meo', S)
        # 3 with gap
        or re.search(r'm.?ow', S)
        or re.search(r'me.?w', S)
        or re.search(r'me.ow', S)
        # swap
        or re.search(r'moew', S)
        ):
    print((1))
# 2 consecutive
elif ( re.search(r'ow', S)
        or re.search(r'eo', S)
        or re.search(r'me', S)
        # 2 with a gap
        or re.search(r'e.?w', S)
        or re.search(r'm.?.?w', S)
        or re.search(r'm.?o', S)
        # 3 with gap
        or re.search(r'm.o.w', S)
        or re.search(r'm.e.w', S)
        ):
    print((2))
elif S.find('m') > -1 \
        or S.find('e') > -1 \
        or S.find('o') > -1 \
        or S.find('w') > -1:
    print((3))
else:
    print((4))
