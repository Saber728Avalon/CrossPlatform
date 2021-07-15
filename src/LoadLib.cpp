#include "LoadLib.h"
#include "DebugOut.h"

LOAD_LIB_HANDLE PW_LoadLib(const char *pszPath, LOAD_FLAGS flags)
{
	LOAD_LIB_HANDLE hDlh = 0;

	//组织路径
#if defined(_WIN32)
	char utf8name_stack[MAX_PATH];
	char *utf8name_malloc = NULL;
	char *utf8name = utf8name_stack;
	wchar_t wname_stack[MAX_PATH];
	wchar_t *wname_malloc = NULL;
	wchar_t *wname = wname_stack;
	int len;

	if (flags == LOAD_FLAGS::CHARACTER_ASCII)
	{
		int wlen = MultiByteToWideChar(CP_ACP, 0, pszPath, -1, NULL, 0);
		if (wlen > MAX_PATH) {
			wname = wname_malloc = (wchar_t*)malloc(wlen * sizeof(wchar_t));
		}
		if (wname == NULL ||
			!MultiByteToWideChar(CP_ACP, 0, pszPath, -1, wname, wlen)) {
			goto unlock;
		}
	}
	else
	{
		wname = (LPWSTR)pszPath;
	}

	len = WideCharToMultiByte(CP_UTF8, 0, wname, -1, NULL, 0, NULL, NULL);
	if (len > MAX_PATH) {
		utf8name = utf8name_malloc = (char *)malloc(len);
	}
	if (utf8name == NULL ||
		!WideCharToMultiByte(CP_UTF8, 0, wname, -1,
			utf8name, len, NULL, NULL)) {
		goto unlock;
	}
#endif

	//如果已经加载则先释放

	//加载库
#ifdef WIN32
	{
		HINSTANCE h;

		h = LoadLibraryExW(wname, NULL,
			LOAD_WITH_ALTERED_SEARCH_PATH);
		if (h == NULL) {
			DWORD dw = GetLastError();
			char chTmpBuf[64] = { 0 };
			sprintf(chTmpBuf, "%d", dw);
			DebugOut(chTmpBuf);
			DebugOut("\n");
			goto unlock;
		}
		hDlh = h;
	}
#endif /* WIN32 */


#if  defined(__APPLE__) || defined(__linux__) || defined(__unix__)
	{
#if defined(USE_DLFCN)
#ifdef NTO
		/* Neutrino needs RTLD_GROUP to load Netscape plugins. (bug 71179) */
		int dl_flags = RTLD_GROUP;
#elif defined(AIX)
		/* AIX needs RTLD_MEMBER to load an archive member.  (bug 228899) */
		int dl_flags = RTLD_MEMBER;
#else
		int dl_flags = 0;
#endif
		void *h = NULL;

		if (flags & PR_LD_LAZY) {
			dl_flags |= RTLD_LAZY;
		}
		if (flags & PR_LD_NOW) {
			dl_flags |= RTLD_NOW;
		}
		if (flags & PR_LD_GLOBAL) {
			dl_flags |= RTLD_GLOBAL;
		}
		if (flags & PR_LD_LOCAL) {
			dl_flags |= RTLD_LOCAL;
		}
#if defined(DARWIN)
		/* ensure the file exists if it contains a slash character i.e. path */
		/* DARWIN's dlopen ignores the provided path and checks for the */
		/* plain filename in DYLD_LIBRARY_PATH */
		if (strchr(pszPath, PR_DIRECTORY_SEPARATOR) == NULL ||
			PR_Access(name, PR_ACCESS_EXISTS) == PR_SUCCESS) {
			h = dlopen(pszPath, dl_flags);
		}
#else
		h = dlopen(pszPath, dl_flags);
#endif
#elif defined(USE_HPSHL)
		int shl_flags = 0;
		shl_t h;

		/*
		* Use the DYNAMIC_PATH flag only if 'name' is a plain file
		* name (containing no directory) to match the behavior of
		* dlopen().
		*/
		if (strchr(pszPath, PR_DIRECTORY_SEPARATOR) == NULL) {
			shl_flags |= DYNAMIC_PATH;
		}
		if (flags & PR_LD_LAZY) {
			shl_flags |= BIND_DEFERRED;
		}
		if (flags & PR_LD_NOW) {
			shl_flags |= BIND_IMMEDIATE;
		}
		/* No equivalent of PR_LD_GLOBAL and PR_LD_LOCAL. */
		h = shl_load(pszPath, shl_flags, 0L);
#elif defined(USE_MACH_DYLD)
		NSModule h = pr_LoadMachDyldModule(name);
#else
#error Configuration error
#endif
		char *psz =(char *) dlerror();
		if (NULL != psz)
		{
			DebugOut(psz);
			DebugOut("\n");
		}
		else
		{
			DebugOut("No Load Error\n");
		}
		if (h) 
		{

			hDlh = h;
		}
		else
		{
			hDlh = NULL;
		}
	}
#endif /* XP_UNIX && !(XP_MACOSX && USE_MACH_DYLD) */

unlock:
	return hDlh;
}


unsigned int  PW_UnloadLib(LOAD_LIB_HANDLE dlh)
{
	int result = 0;
#if  defined(__APPLE__) || defined(__linux__) || defined(__unix__)


	#ifdef USE_DLFCN
		result = dlclose(dlh);
	#elif defined(USE_HPSHL)
		result = shl_unload(dlh);
	#elif defined(USE_MACH_DYLD)
		if (lib->dlh) {
			result = NSUnLinkModule(dlh, NSUNLINKMODULE_OPTION_NONE) ? 0 : -1;
		}
	#else
		#error Configuration error
	#endif
#endif /* XP_UNIX */

#ifdef _WIN32
	if (NULL != dlh) {
		BOOL bSucc = FreeLibrary((HINSTANCE)(dlh));
		if (FALSE == bSucc)
		{
			result = -1;
		}
	}
#endif  /* _WIN32 */

	return result;
}


void * PW_FindSymbolInLib(LOAD_LIB_HANDLE lib, const char *name)
{

	void *f = NULL;

#ifdef WIN32
	f = GetProcAddress(lib, name);
#endif  /* WIN32 */

#if  defined(__APPLE__) || defined(__linux__) || defined(__unix__)
#ifdef USE_DLFCN
	f = dlsym(lib, name);
#elif defined(USE_HPSHL)
	if (shl_findsym(&lib, name, TYPE_PROCEDURE, &f) == -1) {
		f = NULL;
	}
#elif defined(USE_MACH_DYLD)
	if (lib) {
		NSSymbol symbol;
		symbol = NSLookupSymbolInModule(lib, name);
		if (symbol != NULL) {
			f = NSAddressOfSymbol(symbol);
		}
		else {
			f = NULL;
		}
	}
#endif
#endif /* XP_UNIX */
	return f;
}