#include "pch.h"
#include "CMinizipUtil.h"
#ifdef _WIN32
#  include <minizip/iowin32.h>
#endif

#define BUF_SIZE 8192
#define MAX_NAMELEN 256


zipFile CMinizipUtil::CreateZipFile(const char* pszPath)
{
   return  zipOpen64(pszPath, 0);
}

zipFile CMinizipUtil::UnzipFile(const char* pszPath)
{
    return unzOpen64(pszPath);
}

void CMinizipUtil::CloseZip(zipFile zFile)
{
    zipClose(zFile, NULL);
}


bool CMinizipUtil::zipper_add_file(zipFile zfile, const char* filename)
{
    FILE* f;
    unsigned char  buf[BUF_SIZE];
    int            ret;
    size_t         red;
    size_t         flen;

    if (zfile == NULL || filename == NULL)
        return false;

    f = fopen(filename, "r");
    if (f == NULL)
        return false;

    fseek(f, 0, SEEK_END);
    flen = ftell(f);
    rewind(f);

    ret = zipOpenNewFileInZip64(zfile, filename, NULL, NULL, 0, NULL, 0, NULL,
        Z_DEFLATED, Z_DEFAULT_COMPRESSION, (flen > 0xffffffff) ? 1 : 0);
    if (ret != ZIP_OK) {
        fclose(f);
        return false;
    }

    while ((red = fread(buf, sizeof(*buf), sizeof(buf), f)) > 0) {
        ret = zipWriteInFileInZip(zfile, buf, red);
        if (ret != ZIP_OK) {
            fclose(f);
            zipCloseFileInZip(zfile);
            return false;
        }
    }

    zipCloseFileInZip(zfile);
    return true;
}

bool CMinizipUtil::zipper_add_buf(zipFile zfile, const char* zfilename, const unsigned char* buf, size_t buflen)
{
    int ret;

    if (zfile == NULL || buf == NULL || buflen == 0)
        return false;
    

    ret = zipOpenNewFileInZip64(zfile, zfilename, NULL, NULL, 0, NULL, 0, NULL,
        Z_DEFLATED, Z_DEFAULT_COMPRESSION, (buflen > 0xffffffff) ? 1 : 0);
    if (ret != ZIP_OK)
        return false;

    ret = zipWriteInFileInZip(zfile, buf, buflen);
    zipCloseFileInZip(zfile);
    return ret == ZIP_OK ? true : false;
}


bool CMinizipUtil::zipper_add_dir(zipFile zfile, const char* dirname)
{
    char* temp;
    size_t  len;
    int     ret;

    if (zfile == NULL || dirname == NULL || *dirname == '\0')
        return false;

    len = strlen(dirname);
    temp =(char *) calloc(1, len + 2);
    memcpy(temp, dirname, len + 2);
    if (temp[len - 1] != '/') {
        temp[len] = '/';
        temp[len + 1] = '\0';
    }
    else {
        temp[len] = '\0';
    }

    ret = zipOpenNewFileInZip64(zfile, temp, NULL, NULL, 0, NULL, 0, NULL, 0, 0, 0);
    if (ret != ZIP_OK)
        return false;
    free(temp);
    zipCloseFileInZip(zfile);
    return ret == ZIP_OK ? true : false;
}



CMinizipUtil::zipper_result_t CMinizipUtil::zipper_read(unzFile zfile, std::string& binUnzipData)
{
    unsigned char tbuf[BUF_SIZE];
    int           red;
    int           ret;

    if (zfile == NULL)
        return ZIPPER_RESULT_ERROR;

    ret = unzOpenCurrentFile(zfile);
    if (ret != UNZ_OK)
        return ZIPPER_RESULT_ERROR;

    while ((red = unzReadCurrentFile(zfile, tbuf, sizeof(tbuf))) > 0) {
        binUnzipData.append((char *)tbuf, red);
    }

    if (red < 0) {
        unzCloseCurrentFile(zfile);
        return ZIPPER_RESULT_ERROR;
    }

    unzCloseCurrentFile(zfile);
    if (unzGoToNextFile(zfile) != UNZ_OK)
        return ZIPPER_RESULT_SUCCESS_EOF;
    return ZIPPER_RESULT_SUCCESS;
}


std::string CMinizipUtil::zipper_filename(unzFile zfile, bool* isutf8)
{
    char            name[MAX_NAMELEN];
    unz_file_info64 finfo = {0};
    int             ret;
    std::string strRst;

    if (zfile == NULL)
        return std::move(strRst);

    ret = unzGetCurrentFileInfo64(zfile, &finfo, name, sizeof(name), NULL, 0, NULL, 0);
    if (ret != UNZ_OK)
        return strRst;
    if (isutf8 != NULL)
        *isutf8 = (finfo.flag & (1 << 11)) ? true : false;
    strRst = name;
    return std::move(strRst);
}



bool CMinizipUtil::zipper_isdir(unzFile zfile)
{
    char            name[MAX_NAMELEN];
    unz_file_info64 finfo;
    size_t          len;
    int             ret;

    if (zfile == NULL)
        return false;

    ret = unzGetCurrentFileInfo64(zfile, &finfo, name, sizeof(name), NULL, 0, NULL, 0);
    if (ret != UNZ_OK)
        return false;

    len = strlen(name);
    if (finfo.uncompressed_size == 0 && len > 0 && name[len - 1] == '/')
        return true;
    return false;
}


bool CMinizipUtil::zipper_skip_file(unzFile zfile)
{
    if (unzGoToNextFile(zfile) != UNZ_OK)
        return false;
    return true;
}

uint64_t CMinizipUtil::zipper_filesize(unzFile zfile)
{
    unz_file_info64 finfo;
    int             ret;

    if (zfile == NULL)
        return 0;

    ret = unzGetCurrentFileInfo64(zfile, &finfo, NULL, 0, NULL, 0, NULL, 0);
    if (ret != UNZ_OK)
        return 0;
    return finfo.uncompressed_size;
}