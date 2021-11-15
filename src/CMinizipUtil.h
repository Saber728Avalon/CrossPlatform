#pragma once
#include <iostream>
#include <zlib.h>
#include <minizip/zip.h>
#include <minizip/unzip.h>


/*
*   zip example
* 
*       CMinizipUtil mini;
*        zipFile file = mini.CreateZipFile("d:\\1234x.zip");
*        mini.zipper_add_dir(file, "asd");
*        mini.zipper_add_buf(file, "asd/x2", (unsigned char*)"1235", 4);
*        mini.zipper_add_dir(file, "gasd");
*        mini.zipper_add_buf(file, "gasd/x3", (unsigned char*)"1236", 4);
*       mini.CloseZip(file);
* 
* 
*   unzip example
* 
*       CMinizipUtil miniun;
*       zipFile fileUnzip =  miniun.UnzipFile("d:\\1234x.zip");
*       std::string str = miniun.zipper_filename(fileUnzip, NULL);
*       bool bRst = miniun.zipper_isdir(fileUnzip);
*       int nSize = miniun.zipper_filesize(fileUnzip);
*       std::string binDta;
*       miniun.zipper_read(fileUnzip, binDta);
* 
*/


class CMinizipUtil
{
public:

    typedef enum {
        ZIPPER_RESULT_ERROR = 0,
        ZIPPER_RESULT_SUCCESS,
        ZIPPER_RESULT_SUCCESS_EOF
    } zipper_result_t;
    
    void CloseZip(zipFile zFile);

    /******************zip file********************************/
    zipFile CreateZipFile(const char *pszPath);
    typedef void (*zipper_read_cb_t)(const unsigned char* buf, size_t size, void* thunk);

    bool zipper_add_file(zipFile zfile, const char* filename);
    bool zipper_add_buf(zipFile zfile, const char* zfilename, const unsigned char* buf, size_t buflen);
    bool zipper_add_dir(zipFile zfile, const char* dirname);



    /******************unzip file********************************/
    zipFile UnzipFile(const char* pszPath);

    zipper_result_t zipper_read(unzFile zfile, std::string &binUnzipData);
    bool zipper_skip_file(unzFile zfile);
    std::string zipper_filename(unzFile zfile, bool* isutf8);
    bool zipper_isdir(unzFile zfile);
    uint64_t zipper_filesize(unzFile zfile);
};



