#!BPY

"""
Name: 'ALGE Object (.alx)'
Blender: 244
Group: 'Export'
Tooltip: 'Exports .alx file for use with ALGE Kit'
"""
import Blender
from Blender import *
import bpy
import bpy
import os

        
def write_obj(filepath):    
    out = file(filepath, 'w')
    sce = bpy.data.scenes.active
    ob = sce.objects.active
    mesh = Mesh.New()        
    mesh.getFromObject(ob.name)

    editmode = Window.EditMode()
    if editmode: Window.EditMode(0)
    has_quads = False
    for f in mesh.faces:
        if len(f) == 4:
            has_quads = True
            break
    
    if has_quads:
        oldmode = Mesh.Mode()
        Mesh.Mode(Mesh.SelectModes['FACE'])
        
        mesh.sel = True
        tempob = sce.objects.new(mesh)
        mesh.quadToTriangle(0) # more=0 shortest length
        oldmode = Mesh.Mode(oldmode)
        sce.objects.unlink(tempob)
        
        Mesh.Mode(oldmode)
    
    objectname = ob.getData(True)
    basename = objectname.capitalize()

    out.write('//786//\r\nobj[ %s ] {\r\n' %basename)
        
    if (mesh.faceUV):
        for face in mesh.faces:
            for (vert, uvert) in zip(face.verts, face.uv):
                out.write('\tv[ %f, %f, %f]\r\n' % (vert.co.x, vert.co.y, vert.co.z) )
                out.write('\tn[ %f, %f, %f]\r\n' % (vert.no.x, vert.no.y, vert.no.z))
                out.write('\tt[ %f, %f]\r\n' % ( uvert.x-1.0, uvert.y-1.0 ) )

        out.write('}\r\n')
    elif (mesh.vertexColors):
        for face in mesh.faces:
            for (vert, color) in zip(face.verts, face.col):
                out.write('\tv[ %f, %f, %f]\r\n' % (vert.co.x, vert.co.y, vert.co.z) )
                out.write('\tn[ %f, %f, %f]\r\n' % (vert.no.x, vert.no.y, vert.no.z))
                out.write('\tc[ %f, %f, %f, %f]\r\n' % ( color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0) )

        out.write('}\r\n')
    else:
        for face in mesh.faces:
            for vert in face.verts:
                out.write('\tv[ %f, %f, %f]\r\n' % (vert.co.x, vert.co.y, vert.co.z) )
                out.write('\tn[ %f, %f, %f]\r\n' % (vert.no.x, vert.no.y, vert.no.z))
             
        out.write('}\n\n')
    
    if editmode: Window.EditMode(1)
    out.write('vertex_count[%i]\r\n\r\n//Good Luck !!' % (len(mesh.faces) * 3) )
    out.close()

filename = os.path.splitext(Blender.Get('filename'))[0]
Blender.Window.FileSelector(write_obj, "Export", '%s.alx' % filename)