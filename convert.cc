//文件转化工具utf和GBK的相互转化
#include <iconv.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>


int code_convert(char* from_charset, char* to_charset, char* inbuf,size_t inlen,
    char* outbuf, size_t outlen)
{
    iconv_t cd;
    int rc;
    char **pin = &inbuf;
    char **pout = &outbuf;
    
    std::cout<<"Start to open charset"<<std::endl;
    cd = iconv_open(to_charset, from_charset);
    if( cd == 0)
    {
        std::cout<<"Error no such encoding!"<<std::endl;        
        return -1;
    }
    memset(outbuf,0,outlen);     
    if(iconv(cd, pin, &inlen, pout, &outlen) == -1)
    {
        std::cout<<"Convert failed"<<std::endl;
        return -2;
    }
    iconv_close(cd);
    return 0;
}

int main(int argc, char* argv[])
{
    char outFileName[255];
    sprintf(outFileName, "%s.utf", argv[1]);
    FILE* fp = fopen(argv[1], "r");
    fseek(fp, 0, SEEK_END);
    size_t flen = ftell(fp);
    char buffer[flen + 1];
    fseek(fp, 0, SEEK_SET);
    memset(buffer, 0, flen + 1);
    fread(buffer, flen, 1, fp);
    std::cout<<"File Content :"<<buffer<<std::endl;
    char outBuffer[flen * 2 + 1];
    memset(outBuffer, 0, flen * 2 + 1);
    code_convert("gb2312", "utf-8", buffer, flen + 1, outBuffer, flen * 2 + 1);
    long outLen = strlen(outBuffer);
    FILE* outFp = fopen(outFileName, "w");
    fwrite(outBuffer, outLen, 1, outFp);
    fclose(outFp);
    fclose(fp);
    return 0;
}