1. namespace xxx::xyx has not being defined, when it actually defined/declared.
    Cases
      - it might really not being defined, then define/declare it
      - the path hasn't been included (correctly)
	  include the correct path
      - Macro Name Collision in #include: When two files are having similar #ifndef... #define ..#endif
	  e.g #ifndef Header1
	      #define Header1
	      ....
	      #endif //Header1
	      
	  occurs in two included files
	    e.g #include <x/Header1.h>
		#include <home/y/Header1.h>
	
	Solution: Make one unique 

2. GCC Linking error ending with ...[abi:cxx11]
    This is a C++ ABI issue. The ABI for std::string has changed in GCC 5+ (related to C++11 requirements, but it applies even if you aren't using C++11). See:

	https://gcc.gnu.org/gcc-5/changes.html#libstdcxx
	
	If libprotobuf was built with GCC 4.x or prior, but your app is built with GCC 5, then you will see problems, because libprotobuf uses std::string in its interface. You have two options:
	
	Rebuild libprotobuf with GCC 5 (but now any apps built with GCC 4 won't work with the new version of libprotobuf).
    Build you app with -D_GLIBCXX_USE_CXX11_ABI=0 as described at the above link. This will force GCC to use the old ABI version.
    
    source: http://stackoverflow.com/questions/30124264/undefined-reference-to-googleprotobufinternalempty-string-abicxx11

3. to_string() is not a member of std in MinGW
	This could be caused by one of the following:
		i.  Not Enabling The C++0x or C++11 Standard. Use the --std=c++11 or --std=c++11 flag or greater
		Solution: add the necessary flags --std=c++11, --std=c++11, --std=c++1y, --std=c++14, ...
		
		ii. using to_sting() without namespace declaration or specifier e.g:
			declaration: using namespace std; or using std::to_sting;
		Solution:
			- add the necessary namespace declaration i.e 
				using namespace std; Or using std
		
	  	iii.Usually disabled by MinGW developers. Download this Patch: http://tehsausage.com/mingw-to-string
			This patch enables the following list of C++11 functions and templates in the std namespace:
			stoi, stol, stoul, stoll, stof, stod, stold, to_string, to_wstring

		This assumes you are using the official MinGW distribution.
		If you are applying this patch to a version of MinGW GCC later than 4.7, you should examine and apply the patches rather than using the zip file.
		
		* Download mingw-to-string-gcc47.zip which contains three patched header files.
		(Original patches: wchar.h, stdio.h, os_defines.h)
		
		* Copy wchar.h and stdio.h from the include directory in the zip file to the following directory (overwrite):
		C:\mingw\include
		(replace C:\mingw\ with the appropriate directory)
		
		* Copy os_defines.h to the following directory (overwrite):
		C:\mingw\lib\gcc\mingw32\4.7.0\include\c++\mingw32\bits
		(replace C:\mingw\ with the appropriate directory)
		(replace 4.7.0 with the correct version number)
		
		Author: Julian Smythe