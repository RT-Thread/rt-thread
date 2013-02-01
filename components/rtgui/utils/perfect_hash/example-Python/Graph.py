#!/usr/bin/env python
"""
This example shows how to use the class Graph.

The class implements a graph with 'N' vertices.  First, you connect the
graph with edges, which have a desired value associated.  Then the vertex
values are assigned, which will fail if the graph is cyclic.  The vertex
values are assigned such that the two values corresponding to an edge add
up to the desired edge value (mod N).
"""
import sys

sys.path.append('..')
from perfect_hash import Graph

G = Graph(3)
assert G.assign_vertex_values() == True
    
# Now we make an edge between vertex 0 and 1 with desired edge value 2:
G.connect(0, 1, 2)

# Make another edge 1:2 with desired edge value 1:
G.connect(1, 2, 1)
    
# The graph is still acyclic, and assigning values works:
assert G.assign_vertex_values() == True
assert G.vertex_values == [0, 2, 2]
    
# What do these values mean?
# When you add the values for edge 0:1 you get 0 + 2 = 2, as desired.
# For edge 1:2 you add 2 + 2 = 4 = 1 (mod 3), as desired.

# Adding edge 0:2 produces a loop, so the graph is no longer acyclic.
# Assigning values fails.
G.connect(0, 2, 0)

assert G.assign_vertex_values() == False


print 'OK'
