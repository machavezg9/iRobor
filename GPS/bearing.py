# Let R be the radius of earth
# 'L' be the longitude
# 'theta' be the latitude
# 'beta' be bearing
# Denoting two different points A and B as L_a theta_a and L_b theta_b
# Bearing is measured from North direction: 0 deg bearing means North, 90 deg bearing is East
# 180 deg bearing is South, and 270 deg bearing is West.
import math
# Bearing from point A to B, can be calculated with:
# beta = atan2(X,Y)
# where, X and Y can be calculated as follows:
# delta_L = |L_b - L_a| 
# X = cos(theta_b) * sin(delta_L)
# Y = cos(theta_a) * sin(theta_b) - sin(theta_a) * cos(theta_b) * cos(delta_L)
#Point A Kansas City
L_a = -94.581213
theta_a = 39.099912
#Point B St Louis
L_b = -90.200203
theta_b = 38.627089

delta_L = abs(L_b - L_a)
print delta_L
X = math.cos(math.radians(theta_b)) * math.sin(math.radians(delta_L))
print X
Y = math.cos(math.radians(theta_a)) * math.sin(math.radians(theta_b)) - math.sin(math.radians(theta_a)) * math.cos(math.radians(theta_b)) * math.cos(math.radians(delta_L))
print Y
beta = math.atan2(X,Y)
print math.degrees(beta)
