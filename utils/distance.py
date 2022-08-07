import math
angle = 45 * math.pi / 180


dist = 2

V = math.sqrt(dist * 9.8 * math.sin(angle * 2))

print(V)