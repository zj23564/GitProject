#pragma once

#ifdef _LINUX
/* Formatted i/o */
#define _tprintf        wprintf
#define _tprintf_l      _wprintf_l
#define _tprintf_s      wprintf_s
#define _tprintf_s_l    _wprintf_s_l
#define _tprintf_p      _wprintf_p
#define _tprintf_p_l    _wprintf_p_l
#define _tcprintf       _cwprintf
#define _tcprintf_l     _cwprintf_l
#define _tcprintf_s     _cwprintf_s
#define _tcprintf_s_l   _cwprintf_s_l
#define _tcprintf_p     _cwprintf_p
#define _tcprintf_p_l   _cwprintf_p_l
#define _vtcprintf      _vcwprintf
#define _vtcprintf_l    _vcwprintf_l
#define _vtcprintf_s    _vcwprintf_s
#define _vtcprintf_s_l  _vcwprintf_s_l
#define _vtcprintf_p    _vcwprintf_p
#define _vtcprintf_p_l  _vcwprintf_p_l
#define _ftprintf       fwprintf
#define _ftprintf_l     _fwprintf_l
#define _ftprintf_s     fwprintf_s
#define _ftprintf_s_l   _fwprintf_s_l
#define _ftprintf_p     _fwprintf_p
#define _ftprintf_p_l   _fwprintf_p_l
#define _stprintf       _swprintf
#define _stprintf_l     __swprintf_l
#define _stprintf_s     swprintf_s
#define _stprintf_s_l   _swprintf_s_l
#define _stprintf_p     _swprintf_p
#define _stprintf_p_l   _swprintf_p_l
#define _sctprintf      _scwprintf
#define _sctprintf_l    _scwprintf_l
#define _sctprintf_p    _scwprintf_p
#define _sctprintf_p_l  _scwprintf_p_l
#define _sntprintf      _snwprintf
#define _sntprintf_l    _snwprintf_l
#define _sntprintf_s    _snwprintf_s
#define _sntprintf_s_l  _snwprintf_s_l
#define _vtprintf       vwprintf
#define _vtprintf_l     _vwprintf_l
#define _vtprintf_s     vwprintf_s
#define _vtprintf_s_l   _vwprintf_s_l
#define _vtprintf_p     _vwprintf_p
#define _vtprintf_p_l   _vwprintf_p_l
#define _vftprintf      vfwprintf
#define _vftprintf_l    _vfwprintf_l
#define _vftprintf_s    vfwprintf_s
#define _vftprintf_s_l  _vfwprintf_s_l
#define _vftprintf_p    _vfwprintf_p
#define _vftprintf_p_l  _vfwprintf_p_l
#define _vstprintf      vswprintf
#define _vstprintf_l    _vswprintf_l
#define _vstprintf_s    vswprintf_s
#define _vstprintf_s_l  _vswprintf_s_l
#define _vstprintf_p    _vswprintf_p
#define _vstprintf_p_l  _vswprintf_p_l
#define _vsctprintf     _vscwprintf
#define _vsctprintf_l   _vscwprintf_l
#define _vsctprintf_p   _vscwprintf_p
#define _vsctprintf_p_l _vscwprintf_p_l
#define _vsntprintf     _vsnwprintf
#define _vsntprintf_l   _vsnwprintf_l
#define _vsntprintf_s   _vsnwprintf_s
#define _vsntprintf_s_l _vsnwprintf_s_l

#define _tscanf         wscanf
#define _tscanf_l       _wscanf_l
#define _tscanf_s       wscanf_s
#define _tscanf_s_l     _wscanf_s_l
#define _tcscanf        _cwscanf
#define _tcscanf_l      _cwscanf_l
#define _tcscanf_s      _cwscanf_s
#define _tcscanf_s_l    _cwscanf_s_l
#define _ftscanf        fwscanf
#define _ftscanf_l      _fwscanf_l
#define _ftscanf_s      fwscanf_s
#define _ftscanf_s_l    _fwscanf_s_l
#define _stscanf        swscanf
#define _stscanf_l      _swscanf_l
#define _stscanf_s      swscanf_s
#define _stscanf_s_l    _swscanf_s_l
#define _sntscanf       _snwscanf
#define _sntscanf_l     _snwscanf_l
#define _sntscanf_s     _snwscanf_s
#define _sntscanf_s_l   _snwscanf_s_l


/* Unformatted i/o */

#define _fgettc         fgetwc
#define _fgettc_nolock  _fgetwc_nolock
#define _fgettchar      _fgetwchar
#define _fgetts         fgetws
#define _fputtc         fputwc
#define _fputtc_nolock  _fputwc_nolock
#define _fputtchar      _fputwchar
#define _fputts         fputws
#define _cputts         _cputws
#define _cgetts         _cgetws
#define _cgetts_s       _cgetws_s
#define _gettc          getwc
#define _gettc_nolock   _getwc_nolock
#define _gettch         _getwch
#define _gettch_nolock  _getwch_nolock
#define _gettche        _getwche
#define _gettche_nolock _getwche_nolock
#define _gettchar       getwchar
#define _gettchar_nolock _getwchar_nolock
#define _getts          _getws
#define _getts_s        _getws_s
#define _puttc          putwc
#define _puttc_nolock   _putwc_nolock
#define _puttchar       putwchar
#define _puttchar_nolock _putwchar_nolock
#define _puttch         _putwch
#define _puttch_nolock  _putwch_nolock
#define _putts          _putws
#define _ungettc        ungetwc
#define _ungettc_nolock _ungetwc_nolock
#define _ungettch       _ungetwch
#define _ungettch_nolock _ungetwch_nolock


/* String conversion functions */

#define _tcstod     wcstod
#define _tcstol     wcstol
#define _tcstoul    wcstoul
#define _tcstoi64   _wcstoi64
#define _tcstoui64  _wcstoui64
#define _ttof       _wtof
#define _tstof      _wtof
#define _tstol      _wtol
#define _tstoi      _wtoi
#define _tstoi64    _wtoi64
#define _tcstod_l     _wcstod_l
#define _tcstol_l     _wcstol_l
#define _tcstoul_l    _wcstoul_l
#define _tcstoi64_l   _wcstoi64_l
#define _tcstoui64_l  _wcstoui64_l
#define _tstof_l      _wtof_l
#define _tstol_l      _wtol_l
#define _tstoi_l      _wtoi_l
#define _tstoi64_l    _wtoi64_l

#define _itot_s     _itow_s
#define _ltot_s     _ltow_s
#define _ultot_s    _ultow_s
#define _itot       _itow
#define _ltot       _ltow
#define _ultot      _ultow
#define _ttoi       _wtoi
#define _ttol       _wtol

#define _ttoi64     _wtoi64
#define _i64tot_s   _i64tow_s
#define _ui64tot_s  _ui64tow_s
#define _i64tot     _i64tow
#define _ui64tot    _ui64tow

/* String functions */

#define _tcscat         wcscat
#define _tcscat_s       wcscat_s
#define _tcschr         wcschr
#define _tcscpy         wcscpy
#define _tcscpy_s       wcscpy_s
#define _tcscspn        wcscspn
#define _tcslen         wcslen
#define _tcsnlen        wcsnlen
#define _tcsncat        wcsncat
#define _tcsncat_s      wcsncat_s
#define _tcsncat_l      _wcsncat_l
#define _tcsncat_s_l    _wcsncat_s_l
#define _tcsncpy        wcsncpy
#define _tcsncpy_s      wcsncpy_s
#define _tcsncpy_l      _wcsncpy_l
#define _tcsncpy_s_l    _wcsncpy_s_l
#define _tcspbrk        wcspbrk
#define _tcsrchr        wcsrchr
#define _tcsspn         wcsspn
#define _tcsstr         wcsstr
#define _tcstok         wcstok
#define _tcstok_s       wcstok_s
#define _tcstok_l       _wcstok_l
#define _tcstok_s_l     _wcstok_s_l
#define _tcserror       _wcserror
#define _tcserror_s     _wcserror_s
#define __tcserror      __wcserror
#define __tcserror_s    __wcserror_s

#define _tcsdup         _wcsdup
#define _tcsnset        _wcsnset
#define _tcsnset_s      _wcsnset_s
#define _tcsnset_l      _wcsnset_l
#define _tcsnset_s_l    _wcsnset_s_l
#define _tcsrev         _wcsrev
#define _tcsset         _wcsset
#define _tcsset_s       _wcsset_s
#define _tcsset_l       _wcsset_l
#define _tcsset_s_l     _wcsset_s_l

#define _tcscmp         wcscmp
#define _tcsicmp        _wcsicmp
#define _tcsicmp_l      _wcsicmp_l
#define _tcsnccmp       wcsncmp
#define _tcsncmp        wcsncmp
#define _tcsncicmp      _wcsnicmp
#define _tcsncicmp_l    _wcsnicmp_l
#define _tcsnicmp       _wcsnicmp
#define _tcsnicmp_l     _wcsnicmp_l

#define _tcscoll        wcscoll
#define _tcscoll_l      _wcscoll_l
#define _tcsicoll       _wcsicoll
#define _tcsicoll_l     _wcsicoll_l
#define _tcsnccoll      _wcsncoll
#define _tcsnccoll_l    _wcsncoll_l
#define _tcsncoll       _wcsncoll
#define _tcsncoll_l     _wcsncoll_l
#define _tcsncicoll     _wcsnicoll
#define _tcsncicoll_l   _wcsnicoll_l
#define _tcsnicoll      _wcsnicoll
#define _tcsnicoll_l    _wcsnicoll_l

#ifdef _DEBUG
#define _tcsdup_dbg _wcsdup_dbg
#endif

/* Execute functions */

#define _texecl     _wexecl
#define _texecle    _wexecle
#define _texeclp    _wexeclp
#define _texeclpe   _wexeclpe
#define _texecv     _wexecv
#define _texecve    _wexecve
#define _texecvp    _wexecvp
#define _texecvpe   _wexecvpe

#define _tspawnl    _wspawnl
#define _tspawnle   _wspawnle
#define _tspawnlp   _wspawnlp
#define _tspawnlpe  _wspawnlpe
#define _tspawnv    _wspawnv
#define _tspawnve   _wspawnve
#define _tspawnvp   _wspawnvp
#define _tspawnvp   _wspawnvp
#define _tspawnvpe  _wspawnvpe

#define _tsystem    _wsystem


/* Time functions */

#define _tasctime   _wasctime
#define _tctime     _wctime
#define _tctime32   _wctime32
#define _tctime64   _wctime64
#define _tstrdate   _wstrdate
#define _tstrtime   _wstrtime
#define _tutime     _wutime
#define _tutime32   _wutime32
#define _tutime64   _wutime64
#define _tcsftime   wcsftime
#define _tcsftime_l _wcsftime_l

#define _tasctime_s   _wasctime_s
#define _tctime_s     _wctime_s
#define _tctime32_s   _wctime32_s
#define _tctime64_s   _wctime64_s
#define _tstrdate_s   _wstrdate_s
#define _tstrtime_s   _wstrtime_s

/* Directory functions */

#define _tchdir             _wchdir
#define _tgetcwd            _wgetcwd
#define _tgetdcwd           _wgetdcwd
#define _tgetdcwd_nolock    _wgetdcwd_nolock
#define _tmkdir             _wmkdir
#define _trmdir             _wrmdir

#ifdef _DEBUG
#define _tgetcwd_dbg        _wgetcwd_dbg
#define _tgetdcwd_dbg       _wgetdcwd_dbg
#define _tgetdcwd_lk_dbg    _wgetdcwd_lk_dbg
#endif

/* Environment/Path functions */

#define _tfullpath      _wfullpath
#define _tgetenv        _wgetenv
#define _tgetenv_s      _wgetenv_s
#define _tdupenv_s      _wdupenv_s
#define _tmakepath      _wmakepath
#define _tmakepath_s    _wmakepath_s
#define _tpgmptr        _wpgmptr
#define _get_tpgmptr    _get_wpgmptr
#define _tputenv        _wputenv
#define _tputenv_s      _wputenv_s
#define _tsearchenv     _wsearchenv
#define _tsearchenv_s   _wsearchenv_s
#define _tsplitpath     _wsplitpath
#define _tsplitpath_s   _wsplitpath_s

#ifdef _DEBUG
#define _tfullpath_dbg  _wfullpath_dbg
#define _tdupenv_s_dbg  _wdupenv_s_dbg
#endif

/* Stdio functions */

#define _tfdopen    _wfdopen
#define _tfsopen    _wfsopen
#define _tfopen     _wfopen
#define _tfopen_s   _wfopen_s
#define _tfreopen   _wfreopen
#define _tfreopen_s _wfreopen_s
#define _tperror    _wperror
#define _tpopen     _wpopen
#define _ttempnam   _wtempnam
#define _ttmpnam    _wtmpnam
#define _ttmpnam_s  _wtmpnam_s

#ifdef _DEBUG
#define _ttempnam_dbg   _wtempnam_dbg
#endif


/* Io functions */

#define _taccess    _waccess
#define _taccess_s  _waccess_s
#define _tchmod     _wchmod
#define _tcreat     _wcreat
#define _tfindfirst       _wfindfirst
#define _tfindfirst32     _wfindfirst32
#define _tfindfirst64     _wfindfirst64
#define _tfindfirsti64    _wfindfirsti64
#define _tfindfirst32i64  _wfindfirst32i64
#define _tfindfirst64i32  _wfindfirst64i32
#define _tfindnext        _wfindnext
#define _tfindnext32      _wfindnext32
#define _tfindnext64      _wfindnext64
#define _tfindnexti64     _wfindnexti64
#define _tfindnext32i64   _wfindnext32i64
#define _tfindnext64i32   _wfindnext64i32
#define _tmktemp    _wmktemp
#define _tmktemp_s  _wmktemp_s
#define _topen      _wopen
#define _tremove    _wremove
#define _trename    _wrename
#define _tsopen     _wsopen
#define _tsopen_s   _wsopen_s
#define _tunlink    _wunlink

#define _tfinddata_t      _wfinddata_t
#define _tfinddata32_t    _wfinddata32_t
#define _tfinddata64_t    _wfinddata64_t
#define _tfinddatai64_t   _wfinddatai64_t
#define _tfinddata32i64_t _wfinddata32i64_t
#define _tfinddata64i32_t _wfinddata64i32_t


/* Stat functions */

#define _tstat      _wstat
#define _tstat32    _wstat32
#define _tstat32i64 _wstat32i64
#define _tstat64    _wstat64
#define _tstat64i32 _wstat64i32
#define _tstati64   _wstati64


/* Setlocale functions */

#define _tsetlocale _wsetlocale


/* Redundant "logical-character" mappings */

#define _tcsclen        wcslen
#define _tcscnlen       wcsnlen
#define _tcsclen_l(_String, _Locale) wcslen(_String)
#define _tcscnlen_l(_String, _Max_count, _Locale) wcsnlen((_String), (_Max_count))
#define _tcsnccat       wcsncat
#define _tcsnccat_s     wcsncat_s
#define _tcsnccat_l     _wcsncat_l
#define _tcsnccat_s_l   _wcsncat_s_l
#define _tcsnccpy       wcsncpy
#define _tcsnccpy_s     wcsncpy_s
#define _tcsnccpy_l     _wcsncpy_l
#define _tcsnccpy_s_l   _wcsncpy_s_l
#define _tcsncset       _wcsnset
#define _tcsncset_s     _wcsnset_s
#define _tcsncset_l     _wcsnset_l
#define _tcsncset_s_l   _wcsnset_s_l

#define _tcsdec     _wcsdec
#define _tcsinc     _wcsinc
#define _tcsnbcnt   _wcsncnt
#define _tcsnccnt   _wcsncnt
#define _tcsnextc   _wcsnextc
#define _tcsninc    _wcsninc
#define _tcsspnp    _wcsspnp

#define _tcslwr     _wcslwr
#define _tcslwr_l   _wcslwr_l
#define _tcslwr_s   _wcslwr_s
#define _tcslwr_s_l _wcslwr_s_l
#define _tcsupr     _wcsupr
#define _tcsupr_l   _wcsupr_l
#define _tcsupr_s   _wcsupr_s
#define _tcsupr_s_l _wcsupr_s_l
#define _tcsxfrm    wcsxfrm
#define _tcsxfrm_l  _wcsxfrm_l
#endif
