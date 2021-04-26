// dear imgui: single-file wrapper include
// We use this to validate compiling all *.cpp files in a same compilation unit.
// Users of that technique (also called "Unity builds") can generally provide this themselves,
// so we don't really recommend you use this in your projects.

// Do this:
//    #define IMGUI_IMPLEMENTATION
// Before you include this file in *one* C++ file to create the implementation.
// Using this in your project will leak the contents of imgui_internal.h and ImVec2 operators in this compilation unit.
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx9.h"
#include "ImGUI/imgui_impl_win32.h"	   

#ifdef IMGUI_IMPLEMENTATION
#include "ImGui/imgui.cpp"
#include "ImGui/imgui_demo.cpp"
#include "ImGui/imgui_draw.cpp"
#include "ImGui/imgui_tables.cpp"
#include "ImGui/imgui_widgets.cpp"
#endif
