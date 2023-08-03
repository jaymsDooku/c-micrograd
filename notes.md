NOP
------
y = a

dy/da = 1

MUL
------
y = a * b

dy/da = dy/da(a) * b

dy/da = 1 * b

dy/da = b

ADD
------
y = a + b

dy/da = dy/da(a) + dy/da(b)

dy/da = 1 + 0

dy/da = 1

EXP
------
y = a^b

dy/da = b * (a^(b-1))

RELU
------
y = max(0, a)

dy/da = (y > 0) ? 1 : 0


Midpoint Circle Algorithm
-----------------
F(p) = x^2 + y^2 - r^2
if F(p) < 0, p is in circle
F(p) = 0, p is on perimeter
F(p) > 0, p is outside circle