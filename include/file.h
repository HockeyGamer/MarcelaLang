#ifndef FILE_H
#define FILE_H

#ifdef _WIN32
    typedef long long FileOffset;
    #define fileSeek _fseeki64
    #define fileTell _ftelli64
#else
    #include <sys/types.h>
    typedef off_t FileOffset;
    #define fileSeek fseeko
    #define fileTell ftello
#endif

#endif