from anytree import AnyNode, RenderTree
from anytree.exporter import DotExporter

try:

    f = open("out.txt", "r")

    mm = dict()


    l = f.readline()

    l = l[0:len(l)-1]
    tt = AnyNode(name=l, val=l[:l.rfind("(")])

    mm[l] = tt
    l = f.readline()
    while(len(l)>0):
        l = l[0:len(l)-1]
        a = l.split("`")
        ss = a[1][:a[1].rfind("(")]
        ty = AnyNode(name=a[1],parent= mm[a[0]], val=ss)
        if(a[1] not in mm.keys()):
            mm[a[1]] = ty
        l = f.readline()



    DotExporter(tt).to_picture("OutputTree/tree.png")
    # DotExporter(tt).to_dotfile("OutputTree/trees.dot")

except:
    print("Wrong tree format")