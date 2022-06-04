import numpy as np
from scipy.spatial import Delaunay

data1 = np.loadtxt('MapdataBGLla.dat')

u=np.empty(len(data1),dtype=float)
v=np.empty(len(data1),dtype=float)
z=np.empty(len(data1),dtype=float)
u=data1[:,1]
v=data1[:,0]
z=data1[:,2]

tri1=Delaunay(np.array([u,v]).T)

g=open('Korakuen_NamikiClub2.wrl','w')
g.write("#VRML V2.0 utf8\n")
g.write("Shape {\n")
g.write("geometry IndexedFaceSet {\n")
g.write("colorPerVertex FALSE\n")
g.write("solid TRUE\n")
g.write("coord Coordinate {\n")
g.write("point[\n")
for i in range(len(data1)):
    g.write(str(u[i]))
    g.write(" ")
    g.write(str(z[i]))
    g.write(" ")
    g.write(str(v[i]))
    g.write("\n")

g.write("]\n")
g.write("}\n")
g.write("coordIndex [\n")
for vert in tri1.simplices:
    g.write(str(vert[0]))
    g.write(" ")
    g.write(str(vert[2]))
    g.write(" ")
    g.write(str(vert[1]))
    g.write(" ")
    g.write("-1")
    g.write("\n")

g.write("]\n")

g.write("color Color{\n")
g.write("color [\n")
for vert in tri1.simplices:
    a=vert[0]
    b=vert[1]
    c=vert[2]
    if(data1[int(a)][3]==0 or data1[int(b)][3]==0 or data1[int(c)][3]==0):
        g.write("0.5 0.5 0.5,")
    elif(data1[int(a)][3]==1 and data1[int(b)][3]==1):
        g.write("0.5 0.5 0.5,")
    elif(data1[int(a)][3]==1 and data1[int(c)][3]==1):
        g.write("0.5 0.5 0.5,")
    elif(data1[int(b)][3]==1 and data1[int(c)][3]==1):
        g.write("0.5 0.5 0.5,")
    else:
        g.write("0.0 0.6 0.0,")
    g.write("\n")

g.write("]\n")
g.write("}\n")
g.write("}\n")
g.write("appearance Appearance{\n")
g.write("material Material{}\n")
g.write("}\n")
g.write("}\n")
g.write("Transform{\n")
g.write("translation 462 -78 566\n")
g.write("children[\n")
g.write("Shape{\n")
g.write("geometry Box{\n")
g.write("size 927 1 1135\n")
g.write("}\n")
g.write("appearance Appearance{\n")
g.write("material Material{}\n")
g.write("}\n")
g.write("}\n")
g.write("]\n")
g.write("}\n")



