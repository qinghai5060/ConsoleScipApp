# ConsoleScipApp
This project is just for test in VS2015.  It is forked from https://github.com/msakai/scip-maxsat.
you cant configure your vs by:
1. make a empty project and copy "mylib" to it.
2. right click your project and open its "Properties" . Add the "mylib" to this project by adding it to 
   "Additional Include Directories" in "C/C++" .
3. also add "mylib" to "Additional Library Directories" in "Linker" ->"General"
4. add right .lib to "Linker" -> "Input" ->"Additional Dependercies".if your new a console application ,
   you should add "libscip-3.2.1.mingw.x86.msvc.opt.spx.lib",not "libscip-3.2.1.mingw.x86_64.msvc.opt.spx.lib".
   if you dont set like this,some errors will be showed to you like:"LNK2019	unresolved external 
   symbol _SCIPeventhdlrGetName referenced in function "enum SCIP_Retcode __cdecl eventCopyBestsol" 
