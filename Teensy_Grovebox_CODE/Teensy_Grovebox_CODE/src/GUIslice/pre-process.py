'''This script pre-process the generated code output of GUIslice and make it compatible with the project'''
from ctypes.wintypes import HDC
import os

os.rename('./GUIslice.ino', './GUIslice.cpp')
# copy the files into a list
with open('./GUIslice_GSLC.h') as f:
    header_file = f.readlines()
with open('./GUIslice.cpp') as f:
    cpp_file = f.readlines()

# delete setup(), loop()
start = cpp_file.index('//<Tick Callback !End!>\n')
del cpp_file[start:-1]

# move InitGUIslice_gen()

start = header_file.index('// Create page elements\n')
end = header_file.index('#endif // end _GUISLICE_GEN_H\n')

for i in range(start, end):
    cpp_file.append(header_file[i])
del header_file[start:end]

header_file.insert(start, 'void InitGUIslice_gen();\n')

# copy global variable definitions

start = header_file.index('// Create element storage\n')
end = header_file.index('//<GUI_Extra_Elements !End!>\n')
end -= 2

cpp_start = cpp_file.index('// Program Globals\n')
cpp_start += 2

for i in range(start, end):
    cpp_file.insert(cpp_start, header_file[i])
    cpp_start += 1

# add extern in header file

for i in range(start, end):
    header_file[i] = header_file[i].replace('gslc_', 'extern gslc_')

# add inculde "page.h"

start = cpp_file.index('#include "GUIslice_GSLC.h"\n')
cpp_file.insert(start, '#include "Pages/Pages.h"\n')

# connect touch callback

start = cpp_file.index('    switch (pElem->nId) {\n')
end = cpp_file.index('//<Button Enums !End!>\n')
end += 4
del cpp_file[start:end]
cpp_file.insert(start, '    PageManager.PageArr[PageManager.getCurPage()]->onTouch(pElem->nId);\n')

# overwrite the result
with open('./GUIslice_GSLC.h', 'w') as f:
    for line in header_file:
        f.write(line)
with open('./GUIslice.cpp', 'w') as f:
    for line in cpp_file:
        f.write(line)