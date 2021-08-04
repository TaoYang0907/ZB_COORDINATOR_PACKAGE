from building import *

cwd = GetCurrentDir()
path = [cwd + '/inc']
src  = Glob('src/*.c')

# MG21
if GetDepend(['PKG_USING_ZB_COORDINATOR']):
    path += [cwd + '/class/mg21']
    src += Glob('class/mg21/at_device_mg21.c')

group = DefineGroup('at_mg21', src, depend = ['PKG_USING_ZB_COORDINATOR'], CPPPATH = path)

Return('group')
